/*********************************************************************
 * Copyright (c) 2022 Davor Cihlar
 *
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Davor Cihlar
 *     - initial implementation
 **********************************************************************/

#ifndef _IF_SPEC_BUILDER_H_
#define _IF_SPEC_BUILDER_H_

#include <vector>
#include <array>
#include <tuple>
#include <funcbloc.h>


namespace forte::core::util {

class CMixedStorage;

class CInputSpecTag;
class COutputSpecTag;
class CDataSpecTag;
class CEventSpecTag;

template<class TypeTag, class DirTag>
class CSpecReference {
  public:
    constexpr CSpecReference() = default;
    constexpr CSpecReference(int pa_nRef) {
      if (pa_nRef < 0 || pa_nRef >= maxVal) {
        ref = maxVal;
      } else {
        ref = (TDataIOID)pa_nRef;
      }
    }

    constexpr bool isValid() const {
      return ref != maxVal;
    }

    constexpr auto operator*() const {
      return ref;
    }

  private:
    static constexpr auto maxVal = std::numeric_limits<TDataIOID>::max();

    TDataIOID ref = maxVal;
};

class CStringIdListSpecBuilder {
  public:
    CStringIdListSpecBuilder(std::size_t pa_unMaxItems) : m_unMaxItems(pa_unMaxItems)
    {}

    bool setStaticList(const CStringDictionary::TStringId *pa_aunStaticList, std::size_t pa_nItemsCount);
    bool addString(const CStringDictionary::TStringId pa_unString);
    bool addString(const char *pa_sString);

    auto getNumStrings() const { return m_vDynamicList.size(); }

    int findString(const char *pa_sString) const;
    int findString(CStringDictionary::TStringId pa_unString) const;

    std::size_t calcStorageSize() const;
    std::tuple<const CStringDictionary::TStringId*, TForteUInt8> build(CMixedStorage &pa_oStorage) const;

  private:
    const std::size_t m_unMaxItems;
    std::vector<CStringDictionary::TStringId> m_vDynamicList;
    TForteUInt8 m_unStaticListSize = 0;
    const CStringDictionary::TStringId *m_aunStaticList = nullptr;
};

class CEventSpecBuilderBase {
  public:
    bool setStaticEvents(const CStringDictionary::TStringId *pa_aunStaticNames, std::size_t pa_nEventsCount) {
      return m_oNamesListBuilder.setStaticList(pa_aunStaticNames, pa_nEventsCount);
    }
    template<std::size_t N>
    bool setStaticEvents(const std::array<CStringDictionary::TStringId, N> &pa_aStaticNames) {
      return setStaticEvents(pa_aStaticNames.data(), pa_aStaticNames.size());
    }
    bool addEvent(CStringDictionary::TStringId pa_unName) {
      return m_oNamesListBuilder.addString(pa_unName);
    }
    bool addEvent(const char *pa_sName) {
      return m_oNamesListBuilder.addString(pa_sName);
    }
    bool addEventRange(const char *pa_sPrefix, int pa_nRangeSize);

    auto getNumEvents() const {
      return m_oNamesListBuilder.getNumStrings();
    }

    template<typename T>
    int findEvent(T pa_tName) const {
      return m_oNamesListBuilder.findString(pa_tName);
    }

    auto calcStorageSize() const {
      return m_oNamesListBuilder.calcStorageSize();
    }
    auto build(CMixedStorage &pa_oStorage) const {
      return m_oNamesListBuilder.build(pa_oStorage);
    }

