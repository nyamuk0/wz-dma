#pragma once
#include <iostream>
#include <string>
#include "dma.h"
#include "game.h"

int main() {
    if (!DMA::Connect()) {
        std::cout << "Failed to Connect" << std::endl;
        return 0;
    }
    if (!DMA::AttachToProcessId()) {
        std::cout << "Failed to Attach" << std::endl;
        return 0;
    }
    if (DMA::GetPEBAddress(DMA::AttachedProcessId) == false) {
        std::cout << "Failed to get PEB" << std::endl;
        return 0;
    }

    while (true) {
        if (is_user_in_game()) {
            int count = player_count();
            //std::cout << "Player Count: " << count << std::endl;

            uint64_t clientInfo = decrypt_client_info();
            if (clientInfo) {
                //std::cout << "Client Info: 0x" << std::hex << clientInfo << std::dec << std::endl;
                uint64_t clientBase = decrypt_client_base(clientInfo);
                //std::cout << "Client Base: 0x" << std::hex << clientBase << std::dec << std::endl;

                // Local Player
                int index = local_player_index(clientInfo);
                //std::cout << "Index: " << index << std::endl;
                uint64_t localPlayer = clientBase + (index * offsets::player::size);
                //std::cout << "Local Player: 0x" << std::hex << localPlayer << std::dec << std::endl;
                bool valid = is_player_valid(localPlayer);
                //std::cout << "Valid: " << std::boolalpha << valid << std::dec << std::endl;
                int teamId = team_id(localPlayer);
                //std::cout << "Team ID: " << teamId << std::endl;
                fvector pos = get_position(localPlayer);
                //std::cout << "Position: (" << pos.x << ", " << pos.y << ", " << pos.z << ")" << std::endl;

                // Ref Def
                uint64_t refDefPtr = decrypt_refdef->retrieve_ref_def();
                //std::cout << "RefDef Address: 0x" << std::hex << refDefPtr << std::dec << std::endl;
                decrypt_refdef->ref_def_nn = DMA::Read<ref_def_t>(refDefPtr, sizeof(decrypt_refdef->ref_def_nn));
                ref_def_t& ref_def = decrypt_refdef->ref_def_nn;  // A reference for ease of use
                //std::cout << "x: " << ref_def.x << '\n';
                //std::cout << "y: " << ref_def.y << '\n';
                //std::cout << "width: " << ref_def.width << '\n';
                //std::cout << "height: " << ref_def.height << '\n';

                // Bone Base
                uint64_t boneBase = decrypt_bone_base();
                //std::cout << "Bone Base: 0x" << std::hex << boneBase << std::dec << std::endl;
                //fvector bonePos = retrieve_bone_position_vec(clientInfo);
                //std::cout << "Bone Pos: (" << bonePos.x << ", " << bonePos.y << ", " << bonePos.z << ")" << std::endl;

                for (int i = 0; i < count; i++)
                {
                    if (i == index) {
						continue;
					}

                    uint64_t player = clientBase + (i * offsets::player::size);
                    bool player_valid = is_player_valid(player);
                    if (!player_valid)
                    {
                        continue;
                    }
                        
                    fvector player_pos = get_position(player);
                    if (player_pos.x == 0.0 && player_pos.y == 0.0 && player_pos.z == 0.0) {
                        continue;
                    }

                    fvector2d player_screen = { 0, 0 };
                    if (w2s(player_pos, player_screen)) {
                        auto player_distance = units_to_m(pos.distance_to(player_pos));
                        auto player_bone_index = get_bone_index(i);
                        std::cout << "Bone Index: " << player_bone_index << std::endl;
                        auto player_bone_ptr = bone_pointer(boneBase, player_bone_index);
                        std::cout << "Bone Ptr: 0x" << std::hex << player_bone_ptr << std::dec << std::endl;

                        auto player_bone_pos = retrieve_bone_position(player_bone_ptr, 7);
                        std::cout << "Player" << i << " Bone Pos:" << " (" << player_bone_pos.x << ", " << player_bone_pos.y << ", " << player_bone_pos.z << ")" << std::endl;
                        std::cout << "Player" << i << " Pos:" << " (" << player_pos.x << ", " << player_pos.y << ", " << player_pos.z << ")" << std::endl;

                        // Getting wrong bone position, trying to figure out why
                        break;
                    }
                }
            }
        }

        Sleep(1000);
    }

    return 0;
}
