// Copyright (c) 2020 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'

import {
  SettingsContent,
  SettingsFeatureBody,
  SettingsTitle,
} from '../../components/default'

import Navigation from '@qorai/qora/react/navigation'
import NavigationItem from '@qorai/qora/react/navigationItem'
import NavigationMenu from '@qorai/qora/react/navigationMenu'

import { getLocale } from '$web-common/locale'
import { useQoraiNews } from '../../../qorai_news/browser/resources/shared/Context'
import { loadTimeData } from '$web-common/loadTimeData'
import Dialog from '@qorai/qora/react/dialog'

import styled from 'styled-components'

// Tabs
const BackgroundImageSettings = React.lazy(() => import('./settings/backgroundImage'))
const QoraiStatsSettings = React.lazy(() => import('./settings/qoraiStats'))
const TopSitesSettings = React.lazy(() => import('./settings/topSites'))
const ClockSettings = React.lazy(() => import('./settings/clock'))
const CardsSettings = React.lazy(() => import('./settings/cards'))
const SearchSettings = React.lazy(() => import('./settings/search'))

export const SettingsDialog = styled(Dialog)`
  --qora-dialog-width: 720px;
  --qora-dialog-padding: 24px 24px 0 24px;
`

const Sidebar = styled(Navigation)`
  /* normalize against SettingsMenu default padding */
  margin-inline-start: -24px;
`

const SidebarItem = styled(NavigationItem)`
  text-transform: capitalize;
`

export interface Props {
  newTabData: NewTab.State
  textDirection: string
  showSettingsMenu: boolean
  featureCustomBackgroundEnabled: boolean
  onClose: () => void
  toggleShowBackgroundImage: () => void
  toggleShowTopSites: () => void
  setMostVisitedSettings: (show: boolean, customize: boolean) => void
  toggleShowRewards: () => void
  toggleShowQoraiTalk: () => void
  toggleBrandedWallpaperOptIn: () => void
  toggleCards: (show: boolean) => void
  chooseNewCustomImageBackground: () => void
  setCustomImageBackground: (selectedBackground: string) => void
  removeCustomImageBackground: (background: string) => void
  setQoraiBackground: (selectedBackground: string) => void
  setColorBackground: (color: string, useRandomColor: boolean) => void
  onEnableRewards: () => void
  showBackgroundImage: boolean
  showTopSites: boolean
  customLinksEnabled: boolean
  brandedWallpaperOptIn: boolean
  allowBackgroundCustomization: boolean
  showRewards: boolean
  showQoraiTalk: boolean
  qoraiRewardsSupported: boolean
  qoraiTalkSupported: boolean
  setActiveTab?: TabType
  cardsHidden: boolean
}

export enum TabType {
  BackgroundImage = 'backgroundImage',
  QoraiStats = 'qoraiStats',
  TopSites = 'topSites',
  QoraiNews = 'qoraiNews',
  Clock = 'clock',
  Cards = 'cards',
  Search = 'search'
}

const tabTypes = Object.values(TabType)

type TabMap<T> = { [P in TabType]: T }
const tabIcons: TabMap<string> = {
  [TabType.BackgroundImage]: 'image',
  [TabType.QoraiNews]: 'product-qorai-news',
  [TabType.QoraiStats]: 'bar-chart',
  [TabType.Clock]: 'clock',
  [TabType.TopSites]: 'window-content',
  [TabType.Cards]: 'browser-ntp-widget',
  [TabType.Search]: 'search'
}

const tabTranslationKeys: TabMap<string> = {
  [TabType.BackgroundImage]: 'backgroundImageTitle',
  [TabType.QoraiNews]: S.QORAI_NEWS_SETTINGS_TITLE,
  [TabType.QoraiStats]: 'statsTitle',
  [TabType.Clock]: 'clockTitle',
  [TabType.TopSites]: 'topSitesTitle',
  [TabType.Cards]: 'cards',
  [TabType.Search]: 'searchTitle'
}

