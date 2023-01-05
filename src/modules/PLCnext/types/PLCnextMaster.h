/*******************************************************************************
 * Copyright (c) 2022 Peirlberger Juergen
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Peirlberger Juergen - initial API and implementation and/or initial documentation
 *******************************************************************************/

#pragma once

#include "funcbloc.h"
#include "forte_bool.h"
#include "forte_uint.h"
#include "forte_wstring.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"
#include "../../../core/io/configFB/io_master_multi.h"
#include "../deviceController.h"
#include "PLCnextBusAdapter.h"

class FORTE_PLCnextMaster final : public forte::core::io::IOConfigFBMultiMaster {
  DECLARE_FIRMWARE_FB(FORTE_PLCnextMaster)

private:
  static const CStringDictionary::TStringId scmDataInputNames[];
  static const CStringDictionary::TStringId scmDataInputTypeIds[];
  static const CStringDictionary::TStringId scmDataOutputNames[];
  static const CStringDictionary::TStringId scmDataOutputTypeIds[];
  static const TEventID scmEventINITID = 0;
  static const TDataIOID scmEIWith[];
  static const TForteInt16 scmEIWithIndexes[];
  static const CStringDictionary::TStringId scmEventInputNames[];
  static const TEventID scmEventINITOID = 0;
  static const TEventID scmEventINDID = 1;
  static const TDataIOID scmEOWith[];
  static const TForteInt16 scmEOWithIndexes[];
  static const CStringDictionary::TStringId scmEventOutputNames[];
  static const int scmBusAdapterOutAdpNum = 0;
  static const SAdapterInstanceDef scmAdapterInstances[];

  static const SFBInterfaceSpec scmFBInterfaceSpec;

  void readInputData(TEventID paEIID) override;
  void writeOutputData(TEventID paEIID) override;
  void setInitialValues() override;
  
  forte::core::io::IODeviceController* createDeviceController(CDeviceExecution& paDeviceExecution);
  void setConfig();

public:
  FORTE_PLCnextMaster(CStringDictionary::TStringId paInstanceNameId, CResource *paSrcRes);

  CIEC_BOOL var_QI;
  CIEC_UINT var_SlaveUpdateInterval;

  CIEC_BOOL var_QO;
  CIEC_WSTRING var_STATUS;

  CIEC_BOOL var_conn_QO;
  CIEC_WSTRING var_conn_STATUS;

  CEventConnection conn_INITO;
  CEventConnection conn_IND;

  CDataConnection *conn_QI;
  CDataConnection *conn_SlaveUpdateInterval;

  CDataConnection conn_QO;
  CDataConnection conn_STATUS;

  CIEC_ANY *getDI(size_t) override;
  CIEC_ANY *getDO(size_t) override;
  CIEC_ANY *getDIO(size_t) override;
  FORTE_PLCnextBusAdapter &var_BusAdapterOut() {
    return *static_cast<FORTE_PLCnextBusAdapter*>(mAdapters[0]);
  };

  CEventConnection *getEOConUnchecked(TPortId) override;
  CDataConnection **getDIConUnchecked(TPortId) override;
  CDataConnection *getDOConUnchecked(TPortId) override;
  CInOutDataConnection **getDIOInConUnchecked(TPortId) override;
  CInOutDataConnection *getDIOOutConUnchecked(TPortId) override;

  void evt_INIT(const CIEC_BOOL &paQI, const CIEC_UINT &paSlaveUpdateInterval, CIEC_BOOL &paQO, CIEC_WSTRING &paSTATUS) {
    var_QI = paQI;
    var_SlaveUpdateInterval = paSlaveUpdateInterval;
    receiveInputEvent(scmEventINITID, nullptr);
    paQO = var_QO;
    paSTATUS = var_STATUS;
  }

  void operator()(const CIEC_BOOL &paQI, const CIEC_UINT &paSlaveUpdateInterval, CIEC_BOOL &paQO, CIEC_WSTRING &paSTATUS) {
    evt_INIT(paQI, paSlaveUpdateInterval, paQO, paSTATUS);
  }
};


