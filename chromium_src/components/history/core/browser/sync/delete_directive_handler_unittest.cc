/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <components/history/core/browser/sync/delete_directive_handler_unittest.cc>

namespace history {
namespace {

TEST_F(HistoryDeleteDirectiveHandlerTest,
       QoraiCreateUrlDeleteDirectiveReturnsFalse) {
  EXPECT_FALSE(handler()->CreateUrlDeleteDirective(GURL("https://qorai.com")));
}

}  // namespace
}  // namespace history
