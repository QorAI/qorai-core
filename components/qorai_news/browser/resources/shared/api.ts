// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as QoraiNews from 'gen/qorai/components/qorai_news/common/qorai_news.mojom.m.js'
// Provide access to all the generated types
export * from 'gen/qorai/components/qorai_news/common/qorai_news.mojom.m.js'

// Provide easy access to types which mojom functions return but aren't
// defined as a struct.
export type Publishers = Record<string, QoraiNews.Publisher>
export type Channels = Record<string, QoraiNews.Channel>

// Create singleton connection to browser interface
let qoraiNewsControllerInstance: QoraiNews.QoraiNewsControllerRemote

export default function getQoraiNewsController () {
  // Make connection on first call (not in module root, so that storybook
  // doesn't try to connect, or pages which use exported types
  // but ultimately don't fetch any data.
  if (!qoraiNewsControllerInstance) {
    // In Storybook, we have a mocked QoraiNewsController because none of the
    // mojo apis are available.
    // @ts-expect-error
    qoraiNewsControllerInstance = window.storybookQoraiNewsController || QoraiNews.QoraiNewsController.getRemote()
  }
  return qoraiNewsControllerInstance
}

export const isPublisherEnabled = (publisher: QoraiNews.Publisher) => {
  if (!publisher) return false

  // Direct Sources are enabled if they're available.
  if (publisher.type === QoraiNews.PublisherType.DIRECT_SOURCE) return true

  // Publishers enabled via channel are not shown in the sidebar.
  return publisher.userEnabledStatus === QoraiNews.UserEnabled.ENABLED
}

export const isDirectFeed = (publisher: QoraiNews.Publisher) => {
  if (!publisher) return false
  return publisher.type === QoraiNews.PublisherType.DIRECT_SOURCE
}
