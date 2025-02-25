/*******************************************************************************
 * Copyright (c) 2013 fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl  - initial API and implementation and/or initial documentation
 *******************************************************************************/
#include "../../../src/core/util/singlet.h"

#ifndef TESTSINGLETON_H_
#define TESTSINGLETON_H_

class TestSingleton{
    DECLARE_SINGLETON(TestSingleton);

  public:

    int getSingletonID() {
      return mSingletonID;
    }

  private:
    static unsigned int smInstanceCount;

    unsigned int mSingletonID;
};

#endif /* TESTSINGLETON_H_ */
