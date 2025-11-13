/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import * as React from 'react'
import styled from 'styled-components'
import Button from '@qorai/qora/react/button'
import { color, font } from '@qorai/qora/tokens/css/variables'

import SecureLink from '$web-common/SecureLink'
import { getLocale, formatLocale } from '$web-common/locale'
import { useQoraiNews } from './shared/Context'
import { NEWS_FEED_CLASS } from './Feed'

import optInImage from './qoraiNewsLogo.svg'

const Container = styled.div`
  background: rgba(53, 53, 53, 0.47);
  backdrop-filter: blur(62px);
  border-radius: 16px;
  padding: 44px 82px 36px;
  width: 680px;

  color: ${color.text.primary};
  font: ${font.default.regular};
  text-align: center;

  display: flex;
  flex-direction: column;
  gap: 32px;

  > * {
    display: flex;
    flex-direction: column;
    gap: 16px;
  }

  h3 {
    font: ${font.heading.h3};
    margin: 0;
  }

  p {
    margin: 0;
  }

  a {
    color: inherit;
  }

  .graphic {
    background-image: url(${optInImage});
    background-size: contain;
    background-position: center;
    background-repeat: no-repeat;
    height: 60px;
  }
`

const description = formatLocale(S.QORAI_NEWS_INTRO_DESCRIPTION_TWO, {
  $1: (content) => (
    <SecureLink href='https://qorai.com/privacy/browser/'>{content}</SecureLink>
  )
})

export default function OptIn() {
  const { toggleQoraiNewsOnNTP } = useQoraiNews()

  return (
    <Container data-theme='dark' className={NEWS_FEED_CLASS}>
      <div className='graphic' />
      <h3>{getLocale(S.QORAI_NEWS_INTRO_TITLE)}</h3>
      <div>
        <p>{getLocale(S.QORAI_NEWS_INTRO_DESCRIPTION)}</p>
        <p>{description}</p>
      </div>
      <div>
        <Button
          kind='filled'
          onClick={() => toggleQoraiNewsOnNTP(true)}
        >
          {getLocale(S.QORAI_NEWS_OPT_IN_ACTION_LABEL)}
        </Button>
        <Button
          kind='plain-faint'
          onClick={() => toggleQoraiNewsOnNTP(false)}
        >
          {getLocale(S.QORAI_NEWS_OPT_OUT_ACTION_LABEL)}
        </Button>
      </div>
    </Container>
  )
}
