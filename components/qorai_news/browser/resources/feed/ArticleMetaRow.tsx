// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import { font, spacing } from "@qorai/qora/tokens/css/variables"
import getQoraiNewsController, { FeedItemMetadata, UserEnabled } from "../shared/api"
import { channelIcons } from "../shared/Icons"
import styled from "styled-components";
import * as React from "react";
import Flex from '$web-common/Flex'
import ButtonMenu from "@qorai/qora/react/buttonMenu";
import Button from "@qorai/qora/react/button";
import Icon from "@qorai/qora/react/icon";
import { formatLocale } from '$web-common/locale';
import { getTranslatedChannelName } from "../shared/channel";
import useRelativeTime from '$web-common/useRelativeTime'
import { mojoTimeToJSDate } from '$web-common/mojomUtils'

const MenuButton = styled(Button)`
  --qora-button-padding: 0;

  flex-grow: 0;
`

export const MetaInfoContainer = styled.h4`
  --qora-icon-size: 12px;

  margin: 0;

  font: ${font.xSmall.regular};
  color: var(--bn-glass-50);

  display: flex;
  align-items: center;
  gap: ${spacing.s};
`

const publisherDescription = (article: FeedItemMetadata) => {
  if (article.publisherName) return article.publisherName
  const url = new URL(article.url.url)
  return url.hostname
}

export function MetaInfo(props: { article: FeedItemMetadata, hideChannel?: boolean }) {
  const relativeTime = useRelativeTime(mojoTimeToJSDate(props.article.publishTime))
  const maybeChannel = !props.hideChannel && <>
    • {channelIcons[props.article.categoryName] ?? channelIcons.default} {getTranslatedChannelName(props.article.categoryName)}
  </>

  return <MetaInfoContainer>
    {publisherDescription(props.article)} {maybeChannel} • {relativeTime}
  </MetaInfoContainer>
}

export default function ArticleMetaRow(props: { article: FeedItemMetadata, hideChannel?: boolean }) {
  return <Flex direction="row" justify="space-between" align="center">
    <MetaInfo {...props} />

    <ButtonMenu>
      <MenuButton slot='anchor-content' kind='plain-faint' size="tiny">
        <Icon name='more-horizontal' />
      </MenuButton>
      <qora-menu-item onClick={e => {
        getQoraiNewsController().setPublisherPref(props.article.publisherId, UserEnabled.DISABLED)
        e.stopPropagation()
      }}>
        {formatLocale(S.QORAI_NEWS_HIDE_CONTENT_FROM, {
          $1: publisherDescription(props.article)
        })}
      </qora-menu-item>
    </ButtonMenu>
  </Flex>
}
