/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#define QORAI_STORAGE_ACCESS_GRANT_PERMISSION_CONTEXT_CHECK_FOR_AUTO_GRANT_OR_AUTO_DENIAL \
  NotifyPermissionSetInternal(*request_data, std::move(callback),                         \
                              /*persist=*/true, PermissionDecision::kDeny,                \
                              RequestOutcome::kDeniedByPrerequisites);                    \
  return;

#include <chrome/browser/storage_access_api/storage_access_grant_permission_context.cc>
#undef QORAI_STORAGE_ACCESS_GRANT_PERMISSION_CONTEXT_CHECK_FOR_AUTO_GRANT_OR_AUTO_DENIAL
