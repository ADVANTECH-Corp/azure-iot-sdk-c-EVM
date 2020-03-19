﻿/************************************************************************************************
 * This code was automatically generated by Digital Twin Code Generator tool 0.6.1.
 * Changes to this file may cause incorrect behavior and will be lost if the code is regenerated.
 *
 * Generated Date: 2019年8月23日
 ***********************************************************************************************/

#ifndef SENSORSINFORMATION_INTERFACE_H
#define SENSORSINFORMATION_INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "digitaltwin_interface_client.h"
#include "azure_c_shared_utility/xlogging.h"
#include "azure_c_shared_utility/threadapi.h"

#include "digitaltwin_client_helper.h"
#include "digitaltwin_serializer.h"
#include "parson.h"
#include "../AnCAD_impl.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum SENSORSINFORMATION_TELEMETRY_TAG
{
    SensorsInformation_RMS_X_TELEMETRY,
    SensorsInformation_RMS_Y_TELEMETRY,
    SensorsInformation_MOTOR_SPEED_RPM_TELEMETRY
} SENSORSINFORMATION_TELEMETRY;

// DigitalTwin interface name from service perspective.
static const char SensorsInformationInterfaceId[] = "urn:Advantech:EVM:SensorsInformation:1";
static const char SensorsInformationInterfaceInstanceName[] = "SensorsInformation";

// Telemetry names for this interface.

static const char SensorsInformationInterface_Rms_xTelemetry[] = "rms_x";

static const char SensorsInformationInterface_Rms_yTelemetry[] = "rms_y";

static const char SensorsInformationInterface_Motor_speed_rpmTelemetry[] = "motor_speed_rpm";

// Property names for this interface.

// Command names for this interface

// Methods
DIGITALTWIN_INTERFACE_CLIENT_HANDLE SensorsInformationInterface_Create();

void SensorsInformationInterface_Close(DIGITALTWIN_INTERFACE_CLIENT_HANDLE digitalTwinInterfaceClientHandle);

DIGITALTWIN_CLIENT_RESULT SensorsInformationInterface_Telemetry_SendRms_x();

DIGITALTWIN_CLIENT_RESULT SensorsInformationInterface_Telemetry_SendRms_y();

DIGITALTWIN_CLIENT_RESULT SensorsInformationInterface_Telemetry_SendMotor_speed_rpm();

DIGITALTWIN_CLIENT_RESULT SensorsInformationInterface_Telemetry_SendAll();

#ifdef __cplusplus
}
#endif

#endif  // SENSORSINFORMATION_INTERFACE_H