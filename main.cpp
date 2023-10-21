#include <iostream>
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
            std::cout << "Player Count: " << player_count() << std::endl;

            uint64_t clientInfo = decrypt_client_info();
            if (clientInfo) {
                std::cout << "Client Info: 0x" << std::hex << clientInfo << std::dec << std::endl;
                uint64_t clientInfo_base = decrypt_client_base(clientInfo);
                std::cout << "Client Base: 0x" << std::hex << clientInfo_base << std::dec << std::endl;

                int index = local_player_index(clientInfo);
                std::cout << "Index: " << index << std::endl;

                uint64_t localPlayer = DMA::ReadPtr(clientInfo_base + (index * offsets::player::size));
                std::cout << "Local Player: 0x" << std::hex << localPlayer << std::dec << std::endl;
            }
        }

        Sleep(1000);
    }

    return 0;
}
