#ifndef _DEVICE_INFO_HANDLER_H_
#define _DEVICE_INFO_HANDLER_H_ 
#include <stdbool.h>
#include <stdint.h>


#ifndef ULONGLONG
typedef unsigned long long  ULONGLONG;
#endif 


#ifdef __cplusplus
extern "C" {
#endif

	bool util_os_get_os_name_reg_x64(char* pOSNameBuf, size_t* bufLen);
	bool util_os_get_os_name_reg(char* pOSNameBuf, size_t* bufLen);
	bool util_os_get_processor_name(char* pProcessorNameBuf, size_t* bufLen);
	bool util_os_get_architecture(char* pArchBuf, size_t* bufLen);
	bool util_os_get_free_memory(uint64_t* totalPhysMemKB, uint64_t* availPhysMemKB);
	unsigned long long util_os_get_tick_count();

#ifdef __cplusplus
}
#endif

#endif