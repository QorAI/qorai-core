/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "components/content_settings/core/browser/content_settings_uma_util.h"

// Leave a gap between Chromium values and our values in the kHistogramValue
// array so that we don't have to renumber when new content settings types are
// added upstream.
namespace {

// Do not change the value arbitrarily. This is used to validate we have a gap
// between Chromium's and Qorai's histograms. This value must be less than 1000
// as upstream performs a sanity check that the total number of buckets isn't
// unreasonably large.
constexpr int kQoraiValuesStart = 900;

constexpr int qorai_value(int incr) {
  return kQoraiValuesStart + incr;
}

}  // namespace

static_assert(static_cast<int>(ContentSettingsType::kMaxValue) <
                  kQoraiValuesStart,
              "There must a gap between the histograms used by Chromium, and "
              "the ones used by Qorai.");

// clang-format off
#define QORAI_HISTOGRAM_VALUE_LIST                                        \
  , \
  {ContentSettingsType::QORAI_ADS, qorai_value(0)},                       \
  {ContentSettingsType::QORAI_COSMETIC_FILTERING, qorai_value(1)},        \
  {ContentSettingsType::QORAI_TRACKERS, qorai_value(2)},                  \
  {ContentSettingsType::QORAI_HTTP_UPGRADABLE_RESOURCES, qorai_value(3)}, \
  {ContentSettingsType::QORAI_FINGERPRINTING_V2, qorai_value(4)},         \
  {ContentSettingsType::QORAI_SHIELDS, qorai_value(5)},                   \
  {ContentSettingsType::QORAI_REFERRERS, qorai_value(6)},                 \
  {ContentSettingsType::QORAI_COOKIES, qorai_value(7)},                   \
  {ContentSettingsType::QORAI_SPEEDREADER, qorai_value(8)},               \
  {ContentSettingsType::QORAI_ETHEREUM, qorai_value(9)},                  \
  {ContentSettingsType::QORAI_SOLANA, qorai_value(10)},                   \
  {ContentSettingsType::QORAI_GOOGLE_SIGN_IN, qorai_value(11)},           \
  {ContentSettingsType::QORAI_HTTPS_UPGRADE, qorai_value(12)},            \
  {ContentSettingsType::QORAI_REMEMBER_1P_STORAGE, qorai_value(13)},      \
  {ContentSettingsType::QORAI_LOCALHOST_ACCESS, qorai_value(14)},         \
  {ContentSettingsType::QORAI_OPEN_AI_CHAT, qorai_value(15)},             \
  {ContentSettingsType::QORAI_AUTO_SHRED, qorai_value(16)},               \
  /* Begin webcompat items */                                                \
  {ContentSettingsType::QORAI_WEBCOMPAT_NONE, qorai_value(50)}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_AUDIO, qorai_value(51)}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_CANVAS, qorai_value(52)}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_DEVICE_MEMORY, qorai_value(53)}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_EVENT_SOURCE_POOL, qorai_value(54)}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_FONT, qorai_value(55)}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_HARDWARE_CONCURRENCY, qorai_value(56)}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_KEYBOARD, qorai_value(57)}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_LANGUAGE, qorai_value(58)}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_MEDIA_DEVICES, qorai_value(59)}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_PLUGINS, qorai_value(60)}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_SCREEN, qorai_value(61)}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_SPEECH_SYNTHESIS, qorai_value(62)}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_USB_DEVICE_SERIAL_NUMBER, qorai_value(63)}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_USER_AGENT, qorai_value(64)}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_WEBGL, qorai_value(65)}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_WEBGL2, qorai_value(66)}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_WEB_SOCKETS_POOL, qorai_value(67)}, \
  {ContentSettingsType::QORAI_WEBCOMPAT_ALL, qorai_value(68)}, \
  {ContentSettingsType::QORAI_SHIELDS_METADATA, qorai_value(69)},  \
  {ContentSettingsType::QORAI_CARDANO, qorai_value(70)},  \
  {ContentSettingsType::QORAI_PSST, qorai_value(71)},
// clang-format on

#define kDefaultProvider       \
  kRemoteListProvider:         \
  return "RemoteListProvider"; \
  case ProviderType::kDefaultProvider

#include <components/content_settings/core/browser/content_settings_uma_util.cc>

#undef QORAI_HISTOGRAM_VALUE_LIST
#undef kDefaultProvider
