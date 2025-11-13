/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import { color } from '@qorai/qora/tokens/css/variables'
import { scoped } from '../../lib/scoped_css'

export const style = scoped.css`
  & {
    @container style(--is-wide-view) {
      max-width: 600px;
    }
  }

  .processing {
    --qora-progressring-size: 38px;

    padding: 32px 0 16px;
    display: flex;
    flex-direction: column;
    align-items: center;
    gap: 32px;
  }

  .status-icon {
    --qora-icon-size: 40px;

    height: 88px;
    width: 88px;
    padding: 24px;
    margin-bottom: 24px;
    background: ${color.systemfeedback.warningBackground};
    border-radius: 50%;
    color: ${color.systemfeedback.warningIcon};
  }

  h3 {
    margin: 32px 0 16px;
  }

  .error-text {
    display: flex;
    flex-direction: column;
    gap: 16px;
  }
`
