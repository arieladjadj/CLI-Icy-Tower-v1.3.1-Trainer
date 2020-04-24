#include "Trainer.hpp"

Trainer::~Trainer() {
	try {
		CloseHandle(this->_hGameProcess);
	}
	catch (...) {

	}
}

void Trainer::train() {
	printAsciiArt();
	setGameHandle(L"icytower13.exe");
}

void Trainer::setGameHandle(std::wstring gameName) {
	//std::wstring processName = L"icytower13.exe";
	HANDLE hProcess = 0;
	HANDLE hThread = 0;
	DWORD processID = FindProcessId(gameName);

	if (processID == 0) {
		std::wcout << "Could not find " << gameName.c_str() << std::endl;
		std::cout << "Starting icy tower \n";
		STARTUPINFO info = { sizeof(info) };
		PROCESS_INFORMATION processInfo;
		if (!CreateProcess(L"C:\\games\\icytower1.3\\icytower13.exe", nullptr, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo)) {
			std::cerr << "Cannot start icy tower \nExit \n";
			exit(1);
		}

		hProcess = processInfo.hProcess;
		hThread = processInfo.hThread;
	}
	else {
		std::wcout << "Process ID is " << processID << std::endl;

		//Get Handle to Process
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, processID);
	}
	_hGameProcess = hProcess;
}

void Trainer::printAsciiArt() {
	std::cout << " _____             _____                             __    _____   _____         _                 " << "\n";
	std::cout << "|_   _|           |_   _|                           /  |  |____ | |_   _|       (_)                " << "\n";
	std::cout << "  | |  ___ _   _    | | _____      _____ _ ____   __`| |      / /   | |_ __ __ _ _ _ __   ___ _ __ " << "\n";
	std::cout << "  | | / __| | | |   | |/ _ \\ \\ /\\ / / _ \\ '__\\ \\ / / | |      \\ \\   | | '__/ _` | | '_ \\ / _ \\ '__|" << "\n";
	std::cout << " _| || (__| |_| |   | | (_) \ V  V //  __// |  \\ V / _| |__.___/ /   | | | | (_| | | | | |  __/ |   " << "\n";
	std::cout << " \\___/\\___|\\__, |   \\_/\\___/ \\_/\\_/ \\___|_|    \\_/  \\___(_)____/    \\_/_|  \\__,_|_|_| |_|\\___|_|   " << "\n";
	std::cout << "            __/ |                                                                                  " << "\n";
	std::cout << "           |___/                                                                                  " << "\n";

	std::cout << "" << "\n";
	std::cout << "" << "\n";

}

DWORD Trainer::FindProcessId(const std::wstring& processName)
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

uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName)
{
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				if (!_wcsicmp(modEntry.szModule, modName))
				{
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBaseAddr;
}