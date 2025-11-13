// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_NEWS_BROWSER_CHANNEL_MIGRATOR_H_
#define QORAI_COMPONENTS_QORAI_NEWS_BROWSER_CHANNEL_MIGRATOR_H_

#include <string>

#include "components/prefs/pref_service.h"

namespace qorai_news {

void MigrateChannels(PrefService& prefs);
std::string GetMigratedChannel(const std::string& channel);

}  // namespace qorai_news

#endif  // QORAI_COMPONENTS_QORAI_NEWS_BROWSER_CHANNEL_MIGRATOR_H_
