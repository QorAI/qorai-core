/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_SIGNIN_PUBLIC_IDENTITY_MANAGER_IDENTITY_MANAGER_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_SIGNIN_PUBLIC_IDENTITY_MANAGER_IDENTITY_MANAGER_H_

#define GetAccountsInCookieJar           \
  GetAccountsInCookieJar_Unused() const; \
  AccountsInCookieJarInfo GetAccountsInCookieJar

#define PrepareForAddingNewAccount     \
  PrepareForAddingNewAccount_Unused(); \
  void PrepareForAddingNewAccount

#include <components/signin/public/identity_manager/identity_manager.h>  // IWYU pragma: export

#undef PrepareForAddingNewAccount
#undef GetAccountsInCookieJar

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_SIGNIN_PUBLIC_IDENTITY_MANAGER_IDENTITY_MANAGER_H_
