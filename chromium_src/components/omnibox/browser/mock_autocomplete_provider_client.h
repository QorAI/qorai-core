// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_OMNIBOX_BROWSER_MOCK_AUTOCOMPLETE_PROVIDER_CLIENT_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_OMNIBOX_BROWSER_MOCK_AUTOCOMPLETE_PROVIDER_CLIENT_H_

#include "components/omnibox/browser/autocomplete_provider_client.h"

#include "qorai/components/commander/common/buildflags/buildflags.h"

#if BUILDFLAG(ENABLE_COMMANDER)
#include "qorai/components/commander/browser/commander_frontend_delegate.h"
#define GetTopSites                                                          \
  GetTopSites_Unused() {                                                     \
    return nullptr;                                                          \
  }                                                                          \
  commander::CommanderFrontendDelegate* GetCommanderDelegate() {             \
    return commander_delegate_.get();                                        \
  }                                                                          \
  void set_commander_delegate(                                               \
      std::unique_ptr<commander::CommanderFrontendDelegate> delegate) {      \
    commander_delegate_ = std::move(delegate);                               \
  }                                                                          \
                                                                             \
 private:                                                                    \
  std::unique_ptr<commander::CommanderFrontendDelegate> commander_delegate_; \
                                                                             \
 public:                                                                     \
  scoped_refptr<history::TopSites> GetTopSites
#endif

#define GetRemoteSuggestionsService                     \
  GetRemoteSuggestionsService_Unused() {                \
    return nullptr;                                     \
  }                                                     \
  void OpenQora(const std::u16string& query) override {} \
  bool IsQoraProviderEnabled() override {                \
    return false;                                       \
  }                                                     \
  RemoteSuggestionsService* GetRemoteSuggestionsService

#include <components/omnibox/browser/mock_autocomplete_provider_client.h>  // IWYU pragma: export

#undef GetRemoteSuggestionsService
#undef GetTopSites

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_OMNIBOX_BROWSER_MOCK_AUTOCOMPLETE_PROVIDER_CLIENT_H_
