#include <iostream>
#include <windows.h>
#include <filesystem>
#include <vector>
#include <urlmon.h>
#include "print_help.h"
#pragma comment(lib,"urlmon.lib")

struct pkg {
	wchar_t name;
	wchar_t url_download;
	wchar_t program_dir;
	wchar_t exe_path;
};

std::vector<pkg> pkgs = {

};

int wmain(int argc, wchar_t* argv[]) {
	if (argc < 2) {
		print_help();
	}
	else if (argc == 2) {
		if (wcscmp(argv[1], L"update") == 0) {
			// implement update here
		}
		else {
			std::wcout << L"[" << argv[1] << L"]" << L" is not recognized as a valid command";
		}
	}
	else if (argc == 3) {
		if (wcscmp(argv[1], L"install") == 0) 
		{
			std::wcout << L"you installed";
		}
		else if (wcscmp(argv[1], L"uninstall") == 0)
		{
			std::wcout << L"you uninstalled";
		}
		else {
			std::wcout << L"[" << argv[1] << L"]" << L" is not recognized as a valid command";
		}
	}
}