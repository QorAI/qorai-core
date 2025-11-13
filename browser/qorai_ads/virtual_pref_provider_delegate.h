/* Copyright (c) 2025 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_ADS_VIRTUAL_PREF_PROVIDER_DELEGATE_H_
#define QORAI_BROWSER_QORAI_ADS_VIRTUAL_PREF_PROVIDER_DELEGATE_H_

#include <string>
#include <string_view>

#include "base/memory/raw_ref.h"
#include "qorai/components/qorai_ads/core/browser/service/virtual_pref_provider.h"

class Profile;

namespace qorai_ads {

class VirtualPrefProviderDelegate : public VirtualPrefProvider::Delegate {
 public:
  explicit VirtualPrefProviderDelegate(Profile& profile);

  VirtualPrefProviderDelegate(const VirtualPrefProviderDelegate&) = delete;
  VirtualPrefProviderDelegate& operator=(const VirtualPrefProviderDelegate&) =
      delete;

  ~VirtualPrefProviderDelegate() override;

  std::string_view GetChannel() const override;

  std::string GetDefaultSearchEngineName() const override;

 private:
  const raw_ref<Profile> profile_;
};

}  // namespace qorai_ads

#endif  // QORAI_BROWSER_QORAI_ADS_VIRTUAL_PREF_PROVIDER_DELEGATE_H_
