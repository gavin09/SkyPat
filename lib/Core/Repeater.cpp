//===- Repeater.cpp --------------------------------------------------------===//
//
//                     The SkyPat Team
//
// This file is distributed under the New BSD License. 
// See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#include <skypat/skypat.h>

using namespace skypat;

//===----------------------------------------------------------------------===//
// Repeater
//===----------------------------------------------------------------------===//
testing::Repeater::Repeater()
  : m_bForward(true) {
}

testing::Repeater::~Repeater()
{
  // Do nothing. Since we arn't the owner of Listeners.
}

void testing::Repeater::add(Listener* pListener)
{
  if (NULL != pListener) {
    m_Listeners.push_back(pListener);
  }
}

void testing::Repeater::release(Listener& pListener)
{
  ListenerList::iterator listener, lEnd = m_Listeners.end();
  for (listener = m_Listeners.begin(); listener != lEnd; ++listener) {
    if (*listener == &pListener) {
      m_Listeners.erase(listener);
      return;
    }
  }
}

#define SKYPAT_REPEATER_METHOD(Name, ParamType) \
void testing::Repeater::Name(const ParamType& pParam) { \
  if (m_bForward) { \
    ListenerList::iterator listener, lEnd = m_Listeners.end(); \
    for (listener = m_Listeners.begin(); listener != lEnd; ++listener) { \
      (*listener)->Name(pParam); \
    } \
  } \
}

SKYPAT_REPEATER_METHOD(OnTestProgramStart, testing::UnitTest)
SKYPAT_REPEATER_METHOD(OnTestCaseStart, TestCase)
SKYPAT_REPEATER_METHOD(OnSetUpStart, UnitTest)
SKYPAT_REPEATER_METHOD(OnSetUpEnd, UnitTest)
SKYPAT_REPEATER_METHOD(OnTestStart, TestInfo)
SKYPAT_REPEATER_METHOD(OnTestPartResult, TestPartResult)
SKYPAT_REPEATER_METHOD(OnPerfPartResult, PerfPartResult)
SKYPAT_REPEATER_METHOD(OnTestEnd, TestInfo)
SKYPAT_REPEATER_METHOD(OnTearDownStart, UnitTest)
SKYPAT_REPEATER_METHOD(OnTearDownEnd, UnitTest)
SKYPAT_REPEATER_METHOD(OnTestCaseEnd, TestCase)
SKYPAT_REPEATER_METHOD(OnTestProgramEnd, UnitTest)
