/*******************************************************************************
 * Copyright (c) 2005 - 2013 Profactor GmbH, ACIN, fortiss GmbH
 *               2022 Primetals Technologies Austria GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Thomas Strasser, Ingomar Müller, Alois Zoitl, Gerhard Ebenhofer,
 *    Ingo Hegny, Monika Wenger
 *      - initial implementation and rework communication infrastructure,
 *    Martin Melik Merkumains - make TForteUInt16 constructor explicit,
 *        removed built-in type operator=, added castable CIEC types operator=
 *******************************************************************************/
#ifndef _FORTE_UINT_H_
#define _FORTE_UINT_H_

#include "forte_any_int.h"
#include "forte_usint.h"
#include <limits>

/*!\ingroup COREDTS CIEC_UINT represents the uint data type according to IEC 61131.
 */
class CIEC_UINT : public CIEC_ANY_INT{
  DECLARE_FIRMWARE_DATATYPE(UINT)

  public:
    typedef TForteUInt16 TValueType;

    static const TValueType scm_nMinVal = 0;
    static const TValueType scm_nMaxVal;

    CIEC_UINT() = default;

    CIEC_UINT(const CIEC_UINT& paValue) :
        CIEC_ANY_INT(){
      setValueSimple(paValue);
    }

    CIEC_UINT(const CIEC_USINT& paValue) :
        CIEC_ANY_INT(){
      setValueSimple(paValue);
    }

    explicit CIEC_UINT(TForteUInt16 paValue){
      setTUINT16(paValue);
    }

    virtual ~CIEC_UINT() = default;

    CIEC_UINT& operator =(const CIEC_UINT &paValue){
      // Simple value assignment - no self assignment check needed
      setValueSimple(paValue);
      return *this;
    }

    CIEC_UINT& operator =(const CIEC_USINT &paValue){
      // Simple value assignment - no self assignment check needed
      setValueSimple(paValue);
      return *this;
    }

    /*! \brief Converts CIEC_UDINT to elementary unsigned 16 bit integer
     *
     *   Conversion operator for converting CIEC_UDINT to elementary unsigned 16 bit integer
     */
    operator TForteUInt16() const{
      return getTUINT16();
    }

    virtual EDataTypeID getDataTypeID() const{
      return CIEC_ANY::e_UINT;
    }
};

#endif /*_FORTE_UINT_H_*/
