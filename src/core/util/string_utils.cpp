/*******************************************************************************
 * Copyright (c) 2013, 2025 fortiss GmbH, Johannes Kepler University Linz
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl - initial API and implementation and/or initial documentation
 *******************************************************************************/
#include "string_utils.h"
#include <forte_dint.h>
#include <forte_udint.h>
#include <forte_lint.h>
#include <forte_ulint.h>
#include "../../arch/devlog.h"

#include <errno.h>
#include <string.h>
#include <array>
#include <map>

const auto scCharacters2Escape = std::array { '"', '\'', '&', '<', '>' };
const auto scEscapeSequences  = std::array { "&quot;", "&apos;", "&amp;", "&lt;", "&gt;" };

static_assert(scCharacters2Escape.size() == scEscapeSequences.size());

const std::map<char, const char*> scEscapeMap = {
    {scCharacters2Escape[0], scEscapeSequences[0]},
    {scCharacters2Escape[1], scEscapeSequences[1]},
    {scCharacters2Escape[2], scEscapeSequences[2]},
    {scCharacters2Escape[3], scEscapeSequences[3]},
    {scCharacters2Escape[4], scEscapeSequences[4]}
};

bool forte::core::util::isAtoFChar(char paValue){
  paValue = static_cast<char>(toupper(paValue));
  return ((paValue >= 'A') && (paValue <= 'F'));
}

TForteInt8 forte::core::util::charAtoFToInt(char paValue){
  return static_cast<TForteInt8>((toupper(paValue) - 'A') + 10);
}

long int forte::core::util::strtol(const char *nptr, char **endptr, int base) {
  long int nRetVal = 0;
  bool bNegativeNumber = false;
  errno = 0;

  //in difference to IEC 611313-3 literals base 16 literals may have a leading -
  if((*nptr) == '-'){
    bNegativeNumber = true;
    ++nptr;
  }

  if(16 == base && (('0' == (*nptr)) && ('x' == nptr[1]))){
    //we have a preceding 0x step over it
    nptr += 2;
  }

  long nLimit1 = (bNegativeNumber ? -(std::numeric_limits<CIEC_DINT::TValueType>::min() / base) : (std::numeric_limits<CIEC_DINT::TValueType>::max() / base));
  long nLimit2 = (bNegativeNumber ? -(std::numeric_limits<CIEC_DINT::TValueType>::min() % base) : (std::numeric_limits<CIEC_DINT::TValueType>::max() % base));
  if (nLimit2 < 0) // Rounding direction for negative numbers is implementation defined
  {
    nLimit1--;
    nLimit2 = base-nLimit2;
  }

  for(; *nptr; ++nptr){ //Do until '/0'
    if((!isDigit(*nptr)) && (!((16 == base) && isAtoFChar(*nptr)))){
      //we have an invalid character
      break;
    }
    TForteInt8 nCharVal = charHexDigitToInt(*nptr);
    if(nRetVal > nLimit1 || (nRetVal == nLimit1 && nCharVal > nLimit2)) {
      nRetVal = (bNegativeNumber) ? std::numeric_limits<CIEC_DINT::TValueType>::min() : std::numeric_limits<CIEC_DINT::TValueType>::max();
      errno = ERANGE;
      break;
    }
    nRetVal = base * nRetVal + nCharVal;
  }

  if((bNegativeNumber) && (ERANGE != errno)){
    nRetVal = -nRetVal;
  }

  if(nullptr != endptr){
    *endptr = const_cast<char*>(nptr);
  }
  return nRetVal;
}

