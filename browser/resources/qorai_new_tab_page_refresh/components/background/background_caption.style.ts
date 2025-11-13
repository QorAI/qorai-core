/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import { color, font } from '@qorai/qora/tokens/css/variables'
import { scoped } from '../../lib/scoped_css'

export const style = scoped.css`
  a {
    text-decoration: none;
    color: inherit;
  }

  .photo-credits {
    color: ${color.white};
    font: ${font.xSmall.regular};
    text-shadow: 0 1px 0 rgba(255, 255, 255, 0.10);
    white-space: nowrap;
    opacity: .5;
  }

  .sponsored-logo {
    --qora-icon-size: 20px;

    width: min-content;
    display: flex;
    flex-direction: column;
    align-items: end;
    color: ${color.white};

    qora-icon {
      opacity: 0;
      transition: opacity 200ms;
    }

    img {
      margin-top: 2px;
      width: 170px;
      height: auto;
    }

    &:hover {
      qora-icon {
        opacity: .7;
      }
    }
  }
`
