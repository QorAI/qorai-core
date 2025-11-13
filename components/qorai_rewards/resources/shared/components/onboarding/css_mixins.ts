// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as qora from '@qorai/qora/tokens/css/variables'

export const enableRewardsButton = `
  color: ${qora.color.schemes.onPrimary};
  background: ${qora.color.button.background};
  border: none;
  padding: 12px 24px;
  border-radius: 48px;
  font-weight: 600;
  font-size: 13px;
  line-height: 20px;
  cursor: pointer;

  &[disabled] {
    background: ${qora.color.primitive.neutral[70]};
    color: ${qora.color.white};
    cursor: default;

    .qorai-theme-dark & {
      background: ${qora.color.primitive.neutral[40]};
    }
  }
`
