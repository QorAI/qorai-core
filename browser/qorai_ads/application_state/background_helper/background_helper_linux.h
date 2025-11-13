/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_ADS_APPLICATION_STATE_BACKGROUND_HELPER_BACKGROUND_HELPER_LINUX_H_
#define QORAI_BROWSER_QORAI_ADS_APPLICATION_STATE_BACKGROUND_HELPER_BACKGROUND_HELPER_LINUX_H_

#include "base/memory/weak_ptr.h"
#include "qorai/components/qorai_ads/browser/application_state/background_helper.h"
#include "chrome/browser/ui/browser_list_observer.h"

namespace qorai_ads {

class BackgroundHelperLinux final : public BackgroundHelper,
                                    public BrowserListObserver {
 public:
  BackgroundHelperLinux(const BackgroundHelperLinux&) = delete;
  BackgroundHelperLinux& operator=(const BackgroundHelperLinux&) = delete;

  ~BackgroundHelperLinux() override;

 protected:
  friend class BackgroundHelperHolder;

  BackgroundHelperLinux();

 private:
  // BrowserListObserver overrides
  void OnBrowserSetLastActive(Browser* browser) override;
  void OnBrowserNoLongerActive(Browser* browser) override;

  // BackgroundHelper:
  bool IsForeground() const override;

  base::WeakPtrFactory<BackgroundHelperLinux> weak_ptr_factory_{this};
};

}  // namespace qorai_ads

#endif  // QORAI_BROWSER_QORAI_ADS_APPLICATION_STATE_BACKGROUND_HELPER_BACKGROUND_HELPER_LINUX_H_
