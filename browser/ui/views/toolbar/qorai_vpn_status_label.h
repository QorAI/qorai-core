/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_TOOLBAR_QORAI_VPN_STATUS_LABEL_H_
#define QORAI_BROWSER_UI_VIEWS_TOOLBAR_QORAI_VPN_STATUS_LABEL_H_

#include "base/memory/raw_ptr.h"
#include "qorai/components/qorai_vpn/browser/qorai_vpn_service_observer.h"
#include "ui/base/metadata/metadata_header_macros.h"
#include "ui/views/controls/label.h"

namespace qorai_vpn {
class QoraiVpnService;
}  // namespace qorai_vpn

class Browser;

class QoraiVPNStatusLabel : public views::Label,
                            public qorai_vpn::QoraiVPNServiceObserver {
  METADATA_HEADER(QoraiVPNStatusLabel, views::Label)
 public:
  explicit QoraiVPNStatusLabel(Browser* browser);
  ~QoraiVPNStatusLabel() override;

  QoraiVPNStatusLabel(const QoraiVPNStatusLabel&) = delete;
  QoraiVPNStatusLabel& operator=(const QoraiVPNStatusLabel&) = delete;

 private:
  // qorai_vpn::QoraiVPNServiceObserver overrides:
  void OnConnectionStateChanged(
      qorai_vpn::mojom::ConnectionState state) override;

  void UpdateState();

  int longest_state_string_id_ = -1;
  raw_ptr<Browser> browser_ = nullptr;
  raw_ptr<qorai_vpn::QoraiVpnService> service_ = nullptr;
};

#endif  // QORAI_BROWSER_UI_VIEWS_TOOLBAR_QORAI_VPN_STATUS_LABEL_H_
