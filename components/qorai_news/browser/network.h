// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.
#ifndef QORAI_COMPONENTS_QORAI_NEWS_BROWSER_NETWORK_H_
#define QORAI_COMPONENTS_QORAI_NEWS_BROWSER_NETWORK_H_

#include "base/time/time.h"
#include "net/traffic_annotation/network_traffic_annotation.h"

namespace qorai_news {

base::TimeDelta GetDefaultRequestTimeout();
net::NetworkTrafficAnnotationTag GetNetworkTrafficAnnotationTag();

}  // namespace qorai_news

#endif  // QORAI_COMPONENTS_QORAI_NEWS_BROWSER_NETWORK_H_
