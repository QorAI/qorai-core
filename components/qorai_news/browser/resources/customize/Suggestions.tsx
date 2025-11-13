// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import Flex from '$web-common/Flex'
import { getLocale } from '$web-common/locale'
import * as React from 'react'
import { useQoraiNews } from '../shared/Context'
import Carousel from './Carousel'
import CustomizeLink from './CustomizeLink'
import CustomizePage from './CustomizePage'
import DiscoverSection from './DiscoverSection'
import PublisherCard from '../shared/PublisherCard'

export function SuggestionsCarousel () {
  const { suggestedPublisherIds, setCustomizePage } = useQoraiNews()

  return <Carousel
    title={<Flex justify='space-between'>
      {getLocale(S.QORAI_NEWS_SUGGESTIONS_TITLE)}
      <CustomizeLink onClick={() => setCustomizePage('suggestions')}>
        {getLocale(S.QORAI_NEWS_VIEW_ALL_BUTTON)}
      </CustomizeLink>
    </Flex>}
    subtitle={getLocale(S.QORAI_NEWS_SUGGESTIONS_SUBTITLE)}
    publisherIds={suggestedPublisherIds}/>
}

export function SuggestionsPage () {
  const { suggestedPublisherIds } = useQoraiNews()
  return <CustomizePage title={getLocale(S.QORAI_NEWS_SUGGESTIONS_TITLE)}>
    <DiscoverSection>
      {suggestedPublisherIds.map(p => <PublisherCard key={p} publisherId={p} />)}
    </DiscoverSection>
  </CustomizePage>
}
