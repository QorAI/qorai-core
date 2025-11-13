// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import {
  QoraiNewsControllerRemote,
  Configuration,
  ConfigurationListenerInterface,
  ConfigurationListenerReceiver,
} from 'gen/qorai/components/qorai_news/common/qorai_news.mojom.m'
import getQoraiNewsController from './api'

import { CachingWrapper } from '$web-common/mojomCache'

export class ConfigurationCachingWrapper
  extends CachingWrapper<Configuration>
  implements ConfigurationListenerInterface {
  private receiver = new ConfigurationListenerReceiver(this)
  private controller: QoraiNewsControllerRemote

  constructor() {
    super({
      isOptedIn: false,
      showOnNTP: false,
      openArticlesInNewTab: true,
    })

    this.controller = getQoraiNewsController()

    // We can't set up  the mojo pipe in the test environment.
    if (process.env.NODE_ENV !== 'test') {
      this.controller.addConfigurationListener(
        this.receiver.$.bindNewPipeAndPassRemote()
      )
    }
  }

  get value() {
    return this.cache;
  }

  set(change: Partial<Configuration>) {
    const newValue = {...this.cache, ...change }
    this.controller.setConfiguration(newValue)
    this.changed(newValue)
  }

  changed(newConfiguration: Configuration): void {
    this.notifyChanged(newConfiguration)
  }
}