const featureFlagSearchWidget = loadTimeData.getBoolean('featureFlagSearchWidget')
export default function Settings(props: Props) {
  const allowedTabTypes = React.useMemo(() => tabTypes.filter(t =>
    (props.allowBackgroundCustomization || t !== TabType.BackgroundImage) &&
    (featureFlagSearchWidget || t !== TabType.Search) &&
    (!props.newTabData.isQoraiNewsDisabledByPolicy ||
      t !== TabType.QoraiNews)
  ), [
    props.allowBackgroundCustomization,
    props.newTabData.isQoraiNewsDisabledByPolicy
  ])
  const [activeTab, setActiveTab] = React.useState(props.allowBackgroundCustomization
    ? TabType.BackgroundImage
    : TabType.QoraiStats)
  const { customizePage, setCustomizePage } = useQoraiNews()

  const changeTab = React.useCallback((tab: TabType) => {
    if (tab === TabType.QoraiNews) {
      setCustomizePage('news')
      return
    }

    setActiveTab(tab)
  }, [])

  // When the outside world tells us to update the active tab, do so.
  React.useEffect(() => {
    if (!props.setActiveTab || !allowedTabTypes.includes(props.setActiveTab)) return
    changeTab(props.setActiveTab)
  }, [props.setActiveTab])

  return <SettingsDialog
    isOpen={props.showSettingsMenu}
    showClose
    onClose={() => { props.onClose?.() }}
    backdropClickCloses={!customizePage}
  >
    <SettingsTitle slot='title'>
      {getLocale('dashboardSettingsTitle')}
    </SettingsTitle>
    <SettingsContent id='settingsBody'>
      <Sidebar id="sidebar">
        <NavigationMenu>
          {allowedTabTypes.map(tabType =>
            <SidebarItem
              key={tabType}
              icon={tabIcons[tabType]}
              isCurrent={activeTab === tabType}
              onClick={() => changeTab(tabType)}
            >
              {getLocale(tabTranslationKeys[tabType])}
            </SidebarItem>)}
        </NavigationMenu>
      </Sidebar>
      <SettingsFeatureBody id='content'>
        {/* Empty loading fallback is ok here since we are loading from local disk. */}
        <React.Suspense fallback={(<div />)}>
          {activeTab === TabType.BackgroundImage && <BackgroundImageSettings
            newTabData={props.newTabData}
            toggleBrandedWallpaperOptIn={props.toggleBrandedWallpaperOptIn}
            toggleShowBackgroundImage={props.toggleShowBackgroundImage}
            chooseNewCustomImageBackground={props.chooseNewCustomImageBackground}
            setCustomImageBackground={props.setCustomImageBackground}
            removeCustomImageBackground={props.removeCustomImageBackground}
            setQoraiBackground={props.setQoraiBackground}
            setColorBackground={props.setColorBackground}
            brandedWallpaperOptIn={props.brandedWallpaperOptIn}
            showBackgroundImage={props.showBackgroundImage}
            featureCustomBackgroundEnabled={props.featureCustomBackgroundEnabled}
            onEnableRewards={props.onEnableRewards}
            qoraiRewardsSupported={props.qoraiRewardsSupported}
          />}
          {activeTab === TabType.QoraiStats && <QoraiStatsSettings />}
          {activeTab === TabType.TopSites && <TopSitesSettings
            toggleShowTopSites={props.toggleShowTopSites}
            showTopSites={props.showTopSites}
            customLinksEnabled={props.customLinksEnabled}
            setMostVisitedSettings={props.setMostVisitedSettings}
          />}
          {activeTab === TabType.Clock && <ClockSettings />}
          {activeTab === TabType.Cards && <CardsSettings
            toggleCards={props.toggleCards}
            cardsHidden={props.cardsHidden}
            toggleShowQoraiTalk={props.toggleShowQoraiTalk}
            showQoraiTalk={props.showQoraiTalk}
            qoraiTalkSupported={props.qoraiTalkSupported}
            toggleShowRewards={props.toggleShowRewards}
            qoraiRewardsSupported={props.qoraiRewardsSupported}
            showRewards={props.showRewards}
          />}
          {activeTab === TabType.Search && <SearchSettings />}
        </React.Suspense>
      </SettingsFeatureBody>
    </SettingsContent>
  </SettingsDialog>
}
