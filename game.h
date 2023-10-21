#include <cstdint>
#include <iostream>
#include "dma.h"
#include "utilities.h"

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
