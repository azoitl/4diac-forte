/*******************************************************************************
 * Copyright (c) 2006 - 2013 ACIN, Profactor GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl, Gerhard Ebenhofer, Ingo Hegny, Monika Wenger,
 *    - initial API and implementation and/or initial documentation
 *******************************************************************************/
#include "RT_E_MERGE_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "RT_E_MERGE_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_RT_E_MERGE, g_nStringIdRT_E_MERGE)

const CStringDictionary::TStringId FORTE_RT_E_MERGE::scmDataInputNames[] = {g_nStringIdQI, g_nStringIdTmin, g_nStringIdDeadline, g_nStringIdWCET};
const CStringDictionary::TStringId FORTE_RT_E_MERGE::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdTIME, g_nStringIdTIME, g_nStringIdTIME};
const CStringDictionary::TStringId FORTE_RT_E_MERGE::scmDataOutputNames[] = {g_nStringIdQO};
const CStringDictionary::TStringId FORTE_RT_E_MERGE::scmDataOutputTypeIds[] = {g_nStringIdBOOL};
const TDataIOID FORTE_RT_E_MERGE::scmEIWith[] = {0, 1, 2, 3, scmWithListDelimiter};
const TForteInt16 FORTE_RT_E_MERGE::scmEIWithIndexes[] = {0, -1, -1};
const CStringDictionary::TStringId FORTE_RT_E_MERGE::scmEventInputNames[] = {g_nStringIdINIT, g_nStringIdEI1, g_nStringIdEI2};
const TDataIOID FORTE_RT_E_MERGE::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_RT_E_MERGE::scmEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_RT_E_MERGE::scmEventOutputNames[] = {g_nStringIdINITO, g_nStringIdEO};
const SFBInterfaceSpec FORTE_RT_E_MERGE::scmFBInterfaceSpec = {
  3, scmEventInputNames, scmEIWith, scmEIWithIndexes,
  2, scmEventOutputNames, scmEOWith, scmEOWithIndexes,
  4, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_RT_E_MERGE::FORTE_RT_E_MERGE(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
        CRTEventSingle(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_conn_QO(var_QO),
    conn_INITO(this, 0),
    conn_EO(this, 1),
    conn_QI(nullptr),
    conn_Tmin(nullptr),
    conn_Deadline(nullptr),
    conn_WCET(nullptr),
    conn_QO(this, 0, &var_conn_QO) {
};

void FORTE_RT_E_MERGE::setInitialValues() {
  var_QI = 0_BOOL;
  var_Tmin = 0_TIME;
  var_Deadline = 0_TIME;
  var_WCET = 0_TIME;
  var_QO = 0_BOOL;
}

void FORTE_RT_E_MERGE::readInputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITID: {
      readData(0, var_QI, conn_QI);
      readData(1, var_Tmin, conn_Tmin);
      readData(2, var_Deadline, conn_Deadline);
      readData(3, var_WCET, conn_WCET);
      break;
    }
    case scmEventEI1ID: {
      break;
    }
    case scmEventEI2ID: {
      break;
    }
    default:
      break;
  }
}

void FORTE_RT_E_MERGE::writeOutputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITOID: {
      writeData(0, var_QO, conn_QO);
      break;
    }
    case scmEventEOID: {
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_RT_E_MERGE::getDI(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QI;
    case 1: return &var_Tmin;
    case 2: return &var_Deadline;
    case 3: return &var_WCET;
  }
  return nullptr;
}

CIEC_ANY *FORTE_RT_E_MERGE::getDO(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QO;
  }
  return nullptr;
}

CEventConnection *FORTE_RT_E_MERGE::getEOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_INITO;
    case 1: return &conn_EO;
  }
  return nullptr;
}

CDataConnection **FORTE_RT_E_MERGE::getDIConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_Tmin;
    case 2: return &conn_Deadline;
    case 3: return &conn_WCET;
  }
  return nullptr;
}

CDataConnection *FORTE_RT_E_MERGE::getDOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QO;
  }
  return nullptr;
}