unsigned long int forte::core::util::strtoul(const char *nptr, char **endptr, int base){
  unsigned long int unRetVal = 0;
  unsigned long int unLimit1 = (std::numeric_limits<CIEC_UDINT::TValueType>::max() / base);
  unsigned long int unLimit2 = (std::numeric_limits<CIEC_UDINT::TValueType>::max() % base);
  errno = 0;

  if((16 == base) && ('0' == (*nptr)) && ('x' == nptr[1])){
    //we have a preceding 0x step over it
    nptr += 2;
  }

  for(; *nptr; ++nptr){ //Do until '/0'
    if((!isDigit(*nptr)) && (!((16 == base) && isAtoFChar(*nptr)))){
      //we have an invalid character
      break;
    }
    TForteInt8 nCharVal = charHexDigitToInt(*nptr);

    if(unRetVal > unLimit1 || (unRetVal == unLimit1 && (unsigned long int) nCharVal > unLimit2)){
      //in this round we would exceed the limit of the data type
      unRetVal = std::numeric_limits<CIEC_UDINT::TValueType>::max();
      errno = ERANGE;
      break;
    }
    unRetVal = base * unRetVal + nCharVal;
  }
  if(nullptr != endptr){
    *endptr = const_cast<char*>(nptr);
  }
  return unRetVal;
}

long long int forte::core::util::strtoll(const char *nptr, char **endptr, int base) {
  long long int nRetVal = 0;
  bool bNegativeNumber = false;
  errno = 0;

  //in difference to IEC 611313-3 literals base 16 literals may have a leading -
  if((*nptr) == '-'){
    bNegativeNumber = true;
    ++nptr;
  }

  if(16 == base && ('0' == (*nptr)) && ('x' == nptr[1])){
    //we have a preceding 0x step over it
    nptr += 2;
  }

  long long nLimit1;
  long long nLimit2;

  if (bNegativeNumber){
    volatile long long nLimMinDiv = std::numeric_limits<CIEC_LINT::TValueType>::min() / base;
    volatile long long nLimMinMod = std::numeric_limits<CIEC_LINT::TValueType>::min() % base;

    nLimit1 = -nLimMinDiv;
    nLimit2 = -nLimMinMod;

    if (nLimit2 < 0) // Rounding direction for negative numbers is implementation defined
    {
      nLimit1--;
      nLimit2 = base-nLimit2;
    }
  }
  else{
    nLimit1 = std::numeric_limits<CIEC_LINT::TValueType>::max() / base;
    nLimit2 = std::numeric_limits<CIEC_LINT::TValueType>::max() % base;
  }

  for(; *nptr; ++nptr){ //Do until '/0'
    if((!isDigit(*nptr)) && (!((16 == base) && isAtoFChar(*nptr)))){
      //we have an invalid character
      break;
    }
    TForteInt8 nCharVal = charHexDigitToInt(*nptr);
    if(nRetVal > nLimit1 || (nRetVal == nLimit1 && nCharVal > nLimit2)){
      nRetVal = (bNegativeNumber) ? std::numeric_limits<CIEC_LINT::TValueType>::min() : std::numeric_limits<CIEC_LINT::TValueType>::max();
      errno = ERANGE;
      break;
    }
    nRetVal = base * nRetVal + nCharVal;
  }

  if((bNegativeNumber) && (ERANGE != errno)){
    nRetVal = -nRetVal;
  }
  if(nullptr != endptr){
    *endptr = const_cast<char*>(nptr);
  }
  return nRetVal;
}

unsigned long long int forte::core::util::strtoull(const char *nptr, char **endptr, int base){
  unsigned long long int unRetVal = 0;
  unsigned long long int unLimit1 = (std::numeric_limits<CIEC_ULINT::TValueType>::max() / base);
  unsigned long long int unLimit2 = (std::numeric_limits<CIEC_ULINT::TValueType>::max() % base);
  errno = 0;

  if((16 == base) && ('0' == (*nptr)) && ('x' == nptr[1])){
    //we have a preceding 0x step over it
    nptr += 2;
  }

  for(; *nptr; ++nptr){ //Do until '/0'
    if((!isDigit(*nptr)) && (!((16 == base) && isAtoFChar(*nptr)))){
      //we have an invalid character
      break;
    }
    TForteInt8 nCharVal = charHexDigitToInt(*nptr);
    if(unRetVal > unLimit1 || (unRetVal == unLimit1 && (unsigned long long int) nCharVal > unLimit2)){
      //in this round we would exceed the limit of the data type
      unRetVal = std::numeric_limits<CIEC_ULINT::TValueType>::max();
      errno = ERANGE;
      break;
    }
    unRetVal = base * unRetVal + nCharVal;
  }
  if(nullptr != endptr){
    *endptr = const_cast<char*>(nptr);
  }
  return unRetVal;
}

