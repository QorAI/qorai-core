/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_CONSTANTS_NETWORK_CONSTANTS_H_
#define QORAI_COMPONENTS_CONSTANTS_NETWORK_CONSTANTS_H_

inline constexpr char kExtensionUpdaterDomain[] = "extensionupdater.qorai.com";

inline constexpr char kQoraiUsageStandardPath[] = "/1/usage/qorai-core";

inline constexpr char kQoraiReferralsInitPath[] = "/promo/initialize/nonua";
inline constexpr char kQoraiReferralsActivityPath[] = "/promo/activity";

inline constexpr char kQoraiSafeBrowsing2Proxy[] = "safebrowsing2.qorai.com";
inline constexpr char kQoraiSafeBrowsingSslProxy[] = "sb-ssl.qorai.com";
inline constexpr char kQoraiRedirectorProxy[] = "redirector.qorai.com";
inline constexpr char kQoraiClients4Proxy[] = "clients4.qorai.com";
inline constexpr char kQoraiStaticProxy[] = "static1.qorai.com";

inline constexpr char kAutofillPrefix[] = "https://www.gstatic.com/autofill/*";
inline constexpr char kClients4Prefix[] = "*://clients4.google.com/";
inline constexpr char kCRXDownloadPrefix[] =
    "*://clients2.googleusercontent.com/crx/blobs/*crx*";
inline constexpr char kEmptyDataURI[] = "data:text/plain,";
inline constexpr char kEmptyImageDataURI[] =
    "data:image/gif;base64,R0lGODlhAQABAIAAAAAAAP///"
    "yH5BAEAAAAALAAAAAABAAEAAAIBRAA7";
inline constexpr char kJSDataURLPrefix[] =
    "data:application/javascript;base64,";
inline constexpr char kGeoLocationsPattern[] =
    "https://www.googleapis.com/geolocation/v1/geolocate?key=*";
inline constexpr char kSafeBrowsingPrefix[] =
    "https://safebrowsing.googleapis.com/";
inline constexpr char kSafeBrowsingCrxListPrefix[] =
    "https://safebrowsing.google.com/safebrowsing/clientreport/crx-list-info";
inline constexpr char kSafeBrowsingFileCheckPrefix[] =
    "https://sb-ssl.google.com/safebrowsing/clientreport/download";
inline constexpr char kCRLSetPrefix1[] =
    "*://dl.google.com/release2/chrome_component/*crl-set*";
inline constexpr char kCRLSetPrefix2[] =
    "*://*.gvt1.com/edgedl/release2/chrome_component/*";
inline constexpr char kCRLSetPrefix3[] =
    "*://www.google.com/dl/release2/chrome_component/*";
inline constexpr char kCRLSetPrefix4[] =
    "*://storage.googleapis.com/update-delta/hfnkpimlhhgieaddgfemjhofmfblmnib"
    "/*crxd";
inline constexpr char kChromeCastPrefix[] =
    "*://*.gvt1.com/edgedl/chromewebstore/*pkedcjkdefgpdelpbcmbmeomcjbeemfm*";

inline constexpr char kWidevineGvt1Prefix[] =
    "*://*.gvt1.com/*oimompecagnajdejgnnjijobebaeigek*";
inline constexpr char kWidevineGoogleDlPrefix[] =
    "*://dl.google.com/*oimompecagnajdejgnnjijobebaeigek*";

inline constexpr char kUserAgentHeader[] = "User-Agent";
inline constexpr char kQoraiServicesKeyHeader[] = "QoraiServiceKey";

inline constexpr char kBittorrentMimeType[] = "application/x-bittorrent";
inline constexpr char kOctetStreamMimeType[] = "application/octet-stream";

inline constexpr char kSecGpcHeader[] = "Sec-GPC";

#endif  // QORAI_COMPONENTS_CONSTANTS_NETWORK_CONSTANTS_H_
