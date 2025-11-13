/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_PLATFORM_PLATFORM_HELPER_LINUX_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_PLATFORM_PLATFORM_HELPER_LINUX_H_

#include "qorai/components/qorai_ads/core/internal/common/platform/platform_helper.h"

#include <string>

#include "base/no_destructor.h"

namespace qorai_ads {

class PlatformHelperLinux final : public PlatformHelper {
 protected:
  friend class base::NoDestructor<PlatformHelperLinux>;

  PlatformHelperLinux();

 private:
  // PlatformHelper:
  bool IsMobile() const override;
  std::string GetName() const override;
  PlatformType GetType() const override;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_PLATFORM_PLATFORM_HELPER_LINUX_H_
