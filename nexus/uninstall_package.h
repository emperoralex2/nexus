#pragma once


extern bool check_file(const wchar_t* path);

bool delete_dir(const wchar_t* dir) {
	return std::filesystem::remove_all(dir);
}

bool uninstall_package(const wchar_t* name, const wchar_t* url, const wchar_t* program_dir, const wchar_t* zip_name, const wchar_t* exe_path, const wchar_t* bat_path) {

	if (check_file(program_dir)) 
	{
		std::wcout << L"Deleting target package\n";
		if (delete_dir(program_dir)) {
			std::filesystem::remove(bat_path);
			std::wcout << L"Successfully deleted target package\n";
			return true;
		}
		
		if (check_file(program_dir)) {
			std::wcout << L"Program might be in use or another issue, please stop the program and try again\n";
			return false;
		}
	}
	else
	{
		return false;
	}
}