/* Copyright 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/utility/importer/qorai_external_process_importer_bridge.h"

#include <utility>

QoraiExternalProcessImporterBridge::QoraiExternalProcessImporterBridge(
    const base::flat_map<uint32_t, std::string>& localized_strings,
    mojo::SharedRemote<chrome::mojom::ProfileImportObserver> observer,
    mojo::SharedRemote<qorai::mojom::ProfileImportObserver> qorai_observer)
    : ExternalProcessImporterBridge(std::move(localized_strings),
                                         std::move(observer)),
      qorai_observer_(std::move(qorai_observer)) {}

QoraiExternalProcessImporterBridge::
    ~QoraiExternalProcessImporterBridge() = default;

void QoraiExternalProcessImporterBridge::SetCreditCard(
    const std::u16string& name_on_card,
    const std::u16string& expiration_month,
    const std::u16string& expiration_year,
    const std::u16string& decrypted_card_number,
    const std::string& origin) {
  qorai_observer_->OnCreditCardImportReady(
      name_on_card, expiration_month,
      expiration_year, decrypted_card_number,
      origin);
}
