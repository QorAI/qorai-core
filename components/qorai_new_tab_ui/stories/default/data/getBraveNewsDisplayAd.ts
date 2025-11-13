// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import { DisplayAd } from '../../../../qorai_news/browser/resources/shared/api'

let callCount = 0

export default function getQoraiNewsDisplayAd (always: boolean = false) {
  callCount++
  const ad: DisplayAd | null = (always || callCount % 2)
    ? {
      description: 'Technica',
      uuid: '0abc',
      creativeInstanceId: '1234',
      title: '10 reasons why technica recreated the sound of old classics.',
      ctaText: 'Hear it',
      targetUrl: { url: 'https://www.qorai.com' },
      image: { imageUrl: undefined, paddedImageUrl: { url: 'https://pcdn.qorai.software/qorai-today/cache/0e9f8fa60d995c1ca86f924b6104195c40555f696598b2f772b27d9b954ce158.jpg.pad' } },
      dimensions: '1x3'
    }
    : null
  return new Promise<{ ad: DisplayAd | null }>(function (resolve) {
    setTimeout(() => resolve({ ad }), 2400)
  })
}
