/*******************************************************************************
 * Copyright (c) 2013 ACIN
 *               2023 Martin Erich Jobst
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Monika Wenger
 *   - initial API and implementation and/or initial documentation
 *   Martin Jobst
 *     - refactor for ANY variant
 *******************************************************************************/

#include "F_SUB_DATE_DATE_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "F_SUB_DATE_DATE_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_F_SUB_DATE_DATE, g_nStringIdF_SUB_DATE_DATE)

const CStringDictionary::TStringId FORTE_F_SUB_DATE_DATE::scmDataInputNames[] = {g_nStringIdIN1, g_nStringIdIN2};

const CStringDictionary::TStringId FORTE_F_SUB_DATE_DATE::scmDataInputTypeIds[] = {g_nStringIdDATE, g_nStringIdDATE};

const CStringDictionary::TStringId FORTE_F_SUB_DATE_DATE::scmDataOutputNames[] = {g_nStringIdOUT};

const CStringDictionary::TStringId FORTE_F_SUB_DATE_DATE::scmDataOutputTypeIds[] = {g_nStringIdTIME};

const TDataIOID FORTE_F_SUB_DATE_DATE::scmEIWith[] = {0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_F_SUB_DATE_DATE::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_F_SUB_DATE_DATE::scmEventInputNames[] = {g_nStringIdREQ};

const TDataIOID FORTE_F_SUB_DATE_DATE::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_F_SUB_DATE_DATE::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_F_SUB_DATE_DATE::scmEventOutputNames[] = {g_nStringIdCNF};


const SFBInterfaceSpec FORTE_F_SUB_DATE_DATE::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEOWith, scmEOWithIndexes,
  2, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_F_SUB_DATE_DATE::FORTE_F_SUB_DATE_DATE(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_IN1(CIEC_DATE(0)),
    var_IN2(CIEC_DATE(0)),
    var_OUT(CIEC_TIME(0)),
    var_conn_OUT(var_OUT),
    conn_CNF(this, 0),
    conn_IN1(nullptr),
    conn_IN2(nullptr),
    conn_OUT(this, 0, &var_conn_OUT) {
};

void FORTE_F_SUB_DATE_DATE::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQID:
      var_OUT = func_SUB_DATE_DATE(var_IN1, var_IN2);
      sendOutputEvent(scmEventCNFID, paECET);
      break;
  }
}

void FORTE_F_SUB_DATE_DATE::readInputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_IN1, conn_IN1);
      readData(1, var_IN2, conn_IN2);
      break;
    }
    default:
      break;
  }
}

void FORTE_F_SUB_DATE_DATE::writeOutputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_OUT, conn_OUT);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_F_SUB_DATE_DATE::getDI(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_IN1;
    case 1: return &var_IN2;
  }
  return nullptr;
}

CIEC_ANY *FORTE_F_SUB_DATE_DATE::getDO(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_OUT;
  }
  return nullptr;
}

CEventConnection *FORTE_F_SUB_DATE_DATE::getEOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_F_SUB_DATE_DATE::getDIConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_IN1;
    case 1: return &conn_IN2;
  }
  return nullptr;
}

CDataConnection *FORTE_F_SUB_DATE_DATE::getDOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_OUT;
  }
  return nullptr;
}


