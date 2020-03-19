#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.

#this is CMakeLists.txt for AnCAD_DPS

compileAsC99()

cmake_minimum_required(VERSION 2.8)

file(GLOB AnCAD_DPS_h_files
    "*.h"
    "./utilities/*.h"
)

file(GLOB AnCAD_DPS_c_files
    "*.c"
    "./utilities/*.c"
)

include_directories(.)
include_directories(./utilities)
include_directories(${PROJECT_SOURCE_DIR}/deps/parson)
include_directories(${SHARED_UTIL_INC_FOLDER})
include_directories(${IOTHUB_CLIENT_INC_FOLDER})
include_directories(${DIGITALTWIN_CLIENT_INC_FOLDER})
include_directories(${DEV_AUTH_MODULES_CLIENT_INC_FOLDER})

add_executable(AnCAD_DPS ${AnCAD_DPS_c_files} ${AnCAD_DPS_h_files})

target_link_libraries(AnCAD_DPS parson iothub_client_mqtt_transport iothub_client digitaltwin_client prov_device_ll_client prov_mqtt_transport)