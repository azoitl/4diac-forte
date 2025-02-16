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

#pragma once

#include "cfb.h"
#include "typelib.h"
#include "forte_any_magnitude_variant.h"
#include "forte_bool.h"
#include "forte_time.h"
#include "forte_uint.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"
#include "E_PULSE_fbt.h"
#include "E_TRAIN_fbt.h"
#include "GEN_ADD_fbt.h"

class FORTE_E_BLINK_TRAIN final : public CCompositeFB {
  DECLARE_FIRMWARE_FB(FORTE_E_BLINK_TRAIN)

  private:
    static const CStringDictionary::TStringId scmDataInputNames[];
    static const CStringDictionary::TStringId scmDataInputTypeIds[];
    static const CStringDictionary::TStringId scmDataOutputNames[];
    static const CStringDictionary::TStringId scmDataOutputTypeIds[];
    static const TEventID scmEventSTARTID = 0;
    static const TEventID scmEventSTOPID = 1;
    static const TDataIOID scmEIWith[];
    static const TForteInt16 scmEIWithIndexes[];
    static const CStringDictionary::TStringId scmEventInputNames[];
    static const TEventID scmEventCNFID = 0;
    static const TDataIOID scmEOWith[];
    static const TForteInt16 scmEOWithIndexes[];
    static const CStringDictionary::TStringId scmEventOutputNames[];

    static const SFBInterfaceSpec scmFBInterfaceSpec;

    static const SCFB_FBInstanceData scmInternalFBs[];
    static const SCFB_FBConnectionData scmEventConnections[];
    static const SCFB_FBFannedOutConnectionData scmFannedOutEventConnections[];
    static const SCFB_FBConnectionData scmDataConnections[];
    static const SCFB_FBFannedOutConnectionData scmFannedOutDataConnections[];
    static const SCFB_FBNData scmFBNData;

    forte::core::CInternalFB<FORTE_E_PULSE> fb_E_TP;
    forte::core::CInternalFB<FORTE_E_TRAIN> fb_E_TRAIN;
    forte::core::CInternalFB<GEN_ADD> fb_ADD_2;

    void readInputData(TEventID paEIID) override;
    void writeOutputData(TEventID paEIID) override;
    void readInternal2InterfaceOutputData(TEventID paEOID) override;
    void setInitialValues() override;

  public:
    FORTE_E_BLINK_TRAIN(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

    CIEC_TIME var_TIMELOW;
    CIEC_TIME var_TIMEHIGH;
    CIEC_UINT var_N;

    CIEC_BOOL var_OUT;

    CIEC_BOOL var_conn_OUT;

    CEventConnection conn_CNF;

    CDataConnection *conn_TIMELOW;
    CDataConnection *conn_TIMEHIGH;
    CDataConnection *conn_N;

    CDataConnection conn_OUT;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;
    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_START(const CIEC_TIME &paTIMELOW, const CIEC_TIME &paTIMEHIGH, const CIEC_UINT &paN, CIEC_BOOL &paOUT) {
      var_TIMELOW = paTIMELOW;
      var_TIMEHIGH = paTIMEHIGH;
      var_N = paN;
      executeEvent(scmEventSTARTID, nullptr);
      paOUT = var_OUT;
    }

    void evt_STOP(const CIEC_TIME &paTIMELOW, const CIEC_TIME &paTIMEHIGH, const CIEC_UINT &paN, CIEC_BOOL &paOUT) {
      var_TIMELOW = paTIMELOW;
      var_TIMEHIGH = paTIMEHIGH;
      var_N = paN;
      executeEvent(scmEventSTOPID, nullptr);
      paOUT = var_OUT;
    }

    void operator()(const CIEC_TIME &paTIMELOW, const CIEC_TIME &paTIMEHIGH, const CIEC_UINT &paN, CIEC_BOOL &paOUT) {
      evt_START(paTIMELOW, paTIMEHIGH, paN, paOUT);
    }
};

