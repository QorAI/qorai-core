/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import styled from 'styled-components'

import * as qora from '@qorai/qora/tokens/css/variables'

import * as mixins from '../lib/css_mixins'

export const root = styled.div`
  max-width: 500px;
  border-radius: var(--tos-update-notice-border-radius, 16px);
  background: ${qora.color.container.background};
  padding: var(--tos-update-notice-padding, 24px 24px 16px);
  display: flex;
  flex-direction: column;
  gap: 16px;

  a {
    color: ${qora.color.text.interactive};
  }
`

export const heading = styled.div`
  padding-bottom: var(--tos-update-heading-padding-bottom, 8px);
  font: var(--tos-update-notice-heading-font, ${qora.font.heading.h3});
  color: ${qora.color.text.primary};
`

export const text = styled.div`
  font: var(--tos-update-notice-text-font, ${qora.font.default.regular});
  color: ${qora.color.text.secondary};

  button {
    ${mixins.buttonReset}
    text-decoration: underline;
    cursor: pointer;
  }
`
