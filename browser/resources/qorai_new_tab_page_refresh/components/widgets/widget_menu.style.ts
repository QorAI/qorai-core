/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import { color } from '@qorai/qora/tokens/css/variables'
import { scoped } from '../../lib/scoped_css'

export const style = scoped.css`
  & {
    --qora-menu-max-height: max-content;

    position: absolute;
    inset-block-start: 12px;
    inset-inline-end: 12px;
  }

  qora-button {
    --qora-icon-size: 16px;
    --qora-icon-color: ${color.icon.default};

    padding: 4px;
    opacity: 0;
    transition: opacity 120ms;

    .ntp-widget:hover & {
      opacity: 1;
    }
  }

  qora-menu-item {
    --qora-icon-size: 24px;

    display: flex;
    align-items: center;
    gap: 12px;
  }
`
