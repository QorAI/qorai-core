/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#import "qorai/ios/browser/api/sync/driver/qorai_sync_profile_service.h"

#include <array>
#include <unordered_map>

#include "base/memory/raw_ptr.h"
#include "components/sync/base/data_type.h"
#include "components/sync/base/user_selectable_type.h"
#include "components/sync/service/sync_service.h"
#include "components/sync/service/sync_user_settings.h"
#include "ios/web/public/thread/web_thread.h"

#if !defined(__has_feature) || !__has_feature(objc_arc)
#error "This file requires ARC support."
#endif

static_assert(static_cast<NSInteger>(syncer::UserSelectableType::kCookies) ==
                  static_cast<NSInteger>(syncer::UserSelectableType::kLastType),
              "syncer::UserSelectableType has changed in a Chromium update");

namespace qorai {
namespace ios {
constexpr auto kMapping = std::to_array<
    std::pair<syncer::UserSelectableType, QoraiSyncUserSelectableTypes>>(
    {{syncer::UserSelectableType::kBookmarks,
      QoraiSyncUserSelectableTypes_BOOKMARKS},
     {syncer::UserSelectableType::kPreferences,
      QoraiSyncUserSelectableTypes_PREFERENCES},
     {syncer::UserSelectableType::kPasswords,
      QoraiSyncUserSelectableTypes_PASSWORDS},
     {syncer::UserSelectableType::kAutofill,
      QoraiSyncUserSelectableTypes_AUTOFILL},
     {syncer::UserSelectableType::kThemes, QoraiSyncUserSelectableTypes_THEMES},
     {syncer::UserSelectableType::kHistory,
      QoraiSyncUserSelectableTypes_HISTORY},
     {syncer::UserSelectableType::kExtensions,
      QoraiSyncUserSelectableTypes_EXTENSIONS},
     {syncer::UserSelectableType::kApps, QoraiSyncUserSelectableTypes_APPS},
     {syncer::UserSelectableType::kReadingList,
      QoraiSyncUserSelectableTypes_READING_LIST},
     {syncer::UserSelectableType::kTabs, QoraiSyncUserSelectableTypes_TABS},
     {syncer::UserSelectableType::kSavedTabGroups,
      QoraiSyncUserSelectableTypes_SAVED_TAB_GROUPS},
     {syncer::UserSelectableType::kPayments,
      QoraiSyncUserSelectableTypes_PAYMENTS},
     {syncer::UserSelectableType::kProductComparison,
      QoraiSyncUserSelectableTypes_PRODUCT_COMPARISON},
     {syncer::UserSelectableType::kCookies,
      QoraiSyncUserSelectableTypes_COOKIES}});

syncer::UserSelectableTypeSet user_types_from_options(
    QoraiSyncUserSelectableTypes options) {
  syncer::UserSelectableTypeSet results;
  for (auto entry : kMapping) {
    if (options & entry.second) {
      results.Put(entry.first);
    }
  }
  return results;
}

QoraiSyncUserSelectableTypes options_from_user_types(
    const syncer::UserSelectableTypeSet& types) {
  QoraiSyncUserSelectableTypes results = QoraiSyncUserSelectableTypes_NONE;
  for (auto entry : kMapping) {
    if (types.Has(entry.first)) {
      results |= entry.second;
    }
  }
  return results;
}
}  // namespace ios
}  // namespace qorai

@interface QoraiSyncProfileServiceIOS () {
  raw_ptr<syncer::SyncService> sync_service_;
  std::unordered_map<syncer::UserSelectableType, QoraiSyncUserSelectableTypes>
      type_mapping;
}
@end

@implementation QoraiSyncProfileServiceIOS

- (instancetype)initWithProfileSyncService:(syncer::SyncService*)syncService {
  if ((self = [super init])) {
    DCHECK_CURRENTLY_ON(web::WebThread::UI);
    sync_service_ = syncService;
  }
  return self;
}

- (bool)isSyncFeatureActive {
  DCHECK_CURRENTLY_ON(web::WebThread::UI);
  return sync_service_->IsSyncFeatureActive();
}

- (QoraiSyncUserSelectableTypes)activeSelectableTypes {
  DCHECK_CURRENTLY_ON(web::WebThread::UI);
  syncer::DataTypeSet active_types = sync_service_->GetActiveDataTypes();

  syncer::UserSelectableTypeSet user_types;
  for (syncer::UserSelectableType type : syncer::UserSelectableTypeSet::All()) {
    if (active_types.Has(syncer::UserSelectableTypeToCanonicalDataType(type))) {
      user_types.Put(type);
    }
  }
  return qorai::ios::options_from_user_types(user_types);
}

- (QoraiSyncUserSelectableTypes)userSelectedTypes {
  DCHECK_CURRENTLY_ON(web::WebThread::UI);
  syncer::UserSelectableTypeSet types =
      sync_service_->GetUserSettings()->GetSelectedTypes();
  return qorai::ios::options_from_user_types(types);
}

- (void)setUserSelectedTypes:(QoraiSyncUserSelectableTypes)options {
  DCHECK_CURRENTLY_ON(web::WebThread::UI);
  bool sync_everything = false;
  syncer::UserSelectableTypeSet selected_types =
      qorai::ios::user_types_from_options(options);
  sync_service_->GetUserSettings()->SetSelectedTypes(sync_everything,
                                                     selected_types);
}

@end
