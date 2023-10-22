#pragma once
#include "vmmdll.h"
#include "leechcore.h"
#pragma comment(lib,"leechcore.lib")
#pragma comment(lib,"vmm.lib")

#define REMOTE_PROCESS_SHORT "cod.exe"
#define REMOTE_PROCESS_LONG L"cod.exe"

namespace DMA
{
	extern VMM_HANDLE hVMM;
	extern bool Connected;
	extern uint32_t AttachedProcessId;
	extern uint64_t BaseAddress;
	extern uint64_t PebAddress;

	extern bool Connect();
	extern void Disconnect();
	extern bool AttachToProcessId(LPSTR szProcessName = const_cast<LPSTR>(REMOTE_PROCESS_SHORT));
	extern bool GetPEBAddress(uint32_t dwProcessId);

	template<typename Var, typename U>
	Var Read(U address, size_t uiSize, bool bFullReadRequired = true)
	{
		Var output{};
		if (!AttachedProcessId || !Connected || !address) {
			return output;
		}

		uint32_t bytesRead = 0;
		uint32_t flags = VMMDLL_FLAG_NOCACHE | VMMDLL_FLAG_NOPAGING | VMMDLL_FLAG_ZEROPAD_ON_FAIL | VMMDLL_FLAG_NOPAGING_IO;

		BOOL bRetn = (VMMDLL_MemReadEx(DMA::hVMM, AttachedProcessId, (uint64_t)address, (uint8_t*)&output, uiSize,
			reinterpret_cast<PDWORD>(&bytesRead), flags) && bytesRead != 0);

		if (!bRetn || (bFullReadRequired && bytesRead != uiSize)) {
			return output;
		}

		return output;
	}

	template<typename U>
	uintptr_t ReadPtr(U address)
	{
		return Read<uintptr_t>(address, sizeof(uintptr_t), true);
	}
}