// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'
import Button from '@qorai/qora/react/button'
import getPanelBrowserAPI from '../../api/panel_browser_api'
import { formatLocale, getLocale } from '$web-common/locale'
import {
  Container,
  Title,
  Description,
  Actions,
  StyledAlert,
  ActionsSlotWrapper,
} from './style'

const handleLearnMoreClick = (e: React.MouseEvent<HTMLAnchorElement>) => {
  e.preventDefault()
  chrome.tabs.create({ url: 'https://support.qorai.app/hc/en-us/articles/38076796692109', active: true })
}

const onDismissShieldsDisabledAdBlockOnlyModePromptClick = () => {
  getPanelBrowserAPI().dataHandler.setQoraiShieldsAdBlockOnlyModePromptDismissed()
}

const onDismissRepeatedReloadsAdBlockOnlyModePromptClick = async () => {
  await getPanelBrowserAPI().dataHandler.setQoraiShieldsAdBlockOnlyModePromptDismissed()
  getPanelBrowserAPI().panelHandler.closeUI()
}

const onEnableAdBlockOnlyModeClick = async (enableShields: boolean) => {
  if (enableShields) {
    await getPanelBrowserAPI().dataHandler.setQoraiShieldsEnabled(/* isEnabled: */ true)
  }
  await getPanelBrowserAPI().dataHandler.setQoraiShieldsAdBlockOnlyModeEnabled(/* isEnabled: */ true)
  getPanelBrowserAPI().panelHandler.closeUI()
}

export function AdBlockOnlyModePromptAfterRepeatedReloads() {
  return (
    <Container>
      <Title>
        {getLocale('qoraiShieldsAreYouExperiencingIssuesWithThisSiteTitle')}
      </Title>
      <Description>
        <div>
          {formatLocale(`qoraiShieldsAreYouExperiencingIssuesWithThisSiteDesc1`, {
            $1: content => <a href='https://support.qorai.app/hc/en-us/articles/38076796692109'
                              onClick={handleLearnMoreClick}>
              {content}
            </a>
          })}
        </div>
        <div>
          {getLocale('qoraiShieldsAreYouExperiencingIssuesWithThisSiteDesc2')}
        </div>
      </Description>
      <Actions>
        <Button
          kind="outline"
          size="medium"
          onClick={onDismissRepeatedReloadsAdBlockOnlyModePromptClick}
        >
          {getLocale('qoraiShieldsDismissAlert')}
        </Button>
        <Button
          size="medium"
          onClick={() => onEnableAdBlockOnlyModeClick(/* enableShields: */ false)}
        >
          {getLocale('qoraiShieldsEnableAdBlockOnlyMode')}
        </Button>
      </Actions>
    </Container>
  );
}

export function AdBlockOnlyModePromptAfterShieldsDisabled() {
  return (
      <StyledAlert type='info' hideIcon>
        <div slot='title'>
          {getLocale('qoraiShieldsAreYouExperiencingIssuesWithThisSiteTitle')}
        </div>
        <div>
          {formatLocale(`qoraiShieldsAreYouExperiencingIssuesWithThisSiteDesc1`, {
            $1: content => <a href='https://support.qorai.app/hc/en-us/articles/38076796692109'
                              onClick={handleLearnMoreClick}>
              {content}
            </a>
          })}
        </div>
        <div>
          {getLocale('qoraiShieldsAreYouExperiencingIssuesWithThisSiteDesc2')}
        </div>
        <ActionsSlotWrapper slot='actions'>
          <Button
            size="medium"
            onClick={() => onEnableAdBlockOnlyModeClick(/* enableShields: */ true)}
          >
            {getLocale('qoraiShieldsEnableAdBlockOnlyMode')}
          </Button>
          <Button
            kind="plain"
            size="medium"
            onClick={() => onDismissShieldsDisabledAdBlockOnlyModePromptClick()}
          >
            {getLocale('qoraiShieldsDismissAlert')}
          </Button>
        </ActionsSlotWrapper>
      </StyledAlert>
  )
}
