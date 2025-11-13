/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_NET_QORAI_BLOCK_SAFEBROWSING_URLS_H_
#define QORAI_BROWSER_NET_QORAI_BLOCK_SAFEBROWSING_URLS_H_

class GURL;

namespace qorai {

int OnBeforeURLRequest_BlockSafeBrowsingReportingURLs(const GURL& url,
                                                      GURL* new_url);

}  // namespace qorai

#endif  // QORAI_BROWSER_NET_QORAI_BLOCK_SAFEBROWSING_URLS_H_
