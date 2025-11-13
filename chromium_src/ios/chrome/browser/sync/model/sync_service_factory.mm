/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/sync/qorai_sync_service_impl_delegate.h"
#include "qorai/components/sync/service/qorai_sync_service_impl.h"
#include "ios/chrome/browser/history/model/history_service_factory.h"
#include "ios/chrome/browser/sync/model/device_info_sync_service_factory.h"

#define QORAI_BUILD_SERVICE_INSTANCE_FOR                        \
  std::make_unique<syncer::QoraiSyncServiceImpl>(               \
      std::move(init_params),                                   \
      std::make_unique<syncer::QoraiSyncServiceImplDelegate>(   \
          DeviceInfoSyncServiceFactory::GetForProfile(profile), \
          ios::HistoryServiceFactory::GetForProfile(            \
              profile, ServiceAccessType::IMPLICIT_ACCESS)));

#include <ios/chrome/browser/sync/model/sync_service_factory.mm>

#undef QORAI_BUILD_SERVICE_INSTANCE_FOR
