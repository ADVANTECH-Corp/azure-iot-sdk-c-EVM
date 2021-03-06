﻿/************************************************************************************************
 * This code was automatically generated by Digital Twin Code Generator tool 0.6.1.
 * Changes to this file may cause incorrect behavior and will be lost if the code is regenerated.
 *
 * Generated Date: 2019年8月23日
 ***********************************************************************************************/

#ifndef DEVICEDETAILEDINFORMATION_INTERFACE_H
#define DEVICEDETAILEDINFORMATION_INTERFACE_H

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

typedef enum DEVICEDETAILEDINFORMATION_READONLY_PROPERTY_TAG
{
    DeviceDetailedInformation_DEVICENAME_PROPERTY,
    DeviceDetailedInformation_AGENTID_PROPERTY,
    DeviceDetailedInformation_DEVICEGROUPS_PROPERTY,
    DeviceDetailedInformation_WAKEONLAN_PROPERTY,
    DeviceDetailedInformation_CONNECTIONSTATUS_PROPERTY,
    DeviceDetailedInformation_AUTOREPORT_PROPERTY,
    DeviceDetailedInformation_STATUSMESSAGE_PROPERTY,
    DeviceDetailedInformation_PRODUCT_PROPERTY,
    DeviceDetailedInformation_MANUFACTURER_PROPERTY,
    DeviceDetailedInformation_VERSION_PROPERTY,
    DeviceDetailedInformation_PLATFORM_PROPERTY,
    DeviceDetailedInformation_OPERATINGSYSTEM_PROPERTY,
    DeviceDetailedInformation_MAC_PROPERTY,
    DeviceDetailedInformation_CPU_PROPERTY,
    DeviceDetailedInformation_MEMORY_PROPERTY,
    DeviceDetailedInformation_GRAFANAFOLDER_PROPERTY,
    DeviceDetailedInformation_GRAFANABOARD_PROPERTY,
    DeviceDetailedInformation_LASTCONNECTEDAT_PROPERTY
} DEVICEDETAILEDINFORMATION_PROPERTY;

// DigitalTwin interface name from service perspective.
static const char DeviceDetailedInformationInterfaceId[] = "urn:Advantech:EVM:DeviceDetailedInformation:1";
static const char DeviceDetailedInformationInterfaceInstanceName[] = "DeviceDetailedInformation";

// Telemetry names for this interface.

// Property names for this interface.

#define DeviceDetailedInformationInterface_DeviceNameProperty "DeviceName"

#define DeviceDetailedInformationInterface_AgentIDProperty "AgentID"

#define DeviceDetailedInformationInterface_DeviceGroupsProperty "DeviceGroups"

#define DeviceDetailedInformationInterface_WakeOnLANProperty "WakeOnLAN"

#define DeviceDetailedInformationInterface_ConnectionStatusProperty "ConnectionStatus"

#define DeviceDetailedInformationInterface_AutoReportProperty "AutoReport"

#define DeviceDetailedInformationInterface_StatusMessageProperty "StatusMessage"

#define DeviceDetailedInformationInterface_ProductProperty "Product"

#define DeviceDetailedInformationInterface_ManufacturerProperty "Manufacturer"

#define DeviceDetailedInformationInterface_VersionProperty "Version"

#define DeviceDetailedInformationInterface_PlatformProperty "Platform"

#define DeviceDetailedInformationInterface_OperatingSystemProperty "OperatingSystem"

#define DeviceDetailedInformationInterface_MACProperty "MAC"

#define DeviceDetailedInformationInterface_CPUProperty "CPU"

#define DeviceDetailedInformationInterface_MemoryProperty "Memory"

#define DeviceDetailedInformationInterface_GrafanaFolderProperty "GrafanaFolder"

#define DeviceDetailedInformationInterface_GrafanaBoardProperty "GrafanaBoard"

#define DeviceDetailedInformationInterface_LastConnectedAtProperty "LastConnectedAt"

// Command names for this interface

// Methods
DIGITALTWIN_INTERFACE_CLIENT_HANDLE DeviceDetailedInformationInterface_Create();

void DeviceDetailedInformationInterface_Close(DIGITALTWIN_INTERFACE_CLIENT_HANDLE digitalTwinInterfaceClientHandle);

DIGITALTWIN_CLIENT_RESULT DeviceDetailedInformationInterface_Property_ReportAll();

DIGITALTWIN_CLIENT_RESULT DeviceDetailedInformationInterface_Property_ReportDeviceName();

DIGITALTWIN_CLIENT_RESULT DeviceDetailedInformationInterface_Property_ReportAgentID();

DIGITALTWIN_CLIENT_RESULT DeviceDetailedInformationInterface_Property_ReportDeviceGroups();

DIGITALTWIN_CLIENT_RESULT DeviceDetailedInformationInterface_Property_ReportWakeOnLAN();

DIGITALTWIN_CLIENT_RESULT DeviceDetailedInformationInterface_Property_ReportConnectionStatus();

DIGITALTWIN_CLIENT_RESULT DeviceDetailedInformationInterface_Property_ReportAutoReport();

DIGITALTWIN_CLIENT_RESULT DeviceDetailedInformationInterface_Property_ReportStatusMessage();

DIGITALTWIN_CLIENT_RESULT DeviceDetailedInformationInterface_Property_ReportProduct();

DIGITALTWIN_CLIENT_RESULT DeviceDetailedInformationInterface_Property_ReportManufacturer();

DIGITALTWIN_CLIENT_RESULT DeviceDetailedInformationInterface_Property_ReportVersion();

DIGITALTWIN_CLIENT_RESULT DeviceDetailedInformationInterface_Property_ReportPlatform();

DIGITALTWIN_CLIENT_RESULT DeviceDetailedInformationInterface_Property_ReportOperatingSystem();

DIGITALTWIN_CLIENT_RESULT DeviceDetailedInformationInterface_Property_ReportMAC();

DIGITALTWIN_CLIENT_RESULT DeviceDetailedInformationInterface_Property_ReportCPU();

DIGITALTWIN_CLIENT_RESULT DeviceDetailedInformationInterface_Property_ReportMemory();

DIGITALTWIN_CLIENT_RESULT DeviceDetailedInformationInterface_Property_ReportGrafanaFolder();

DIGITALTWIN_CLIENT_RESULT DeviceDetailedInformationInterface_Property_ReportGrafanaBoard();

DIGITALTWIN_CLIENT_RESULT DeviceDetailedInformationInterface_Property_ReportLastConnectedAt();

#ifdef __cplusplus
}
#endif

#endif  // DEVICEDETAILEDINFORMATION_INTERFACE_H
