#pragma once
#ifndef __SENSOR_SOURCES__
#define __SENSOR_SOURCES__


#if defined(WIN32)
#pragma once
#define ADV_CALL __stdcall
#define ADV_EXPORT __declspec(dllexport)
#define __func__ __FUNCTION__
#else
#define ADV_CALL
#define ADV_EXPORT
#endif

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

#define EXPORT __declspec(dllexport)

typedef void(*SERVER_RECV_CALLBACK)(char* message, int len, void* callbackPara); 
int StartRequestLoop(SERVER_RECV_CALLBACK HandleReceivedMessage, void* callbackPara);
EXTERNC ADV_EXPORT void ADV_CALL StartMqttSneakLoop(SERVER_RECV_CALLBACK HandleReceivedMessage, void* callbackPara);
void Parse_RMS(const char* content, long long * interval, double* gap, double data[25]);

#undef EXTERNC
#endif //__SENSOR_SOURCES__
