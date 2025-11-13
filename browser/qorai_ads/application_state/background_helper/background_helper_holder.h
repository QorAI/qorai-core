/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_ADS_APPLICATION_STATE_BACKGROUND_HELPER_BACKGROUND_HELPER_HOLDER_H_
#define QORAI_BROWSER_QORAI_ADS_APPLICATION_STATE_BACKGROUND_HELPER_BACKGROUND_HELPER_HOLDER_H_

#include <memory>

namespace base {
template <typename T>
class NoDestructor;
}  // namespace base

namespace qorai_ads {

class BackgroundHelper;

class BackgroundHelperHolder final {
 public:
  BackgroundHelperHolder(const BackgroundHelperHolder&) = delete;
  BackgroundHelperHolder& operator=(const BackgroundHelperHolder&) = delete;

  static BackgroundHelperHolder* GetInstance();

  BackgroundHelper* GetBackgroundHelper();

 private:
  friend base::NoDestructor<BackgroundHelperHolder>;

  BackgroundHelperHolder();

  ~BackgroundHelperHolder();

  std::unique_ptr<BackgroundHelper> background_helper_;
};

}  // namespace qorai_ads

#endif  // QORAI_BROWSER_QORAI_ADS_APPLICATION_STATE_BACKGROUND_HELPER_BACKGROUND_HELPER_HOLDER_H_
