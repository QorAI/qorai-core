/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CONTENT_TEST_MOCK_CLIPBOARD_HOST_H_
#define QORAI_CHROMIUM_SRC_CONTENT_TEST_MOCK_CLIPBOARD_HOST_H_

#include "third_party/blink/public/mojom/clipboard/clipboard.mojom.h"

#define CommitWrite       \
  CommitWrite() override; \
  void SanitizeOnNextWriteText

#include <content/test/mock_clipboard_host.h>  // IWYU pragma: export

#undef CommitWrite

#endif  // QORAI_CHROMIUM_SRC_CONTENT_TEST_MOCK_CLIPBOARD_HOST_H_
