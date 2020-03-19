#include "DeviceInfoHandler.h"
#include <Windows.h>

#define OS_UNKNOW                 "Unknow"
#define OS_WINDOWS_95             "Windows 95"
#define OS_WINDOWS_98             "Windows 98"
#define OS_WINDOWS_ME             "Windows ME"
#define OS_WINDOWS_NT_3_51        "Windows NT 3.51"
#define OS_WINDOWS_NT_4           "Windows NT 4"
#define OS_WINDOWS_2000           "Windows 2000"
#define OS_WINDOWS_XP             "Windows XP"
#define OS_WINDOWS_SERVER_2003    "Windows Server 2003"
#define OS_WINDOWS_VISTA          "Windows Vista"
#define OS_WINDOWS_7              "Windows 7"
#define OS_WINDOWS_8              "Windows 8"
#define OS_WINDOWS_SERVER_2012    "Windows Server 2012"
#define OS_WINDOWS_8_1            "Windows 8.1"
#define OS_WINDOWS_SERVER_2012_R2 "Windows Server 2012 R2"
#define OS_WINDOWS_10			  "Windows 10"
#define OS_WINDOWS_SERVER_2016	  "Windows Server 2016"

#define ARCH_UNKNOW               "Unknow"
#define ARCH_X64                  "X64"
#define ARCH_ARM                  "ARM"
#define ARCH_IA64                 "IA64"
#define ARCH_X86                  "X86"

#define DIV                       (1024)

bool util_os_get_os_name_reg_x64(char* pOSNameBuf, size_t* bufLen)
{
	bool bRet = false;
	HKEY hk;
	char regName[] = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion";
	if (ERROR_SUCCESS != RegOpenKeyEx(HKEY_LOCAL_MACHINE, regName, 0, KEY_READ | KEY_WOW64_64KEY, &hk)) return false;
	else
	{
		char valueName[] = "ProductName";
		char valueData[256] = { 0 };
		unsigned long  valueDataSize = sizeof(valueData);
		if (ERROR_SUCCESS != RegQueryValueEx(hk, valueName, 0, NULL, (LPBYTE)valueData, &valueDataSize))
		{
			RegCloseKey(hk);
			return false;
		}
		RegCloseKey(hk);
		bRet = valueDataSize == 0 ? false : true;
		if (bRet)
		{
			//unsigned int cpyLen = valueDataSize < *bufLen ? valueDataSize : *bufLen; 
			if (pOSNameBuf)
				memcpy(pOSNameBuf, valueData, valueDataSize);
			if (bufLen)
				* bufLen = valueDataSize;
		}
	}
	return bRet;
}

bool util_os_get_os_name_reg(char* pOSNameBuf, size_t* bufLen)
{
	bool bRet = false;
	HKEY hk;
	char regName[] = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion";
	if (ERROR_SUCCESS != RegOpenKeyEx(HKEY_LOCAL_MACHINE, regName, 0, KEY_READ, &hk)) return util_os_get_os_name_reg_x64(pOSNameBuf, bufLen);
	else
	{
		char valueName[] = "ProductName";
		char valueData[256] = { 0 };
		unsigned long  valueDataSize = sizeof(valueData);
		if (ERROR_SUCCESS != RegQueryValueEx(hk, valueName, 0, NULL, (LPBYTE)valueData, &valueDataSize))
		{
			RegCloseKey(hk);
			return util_os_get_os_name_reg_x64(pOSNameBuf, bufLen);
		}
		RegCloseKey(hk);
		bRet = valueDataSize == 0 ? false : true;

		if (bRet)
		{
			//unsigned int cpyLen = valueDataSize < *bufLen ? valueDataSize : *bufLen; 
			if (pOSNameBuf) {
				memcpy(pOSNameBuf, valueData, valueDataSize);
				pOSNameBuf[valueDataSize] = '\0';
			}
			if (bufLen) {
				*bufLen = valueDataSize + 1;
			}
		}
	}

	return bRet;
}

