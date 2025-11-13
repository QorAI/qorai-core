/* Copyright 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_P3A_P3A_CORE_METRICS_H_
#define QORAI_BROWSER_P3A_P3A_CORE_METRICS_H_

// The class below can be used on desktop only
// because BrowserListObserver is available on desktop only
// Qorai.Core.LastTimeIncognitoUsed and
// Qorai.Core.TorEverUsed don't work on Android

#include "build/build_config.h"

#if BUILDFLAG(IS_ANDROID)
#error This file should only be included on desktop.
#endif

#include "base/memory/raw_ptr.h"
#include "base/timer/timer.h"
#include "chrome/browser/ui/browser_list_observer.h"

class PrefService;
class PrefRegistrySimple;

namespace qorai {

// QoraiWindowTracker is under !OS_ANDROID guard because
// BrowserListObserver should only be only on desktop
// Qorai.Uptime.BrowserOpenMinutes and Qorai.Core.LastTimeIncognitoUsed
// don't work on Android
#if !BUILDFLAG(IS_ANDROID)
// Periodically records P3A stats (extracted from Local State) regarding the
// time when incognito windows were used.
// Used as a leaking singletone.
class QoraiWindowTracker : public BrowserListObserver {
 public:
  explicit QoraiWindowTracker(PrefService* local_state);
  QoraiWindowTracker(const QoraiWindowTracker&) = delete;
  QoraiWindowTracker& operator=(const QoraiWindowTracker&) = delete;
  ~QoraiWindowTracker() override;

  static void CreateInstance(PrefService* local_state);

  static void RegisterPrefs(PrefRegistrySimple* registry);

 private:
  // BrowserListObserver:
  void OnBrowserAdded(Browser* browser) override;
  void OnBrowserSetLastActive(Browser* browser) override;

  void UpdateP3AValues() const;

  base::RepeatingTimer timer_;
  raw_ptr<PrefService, DanglingUntriaged> local_state_ = nullptr;
};
#endif  // !BUILDFLAG(IS_ANDROID)

}  // namespace qorai

#endif  // QORAI_BROWSER_P3A_P3A_CORE_METRICS_H_
