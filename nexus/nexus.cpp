#include <iostream>
#include <windows.h>
#include <filesystem>
#include <vector>
#include <urlmon.h>
#include <winternl.h>
#include <cstdlib>
#include "print_help.h"
#include "check_nexus_path.h"
#include "add_to_path.h"
#pragma comment(lib, "ntdll.lib")
#pragma comment(lib,"urlmon.lib")

bool check_file(const wchar_t* path) {
	return std::filesystem::exists(path);
}

struct pkg {
	wchar_t* name;
	wchar_t* url_download;
	wchar_t* program_dir;
	wchar_t* exe_path;
};

std::vector<pkg> pkgs = {

};

int wmain(int argc, wchar_t* argv[]) {
	
	if (check_file(L"C:\\Nexus\\bin") && check_file(L"C:\\Nexus\\pkgs"))
	{

	}
	else {
		std::filesystem::create_directories(L"C:\\Nexus\\bin");
		std::filesystem::create_directories(L"C:\\Nexus\\pkgs");
	}

	if (_wcsicmp(check_nexus_path(),L"C:\\Nexus\\bin\\nexus.exe") == 0)
	{

	}
	else
	{
		std::wcout << L"\nNexus added to path, use from any dir now without going back here!\n";
		CopyFileW(check_nexus_path(), L"C:\\Nexus\\bin\\nexus.exe", FALSE);
		return 0;
	}
	add_to_path(L"C:\\Nexus\\bin");

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