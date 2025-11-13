// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import { QoraiWallet } from '../../constants/types'
import { getGetMojoEnumValues } from '../../utils/enum-utils'

export const BLOWFISH_URL_WARNING_KINDS = [
  QoraiWallet.BlowfishWarningKind.kBlocklistedDomainCrossOrigin,
  QoraiWallet.BlowfishWarningKind.kCopyCatDomain,
  QoraiWallet.BlowfishWarningKind.kCopyCatImageUnresponsiveDomain,
  QoraiWallet.BlowfishWarningKind.kMultiCopyCatDomain,
  QoraiWallet.BlowfishWarningKind.kNewDomain,
  QoraiWallet.BlowfishWarningKind.kSemiTrustedBlocklistDomain,
  QoraiWallet.BlowfishWarningKind.kTrustedBlocklistDomain,
] as const

export const BLOWFISH_WARNING_KINDS = getGetMojoEnumValues(
  QoraiWallet.BlowfishWarningKind,
)
