#include <iostream>
#include <windows.h>
#include <filesystem>
#include <vector>
#include <string>
#include <urlmon.h>
#include <winternl.h>
#include <cstdlib>
#include "print_help.h"
#include "check_nexus_path.h"
#include "install.h"
#include "unzip.h"
#include "add_to_path.h"
#include "install_package.h"
#include "uninstall_package.h"
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
	const wchar_t* bat_path;
};

std::vector<pkg> pkgs = {
	{L"firefox",L"https://github.com/dpadGuy/UwUToolsSoftware/releases/download/Files/MozillaFirefox.zip",L"C:\\Nexus\\pkgs\\firefox",L"firefox.zip",L"C:\\Nexus\\pkgs\\firefox\\Mozilla Firefox\\firefox.exe", L"C:\\Nexus\\bin\\firefox.bat"},
	{L"sysinformer", L"https://github.com/dpadGuy/UwUToolsSoftware/releases/download/Files/SystemInformer.zip",L"C:\\Nexus\\pkgs\\sysinformer",L"sysinformer.zip",L"C:\\Nexus\\pkgs\\sysinformer\\amd64\\systeminformer.exe", L"C:\\Nexus\\bin\\sysinformer.bat"},
	{L"primeshell",L"https://github.com/emperoralex2/nexus/releases/download/%23program/PrimeShell.zip",L"C:\\Nexus\\pkgs\\primeshell",L"primeshell.zip",L"C:\\Nexus\\pkgs\\primeshell\\PrimeShell\\PrimeShell.exe",L"C:\\Nexus\\bin\\primeshell.bat"},
	{L"explorer++",L"https://github.com/emperoralex2/nexus/releases/download/%23program/explorerpp.zip",L"C:\\Nexus\\pkgs\\explorerpp",L"explorerpp.zip",L"C:\\Nexus\\pkgs\\explorerpp\\explorerpp\\Explorer++.exe",L"C:\\Nexus\\bin\\explorer++.bat"},
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
		if (!check_file(L"C:\\Nexus\\bin\\nexus_updater.exe")) {
			URLDownloadToFileW(NULL, L"https://github.com/emperoralex2/nexus/releases/download/%23program/nexus_updater.exe", L"C:\\Nexus\\bin\\nexus_updater.exe", 0, NULL);
		}
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
			if (check_file(L"C:\\Nexus\\bin\\nexus_updater.exe")) {
				std::wcout << L"\n";
				WinExec("C:\\Nexus\\bin\\nexus_updater.exe", SW_SHOW);
				return 0;
			}
			else {
				std::wcout << L"Updater exe not found, relaunch nexus and try again\n";
			}
		}
		else if (wcscmp(argv[1], L"list") == 0) {
			for (int i = 0; i < pkgs.size(); i++) {
				std::wcout << pkgs[i].name << std::endl;
			}
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
					if (install_package(pkgs[i].name, pkgs[i].url_download, pkgs[i].program_dir, pkgs[i].zip_name, pkgs[i].exe_path,pkgs[i].bat_path)) {
						std::wcout << L"Successfully installed package!";
					}
					else {
						std::wcout << L"Errored";
					}
					break;
				}
				else {
					is_found = false;
				}
			}
			if (!is_found) {
				std::wcout << L"Package not found";
			}
		}
		else if (wcscmp(argv[1], L"uninstall") == 0)
		{
			bool is_found = false;
			for (int i = 0; i < pkgs.size(); i++) {
				if (_wcsicmp(pkgs[i].name, argv[2]) == 0) 
				{
					is_found = true;
					if (uninstall_package(pkgs[i].name, pkgs[i].url_download, pkgs[i].program_dir, pkgs[i].zip_name, pkgs[i].exe_path, pkgs[i].bat_path)) {
						break;
					}
					else {
						is_found = false;
					}
				}
				else
				{
					is_found = false;
				}
			}
			if (!is_found) {
				std::wcout << L"Target package not found";
			}
		}
		else {
			std::wcout << L"[" << argv[1] << L"]" << L" is not recognized as a valid command";
		}
	}
}