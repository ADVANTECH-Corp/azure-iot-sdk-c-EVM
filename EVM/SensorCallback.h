#pragma once
#ifndef __SENSOR_CALLBACK_H__
#define __SENSOR_CALLBACK_H__

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

EXTERNC void CallBack_SensorData(char* content, int len, void* para);

EXTERNC double Get_rms_x();
EXTERNC double Get_rms_y();
EXTERNC double Get_motor_speed_rpm();

#endif //__SENSOR_CALLBACK_H__