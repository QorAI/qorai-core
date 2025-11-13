// Copyright (c) 2022 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

declare namespace chrome.qoraiTheme {
  type ThemeType = 'Light' | 'Dark' | 'System'
  type ThemeTypeCallback = (themeType: ThemeType) => unknown
  const setQorAIThemeType: (themeType: ThemeType) => void
}
