/*******************************************************************************
 * Copyright (c) 2023 Martin Erich Jobst
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Martin Jobst
 *     - initial API and implementation and/or initial documentation
 *******************************************************************************/

#include "FB_CTU_DINT_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "FB_CTU_DINT_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_bool.h"
#include "forte_dint.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_FB_CTU_DINT, g_nStringIdFB_CTU_DINT)

const CStringDictionary::TStringId FORTE_FB_CTU_DINT::scmDataInputNames[] = {g_nStringIdCU, g_nStringIdR, g_nStringIdPV};

const CStringDictionary::TStringId FORTE_FB_CTU_DINT::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdDINT};

const CStringDictionary::TStringId FORTE_FB_CTU_DINT::scmDataOutputNames[] = {g_nStringIdQ, g_nStringIdCV};

const CStringDictionary::TStringId FORTE_FB_CTU_DINT::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdDINT};

const TDataIOID FORTE_FB_CTU_DINT::scmEIWith[] = {0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_FB_CTU_DINT::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_FB_CTU_DINT::scmEventInputNames[] = {g_nStringIdREQ};

const TDataIOID FORTE_FB_CTU_DINT::scmEOWith[] = {0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_FB_CTU_DINT::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_FB_CTU_DINT::scmEventOutputNames[] = {g_nStringIdCNF};


const SFBInterfaceSpec FORTE_FB_CTU_DINT::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEOWith, scmEOWithIndexes,
  3, scmDataInputNames, scmDataInputTypeIds,
  2, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};


FORTE_FB_CTU_DINT::FORTE_FB_CTU_DINT(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CSimpleFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, nullptr),
    var_CU(CIEC_BOOL(0)),
    var_R(CIEC_BOOL(0)),
    var_PV(CIEC_DINT(0)),
    var_Q(CIEC_BOOL(0)),
    var_CV(CIEC_DINT(0)),
    var_conn_Q(var_Q),
    var_conn_CV(var_CV),
    conn_CNF(this, 0),
    conn_CU(nullptr),
    conn_R(nullptr),
    conn_PV(nullptr),
    conn_Q(this, 0, &var_conn_Q),
    conn_CV(this, 1, &var_conn_CV) {
}

void FORTE_FB_CTU_DINT::alg_REQ(void) {
  
  if (var_R) {
    var_CV = CIEC_DINT(0);
  }
  else if (func_AND<CIEC_BOOL>(var_CU, func_LT(var_CV, CIEC_DINT(std::numeric_limits<CIEC_DINT::TValueType>::max())))) {
    var_CV = func_ADD<CIEC_DINT>(var_CV, CIEC_DINT(1));
  }
  var_Q = func_GE(var_CV, var_PV);
}


void FORTE_FB_CTU_DINT::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQID:
      alg_REQ();
      break;
    default:
      break;
  }
  sendOutputEvent(scmEventCNFID, paECET);
}

void FORTE_FB_CTU_DINT::readInputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_CU, conn_CU);
      readData(1, var_R, conn_R);
      break;
    }
    default:
      break;
  }
}

void FORTE_FB_CTU_DINT::writeOutputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_Q, conn_Q);
      writeData(1, var_CV, conn_CV);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_FB_CTU_DINT::getDI(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_CU;
    case 1: return &var_R;
    case 2: return &var_PV;
  }
  return nullptr;
}

CIEC_ANY *FORTE_FB_CTU_DINT::getDO(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_Q;
    case 1: return &var_CV;
  }
  return nullptr;
}

CEventConnection *FORTE_FB_CTU_DINT::getEOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_FB_CTU_DINT::getDIConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CU;
    case 1: return &conn_R;
    case 2: return &conn_PV;
  }
  return nullptr;
}

CDataConnection *FORTE_FB_CTU_DINT::getDOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_Q;
    case 1: return &conn_CV;
  }
  return nullptr;
}

CIEC_ANY *FORTE_FB_CTU_DINT::getVarInternal(size_t) {
  return nullptr;
}


