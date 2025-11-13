/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_SANDBOX_WIN_SRC_INTERCEPTORS_H_
#define QORAI_CHROMIUM_SRC_SANDBOX_WIN_SRC_INTERCEPTORS_H_

// clang-format off

#define CREATE_SECTION_ID      \
  CREATE_SECTION_ID,           \
  GET_MODULE_FILENAME_A_ID,    \
  GET_MODULE_FILENAME_W_ID,    \
  GET_MODULE_FILENAME_EX_A_ID, \
  GET_MODULE_FILENAME_EX_W_ID

// clang-format on

#include <sandbox/win/src/interceptors.h>  // IWYU pragma: export

#undef CREATE_SECTION_ID

#endif  // QORAI_CHROMIUM_SRC_SANDBOX_WIN_SRC_INTERCEPTORS_H_
