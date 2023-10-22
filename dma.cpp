#pragma once
#include <cstdint>
#include <iostream>
#include "vmmdll.h"
#include "dma.h"

VMM_HANDLE DMA::hVMM = nullptr;
bool DMA::Connected = false;
uint32_t DMA::AttachedProcessId = 0;
uint64_t DMA::BaseAddress = 0;
uint64_t DMA::PebAddress = 0;

bool DMA::Connect()
{
	if (DMA::Connected)
		return true;

	bool bReturnStatus = true;

	unsigned int iArgumentCount = 3;

	char args[3][50] = { "", "-device", "fpga" };

	LPSTR argv[3];
	for (int i = 0; i < 3; i++) {
		argv[i] = args[i];
	}

	DMA::hVMM = VMMDLL_Initialize(iArgumentCount, argv);

	if (!DMA::hVMM)
	{
		MessageBoxA(nullptr, "Could not initialize the DMA device!", nullptr, 0);
		return false;
	}

	DMA::Connected = bReturnStatus;

	std::cout << "DMA: Connected" << std::endl;
	return bReturnStatus;
}

bool DMA::AttachToProcessId(LPSTR ProcessName)
{
	if (!DMA::Connected)
		return false;

	if (VMMDLL_PidGetFromName(DMA::hVMM, ProcessName, reinterpret_cast<PDWORD>(&DMA::AttachedProcessId)) == FALSE)
		return false;
	std::cout << "PID: " << DMA::AttachedProcessId << std::endl;

	DMA::BaseAddress = VMMDLL_ProcessGetModuleBase(DMA::hVMM, DMA::AttachedProcessId, const_cast<LPWSTR>(REMOTE_PROCESS_LONG));
	std::cout << "Base: 0x" << std::hex << DMA::BaseAddress << std::dec << std::endl;

	return (AttachedProcessId != 0 && BaseAddress != 0);
}

void DMA::Disconnect()
{
	DMA::Connected = false;

	DMA::AttachedProcessId = 0;
	DMA::BaseAddress = 0;

	VMMDLL_CloseAll();
}

bool DMA::GetPEBAddress(uint32_t ProcessId)
{
	VMMDLL_PROCESS_INFORMATION procInfo = { 0 };
	SIZE_T cbProcInfo = sizeof(VMMDLL_PROCESS_INFORMATION);

	procInfo.magic = VMMDLL_PROCESS_INFORMATION_MAGIC;
	procInfo.wVersion = VMMDLL_PROCESS_INFORMATION_VERSION;
	procInfo.wSize = (WORD)cbProcInfo;

	if (!VMMDLL_ProcessGetInformation(DMA::hVMM, ProcessId, &procInfo, &cbProcInfo)) {
		std::cerr << "Failed to get process information for PID: " << ProcessId << std::endl;
		return false;
	}

	DMA::PebAddress = procInfo.win.vaPEB;
	std::cout << "PEB: 0x" << std::hex << DMA::PebAddress << std::dec << std::endl;
	return true;
}

