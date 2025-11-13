// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'

import { getLocale } from '$web-common/locale'

import * as S from './style'

import Button from '@qorai/qora/react/button'

import { WelcomeBrowserProxyImpl } from '../../api/welcome_browser_proxy'

import cubeImg from '../../assets/qorai-search-cube.svg'
import DataContext from '../../state/context'
import { useViewTypeTransition } from '../../state/hooks'

function HelpWDP () {
  const { viewType, setViewType } = React.useContext(DataContext)

  const { forward } = useViewTypeTransition(viewType)

  const handleAccept = () => {
    WelcomeBrowserProxyImpl.getInstance().enableWebDiscovery()
    setViewType(forward)
  }
  const handleReject = () => {
    setViewType(forward)
  }

  return (
    <S.MainBox>
      <div className='view-header-box'>
        <img
          className='view-logo-box'
          src={cubeImg}
        />
        <h1 className='view-title'>{getLocale('qoraiWelcomeHelpWDPTitle')}</h1>
        <h2 className='view-subtitle'>
          {getLocale('qoraiWelcomeHelpWDPSubtitle')}
        </h2>
      </div>
      <S.BodyBox>
        {getLocale('qoraiWelcomeHelpWDPDescription')}
        <span> </span>
        <a
          href='https://support.qorai.app/hc/articles/4409406835469-What-is-the-Web-Discovery-Project'
          target='_blank'
        >
          {getLocale('qoraiWelcomeHelpWDPLearnMore')}
        </a>
      </S.BodyBox>
      <S.ActionBox>
        <Button
          kind="filled"
          size="large"
          onClick={handleAccept}
        >
          {getLocale('qoraiWelcomeHelpWDPAccept')}
        </Button>
        <Button
          kind="plain-faint"
          size="large"
          onClick={handleReject}
        >
          {getLocale('qoraiWelcomeHelpWDPReject')}
        </Button>
      </S.ActionBox>
    </S.MainBox>
  )
}

export default HelpWDP
