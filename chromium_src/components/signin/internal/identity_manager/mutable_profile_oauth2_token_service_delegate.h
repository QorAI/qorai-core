/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_SIGNIN_INTERNAL_IDENTITY_MANAGER_MUTABLE_PROFILE_OAUTH2_TOKEN_SERVICE_DELEGATE_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_SIGNIN_INTERNAL_IDENTITY_MANAGER_MUTABLE_PROFILE_OAUTH2_TOKEN_SERVICE_DELEGATE_H_

#define CancelWebTokenFetch                                   \
  Unused();                                                   \
  friend class QoraiMutableProfileOAuth2TokenServiceDelegate; \
  void CancelWebTokenFetch

#include <components/signin/internal/identity_manager/mutable_profile_oauth2_token_service_delegate.h>  // IWYU pragma: export

#undef CancelWebTokenFetch

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_SIGNIN_INTERNAL_IDENTITY_MANAGER_MUTABLE_PROFILE_OAUTH2_TOKEN_SERVICE_DELEGATE_H_
