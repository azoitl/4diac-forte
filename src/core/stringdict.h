/*******************************************************************************
 * Copyright (c) 2008, 2023 nxtControl GmbH, ACIN, fortiss GmbH,
 *                          Martin Erich Jobst
 *               2025 Jörg Walter
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Stanislav Meduna, Alois Zoitl
 *      - initial implementation and rework communication infrastructure
 *    Martin Jobst
 *      - add string functions accepting a size parameter
 *    Jörg Walter
 *      - rework to use std::vector/inplace_vecctor
 *******************************************************************************/
#ifndef _CStringDictionary_H_
#define _CStringDictionary_H_

#include "forte_config.h"
#include "core/util/singlet.h"
#include "datatype.h"

#include <limits>

/**\ingroup CORE\brief Manages a dictionary of strings that can be referenced by ids
 *
 * Manages a dictionary of strings that can be referenced by ids
 */
// cppcheck-suppress noConstructor
class CStringDictionary{
  DECLARE_SINGLETON(CStringDictionary)
public:
  typedef size_t TStringId;

  //!\brief Invalid string id
  static const TStringId scmInvalidStringId = std::numeric_limits<TStringId>::max();


  /*!\brief Get a string from the dictionary
   *
   * \param paId String id
   * \return the found string or 0 if not found
   */
  const char *get(TStringId paId);

  /*!\brief Insert a string into the dictionary
   *
   * \param paStr String to be inserted
   * \return id of the inserted string (or the existing one if the dictionary already has it)
   */
  TStringId insert(const char *paStr);

  /*!\brief Insert a string into the dictionary
   *
   * \param paStr String to be searched for (need not be '\0' terminated)
   * \param paStrSize Size of the string (excluding any terminating '\0' character)
   * \return id of the inserted string (or the existing one if the dictionary already has it)
   */
  TStringId insert(const char *paStr, size_t paStrSize);

  /*!\brief Retrieve the Id of a given string if it is already in the dictionary
   *
   * \param paStr String to be searched for
   * \return id of the string (or scmInvalidStringId if it is not in the dictionary)
   */
  TStringId getId(const char *paStr) const;

  /*!\brief Retrieve the Id of a given string if it is already in the dictionary
   *
   * \param paStr String to be searched for (need not be '\0' terminated)
   * \param paStrSize Size of the string (excluding any terminating '\0' character)
   * \return id of the string (or scmInvalidStringId if it is not in the dictionary)
   */
  TStringId getId(const char *paStr, size_t paStrSize) const;

private:
  // Find an exact match or place to be the new index
  TStringId findEntry(const char *paStr, size_t paStrSize, unsigned int &paIdx) const;
};

#endif // _CStringDictionary_H_
