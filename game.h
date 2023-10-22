#pragma once
#include <cstdint>
#include <iostream>
#include "dma.h"
#include "utilities.h"
#include "game_math.h"

inline auto is_user_in_game() -> bool
{
    int ingame = DMA::Read<int64_t>(DMA::BaseAddress + offsets::game_mode, sizeof(ingame));

    return ingame > 0;
}

inline auto player_count() -> int
{
    int playercount = DMA::Read<int>(DMA::BaseAddress + offsets::game_mode, sizeof(playercount));

    return playercount;
}

inline auto local_player_index(QWORD client_info) -> int
{
    auto index = DMA::ReadPtr(client_info + offsets::local_index);
    std::cout << "Index Ptr: 0x" << std::hex << index << std::dec << std::endl;
    int read_return = DMA::Read<int>(index + offsets::local_index_pos, sizeof(read_return));
    return read_return;
}

inline auto is_player_valid(QWORD player_address) -> bool
{
    bool response = DMA::Read<bool>(player_address + offsets::player::valid, sizeof(response));
    return response;
}

inline auto team_id(QWORD player_address) -> int
{
    int team = DMA::Read<int>(player_address + offsets::player::team, sizeof(team));
    return team;
}

inline auto get_position(QWORD player_address) -> fvector
{
    auto local_position = DMA::ReadPtr(player_address + offsets::player::pos);
    fvector final_pos = DMA::Read<fvector>(local_position + 0x48, sizeof(final_pos));
    return final_pos;
}

auto retrieve_camera_posistion() -> fvector
{
    auto player_camera = DMA::ReadPtr(DMA::BaseAddress + offsets::camera_base);
    if (!player_camera)
        return {};

    fvector received = DMA::Read<fvector>(player_camera + offsets::camera_pos, sizeof(received));
    return received;
}
auto get_angles() -> fvector2d
{
    auto camera_angle = DMA::ReadPtr(DMA::BaseAddress + offsets::camera_base);
    if (!camera_angle)
        return {};

    fvector2d received = DMA::Read<fvector2d>(camera_angle + offsets::camera_pos + 0xC, sizeof(received));
    return received;
}

auto retrieve_bone_position(const uintptr_t pointer, const int Bone) -> fvector
{
    std::cout << "Address to Bone: 0x" << std::hex << pointer + ((uint64_t)Bone * 0x20) + 0x10 << std::dec << std::endl;
    fvector position = DMA::Read<fvector>(pointer + ((uint64_t)Bone * 0x20) + 0x10, sizeof(position));
    return position;
}

auto retrieve_bone_position_vec(const uintptr_t Client_Information) -> fvector
{
    fvector information = DMA::Read<fvector>(Client_Information + offsets::bone::bone_base, sizeof(information));
    return information;
}

auto bone_pointer(uint64_t base, uint64_t index) -> uint64_t
{
    std::cout << "Address to BonePtr: 0x" << std::hex << base + (index * offsets::bone::size) + offsets::bone::offset << std::dec << std::endl;
    auto bone = DMA::ReadPtr(base + (index * offsets::bone::size) + offsets::bone::offset);
    return bone;
}

auto world_to_screen(fvector world_location, fvector2d& out, fvector camera_pos, int screen_width, int screen_height, fvector2d fov, fvector matricies[3]) -> bool
{
    // Local Calculation
    auto local = world_location - camera_pos;

    // Transformation Calculation
    auto trans = fvector{
        local.Dot(matricies[1]),
        local.Dot(matricies[2]),
        local.Dot(matricies[0])
    };

    // Check trans.z
    if (trans.z < 0.01f) {
        return false;
    }

    // Screen Coordinates Calculation
    out.x = ((float)screen_width / 2.0) * (1.0 - (trans.x / fov.x / trans.z));
    out.y = ((float)screen_height / 2.0) * (1.0 - (trans.y / fov.y / trans.z));

    // Bounds Check
    if (out.x < 1 || out.y < 1 || (out.x > decrypt_refdef->ref_def_nn.width) || (out.y > decrypt_refdef->ref_def_nn.height)) {
        return false;
    }

    return true;
}

auto w2s(fvector world_position, fvector2d& screen_position) -> bool
{
    return world_to_screen(world_position, screen_position, retrieve_camera_posistion(), decrypt_refdef->ref_def_nn.width, decrypt_refdef->ref_def_nn.height, decrypt_refdef->ref_def_nn.tan_half_fov, decrypt_refdef->ref_def_nn.axis);
}

auto units_to_m(float units) -> float {
    return units * 0.0254;
}