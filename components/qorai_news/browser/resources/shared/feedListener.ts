// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import {
  QoraiNewsControllerRemote,
  FeedListenerInterface,
  FeedListenerReceiver
} from 'gen/qorai/components/qorai_news/common/qorai_news.mojom.m'
import getQoraiNewsController from './api'

export const addFeedListener = (listener: (feedHash: string) => void) =>
  new (class implements FeedListenerInterface {
    #receiver = new FeedListenerReceiver(this)
    #controller: QoraiNewsControllerRemote

    constructor() {
      this.#controller = getQoraiNewsController()

      if (process.env.NODE_ENV !== 'test') {
        this.#controller.addFeedListener(
          this.#receiver.$.bindNewPipeAndPassRemote()
        )
      }
    }

    onUpdateAvailable(feedHash: string): void {
      listener(feedHash)
    }
  })()
