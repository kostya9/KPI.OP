#include "NewGameMenuOption.h"
#include "Game.h"
#include <Windows.h>
NewGameMenuOption::NewGameMenuOption(Loader * loader, Font * font, glm::fvec3 color) : MenuOptionButton(loader, font, color, string("New Game"))
{
	this->scale = 1.2f;
	this->id = 100;
}

int NewGameMenuOption::onClick()
{
	// additional information
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	// set the size of the structures
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	wchar_t buff[100];
	GetCurrentDirectory(100, buff);
	wstring curD = wstring(buff) + wstring(TEXT("\\"));
	wstring exec = wstring(TEXT("levels\\consoleLevelGenerator.exe"));
	wstring path = (curD + exec);
	BOOL rc = CreateProcess(path.c_str() ,   // the path
		NULL,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi         // Pointer to PROCESS_INFORMATION structure
		);
	WaitForSingleObject(pi.hProcess, INFINITE);
	DWORD retD;
	BOOL ret = GetExitCodeProcess(pi.hProcess, &retD);
	// Close the handles.
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	menu->getGame()->cleanGameObjects();
	menu->getGame()->setState(GAME_ACTIVE);
	menu->getGame()->loadLevel(string("output.txt"));
	return RETURN;
}
