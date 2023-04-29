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

#pragma once

#include "simplefb.h"
#include "forte_bool.h"
#include "forte_int.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class FORTE_FB_CTU: public CSimpleFB {
  DECLARE_FIRMWARE_FB(FORTE_FB_CTU)

private:
  static const CStringDictionary::TStringId scm_anDataInputNames[];
  static const CStringDictionary::TStringId scm_anDataInputTypeIds[];
  
  static const CStringDictionary::TStringId scm_anDataOutputNames[];
  static const CStringDictionary::TStringId scm_anDataOutputTypeIds[];
  
  static const TEventID scm_nEventREQID = 0;
  
  static const TDataIOID scm_anEIWith[];
  static const TForteInt16 scm_anEIWithIndexes[];
  static const CStringDictionary::TStringId scm_anEventInputNames[];
  
  static const TEventID scm_nEventCNFID = 0;
  
  static const TDataIOID scm_anEOWith[]; 
  static const TForteInt16 scm_anEOWithIndexes[];
  static const CStringDictionary::TStringId scm_anEventOutputNames[];
  

  static const SFBInterfaceSpec scm_stFBInterfaceSpec;
  CIEC_ANY *getVarInternal(size_t) override;
  void alg_REQ(void);

  void executeEvent(int pa_nEIID) override;

  void readInputData(size_t pa_nEIID) override;
  void writeOutputData(size_t pa_nEIID) override;

public:
  FORTE_FB_CTU(CStringDictionary::TStringId pa_nInstanceNameId, CResource *pa_poSrcRes);


  CIEC_BOOL var_CU;
  CIEC_BOOL var_R;
  CIEC_INT var_PV;
  CIEC_BOOL var_Q;
  CIEC_INT var_CV;
  
  CIEC_BOOL var_conn_Q;
  CIEC_INT var_conn_CV;
  CEventConnection conn_CNF;
  CDataConnection *conn_CU;
  CDataConnection *conn_R;
  CDataConnection *conn_PV;
  CDataConnection conn_Q;
  CDataConnection conn_CV;
  
  CIEC_ANY *getDI(size_t) override;
  CIEC_ANY *getDO(size_t) override;
  CEventConnection *getEOConUnchecked(TPortId) override;
  CDataConnection **getDIConUnchecked(TPortId) override;
  CDataConnection *getDOConUnchecked(TPortId) override;
  
  void evt_REQ(const CIEC_BOOL &pa_CU, const CIEC_BOOL &pa_R, const CIEC_INT &pa_PV, CIEC_BOOL &pa_Q, CIEC_INT &pa_CV) {
    var_CU = pa_CU;
    var_R = pa_R;
    var_PV = pa_PV;
    receiveInputEvent(scm_nEventREQID, nullptr);
    pa_Q = var_Q;
    pa_CV = var_CV;
  }
  
  void operator()(const CIEC_BOOL &pa_CU, const CIEC_BOOL &pa_R, const CIEC_INT &pa_PV, CIEC_BOOL &pa_Q, CIEC_INT &pa_CV) {
    evt_REQ(pa_CU, pa_R, pa_PV, pa_Q, pa_CV);
  }
  
};



