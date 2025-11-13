/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_QORAI_ADS_VIRTUAL_PREF_PROVIDER_DELEGATE_IOS_H_
#define QORAI_IOS_BROWSER_QORAI_ADS_VIRTUAL_PREF_PROVIDER_DELEGATE_IOS_H_

#include <string>
#include <string_view>

#include "base/memory/raw_ref.h"
#include "qorai/components/qorai_ads/core/browser/service/virtual_pref_provider.h"

class ProfileIOS;

namespace qorai_ads {

class VirtualPrefProviderDelegateIOS : public VirtualPrefProvider::Delegate {
 public:
  explicit VirtualPrefProviderDelegateIOS(ProfileIOS& profile);

  VirtualPrefProviderDelegateIOS(const VirtualPrefProviderDelegateIOS&) =
      delete;
  VirtualPrefProviderDelegateIOS& operator=(
      const VirtualPrefProviderDelegateIOS&) = delete;

  ~VirtualPrefProviderDelegateIOS() override;

  std::string_view GetChannel() const override;

  std::string GetDefaultSearchEngineName() const override;

 private:
  const raw_ref<ProfileIOS> profile_;
};

}  // namespace qorai_ads

#endif  // QORAI_IOS_BROWSER_QORAI_ADS_VIRTUAL_PREF_PROVIDER_DELEGATE_IOS_H_
