// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/ios/browser/api/password/importer/qorai_password_importer.h"

#include "base/apple/foundation_util.h"
#include "base/base_paths.h"
#include "base/files/file_path.h"
#include "base/functional/bind.h"
#include "base/functional/callback_helpers.h"
#include "base/strings/sys_string_conversions.h"
#include "base/task/task_traits.h"
#include "base/task/thread_pool.h"
#include "qorai/components/password_manager/core/browser/import/safari_password_importer.h"
#include "components/keyed_service/core/service_access_type.h"
#include "components/password_manager/core/browser/password_store/password_store_interface.h"
#include "components/password_manager/core/browser/ui/saved_passwords_presenter.h"
#include "ios/chrome/browser/affiliations/model/ios_chrome_affiliation_service_factory.h"
#include "ios/chrome/browser/passwords/model/ios_chrome_account_password_store_factory.h"
#include "ios/chrome/browser/passwords/model/ios_chrome_profile_password_store_factory.h"
#include "ios/chrome/browser/shared/model/application_context/application_context.h"
#include "ios/chrome/browser/shared/model/profile/profile_ios.h"
#include "ios/chrome/browser/shared/model/profile/profile_manager_ios.h"
#include "ios/chrome/browser/webauthn/model/ios_passkey_model_factory.h"
#include "ios/web/public/thread/web_task_traits.h"
#include "ios/web/public/thread/web_thread.h"

// MARK: - QoraiPasswordImportEntryStatus

QoraiPasswordImportEntryStatus const QoraiPasswordImportEntryStatusNone =
    static_cast<NSInteger>(password_manager::SafariImportEntry::Status::NONE);
QoraiPasswordImportEntryStatus const
    QoraiPasswordImportEntryStatusUnknownError = static_cast<NSInteger>(
        password_manager::SafariImportEntry::Status::UNKNOWN_ERROR);
QoraiPasswordImportEntryStatus const
    QoraiPasswordImportEntryStatusMissingPassword = static_cast<NSInteger>(
        password_manager::SafariImportEntry::Status::MISSING_PASSWORD);
QoraiPasswordImportEntryStatus const QoraiPasswordImportEntryStatusMissingURL =
    static_cast<NSInteger>(
        password_manager::SafariImportEntry::Status::MISSING_URL);
QoraiPasswordImportEntryStatus const QoraiPasswordImportEntryStatusInvalidURL =
    static_cast<NSInteger>(
        password_manager::SafariImportEntry::Status::INVALID_URL);
QoraiPasswordImportEntryStatus const QoraiPasswordImportEntryStatusLongURL =
    static_cast<NSInteger>(
        password_manager::SafariImportEntry::Status::LONG_URL);
QoraiPasswordImportEntryStatus const
    QoraiPasswordImportEntryStatusLongPassword = static_cast<NSInteger>(
        password_manager::SafariImportEntry::Status::LONG_PASSWORD);
QoraiPasswordImportEntryStatus const
    QoraiPasswordImportEntryStatusLongUsername = static_cast<NSInteger>(
        password_manager::SafariImportEntry::Status::LONG_USERNAME);
QoraiPasswordImportEntryStatus const
    QoraiPasswordImportEntryStatusConflictProfile = static_cast<NSInteger>(
        password_manager::SafariImportEntry::Status::CONFLICT_PROFILE);
QoraiPasswordImportEntryStatus const
    QoraiPasswordImportEntryStatusConflictAccount = static_cast<NSInteger>(
        password_manager::SafariImportEntry::Status::CONFLICT_ACCOUNT);
QoraiPasswordImportEntryStatus const QoraiPasswordImportEntryStatusLongNote =
    static_cast<NSInteger>(
        password_manager::SafariImportEntry::Status::LONG_NOTE);
QoraiPasswordImportEntryStatus const
    QoraiPasswordImportEntryStatusLongConcatenatedNote = static_cast<NSInteger>(
        password_manager::SafariImportEntry::Status::LONG_CONCATENATED_NOTE);
QoraiPasswordImportEntryStatus const QoraiPasswordImportEntryStatusValid =
    static_cast<NSInteger>(password_manager::SafariImportEntry::Status::VALID);

// MARK: - QoraiPasswordImporterResultsStatus

QoraiPasswordImporterResultsStatus const
    QoraiPasswordImporterResultsStatusNone = static_cast<NSInteger>(
        password_manager::SafariImportResults::Status::NONE);
QoraiPasswordImporterResultsStatus const
    QoraiPasswordImporterResultsStatusUnknownError = static_cast<NSInteger>(
        password_manager::SafariImportResults::Status::UNKNOWN_ERROR);
QoraiPasswordImporterResultsStatus const
    QoraiPasswordImporterResultsStatusSuccess = static_cast<NSInteger>(
        password_manager::SafariImportResults::Status::SUCCESS);
QoraiPasswordImporterResultsStatus const
    QoraiPasswordImporterResultsStatusIOError = static_cast<NSInteger>(
        password_manager::SafariImportResults::Status::IO_ERROR);
QoraiPasswordImporterResultsStatus const
    QoraiPasswordImporterResultsStatusBadFormat = static_cast<NSInteger>(
        password_manager::SafariImportResults::Status::BAD_FORMAT);
QoraiPasswordImporterResultsStatus const
    QoraiPasswordImporterResultsStatusDismissed = static_cast<NSInteger>(
        password_manager::SafariImportResults::Status::DISMISSED);
