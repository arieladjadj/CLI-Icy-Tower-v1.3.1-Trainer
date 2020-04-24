#pragma once
#include <windows.h>
#include <tlhelp32.h>
#include <string>
#include <iostream>

class Trainer
{
public:
	~Trainer();
	void train();

private:
	HANDLE _hGameProcess, _hGameThread;
	uintptr_t _moduleBaseAddress;


	void setGameHandle(std::wstring gameName);
	DWORD FindProcessId(const std::wstring& processName);
	//void printMenu();
	void printAsciiArt();

};

