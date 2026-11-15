/*******************************************************************************
 * Copyright (c) 2026 Thomas Oellinger
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Thomas Oellinger - initial implementation
 *******************************************************************************/

#include "forte/io/mapper/io_mapper.h"
#include "forte/io/mapper/io_handle.h"
#include "forte/io/mapper/io_observer.h"
#include "forte/io/device/io_controller.h"

#include "../fbtests/fbtesterglobalfixture.h"

#include <boost/test/unit_test.hpp>

namespace forte::io::test {

  namespace {
    //! Controller that is never started; IOHandle only needs it as a reference.
    class StubController : public IODeviceController {
      public:
        StubController() : IODeviceController(forte::test::CFBTestDataGlobalFixture::getDevice().getDeviceExecution()) {
        }

        void setConfig(Config *) override {
        }

      protected:
        const char *init() override {
          return nullptr;
        }
        void runLoop() override {
        }
        void deInit() override {
        }
        IOHandle *createIOHandle(HandleDescriptor &) override {
          return nullptr;
        }
    };

    class StubHandle : public IOHandle {
      public:
        explicit StubHandle(IODeviceController &paController) : IOHandle(paController, IOMapper::In, CIEC_ANY::e_BOOL) {
        }

        void set(const CIEC_ANY &) override {
        }
        void get(CIEC_ANY &) override {
        }
    };

    //! Counts the mapper callbacks; onChange() returns false so no indication event is fired.
    class CountingObserver : public IOObserver {
      public:
        int mChanges = 0;
        int mConnects = 0;
        int mDrops = 0;

        bool onChange() override {
          ++mChanges;
          return false;
        }
        CIEC_ANY::EDataTypeID getIOObserverDataType() const override {
          return CIEC_ANY::e_BOOL;
        }
        IOMapper::Direction getDirection() const override {
          return IOMapper::In;
        }

      protected:
        void onHandle() override {
          ++mConnects;
        }
        void dropHandle() override {
          ++mDrops;
        }
    };
  } // namespace

  BOOST_AUTO_TEST_SUITE(IOMapperTests)

  BOOST_AUTO_TEST_CASE(observerRegisteredBeforeHandleIsConnectedWhenHandleArrives) {
    constexpr std::string_view scId = "iomappertest.observerfirst";
    StubController controller;
    StubHandle handle(controller);
    CountingObserver observer;
    IOMapper &mapper = IOMapper::getInstance();

    BOOST_TEST(mapper.registerObserver(scId, observer));
    BOOST_TEST(observer.getHandle() == nullptr);
    BOOST_TEST(observer.mConnects == 0);

    BOOST_TEST(mapper.registerHandle(scId, handle));
    BOOST_TEST(observer.mConnects == 1);
    BOOST_TEST(observer.getHandle() == &handle);
    BOOST_TEST(handle.hasObserver());

    handle.onChange();
    BOOST_TEST(observer.mChanges == 1);

    mapper.deregisterObserver(observer);
    BOOST_TEST(observer.getHandle() == nullptr);
    BOOST_TEST(!handle.hasObserver());
    mapper.deregisterHandle(handle);
    BOOST_TEST(!handle.isBound());
  }

  BOOST_AUTO_TEST_CASE(observerDeregisteredBeforeHandleLeavesNoStaleEntry) {
    constexpr std::string_view scId = "iomappertest.observerleft";
    StubController controller;
    StubHandle handle(controller);
    CountingObserver observer;
    IOMapper &mapper = IOMapper::getInstance();

    BOOST_TEST(mapper.registerObserver(scId, observer));
    mapper.deregisterObserver(observer);

    // a stale entry would be called back here although the observer is gone
    BOOST_TEST(mapper.registerHandle(scId, handle));
    BOOST_TEST(observer.mConnects == 0);
    BOOST_TEST(!handle.hasObserver());

    mapper.deregisterHandle(handle);
  }

  BOOST_AUTO_TEST_CASE(observerRegisteredBeforeHandleIsDroppedWithHandle) {
    constexpr std::string_view scId = "iomappertest.handledropped";
    StubController controller;
    StubHandle handle(controller);
    CountingObserver observer;
    IOMapper &mapper = IOMapper::getInstance();

    BOOST_TEST(mapper.registerObserver(scId, observer));
    BOOST_TEST(mapper.registerHandle(scId, handle));
    mapper.deregisterHandle(handle);
    BOOST_TEST(observer.mDrops == 1);
    BOOST_TEST(observer.getHandle() == nullptr);

    // the observer stays registered and is connected again by the next handle
    StubHandle secondHandle(controller);
    BOOST_TEST(mapper.registerHandle(scId, secondHandle));
    BOOST_TEST(observer.mConnects == 2);
    BOOST_TEST(observer.getHandle() == &secondHandle);

    mapper.deregisterObserver(observer);
    mapper.deregisterHandle(secondHandle);
  }

  BOOST_AUTO_TEST_SUITE_END()

} // namespace forte::io::test
