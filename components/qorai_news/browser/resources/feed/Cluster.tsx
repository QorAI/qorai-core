// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.
import * as React from 'react';
import { Cluster as Info, ClusterType } from 'gen/qorai/components/qorai_news/common/qorai_news.mojom.m';
import Card, { Title } from './Card';
import Article from './Article';
import styled from 'styled-components';
import { icon, radius, spacing } from '@qorai/qora/tokens/css/variables';
import { channelIcons } from '../shared/Icons';
import { getTranslatedChannelName } from '../shared/channel';

interface Props {
  info: Info
  feedDepth?: number
}

const Container = styled(Card)`
  display: flex;
  flex-direction: column;
  gap: ${spacing.l};

  & > ${Title} {
    --qora-icon-color: currentColor;
    --qora-icon-size: ${icon.s};

    gap: ${spacing.m};
    align-items: center;

    margin: ${spacing.m} 0;
  }

  & > ${Card} {
    border-radius: ${radius.m};
  }
`

export default function Cluster({ info, feedDepth }: Props) {
  const groupName = info.type === ClusterType.CHANNEL
    ? getTranslatedChannelName(info.id)
    : info.id
  return <Container>
    <Title>
      {channelIcons[info.id] ?? channelIcons.default} {groupName}
    </Title>
    {info.articles.map((a, i) => {
      const info: any = a.article || a.hero
      return <Article
        key={i}
        info={info}
        hideChannel={info.type === ClusterType.CHANNEL}
        feedDepth={feedDepth === undefined ? undefined : (feedDepth + i)}
      />
    })}
  </Container>
}
