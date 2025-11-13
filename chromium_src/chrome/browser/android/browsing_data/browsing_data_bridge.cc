/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#define QORAI_CLEAR_BROWSING_DATA                                             \
  remove_mask |= BrowsingDataRemover::DATA_TYPE_DOWNLOADS;                    \
  break;                                                                      \
  case browsing_data::BrowsingDataType::QORAI_AI_CHAT:                        \
    remove_mask |= chrome_browsing_data_remover::DATA_TYPE_QORAI_QORA_HISTORY; \
    break;

#include <chrome/browser/android/browsing_data/browsing_data_bridge.cc>
#undef QORAI_CLEAR_BROWSING_DATA
