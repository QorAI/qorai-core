// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as QoraiVPN from 'gen/qorai/components/qorai_vpn/common/mojom/qorai_vpn.mojom.m.js'
// Provide access to all the generated types
export * from 'gen/qorai/components/qorai_vpn/common/mojom/qorai_vpn.mojom.m.js'

export default function getVPNServiceHandler () {
  return QoraiVPN.ServiceHandler.getRemote()
}
