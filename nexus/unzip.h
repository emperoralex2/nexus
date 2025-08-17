#include <string>
#pragma once


void unzip(std::wstring path, std::wstring zip_name) {
	std::wstring command = (std::wstring)L"tar -xf " + path + zip_name + L" -C " + path;
	_wsystem(command.c_str());

}