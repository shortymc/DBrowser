/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "PerformanceWorker.h"
#include "WorkerPrivate.h"
/*SECLAB*/
#include "../../js/src/vm/Counter.h"
/*SECLAB*/

//SECLAB BEGIN 10/03/2016
#include "../../js/src/vm/Counter.h"
//SECLAB END

namespace mozilla {
namespace dom {

using namespace workers;

PerformanceWorker::PerformanceWorker(WorkerPrivate* aWorkerPrivate)
  : mWorkerPrivate(aWorkerPrivate)
{
  mWorkerPrivate->AssertIsOnWorkerThread();
}

PerformanceWorker::~PerformanceWorker()
{
  mWorkerPrivate->AssertIsOnWorkerThread();
}

DOMHighResTimeStamp
PerformanceWorker::Now() const
{

  //SECLAB BEGIN 10/21/2016
  printf("PerformanceWorker %ld\n", get_counter());
  return get_counter();
  //SECLAB END

  TimeDuration duration =
    TimeStamp::Now() - mWorkerPrivate->NowBaseTimeStamp();
  //return RoundTime(duration.ToMilliseconds());
  /*SECLAB*/
  //printf("PerformanceWorker, %d\n", get_counter());
  return (double)get_counter() / (1e7);
  /*SECLAB*/
}

// To be removed once bug 1124165 lands
bool
PerformanceWorker::IsPerformanceTimingAttribute(const nsAString& aName)
{
  // In workers we just support navigationStart.
  return aName.EqualsASCII("navigationStart");
}

DOMHighResTimeStamp
PerformanceWorker::GetPerformanceTimingFromString(const nsAString& aProperty)
{
  if (!IsPerformanceTimingAttribute(aProperty)) {
    return 0;
  }

  if (aProperty.EqualsLiteral("navigationStart")) {
    return mWorkerPrivate->NowBaseTime();
  }

  MOZ_CRASH("IsPerformanceTimingAttribute and GetPerformanceTimingFromString are out of sync");
  return 0;
}

void
PerformanceWorker::InsertUserEntry(PerformanceEntry* aEntry)
{
  if (mWorkerPrivate->PerformanceLoggingEnabled()) {
    nsAutoCString uri;
    nsCOMPtr<nsIURI> scriptURI = mWorkerPrivate->GetResolvedScriptURI();
    if (!scriptURI || NS_FAILED(scriptURI->GetHost(uri))) {
      // If we have no URI, just put in "none".
      uri.AssignLiteral("none");
    }
    Performance::LogEntry(aEntry, uri);
  }
  Performance::InsertUserEntry(aEntry);
}

TimeStamp
PerformanceWorker::CreationTimeStamp() const
{
  return mWorkerPrivate->NowBaseTimeStamp();
}

DOMHighResTimeStamp
PerformanceWorker::CreationTime() const
{
  return mWorkerPrivate->NowBaseTime();
}

} // dom namespace
} // mozilla namespace