bool util_os_get_processor_name(char* pProcessorNameBuf, size_t* bufLen)
{
	bool bRet = false;
	HKEY hk;
	char regName[] = "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0";
	if (ERROR_SUCCESS != RegOpenKeyEx(HKEY_LOCAL_MACHINE, regName, 0, KEY_ALL_ACCESS, &hk)) return false;
	else
	{
		char valueName[] = "ProcessorNameString";
		char valueData[256] = { 0 };
		unsigned long  valueDataSize = sizeof(valueData);
		if (ERROR_SUCCESS != RegQueryValueEx(hk, valueName, 0, NULL, (LPBYTE)valueData, &valueDataSize))
		{
			RegCloseKey(hk);
			return false;
		}
		RegCloseKey(hk);
		bRet = valueDataSize == 0 ? false : true;
		if (bRet)
		{
			//unsigned int cpyLen = valueDataSize < *bufLen ? valueDataSize : *bufLen; 
			if (pProcessorNameBuf) {
				memcpy(pProcessorNameBuf, valueData, valueDataSize);
				pProcessorNameBuf[valueDataSize] = '\0';
			}
			if (bufLen)
				* bufLen = valueDataSize + 1;
		}
	}
	return bRet;
}

bool util_os_get_architecture(char* pArchBuf, size_t* bufLen)
{
	bool bRet = true;
	SYSTEM_INFO siSysInfo;
	typedef void (WINAPI * LPFN_GetNativeSystemInfo)(LPSYSTEM_INFO);
	LPFN_GetNativeSystemInfo fnGetNativeSystemInfo = (LPFN_GetNativeSystemInfo)GetProcAddress(GetModuleHandle("kernel32"), "GetNativeSystemInfo");
	if (NULL != fnGetNativeSystemInfo)
	{
		fnGetNativeSystemInfo(&siSysInfo);
	}
	else
	{
		GetSystemInfo(&siSysInfo);
	}

	switch (siSysInfo.wProcessorArchitecture)
	{
	case PROCESSOR_ARCHITECTURE_AMD64:
	{
		if (pArchBuf) {
			memcpy(pArchBuf, ARCH_X64, strlen(ARCH_X64));
			pArchBuf[strlen(ARCH_X64)] = '\0';
		}
		if (bufLen)
			*bufLen = strlen(ARCH_X64) + 1;
		break;
	}
	case PROCESSOR_ARCHITECTURE_ARM:
	{
		if (pArchBuf) {
			memcpy(pArchBuf, ARCH_ARM, strlen(ARCH_ARM));
			pArchBuf[strlen(ARCH_ARM)] = '\0';
		}
		if (bufLen)
			* bufLen = strlen(ARCH_ARM) + 1;
		break;
	}
	case PROCESSOR_ARCHITECTURE_IA64:
	{
		if (pArchBuf) {
			memcpy(pArchBuf, ARCH_IA64, strlen(ARCH_IA64));
			pArchBuf[strlen(ARCH_IA64)] = '\0';
		}
		if (bufLen)
			* bufLen = strlen(ARCH_IA64) + 1;
		break;
	}
	case PROCESSOR_ARCHITECTURE_INTEL:
	{
		if (pArchBuf) {
			memcpy(pArchBuf, ARCH_X86, strlen(ARCH_X86));
			pArchBuf[strlen(ARCH_X86)] = '\0';
		}
		if (bufLen)
			* bufLen = strlen(ARCH_X86) + 1;
		break;
	}
	case PROCESSOR_ARCHITECTURE_UNKNOWN:
	{
		if (pArchBuf) {
			memcpy(pArchBuf, ARCH_UNKNOW, strlen(ARCH_UNKNOW));
			pArchBuf[strlen(ARCH_UNKNOW)] = '\0';
		}
		if (bufLen)
			* bufLen = strlen(ARCH_UNKNOW) + 1;
		break;
	}
	default:
		bRet = false;
		break;
	}
	return bRet;
}

bool util_os_get_free_memory(uint64_t* totalPhysMemKB, uint64_t* availPhysMemKB)
{
	MEMORYSTATUSEX memStatex;
	memStatex.dwLength = sizeof(memStatex);
	GlobalMemoryStatusEx(&memStatex);

	if (totalPhysMemKB)
		* totalPhysMemKB = (long)(memStatex.ullTotalPhys / DIV);
	if (availPhysMemKB)
		* availPhysMemKB = (long)(memStatex.ullAvailPhys / DIV);

	return true;
}

unsigned long long util_os_get_tick_count()
{
	LARGE_INTEGER qpc;
	LARGE_INTEGER qpf;
	unsigned long long tickMs = 0;
	QueryPerformanceCounter(&qpc);
	QueryPerformanceFrequency(&qpf);
	tickMs = qpc.QuadPart * 1000 / qpf.QuadPart;
	return tickMs;
}