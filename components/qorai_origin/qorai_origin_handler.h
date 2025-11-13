/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ORIGIN_QORAI_ORIGIN_HANDLER_H_
#define QORAI_COMPONENTS_QORAI_ORIGIN_QORAI_ORIGIN_HANDLER_H_

#include "qorai/components/qorai_origin/common/mojom/qorai_origin_settings.mojom.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/receiver.h"

namespace qorai_origin {
class QoraiOriginService;

class QoraiOriginSettingsHandlerImpl
    : public mojom::QoraiOriginSettingsHandler {
 public:
  explicit QoraiOriginSettingsHandlerImpl(
      QoraiOriginService* qorai_origin_service);
  ~QoraiOriginSettingsHandlerImpl() override;

  QoraiOriginSettingsHandlerImpl(const QoraiOriginSettingsHandlerImpl&) =
      delete;
  QoraiOriginSettingsHandlerImpl& operator=(
      const QoraiOriginSettingsHandlerImpl&) = delete;

  void BindInterface(
      mojo::PendingReceiver<mojom::QoraiOriginSettingsHandler> receiver);

  // mojom::QoraiOriginSettingsHandler:
  void IsQoraiOriginUser(IsQoraiOriginUserCallback callback) override;
  void IsPolicyControlledByQoraiOrigin(
      const std::string& policy_key,
      IsPolicyControlledByQoraiOriginCallback callback) override;
  void GetPolicyValue(const std::string& policy_key,
                      GetPolicyValueCallback callback) override;
  void SetPolicyValue(const std::string& policy_key,
                      bool value,
                      SetPolicyValueCallback callback) override;

 private:
  raw_ptr<QoraiOriginService> qorai_origin_service_;
  mojo::Receiver<mojom::QoraiOriginSettingsHandler> receiver_{this};
};

}  // namespace qorai_origin

#endif  // QORAI_COMPONENTS_QORAI_ORIGIN_QORAI_ORIGIN_HANDLER_H_
