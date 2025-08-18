#include <fstream>
#pragma once

extern bool check_file(const wchar_t* path);

bool install_package(const wchar_t* name,const wchar_t* url, const wchar_t* program_dir, const wchar_t* zip_name, const wchar_t* exe_path, const wchar_t* bat_path) {

	if (check_file(program_dir)) {
		std::wcout << L"The package " << name << L" is already installed\n";
		return false;
	}
	else {
		std::filesystem::create_directories(program_dir);
		std::wcout << L"Starting package file download\n";
		std::wstring download_zip = (std::wstring)program_dir + L"\\" + zip_name;
		std::wstring unzip_zip = (std::wstring)program_dir + L"\\";
		HRESULT download = URLDownloadToFileW(NULL, url, download_zip.c_str(), 0,NULL);
		if (download == S_OK) {
			std::wcout << L"Downloaded package file successfully\n";
		}
		else {
			std::wcout << L"Failed to download package file, try updating nexus and attempt again.\n";
		}
		unzip(unzip_zip,zip_name);
		std::wcout << L"Adding package to PATH\n";
		std::wofstream batch(bat_path);
		batch << L"@echo off\n";
		batch << L"start \"\" " << L"\"" << (std::wstring)exe_path << L"\"";
		batch.close();
		std::wcout << L"Package added to PATH\n";
		return true;
	}
}