// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import {
  QoraiNewsControllerRemote,
  Publisher,
  PublishersListenerInterface,
  PublishersListenerReceiver,
  UserEnabled
} from 'gen/qorai/components/qorai_news/common/qorai_news.mojom.m'
import getQoraiNewsController, { isDirectFeed } from './api'

import { EntityCachingWrapper } from '$web-common/mojomCache'

export class PublishersCachingWrapper
  extends EntityCachingWrapper<Publisher>
  implements PublishersListenerInterface {
  private receiver = new PublishersListenerReceiver(this)
  private controller: QoraiNewsControllerRemote

  constructor() {
    super()

    this.controller = getQoraiNewsController()

    // We can't set up  the mojo pipe in the test environment.
    if (process.env.NODE_ENV !== 'test') {
      this.controller.addPublishersListener(
        this.receiver.$.bindNewPipeAndPassRemote()
      )
    }
  }

  setPublisherFollowed(publisherId: string, enabled: boolean) {
    const copy = {
      ...this.cache
    }

    if (isDirectFeed(this.cache[publisherId]) && !enabled) {
      this.controller.setPublisherPref(publisherId, UserEnabled.DISABLED)
      delete copy[publisherId]
    } else {
      const status = enabled ? UserEnabled.ENABLED : UserEnabled.NOT_MODIFIED
      this.controller.setPublisherPref(publisherId, status)
      copy[publisherId].userEnabledStatus = status
    }

    this.notifyChanged(copy)
  }
}
