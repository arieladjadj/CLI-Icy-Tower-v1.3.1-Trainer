#include <iostream>
#include <string>
#include <windows.h>
#include <tlhelp32.h>
#include "Trainer.hpp"

DWORD FindProcessId(const std::wstring& processName);
uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName);
void RegisterHotKeys();

int main()
{
	Trainer trainer;
	trainer.train();

	//std::wstring processName = L"icytower13.exe";
	//HANDLE hProcess = 0;

	//DWORD processID = FindProcessId(processName);

	//if (processID == 0) {
	//	std::wcout << "Could not find " << processName.c_str() << std::endl;
	//	std::cout << "Starting icy tower \n";
	//	STARTUPINFO info = { sizeof(info) };
	//	PROCESS_INFORMATION processInfo;
	//	if (!CreateProcess(L"C:\\games\\icytower1.3\\icytower13.exe", nullptr, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo)) {
	//		std::cerr << "Cannot start icy tower \nExit \n";
	//		exit(1);
	//	}
	//	processID = FindProcessId(processName);

	//	hProcess = processInfo.hProcess;
	//	//CloseHandle(processInfo.hThread);
	//}
	//else {
	//	std::wcout << "Process ID is " << processID << std::endl;

	//	//Get Handle to Process
	//	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, processID);
	//}

	////Getmodulebaseaddress
	//uintptr_t moduleBase = GetModuleBaseAddress(processID, L"icytower13.exe");
	//moduleBase += 0xCB908;
	//uintptr_t addr1;
	//ReadProcessMemory(hProcess, (BYTE*)moduleBase, &addr1, 4, nullptr);
	////moduleBase ;
	//uintptr_t addr2 = addr1 * 4 + 0x004CB920;//moduleBase + 0x4CB920; //ecx*4+004CB920
	//ReadProcessMemory(hProcess, (BYTE*)addr2, &addr2, 4, nullptr);

	//uintptr_t floorAddr = addr2 + 0x28;
	//uintptr_t comboAddr = addr2 + 0x44;	
	//uintptr_t buffer = addr2 + 0x40;
	//uintptr_t mul = addr2 + 0x48;
	//uintptr_t scoreAddr = addr2 + 0x2c;

	////change score
	//int newScore = 0;
	//WriteProcessMemory(hProcess, (BYTE*)scoreAddr, &newScore, sizeof(newScore), nullptr);


	//MSG msg = { 0 };

	/*RegisterHotKeys();
	while (GetMessage(&msg, NULL, 0, 0) != 0)
	{
		PeekMessage(&msg, 0, 0, 0, 0x0001);
		switch (msg.message)
		{
		case WM_HOTKEY:
			if (msg.wParam == 0)
			{
				printf("F1 Pressed");
			}
			else if (msg.wParam ==1)
			{
				printf("F2 Pressed");
			}
		}

	}*/


	



	//combo 
	////Write to it
	//int newCombo = 2;
	//WriteProcessMemory(hProcess, (BYTE*)mul, &newCombo, sizeof(newCombo), nullptr);

	//newCombo = 1337;
	//WriteProcessMemory(hProcess, (BYTE*)comboAddr, &newCombo, sizeof(newCombo), nullptr);

	// newCombo = 1;
	//WriteProcessMemory(hProcess, (BYTE*)buffer, &newCombo, sizeof(newCombo), nullptr);



	//CloseHandle(hProcess);
	system("PAUSE");
	return 0;
}

DWORD FindProcessId(const std::wstring& processName)
{
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processesSnapshot == INVALID_HANDLE_VALUE)
		return 0;

	Process32First(processesSnapshot, &processInfo);
	if (!processName.compare(processInfo.szExeFile))
	{
		CloseHandle(processesSnapshot);
		return processInfo.th32ProcessID;
	}

	while (Process32Next(processesSnapshot, &processInfo))
	{
		if (!processName.compare(processInfo.szExeFile))
		{
			CloseHandle(processesSnapshot);
			return processInfo.th32ProcessID;
		}
	}

	CloseHandle(processesSnapshot);
	return 0;
}


void RegisterHotKeys()
{
	for (int i = 0; i <= 4; i++)
	{
		if (!RegisterHotKey(NULL, i, NULL, VK_F1 + i))
		{
			std::cerr << ("Could not register F%d hotkey\n");
		}
	}
}