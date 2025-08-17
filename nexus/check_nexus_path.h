#pragma once

EXTERN_C NTSTATUS NTAPI NtQuerySystemInformation(
SYSTEM_INFORMATION_CLASS SystemInformationClass,
PVOID                    SystemInformation,
ULONG                    SystemInformationLength,
PULONG                   ReturnLength
);

EXTERN_C NTSTATUS NTAPI NtQueryInformationProcess(
HANDLE           ProcessHandle,
PROCESSINFOCLASS ProcessInformationClass,
PVOID            ProcessInformation,
ULONG            ProcessInformationLength,
PULONG           ReturnLength);

const wchar_t* check_nexus_path() {
	ULONG buffer_size = 1024 * 1024;
	PVOID buffer = malloc(buffer_size);
	NtQuerySystemInformation(SystemProcessInformation, buffer, buffer_size, NULL);
	SYSTEM_PROCESS_INFORMATION* spi = (SYSTEM_PROCESS_INFORMATION*)buffer;
	while (true) {
		if (spi->ImageName.Buffer && _wcsicmp(spi->ImageName.Buffer, L"nexus.exe") == 0) {
			HANDLE hproc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, (DWORD)spi->UniqueProcessId);
			wchar_t path[256];
			DWORD out_size = 256;
			QueryFullProcessImageNameW(hproc, 0, path, &out_size);
			return path;

		}

		if (spi->NextEntryOffset == 0) break;
		spi = (SYSTEM_PROCESS_INFORMATION*)((BYTE*)spi + spi->NextEntryOffset);
	}
}
