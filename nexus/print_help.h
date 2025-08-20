#include <iostream>
#pragma once


void print_help() {
	std::wcout << L"\nWelcome to Nexus - Simple C++ Package Manager\n";
	std::wcout << L"----------------------------------------------\n\n";
	std::wcout << L"Available commands:\n\n";
	std::wcout << L"\tupdate\t\t\t\tUpdate the package manager\n";
	std::wcout << L"\tinstall <package>\t\tInstall a package by name\n";
	std::wcout << L"\tuninstall <package>\t\tUninstall a package by name\n";
	std::wcout << L"\tlist\t\t\t\tList packages available";

}
