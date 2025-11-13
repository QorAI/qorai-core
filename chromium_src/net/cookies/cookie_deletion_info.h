/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_NET_COOKIES_COOKIE_DELETION_INFO_H_
#define QORAI_CHROMIUM_SRC_NET_COOKIES_COOKIE_DELETION_INFO_H_

#define QORAI_COOKIE_DELETION_INFO_H \
  std::optional<std::string> ephemeral_storage_domain;

#include <net/cookies/cookie_deletion_info.h>  // IWYU pragma: export

#include <optional>

#undef QORAI_COOKIE_DELETION_INFO_H

#endif  // QORAI_CHROMIUM_SRC_NET_COOKIES_COOKIE_DELETION_INFO_H_
