/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_SIGNIN_INTERNAL_IDENTITY_MANAGER_QORAI_MUTABLE_PROFILE_OAUTH2_TOKEN_SERVICE_DELEGATE_H_
#define QORAI_COMPONENTS_SIGNIN_INTERNAL_IDENTITY_MANAGER_QORAI_MUTABLE_PROFILE_OAUTH2_TOKEN_SERVICE_DELEGATE_H_

#include <memory>

#include "base/memory/raw_ptr.h"
#include "components/signin/internal/identity_manager/mutable_profile_oauth2_token_service_delegate.h"

class QoraiMutableProfileOAuth2TokenServiceDelegate
    : public MutableProfileOAuth2TokenServiceDelegate {
 public:
  QoraiMutableProfileOAuth2TokenServiceDelegate(
      SigninClient* client,
      AccountTrackerService* account_tracker_service,
      network::NetworkConnectionTracker* network_connection_tracker,
      scoped_refptr<TokenWebData> token_web_data,
      signin::AccountConsistencyMethod account_consistency,
      RevokeAllTokensOnLoad revoke_all_tokens_on_load,
      std::unique_ptr<TokenBindingHelper> token_binding_helper,
      FixRequestErrorCallback fix_request_error_callback);
  ~QoraiMutableProfileOAuth2TokenServiceDelegate() override;
  QoraiMutableProfileOAuth2TokenServiceDelegate(
      const QoraiMutableProfileOAuth2TokenServiceDelegate&) = delete;
  QoraiMutableProfileOAuth2TokenServiceDelegate& operator=(
      const QoraiMutableProfileOAuth2TokenServiceDelegate&) = delete;

  void LoadCredentialsInternal(
      const CoreAccountId& primary_account_id) override;

 private:
  raw_ptr<AccountTrackerService> account_tracker_service_ = nullptr;
};

#endif  // QORAI_COMPONENTS_SIGNIN_INTERNAL_IDENTITY_MANAGER_QORAI_MUTABLE_PROFILE_OAUTH2_TOKEN_SERVICE_DELEGATE_H_
