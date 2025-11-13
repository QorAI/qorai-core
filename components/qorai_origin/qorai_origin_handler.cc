/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_origin/qorai_origin_handler.h"

#include "qorai/components/qorai_origin/qorai_origin_service.h"
#include "qorai/components/qorai_origin/qorai_origin_utils.h"

namespace qorai_origin {

QoraiOriginSettingsHandlerImpl::QoraiOriginSettingsHandlerImpl(
    QoraiOriginService* qorai_origin_service)
    : qorai_origin_service_(qorai_origin_service) {
  CHECK(qorai_origin_service_);
}

QoraiOriginSettingsHandlerImpl::~QoraiOriginSettingsHandlerImpl() = default;

void QoraiOriginSettingsHandlerImpl::BindInterface(
    mojo::PendingReceiver<mojom::QoraiOriginSettingsHandler> receiver) {
  receiver_.reset();
  receiver_.Bind(std::move(receiver));
}

void QoraiOriginSettingsHandlerImpl::IsQoraiOriginUser(
    IsQoraiOriginUserCallback callback) {
  bool is_qorai_origin_user = qorai_origin::IsQoraiOriginEnabled();
  std::move(callback).Run(is_qorai_origin_user);
}

void QoraiOriginSettingsHandlerImpl::IsPolicyControlledByQoraiOrigin(
    const std::string& policy_key,
    IsPolicyControlledByQoraiOriginCallback callback) {
  bool is_controlled =
      qorai_origin_service_->IsPolicyControlledByQoraiOrigin(policy_key);
  std::move(callback).Run(is_controlled);
}

void QoraiOriginSettingsHandlerImpl::GetPolicyValue(
    const std::string& policy_key,
    GetPolicyValueCallback callback) {
  if (!qorai_origin::IsQoraiOriginEnabled()) {
    std::move(callback).Run(std::nullopt);
    return;
  }

  std::optional<bool> value = qorai_origin_service_->GetPolicyValue(policy_key);
  std::move(callback).Run(value);
}

void QoraiOriginSettingsHandlerImpl::SetPolicyValue(
    const std::string& policy_key,
    bool value,
    SetPolicyValueCallback callback) {
  if (!qorai_origin::IsQoraiOriginEnabled()) {
    std::move(callback).Run(false);
    return;
  }

  bool success = qorai_origin_service_->SetPolicyValue(policy_key, value);
  std::move(callback).Run(success);
}

}  // namespace qorai_origin