size_t forte::core::util::getExtraSizeForXMLEscapedChars(const char* paString){
  size_t retVal = 0;
  while(0 != *paString){
    auto escapeChar = scEscapeMap.find(*paString);
    if(escapeChar != scEscapeMap.end()){
      retVal += strlen(escapeChar->second) - 1;
    }
    paString++;
  }
  return retVal;
}

size_t forte::core::util::transformNonEscapedToEscapedXMLText(char* const paString){
  size_t retVal = 0;
  char* runner = strchr(paString, '\0');
  char* originalEnd = runner;
  runner--;
  while(paString <= runner){
    auto escapeChar = scEscapeMap.find(*runner);
    if(escapeChar != scEscapeMap.end()){
      size_t toMove = strlen(escapeChar->second);
      memmove(&runner[toMove], runner + 1, originalEnd - runner + retVal);
      memcpy(runner, escapeChar->second, toMove);
      retVal += toMove - 1;
    }
    runner--;
  }
  return retVal;
}

size_t forte::core::util::transformEscapedXMLToNonEscapedText(char* const paString){
  char* runner = paString;
  char *endRunner = strchr(paString, '\0');
  size_t retVal = 0;
  while(runner <= endRunner){
    if('&' == *runner){
      char toCopy = 0;
      size_t toMove = 0;

      for(size_t i = 0; i < scEscapeSequences.size(); i++){
        if(0 == strncmp(runner, scEscapeSequences[i], strlen(scEscapeSequences[i]))){
          toCopy = scCharacters2Escape[i];
          toMove = strlen(scEscapeSequences[i]);
          break;
        }
      }

      if(0 != toCopy){
        *runner = toCopy;
        memmove(runner + 1, &runner[toMove], (endRunner - &runner[toMove]) + 1);
        endRunner -= toMove - 1;
        retVal += toMove - 1;
      }
      else{
        DEVLOG_ERROR("[XML Transformer] The given XML text has & character but it's none of the known escaped characters");
      }
    }
    runner++;
  }
  return retVal;
}

char * forte::core::util::lookForNonEscapedChar(char **paString, char paChar, char paEscapingChar) {
  char *foundChar = nullptr;
  char* initialPosition = *paString;
  while(!foundChar && '\0' != **paString) {
    foundChar = strchr(*paString, paChar);
    if(nullptr != foundChar) {
      *paString = foundChar;
      if(isEscaped(foundChar, initialPosition, paEscapingChar)) {
        while('\0' != *foundChar) { //move the rest of the string one char back
          *(foundChar - 1) = *foundChar;
          foundChar++;
        }
        *(foundChar - 1) = *foundChar; //move also the ending \0
        foundChar = nullptr; //reset to keep looking
      } else {
        *foundChar = '\0';
        (*paString)++;
      }
    } else { //there's no paChar in the string
      break;
    }
  }
  return foundChar;
}

bool forte::core::util::isEscaped(char *paChar, char *paBeginLimit, char paEscapingChar) {
  size_t noOfScapingSigns = 0;
  while(paBeginLimit != paChar) { //count the amount of \ signs before paChar to know if the \ signs was also escaped.
    paChar--;
    if(paEscapingChar == *paChar) {
      noOfScapingSigns++;
    } else {
      break;
    }
  }

  return (noOfScapingSigns % 2); //an even number of \ (or zero) means paChar was not escaped
}

void forte::core::util::removeEscapedSigns(char **paString, char paEscapingChar) {
  char *runner = *paString;
  while('\0' != *runner) {
    if(paEscapingChar == *runner && paEscapingChar == *(runner + 1)) {
      char *copier = runner + 1;
      while('\0' != *copier) {
        *(copier - 1) = *copier;
        copier++;
      }
      *(copier - 1) = *copier; //move also the ending \0
    }
    runner++;
  }
}
