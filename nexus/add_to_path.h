#include <string>
#pragma once


bool add_to_path(const wchar_t* dir) {
    HKEY hKey;
    RegOpenKeyExW(HKEY_CURRENT_USER, L"Environment", 0, KEY_READ | KEY_WRITE, &hKey);

    DWORD size = 0;
    RegQueryValueExW(hKey, L"Path", nullptr, nullptr, nullptr, &size);

    std::wstring currentPath;
    if (size > 0) {
        currentPath.resize((size / sizeof(wchar_t)) - 1);
        RegQueryValueExW(hKey, L"Path", nullptr, nullptr,
            reinterpret_cast<BYTE*>(&currentPath[0]), &size);
    }

    if (currentPath.find(dir) != std::wstring::npos) {
        RegCloseKey(hKey);
        return true;
    }

    if (!currentPath.empty() && currentPath.back() != L';')
        currentPath += L";";
    currentPath += dir;

    if (RegSetValueExW(hKey, L"Path", 0, REG_EXPAND_SZ,
        reinterpret_cast<const BYTE*>(currentPath.c_str()),
        static_cast<DWORD>((currentPath.size() + 1) * sizeof(wchar_t))) != ERROR_SUCCESS) {
        std::wcerr << L"Failed to set PATH." << std::endl;
        RegCloseKey(hKey);
        return false;
    }

    RegCloseKey(hKey);

    SendMessageTimeoutW(HWND_BROADCAST, WM_SETTINGCHANGE, 0,
        reinterpret_cast<LPARAM>(L"Environment"),
        SMTO_ABORTIFHUNG, 5000, nullptr);
    return true;
}