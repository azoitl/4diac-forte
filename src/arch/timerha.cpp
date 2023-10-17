/*******************************************************************************
 * Copyright (c) 2005 - 2015 ACIN, Profactor GmbH, fortiss GmbH
 *               2020 Johannes Kepler University Linz
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl, Rene Smodic, Thomas Strasser, Ingo Hegny
 *      - initial API and implementation and/or initial documentation
 *   Alois Zoitl - worked on reducing the jitter and overhead of timer handler
 *                 Bug #568902
 *******************************************************************************/
#include "timerha.h"
#include "../core/datatypes/forte_any_duration.h"
#include "../core/devexec.h"
#include "../core/esfb.h"
#include "../core/utils/criticalregion.h"
#include <algorithm>
#include <functional>

DEFINE_HANDLER(CTimerHandler)

CTimerHandler::CTimerHandler(CDeviceExecution& paDeviceExecution) : CExternalEventHandler(paDeviceExecution),
    mForteTime(0) {
}

CTimerHandler::~CTimerHandler() = default;

void CTimerHandler::registerOneShotTimedFB(CEventSourceFB *const paTimedFB, const CIEC_TIME &paTimeInterval) {
	TForteUInt32 interval = convertIntervalToTimerHandlerUnits(paTimeInterval);
	addToAddFBList(STimedFBListEntry(paTimedFB, mForteTime + interval, scmOneShotIndicator));
}

void CTimerHandler::registerPeriodicTimedFB(CEventSourceFB *const paTimedFB, const CIEC_TIME &paTimeInterval) {
	TForteUInt32 interval = convertIntervalToTimerHandlerUnits(paTimeInterval);
	addToAddFBList(STimedFBListEntry(paTimedFB, mForteTime + interval, interval));
}

TForteUInt32 CTimerHandler::convertIntervalToTimerHandlerUnits(const CIEC_TIME &paTimeInterval){
  //calculate the correct interval based on time-base and timer ticks per seconds
  TForteUInt32 interval = static_cast<TForteUInt32>((static_cast<CIEC_TIME::TValueType>(paTimeInterval) * getTicksPerSecond()) / CIEC_ANY_DURATION::csmForteTimeBaseUnitsPerSecond);
  if(interval == 0) {
    interval = 1;
  }
  return interval;
}

void CTimerHandler::addToAddFBList(const STimedFBListEntry& paTimerListEntry){
  CCriticalRegion criticalRegion(mAddListSync);
  mAddFBList.push_back(paTimerListEntry);
}

void CTimerHandler::addTimedFBEntry(const STimedFBListEntry& paTimerListEntry) {
  auto it = std::lower_bound(mTimedFBList.begin(), mTimedFBList.end(), paTimerListEntry, 
    [](const STimedFBListEntry& entry1, const STimedFBListEntry& entry2) { return entry1.mTimeOut < entry2.mTimeOut; });
  mTimedFBList.insert(it, paTimerListEntry);
}

void CTimerHandler::unregisterTimedFB(CEventSourceFB *paTimedFB) {
  CCriticalRegion criticalRegion(mRemoveListSync);
  mRemoveFBList.push_back(paTimedFB);
}

void CTimerHandler::removeTimedFB(CEventSourceFB *paTimedFB) {
  auto it = std::remove_if(mTimedFBList.begin(), mTimedFBList.end(), 
  	[&paTimedFB](const STimedFBListEntry& entry) { return entry.mTimedFB == paTimedFB; });
  mTimedFBList.erase(it, mTimedFBList.end());
}

void CTimerHandler::nextTick() {
  ++mForteTime;
  mDeviceExecution.notifyTime(mForteTime); //notify the device execution that one tick passed by.

  if(!mRemoveFBList.empty()){
    processRemoveList();
  }

  processTimedFBList();

  if(!mAddFBList.empty()){
    processAddList();
  }
}

void CTimerHandler::processTimedFBList() {
  for (auto it = mTimedFBList.begin(); it != mTimedFBList.end();) {
    if (it->mTimeOut > mForteTime) {
      break;  
    }
    STimedFBListEntry entry = *it; // buffer entry
    it = mTimedFBList.erase(it);
    triggerTimedFB(entry);
  }
}

void CTimerHandler::triggerTimedFB(STimedFBListEntry paTimerListEntry) {
  mDeviceExecution.startNewEventChain(paTimerListEntry.mTimedFB);
  if(paTimerListEntry.mInterval != scmOneShotIndicator){
      paTimerListEntry.mTimeOut = mForteTime + paTimerListEntry.mInterval;  // the next activation time of this FB
      addTimedFBEntry(paTimerListEntry); //re-register the timed FB
  }
}

void CTimerHandler::processAddList() {
  CCriticalRegion criticalRegion(mAddListSync);
  for (auto entry : mAddFBList) {
	  if(entry.mTimeOut < mForteTime) {
		  triggerTimedFB(entry);
	  } else {
	    addTimedFBEntry(entry);
	  }
  }
  mAddFBList.clear();
}

void CTimerHandler::processRemoveList() {
  CCriticalRegion criticalRegion(mRemoveListSync);
  std::for_each(mRemoveFBList.begin(), mRemoveFBList.end(), [this](CEventSourceFB *event) { removeTimedFB(event);} );
  mRemoveFBList.clear();
}
