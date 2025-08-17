#include <iostream>
#include <windows.h>
#include <filesystem>
#include <vector>
#include <urlmon.h>
#include <winternl.h>
#include <cstdlib>
#include "print_help.h"
#include "check_nexus_path.h"
#include "install.h"
#include "add_to_path.h"
#pragma comment(lib, "ntdll.lib")
#pragma comment(lib,"urlmon.lib")

bool check_file(const wchar_t* path) {
	return std::filesystem::exists(path);
}

struct pkg {
	const wchar_t* name;
	const wchar_t* url_download;
	const wchar_t* program_dir;
	const wchar_t* zip_name;
	const wchar_t* exe_path;
};

std::vector<pkg> pkgs = {
	{L"firefox",L"https://github.com/dpadGuy/UwUToolsSoftware/releases/download/Files/MozillaFirefox.zip",L"C:\\Nexus\\pkgs\\firefox",L"firefox.zip",L"C:\\Nexus\\pkgs\\firefox\\MozillaFirefox\\Mozilla Firefox\\firefox.exe"},
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
			bool is_found = false;
			for (int i = 0; i < pkgs.size(); i++) {
				if (_wcsicmp(pkgs[i].name,argv[2]) == 0) {
					is_found = true;
					break;
				}
				else {
					is_found = false;
				}
			}
			if (is_found) {

			}
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