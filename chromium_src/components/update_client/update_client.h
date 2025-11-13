/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_UPDATE_CLIENT_UPDATE_CLIENT_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_UPDATE_CLIENT_UPDATE_CLIENT_H_

#define Uninstall(...)      \
  IsQoraiComponent() const; \
  virtual bool Uninstall(__VA_ARGS__)

#define UpdateClientFactory                                             \
  UpdateClientFactory_ChromiumImpl(scoped_refptr<Configurator> config); \
  scoped_refptr<UpdateClient> UpdateClientFactory

#include <components/update_client/update_client.h>  // IWYU pragma: export

#undef Uninstall
#undef UpdateClientFactory

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_UPDATE_CLIENT_UPDATE_CLIENT_H_
