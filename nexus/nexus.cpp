#include <iostream>
#include <windows.h>
#include <filesystem>
#include <vector>
#include <urlmon.h>
#pragma comment(lib,"urlmon.lib")

struct pkg {
	wchar_t name;
	wchar_t url_download;
	wchar_t program_dir;
	wchar_t exe_path;
};

std::vector<pkg> pkgs = {

};

int main(int argc, wchar_t* argv[]) {
	if (argc < 1) {

	}
}