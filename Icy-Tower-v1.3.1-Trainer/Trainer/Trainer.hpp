#pragma once
#include <windows.h>
#include <tlhelp32.h>
#include <string>

class Trainer
{
public:
	Trainer();
	void start();

private:
	HANDLE _hGame;

	void setGameHandle();
	void printMenu();


};

