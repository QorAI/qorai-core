// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import { mangle } from 'lit_mangler'

mangle(
  (element) => {
    const name = element.querySelector('#name-and-version')
    if (!name) {
      throw new Error(
        '[Qorai Extensions Overrides] '
          + 'Could not find element. Has the ID changed?',
      )
    }
    name.insertAdjacentHTML(
      'afterend',
      `<div ?hidden="\${!this.isQoraiHosted_(this.data.id)}"
            class="qorai-hosted">
          \$i18n{qoraiHosted}
       </div>`,
    )
  },
  (t) => t.text.includes('id="name-and-version"'),
)
