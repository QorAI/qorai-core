/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import * as React from 'react'
import Icon from '@qorai/qora/react/icon'

import { formatString } from '$web-common/locale'
import { Link } from '../common/link'
import { getString } from '../../lib/strings'
import { QoraiBackground, SponsoredImageBackground } from '../../state/background_state'
import { useCurrentBackground, useBackgroundActions } from '../../context/background_context'

import { style } from './background_caption.style'

export function BackgroundCaption() {
  const currentBackground = useCurrentBackground()

  function renderCaption() {
    switch (currentBackground?.type) {
      case 'qorai':
        return <QoraiBackgroundCredits background={currentBackground} />
      case 'sponsored-image':
        return <SponsoredBackgroundLogo background={currentBackground} />
      default:
        return null
    }
  }

  return (
    <div data-css-scope={style.scope}>
      {renderCaption()}
    </div>
  )
}

interface QoraiBackgroundCreditsProps {
  background: QoraiBackground
}

function QoraiBackgroundCredits(props: QoraiBackgroundCreditsProps) {
  const { author, link } = props.background
  if (!author) {
    return null
  }
  return (
    <Link className='photo-credits' url={link}>
      {formatString(getString(S.NEW_TAB_PHOTO_CREDITS_TEXT), [author])}
    </Link>
  )
}

interface SponsoredBackgroundLogoProps {
  background: SponsoredImageBackground
}

function SponsoredBackgroundLogo(props: SponsoredBackgroundLogoProps) {
  const actions = useBackgroundActions()
  const { logo } = props.background
  if (!logo || !logo.imageUrl) {
    return null
  }
  return (
    <Link
      url={logo.destinationUrl}
      className='sponsored-logo'
      onClick={() => actions.notifySponsoredImageLogoClicked()}
    >
      <Icon name='launch' />
      <img src={logo.imageUrl} alt={logo.alt} />
    </Link>
  )
}
