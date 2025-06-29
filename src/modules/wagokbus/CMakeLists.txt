# *******************************************************************************
# Copyright (c) 2016, 2025 fortiss GmbH, Monika Wenger This program and the
# accompanying materials are made available under the terms of the Eclipse
# Public License 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0.
#
# SPDX-License-Identifier: EPL-2.0
#
# Contributors: Milan Vathoopan, Alois Zoitl - initial API and implementation
# and/or initial documentation Jose Cabral - Add modular IOs Monika Wenger -
# all files start with capital letters
# *******************************************************************************/
# ############################################################################
# WAGO KBUS SIFBs
# ############################################################################
if (NOT FORTE_ARCHITECTURE STREQUAL "Posix")
    return()
endif ()

# FIXME: shouldn't this be io, not module?
forte_register_module(WagoKbus OFF "Wago Kbus interface" FORTE_IO)

set(FORTE_WAGO_INCLUDE_DIR
    ""
    CACHE STRING "Path where the include for wago is found"
)
set(FORTE_WAGO_LIB_DIR
    ""
    CACHE STRING "Path where the  libraries for wago is found"
)
target_link_libraries(forte PUBLIC dal libloader pthread ffi dbus-glib-1
                                   glib-2.0
)
target_link_libraries(forte PUBLIC typelabel oslinux dbuskbuscommon)

# TODO: Further dependencies are to be checked and added later
add_library(forte-modules-wagokbus OBJECT
            WagoHandle.h
            WagoHandle.cpp
            WagoDeviceController.h
            WagoDeviceController.cpp
            types/WagoMaster.h
            types/WagoMaster.cpp
            types/WagoBusAdapter.h
            types/WagoBusAdapter.cpp
            types/WagoSlaveBase.h
            types/WagoSlaveBase.cpp
            types/Wago1506.h
            types/Wago1506.cpp
            types/Wago1405_6.h
            types/Wago1405_6.cpp
            types/Wago1504_5.h
            types/Wago1504_5.cpp
            types/Wago459.h
            types/Wago459.cpp
            types/Wago636_fbt.h
            types/Wago636_fbt.cpp
)
target_link_libraries(forte PRIVATE forte-modules-wagokbus)
target_include_directories(forte-modules-wagokbus
                           PUBLIC ${FORTE_WAGO_INCLUDE_DIR}
)
target_include_directories(forte-modules-wagokbus
                           PUBLIC ${FORTE_WAGO_INCLUDE_DIR}/dal
)
target_include_directories(forte-modules-wagokbus
                           PUBLIC ${FORTE_WAGO_INCLUDE_DIR}/OsLinux
)
target_link_directories(forte-modules-wagokbus PUBLIC ${FORTE_WAGO_LIB_DIR})