QoraiPasswordImporterResultsStatus const
    QoraiPasswordImporterResultsStatusMaxFileSize = static_cast<NSInteger>(
        password_manager::SafariImportResults::Status::MAX_FILE_SIZE);
QoraiPasswordImporterResultsStatus const
    QoraiPasswordImporterResultsStatusImportAlreadyActive = static_cast<
        NSInteger>(
        password_manager::SafariImportResults::Status::IMPORT_ALREADY_ACTIVE);
QoraiPasswordImporterResultsStatus const
    QoraiPasswordImporterResultsStatusNumPasswordsExceeded = static_cast<
        NSInteger>(
        password_manager::SafariImportResults::Status::NUM_PASSWORDS_EXCEEDED);
QoraiPasswordImporterResultsStatus const
    QoraiPasswordImporterResultsStatusConflicts = static_cast<NSInteger>(
        password_manager::SafariImportResults::Status::CONFLICTS);

// MARK: - QoraiPasswordImportEntry

@implementation QoraiPasswordImportEntry
- (instancetype)initWithEntry:
    (const password_manager::SafariImportEntry&)entry {
  if ((self = [super init])) {
  }
  return self;
}
@end

// MARK: - QoraiPasswordImporterResults

@interface QoraiPasswordImporterResults () {
  password_manager::SafariImportResults results_;
}
@end

@implementation QoraiPasswordImporterResults
- (instancetype)initWithResults:
    (const password_manager::SafariImportResults&)results {
  if ((self = [super init])) {
    results_ = results;
  }
  return self;
}

- (QoraiPasswordImporterResultsStatus)status {
  return static_cast<QoraiPasswordImporterResultsStatus>(results_.status);
}

- (NSString*)fileName {
  return base::SysUTF8ToNSString(results_.file_name);
}

- (NSUInteger)numberImported {
  return results_.number_imported;
}

- (NSArray<QoraiPasswordImportEntry*>*)displayedEntries {
  NSMutableArray* result = [[NSMutableArray alloc] init];

  for (const auto& entry : results_.displayed_entries) {
    [result addObject:[[QoraiPasswordImportEntry alloc] initWithEntry:entry]];
  }

  return [result copy];
}
@end

// MARK: - QoraiPasswordImporter

namespace {
// Returns a passkey model instance if the feature is enabled.
webauthn::PasskeyModel* MaybeGetPasskeyModel(ProfileIOS* profile) {
  return IOSPasskeyModelFactory::GetInstance()->GetForProfile(profile);
}

}  // namespace

@interface QoraiPasswordImporter () {
  std::unique_ptr<password_manager::SavedPasswordsPresenter> _presenter;
  std::unique_ptr<password_manager::SafariPasswordImporter> _safari_importer;
}
@end

@implementation QoraiPasswordImporter

- (void)importPasswords:(NSString*)filePath
             completion:(void (^)(QoraiPasswordImporterResults*))completion {
  __weak QoraiPasswordImporter* weakSelf = self;

  auto start_import = ^{
    __strong QoraiPasswordImporter* importer = weakSelf;
    if (!importer) {
      return;
    }

    std::vector<ProfileIOS*> profiles =
        GetApplicationContext()->GetProfileManager()->GetLoadedProfiles();
    ProfileIOS* last_used_profile = profiles.at(0);

    importer->_presenter =
        std::make_unique<password_manager::SavedPasswordsPresenter>(
            IOSChromeAffiliationServiceFactory::GetForProfile(
                last_used_profile),
            IOSChromeProfilePasswordStoreFactory::GetForProfile(
                last_used_profile, ServiceAccessType::EXPLICIT_ACCESS),
            IOSChromeAccountPasswordStoreFactory::GetForProfile(
                last_used_profile, ServiceAccessType::EXPLICIT_ACCESS),
            MaybeGetPasskeyModel(last_used_profile));

    importer->_safari_importer =
        std::make_unique<password_manager::SafariPasswordImporter>(
            importer->_presenter.get());

    // Execute the importer

    importer->_presenter->Init(base::BindOnce(^{
      if (!importer) {
        return;
      }

      base::FilePath path = base::apple::NSStringToFilePath(filePath);
      auto password_store =
          password_manager::PasswordForm::Store::kProfileStore;

      importer->_safari_importer->Import(
          path, password_store,
          base::BindOnce(
              ^(const password_manager::SafariImportResults& results) {
                completion([[QoraiPasswordImporterResults alloc]
                    initWithResults:results]);
              }));
    }));
  };

  web::GetUIThreadTaskRunner({})->PostTask(FROM_HERE,
                                           base::BindOnce(start_import));
}

- (void)continueImport:(NSArray<QoraiPasswordImportEntry*>*)entriesToReplace
            completion:(void (^)(QoraiPasswordImporterResults*))completion {
  __weak QoraiPasswordImporter* weakSelf = self;

  auto continue_import = ^{
    __strong QoraiPasswordImporter* importer = weakSelf;
    if (!importer) {
      return;
    }

    std::vector<int> entry_ids;
    for (QoraiPasswordImportEntry* entry in entriesToReplace) {
      entry_ids.push_back(entry.id);
    }

    importer->_safari_importer->ContinueImport(
        entry_ids,
        base::BindOnce(^(const password_manager::SafariImportResults& results) {
          completion(
              [[QoraiPasswordImporterResults alloc] initWithResults:results]);
        }));
  };

  web::GetUIThreadTaskRunner({})->PostTask(FROM_HERE,
                                           base::BindOnce(continue_import));
}

@end
