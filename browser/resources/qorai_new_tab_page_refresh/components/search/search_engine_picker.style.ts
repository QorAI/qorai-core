/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import { color, font } from '@qorai/qora/tokens/css/variables'
import { scoped } from '../../lib/scoped_css'

export const style = scoped.css`
  .engine-icon {
    --qora-icon-size: var(--search-engine-icon-size, 16px);
    height: var(--qora-icon-size);
    width: var(--qora-icon-size);
  }

  .engine-picker-button {
    padding: 7px;
    border-radius: 4px;

    &:hover {
      background-color: ${color.container.interactive};
    }

    &.open {
      background-color: ${color.container.interactive};
      border-color: ${color.divider.interactive};
    }
  }

  qora-menu-item {
    --qora-icon-size: 20px;

    display: flex;
    align-items: center;
    gap: 16px;
    min-width: 180px;

    &[data-customize] {
      font: ${font.components.buttonSmall};
      color: ${color.text.secondary};
      justify-content: center;
    }
  }

  .divider {
    border-top: solid 1px ${color.divider.subtle};
  }
`
