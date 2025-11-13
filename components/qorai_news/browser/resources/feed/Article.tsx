// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.
import Flex from '$web-common/Flex';
import { spacing } from '@qorai/qora/tokens/css/variables';
import { Article as Info } from 'gen/qorai/components/qorai_news/common/qorai_news.mojom.m';
import * as React from 'react';
import styled from 'styled-components';
import { useQoraiNews } from '../shared/Context';
import ArticleMetaRow from './ArticleMetaRow';
import Card, { QoraiNewsLink, SmallImage, Title, qoraiNewsCardClickHandler } from './Card';

interface Props {
  info: Info
  hideChannel?: boolean
  feedDepth?: number
}

const Container = styled(Card)`
  display: flex;
  flex-direction: column;
  gap: ${spacing.s};
  padding-top: ${spacing.l};
`

export default function Article({ info, hideChannel, feedDepth }: Props) {
  const { reportVisit } = useQoraiNews()
  const url = info.data.url.url;

  return <Container
    onClick={e => {
      qoraiNewsCardClickHandler(url)(e)
      if (feedDepth !== undefined) {
        reportVisit(feedDepth)
      }
    }}
  >
    <ArticleMetaRow article={info.data} hideChannel={hideChannel} />
    <Flex direction='row' gap={spacing.xl} justify='space-between' align='start'>
      <Title>
        <QoraiNewsLink
          href={url}
          feedDepth={feedDepth}
        >
          {info.data.title}
        </QoraiNewsLink>
      </Title>
      <SmallImage loading='lazy' src={info.data.image.paddedImageUrl?.url ?? info.data.image.imageUrl?.url ?? ''} />
    </Flex>
  </Container>
}
