/*************************************************************************
 *** Copyright (c) 2025 HR Agrartechnik GmbH
 *** This program and the accompanying materials are made available under the
 *** terms of the Eclipse Public License 2.0 which is available at
 *** http://www.eclipse.org/legal/epl-2.0.
 ***
 *** SPDX-License-Identifier: EPL-2.0
 ***
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: E_BLINK_TRAIN
 *** Description: Simulates a blinking signal (turning on and off for specific durations), with a limited N
 *** Version:
 ***     1.0: 2025-02-15/Franz Höpfinger - HR Agrartechnik GmbH   - initial API and implementation and/or initial documentation
 *************************************************************************/

#include "E_BLINK_TRAIN_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "E_BLINK_TRAIN_fbt_gen.cpp"
#endif

#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_E_BLINK_TRAIN, g_nStringIdE_BLINK_TRAIN)

const CStringDictionary::TStringId FORTE_E_BLINK_TRAIN::scmDataInputNames[] = {g_nStringIdTIMELOW, g_nStringIdTIMEHIGH, g_nStringIdN};
const CStringDictionary::TStringId FORTE_E_BLINK_TRAIN::scmDataInputTypeIds[] = {g_nStringIdTIME, g_nStringIdTIME, g_nStringIdUINT};
const CStringDictionary::TStringId FORTE_E_BLINK_TRAIN::scmDataOutputNames[] = {g_nStringIdOUT};
const CStringDictionary::TStringId FORTE_E_BLINK_TRAIN::scmDataOutputTypeIds[] = {g_nStringIdBOOL};
const TDataIOID FORTE_E_BLINK_TRAIN::scmEIWith[] = {0, 1, 2, scmWithListDelimiter};
const TForteInt16 FORTE_E_BLINK_TRAIN::scmEIWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_E_BLINK_TRAIN::scmEventInputNames[] = {g_nStringIdSTART, g_nStringIdSTOP};
const TDataIOID FORTE_E_BLINK_TRAIN::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_E_BLINK_TRAIN::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_E_BLINK_TRAIN::scmEventOutputNames[] = {g_nStringIdCNF};
const SFBInterfaceSpec FORTE_E_BLINK_TRAIN::scmFBInterfaceSpec = {
  2, scmEventInputNames, nullptr, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, nullptr, scmEOWith, scmEOWithIndexes,
  3, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_E_BLINK_TRAIN::FORTE_E_BLINK_TRAIN(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CCompositeFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, scmFBNData),
    fb_E_TP(g_nStringIdE_TP, *this),
    fb_E_TRAIN(g_nStringIdE_TRAIN, *this),
    fb_ADD_2(g_nStringIdADD_2, "ADD_2", *this),
    var_TIMELOW(0_TIME),
    var_TIMEHIGH(0_TIME),
    var_N(0_UINT),
    var_OUT(0_BOOL),
    var_conn_OUT(var_OUT),
    conn_CNF(this, 0),
    conn_TIMELOW(nullptr),
    conn_TIMEHIGH(nullptr),
    conn_N(nullptr),
    conn_OUT(this, 0, &var_conn_OUT) {
};

void FORTE_E_BLINK_TRAIN::setInitialValues() {
  var_TIMELOW = 0_TIME;
  var_TIMEHIGH = 0_TIME;
  var_N = 0_UINT;
  var_OUT = 0_BOOL;
}

const SCFB_FBInstanceData FORTE_E_BLINK_TRAIN::scmInternalFBs[] = {
  {g_nStringIdE_TP, g_nStringIdE_PULSE},
  {g_nStringIdE_TRAIN, g_nStringIdE_TRAIN},
  {g_nStringIdADD_2, g_nStringIdADD_2}
};

const SCFB_FBConnectionData FORTE_E_BLINK_TRAIN::scmEventConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_TRAIN, g_nStringIdEO), 1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_TP, g_nStringIdREQ), 0},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdSTART), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdADD_2, g_nStringIdREQ), 2},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdADD_2, g_nStringIdCNF), 2, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_TRAIN, g_nStringIdSTART), 1},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdSTOP), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_TRAIN, g_nStringIdSTOP), 1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_TP, g_nStringIdCNF), 0, GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdCNF), -1},
};

const SCFB_FBFannedOutConnectionData FORTE_E_BLINK_TRAIN::scmFannedOutEventConnections[] = {
  {3, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_TP, g_nStringIdR), 0},
};

const SCFB_FBConnectionData FORTE_E_BLINK_TRAIN::scmDataConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdADD_2, g_nStringIdOUT), 2, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_TRAIN, g_nStringIdDT), 1},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdTIMELOW), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdADD_2, g_nStringIdIN1), 2},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdTIMEHIGH), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdADD_2, g_nStringIdIN2), 2},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_TP, g_nStringIdQ), 0, GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdOUT), -1},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdN), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_TRAIN, g_nStringIdN), 1},
};

const SCFB_FBFannedOutConnectionData FORTE_E_BLINK_TRAIN::scmFannedOutDataConnections[] = {
  {2, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_TP, g_nStringIdPT), 0},
};

const SCFB_FBNData FORTE_E_BLINK_TRAIN::scmFBNData = {
  3, scmInternalFBs,
  5, scmEventConnections,
  1, scmFannedOutEventConnections,
  5, scmDataConnections,
  1, scmFannedOutDataConnections,
  0, nullptr
};

void FORTE_E_BLINK_TRAIN::readInternal2InterfaceOutputData(const TEventID paEOID) {
  switch(paEOID) {
    case scmEventCNFID: {
      if(CDataConnection *conn = getIn2IfConUnchecked(0); conn) { conn->readData(var_OUT); }
      break;
    }
    default:
      break;
  }
}
void FORTE_E_BLINK_TRAIN::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventSTARTID: {
      readData(0, var_TIMELOW, conn_TIMELOW);
      readData(1, var_TIMEHIGH, conn_TIMEHIGH);
      readData(2, var_N, conn_N);
      break;
    }
    default:
      break;
  }
}

void FORTE_E_BLINK_TRAIN::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_OUT, conn_OUT);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_E_BLINK_TRAIN::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_TIMELOW;
    case 1: return &var_TIMEHIGH;
    case 2: return &var_N;
  }
  return nullptr;
}

CIEC_ANY *FORTE_E_BLINK_TRAIN::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_OUT;
  }
  return nullptr;
}

CEventConnection *FORTE_E_BLINK_TRAIN::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_E_BLINK_TRAIN::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_TIMELOW;
    case 1: return &conn_TIMEHIGH;
    case 2: return &conn_N;
  }
  return nullptr;
}

CDataConnection *FORTE_E_BLINK_TRAIN::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_OUT;
  }
  return nullptr;
}
