/*******************************************************************************
 * Copyright (c) 2016 - 2018 Johannes Messmer (admin@jomess.com), fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Johannes Messmer - initial API and implementation and/or initial documentation
 *   Jose Cabral - Cleaning of namespaces
 *******************************************************************************/

#include "EBSlave2301.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "EBSlave2301_gen.cpp"
#endif

#include "../handler/bus.h"

DEFINE_FIRMWARE_FB(FORTE_EBSlave2301, g_nStringIdEBSlave2301)

const CStringDictionary::TStringId FORTE_EBSlave2301::scmDataInputNames[] = {
    g_nStringIdQI, g_nStringIdRelay_1, g_nStringIdRelay_2, g_nStringIdRelay_3,
    g_nStringIdRelay_4, g_nStringIdRelay_5, g_nStringIdRelay_6,
    g_nStringIdUpdateInterval };

const CStringDictionary::TStringId FORTE_EBSlave2301::scmDataInputTypeIds[] =
    { g_nStringIdBOOL, g_nStringIdWSTRING, g_nStringIdWSTRING,
        g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING,
        g_nStringIdWSTRING, g_nStringIdUINT };

const CStringDictionary::TStringId FORTE_EBSlave2301::scmDataOutputNames[] = {
    g_nStringIdQO, g_nStringIdSTATUS };

const CStringDictionary::TStringId FORTE_EBSlave2301::scmDataOutputTypeIds[] = {
    g_nStringIdBOOL, g_nStringIdWSTRING };

const TForteInt16 FORTE_EBSlave2301::scmEIWithIndexes[] = { 0 };
const TDataIOID FORTE_EBSlave2301::scmEIWith[] = { 1, 2, 3, 4, 5, 6, 0, scmWithListDelimiter };
const CStringDictionary::TStringId FORTE_EBSlave2301::scmEventInputNames[] = {
    g_nStringIdMAP };

const TDataIOID FORTE_EBSlave2301::scmEOWith[] = { 0, scmWithListDelimiter, 0, 1, scmWithListDelimiter };
const TForteInt16 FORTE_EBSlave2301::scmEOWithIndexes[] = { 0, 2, -1 };
const CStringDictionary::TStringId FORTE_EBSlave2301::scmEventOutputNames[] = {
    g_nStringIdMAPO, g_nStringIdIND };

const SAdapterInstanceDef FORTE_EBSlave2301::scmAdapterInstances[] = { {
    g_nStringIdEBBusAdapter, g_nStringIdBusAdapterOut, true }, {
    g_nStringIdEBBusAdapter, g_nStringIdBusAdapterIn, false } };

const SFBInterfaceSpec FORTE_EBSlave2301::scmFBInterfaceSpec = { 1,
    scmEventInputNames, scmEIWith, scmEIWithIndexes, 2,
    scmEventOutputNames, scmEOWith, scmEOWithIndexes, 8,
    scmDataInputNames, scmDataInputTypeIds, 2, scmDataOutputNames,
    scmDataOutputTypeIds, 2, scmAdapterInstances };

const TForteUInt8 FORTE_EBSlave2301::scmSlaveConfigurationIO[] = { 7 };
const TForteUInt8 FORTE_EBSlave2301::scmSlaveConfigurationIONum = 1;

void FORTE_EBSlave2301::initHandles() {
  // Initialize handles
  int iCount = 0;
  int oCount = 6;
  int iOffset = 1;
  int oOffset = iOffset + iCount;

  for (int i = 0; i < oCount; i++) {
    EmbrickBusHandler::HandleDescriptor desc = EmbrickBusHandler::HandleDescriptor(
        *static_cast<CIEC_WSTRING*>(getDI(oOffset + i)), forte::core::io::IOMapper::Out, mIndex,
        EmbrickBusHandler::Bit, (uint8_t) (i / 8), (uint8_t) (i % 8));
    initHandle(&desc);
  }
}