  private:
    static constexpr auto scm_unMaxEvents = CFunctionBlock::scm_nMaxInterfaceEvents;
    CStringIdListSpecBuilder m_oNamesListBuilder{scm_unMaxEvents};
};

template<class DirTag>
class CEventSpecBuilder : public CEventSpecBuilderBase {
  public:
    template<typename TNameType>
    CSpecReference<CEventSpecTag, DirTag> operator[] (TNameType pa_tName) const {
      return { findEvent(pa_tName) };
    }
};

class CDataSpecBuilderBase {
  public:
    bool setStaticData(const CStringDictionary::TStringId *pa_aunStaticDataNames, const CStringDictionary::TStringId *pa_aunStaticTypeNames, std::size_t pa_nDataCount) {
      return
        m_oNamesListBuilder.setStaticList(pa_aunStaticDataNames, pa_nDataCount) &&
        m_oTypesListBuilder.setStaticList(pa_aunStaticTypeNames, pa_nDataCount);
    }
    bool addData(CStringDictionary::TStringId pa_unName, CStringDictionary::TStringId pa_unTypeName) {
      return m_oNamesListBuilder.addString(pa_unName) && m_oTypesListBuilder.addString(pa_unTypeName);
    }
    bool addData(const char *pa_sName, CStringDictionary::TStringId pa_unTypeName) {
      return m_oNamesListBuilder.addString(pa_sName) && m_oTypesListBuilder.addString(pa_unTypeName);
    }
    bool addData(CStringDictionary::TStringId pa_unName, const char * pa_sTypeName) {
      return m_oNamesListBuilder.addString(pa_unName) && m_oTypesListBuilder.addString(pa_sTypeName);
    }
    bool addData(const char *pa_sName, const char *pa_sTypeName) {
      return m_oNamesListBuilder.addString(pa_sName) && m_oTypesListBuilder.addString(pa_sTypeName);
    }
    bool addDataRange(const char *pa_sPrefix, int pa_nRangeSize);

    template<typename T>
    int findData(T pa_tName) const {
      return m_oNamesListBuilder.findString(pa_tName);
    }

    std::size_t calcStorageSize() const {
      return m_oNamesListBuilder.calcStorageSize() + m_oTypesListBuilder.calcStorageSize();
    }
    std::tuple<const CStringDictionary::TStringId*, const CStringDictionary::TStringId*, TForteUInt8> build(CMixedStorage &pa_oStorage) const;

  private:
    static constexpr auto scm_unMaxData = CFunctionBlock::scm_nMaxInterfaceEvents;
    CStringIdListSpecBuilder m_oNamesListBuilder{scm_unMaxData};
    CStringIdListSpecBuilder m_oTypesListBuilder{scm_unMaxData};
};

template<class DirTag>
class CDataSpecBuilder : public CDataSpecBuilderBase {
  public:
    template<typename TNameType>
    CSpecReference<CDataSpecTag, DirTag> operator[] (TNameType pa_tName) const {
      return { findData(pa_tName) };
    }
};

class CWithSpecBuilderBase {
  public:
    bool setStaticBindings(const TDataIOID *pa_aunStaticBindings, const TForteInt16 *pa_anStaticIndexes, std::size_t pa_unNumEvents);
    template<std::size_t NBindings, std::size_t NEvents>
    bool setStaticBindings(const std::array<TDataIOID, NBindings> &pa_aunStaticBindings, const std::array<TForteInt16, NEvents> &pa_anStaticIndexes) {
      return setStaticBindings(pa_aunStaticBindings.data(), pa_anStaticIndexes.data(), NEvents);
    }
    bool bind(TDataIOID pa_unEventId, TDataIOID pa_unDataId);
    bool bind(TDataIOID pa_unEventId, std::initializer_list<TDataIOID> pa_aunDataIds) {
      bool retVal = true;
      for (auto dataId : pa_aunDataIds) {
        retVal = retVal && bind(pa_unEventId, dataId);
      }
      return retVal;
    }
    bool bindRange(TDataIOID pa_unEventId, TDataIOID pa_unFirstDataId, TDataIOID pa_unLastDataId);
    
    std::size_t calcStorageSize(std::size_t pa_unNumEvents) const;
    std::tuple<const TDataIOID*, const TForteInt16*> build(CMixedStorage &pa_oStorage, std::size_t pa_unNumEvents) const;

