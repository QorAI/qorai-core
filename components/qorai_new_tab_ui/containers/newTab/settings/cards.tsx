// Copyright (c) 2020 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'

import {
  FeaturedSettingsWidget,
  StyledBannerImage,
  StyledSettingsInfo,
  StyledSettingsTitle,
  StyledSettingsCopy,
  SettingsWidget,
  StyledWidgetSettings,
  ToggleCardsWrapper,
  ToggleCardsTitle,
  ToggleCardsCopy,
  ToggleCardsSwitch,
  ToggleCardsText
} from '../../../components/default'
import qoraiTalkBanner from './assets/qorai-talk.png'
import qoraiVPNBanner from './assets/qorai-vpn.png'
import rewardsBanner from './assets/qorairewards.png'
import Toggle from '@qorai/qora/react/toggle'
import Button from '@qorai/qora/react/button'

import { getLocale } from '$web-common/locale'
import { loadTimeData } from '$web-common/loadTimeData'
import Icon from '@qorai/qora/react/icon'
import styled, { css } from 'styled-components'
import { spacing } from '@qorai/qora/tokens/css/variables'
import { useNewTabPref } from '../../../hooks/usePref'

const StyledButton = styled(Button) <{ float: boolean }>`
  margin-top: ${spacing.xl};
  width: fit-content;
  ${p => p.float && css`
    float: right;
    margin-right: ${spacing.m};
  `}
`

interface Props {
  toggleShowQoraiTalk: () => void
  showQoraiTalk: boolean
  qoraiTalkSupported: boolean
  toggleShowRewards: () => void
  showRewards: boolean
  qoraiRewardsSupported: boolean
  toggleCards: (show: boolean) => void
  cardsHidden: boolean
}

const ToggleButton = ({ on, toggleFunc, float }: { on: boolean, toggleFunc: any, float?: boolean }) => {
  return <StyledButton onClick={toggleFunc} kind={on ? 'outline' : 'filled'} float={!!float}>
    <div slot="icon-before">
      <Icon name={on ? 'eye-off' : 'plus-add'} />
    </div>
    {getLocale(on ? 'hideWidget' : 'addWidget')}
  </StyledButton>
}

function CardSettings({ toggleShowQoraiTalk, showQoraiTalk, qoraiTalkSupported, toggleShowRewards, showRewards, qoraiRewardsSupported, toggleCards, cardsHidden }: Props) {
  const [showQoraiVPN, saveShowQoraiVPN] = useNewTabPref('showQoraiVPN')
  const [isQoraiTalkDisabledByPolicy] = useNewTabPref(
    'isQoraiTalkDisabledByPolicy'
  )

  return <StyledWidgetSettings>
    {qoraiTalkSupported && !isQoraiTalkDisabledByPolicy &&
      <FeaturedSettingsWidget>
      <StyledBannerImage src={qoraiTalkBanner} />
      <StyledSettingsInfo>
        <StyledSettingsTitle>
          {getLocale('qoraiTalkWidgetTitle')}
        </StyledSettingsTitle>
        <StyledSettingsCopy>
          {getLocale('qoraiTalkWidgetWelcomeTitle')}
        </StyledSettingsCopy>
      </StyledSettingsInfo>
      <ToggleButton on={showQoraiTalk} toggleFunc={toggleShowQoraiTalk} float />
    </FeaturedSettingsWidget>}
    {qoraiRewardsSupported && <SettingsWidget>
      <StyledBannerImage src={rewardsBanner} />
      <StyledSettingsInfo>
        <StyledSettingsTitle>
          {getLocale('qoraiRewardsTitle')}
        </StyledSettingsTitle>
        <StyledSettingsCopy>
          {getLocale('rewardsWidgetDesc')}
        </StyledSettingsCopy>
      </StyledSettingsInfo>
      <ToggleButton on={showRewards} toggleFunc={toggleShowRewards} />
    </SettingsWidget>}
    {loadTimeData.getBoolean('vpnWidgetSupported') && <SettingsWidget>
      <StyledBannerImage src={qoraiVPNBanner} />
      <StyledSettingsInfo>
        <StyledSettingsTitle>
          {getLocale('qoraiVpnWidgetSettingTitle')}
        </StyledSettingsTitle>
        <StyledSettingsCopy>
          {getLocale('qoraiVpnWidgetSettingDesc')}
        </StyledSettingsCopy>
      </StyledSettingsInfo>
      <ToggleButton on={showQoraiVPN!} toggleFunc={() => saveShowQoraiVPN(!showQoraiVPN)} />
    </SettingsWidget>}
    <FeaturedSettingsWidget>
      <ToggleCardsWrapper>
        <ToggleCardsText>
          <ToggleCardsTitle>
            {getLocale('cardsToggleTitle')}
          </ToggleCardsTitle>
          <ToggleCardsCopy>
            {getLocale('cardsToggleDesc')}
          </ToggleCardsCopy>
        </ToggleCardsText>
        <ToggleCardsSwitch>
          <Toggle
            size='small'
            onChange={() => toggleCards(cardsHidden)}
            checked={!cardsHidden}
          />
        </ToggleCardsSwitch>
      </ToggleCardsWrapper>
    </FeaturedSettingsWidget>
  </StyledWidgetSettings>
}

export default React.memo(CardSettings)
