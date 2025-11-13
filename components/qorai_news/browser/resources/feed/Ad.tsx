// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.
import SecureLink from '$web-common/SecureLink';
import { getLocale } from '$web-common/locale';
import { useOnVisibleCallback } from '$web-common/useVisible';
import VisibilityTimer from '$web-common/visibilityTimer';
import Button from '@qorai/qora/react/button';
import { font, spacing } from '@qorai/qora/tokens/css/variables';
import { DisplayAd, FeedV2Ad } from 'gen/qorai/components/qorai_news/common/qorai_news.mojom.m';
import * as React from 'react';
import styled from 'styled-components';
import getQoraiNewsController from '../shared/api';
import { MetaInfoContainer } from './ArticleMetaRow';
import Card, { LargeImage, Title, qoraiNewsCardClickHandler } from './Card';
import { useQoraiNews } from '../shared/Context';

interface Props {
  info: FeedV2Ad
}

const Container = styled(Card)`
  display: flex;
  flex-direction: column;
  gap: ${spacing.m}
`

const BatAdLabel = styled.a`
  padding: 0 2px;

  border: 1px solid rgba(var(--bn-text-base), 0.3);
  border-radius: 3px;

  text-decoration: none;

  color: rgba(var(--bn-text-base, 0.7));
  font: ${font.small.regular};
  line-height: 16px;
`

const CtaButton = styled(Button)`
  --qora-button-color: var(--bn-glass-container);
  align-self: flex-start;
`

const AdImage = styled(LargeImage)`
  height: unset;
`

export const useVisibleFor = (callback: () => void, timeout: number) => {
  const [el, setEl] = React.useState<HTMLElement | null>(null)
  const callbackRef = React.useRef<() => void>()
  callbackRef.current = callback

  React.useEffect(() => {
    if (!el) return

    const observer = new VisibilityTimer(() => {
      callbackRef.current?.()
    }, timeout, el)
    observer.startTracking()

    return () => {
      observer.stopTracking()
    }
  }, [el, timeout, callback])

  return {
    setEl,
  }
}

const adTargetUrlAllowedSchemes = ['https:', 'chrome:', 'qorai:']

export default function Advert(props: Props) {
  const [advert, setAdvert] = React.useState<DisplayAd | null | undefined>(undefined)
  const imageUrl = advert?.image.paddedImageUrl?.url ?? advert?.image.imageUrl?.url ?? ''
  const { openArticlesInNewTab } = useQoraiNews()

  const onDisplayAdViewed = React.useCallback(() => {
    if (!advert) return

    console.debug(`Qorai News: Viewed display ad: ${advert.uuid}`)
    getQoraiNewsController().onDisplayAdView(advert.uuid, advert.creativeInstanceId)
  }, [advert])

  const { setEl: setAdEl } = useVisibleFor(onDisplayAdViewed, 1000)

  const onDisplayAdVisited = React.useCallback(async (e: React.MouseEvent) => {
    if (!advert) return

    console.debug(`Qorai News: Visited display ad: ${advert.uuid}`)
    await getQoraiNewsController().onDisplayAdVisit(advert.uuid, advert.creativeInstanceId)
    qoraiNewsCardClickHandler(advert.targetUrl.url, adTargetUrlAllowedSchemes)(e);
  }, [advert])

  const { setElementRef: setTriggerRef } = useOnVisibleCallback(async () => {
    console.debug(`Qorai News: Fetching an advertisement`)

    const advert = await getQoraiNewsController().getDisplayAd().then(r => r.ad)
    setAdvert(advert ?? null)
  }, {
    // Trigger ad fetch when the ad unit is 1000px away from the viewport
    rootMargin: '0px 0px 1000px 0px'
  })

  // Advert is null if we didn't manage to load an advertisement
  if (advert === null) return null

  // Otherwise, render a placeholder div - when close to the viewport we'll
  // request an ad.
  if (!advert) {
    return <div ref={setTriggerRef} />
  }

  return <Container ref={setAdEl} onClick={onDisplayAdVisited}>
    <AdImage loading='eager' src={imageUrl} />
    <MetaInfoContainer>
      <QorAdLabel onClick={e => e.stopPropagation()} target={openArticlesInNewTab ? '_blank' : undefined} href="chrome://rewards">{getLocale(S.QORAI_NEWS_ADVERT_BADGE)}</QorAdLabel>
      •
      {' ' + advert.description}
    </MetaInfoContainer>
    <Title>
      <SecureLink allowedSchemes={adTargetUrlAllowedSchemes} href={advert.targetUrl.url} onClick={e => {
        // preventDefault, so we go through onDisplayAdVisit and record the
        // result.
        e.preventDefault()
      }}>
        {advert.title}
      </SecureLink>
    </Title>
    <CtaButton kind='filled'>{advert.ctaText}</CtaButton>
  </Container>
}