  private:
    const TDataIOID *m_aunStaticBindings = nullptr;
    const TForteInt16 *m_anStaticIndexes = nullptr;
    std::size_t m_unNumStaticEvents = 0;
    std::vector<std::vector<TDataIOID>> m_vvDynamicList;

    void grow(std::size_t pa_unNumEvents);
};

template<class DirTag>
class CWithSpecBuilder : public CWithSpecBuilderBase {
  public:
    bool bind(CSpecReference<CEventSpecTag, DirTag> pa_oEventRef, CSpecReference<CDataSpecTag, DirTag> pa_oDataRef) {
      return pa_oEventRef.isValid() && pa_oDataRef.isValid() && CWithSpecBuilderBase::bind(*pa_oEventRef, *pa_oDataRef);
    }
    bool bind(CSpecReference<CEventSpecTag, DirTag> pa_oEventRef, std::initializer_list<CSpecReference<CDataSpecTag, DirTag>> pa_aoDataRefs) {
      bool retVal = pa_oEventRef.isValid();
      for (auto ref : pa_aoDataRefs) {
        retVal = retVal && ref.isValid() && bind(pa_oEventRef, *ref);
      }
      return retVal;
    }
    bool bindRange(CSpecReference<CEventSpecTag, DirTag> pa_oEventRef, CSpecReference<CDataSpecTag, DirTag> pa_oFirstDataRef, CSpecReference<CDataSpecTag, DirTag> pa_oLastDataRef) {
      return pa_oEventRef.isValid() && pa_oFirstDataRef.isValid() && pa_oLastDataRef.isValid() && CWithSpecBuilderBase::bindRange(*pa_oEventRef, *pa_oFirstDataRef, *pa_oLastDataRef);
    }
};

class CIfSpecBuilder {
  public:
    CEventSpecBuilder<CInputSpecTag>  m_oEI;
    CEventSpecBuilder<COutputSpecTag> m_oEO;
    CDataSpecBuilder<CInputSpecTag>   m_oDI;
    CDataSpecBuilder<COutputSpecTag>  m_oDO;
    CWithSpecBuilder<CInputSpecTag>   m_oIWith;
    CWithSpecBuilder<COutputSpecTag>  m_oOWith;

    template<class DirTag>
    bool bind(CSpecReference<CEventSpecTag, DirTag> pa_oEventRef, CSpecReference<CDataSpecTag, DirTag> pa_oDataRef) {
      return getWithFromDir(pa_oEventRef).bind(pa_oEventRef, pa_oDataRef);
    }
    template<class DirTag>
    bool bind(CSpecReference<CEventSpecTag, DirTag> pa_oEventRef, std::initializer_list<CSpecReference<CDataSpecTag, DirTag>> &&pa_loDataRef) {
      return getWithFromDir(pa_oEventRef).bind(pa_oEventRef, std::move(pa_loDataRef));
    }
    template<class DirTag>
    bool bindRange(CSpecReference<CEventSpecTag, DirTag> pa_oEventRef, CSpecReference<CDataSpecTag, DirTag> pa_oFirstDataRef, CSpecReference<CDataSpecTag, DirTag> pa_oLastDataRef) {
      return getWithFromDir(pa_oEventRef).bindRange(pa_oEventRef, pa_oFirstDataRef, pa_oLastDataRef);
    }

    bool build(CMixedStorage &pa_oStorage, SFBInterfaceSpec &pa_oInterfaceSpec) const;

  private:
    constexpr CWithSpecBuilder<CInputSpecTag>& getWithFromDir(CSpecReference<CEventSpecTag, CInputSpecTag>) {
      return m_oIWith;
    }
    constexpr CWithSpecBuilder<COutputSpecTag>& getWithFromDir(CSpecReference<CEventSpecTag, COutputSpecTag>) {
      return m_oOWith;
    }
};

}

#endif /* _IF_SPEC_BUILDER_H_ */
