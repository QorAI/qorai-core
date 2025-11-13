/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#import "qorai/ios/browser/api/qorai_rewards/qorai_rewards_api.h"

#import <UIKit/UIKit.h>

#include <optional>

#include "base/apple/foundation_util.h"
#include "base/check.h"
#include "base/containers/flat_map.h"
#include "base/ios/ios_util.h"
#include "base/json/json_reader.h"
#include "base/logging.h"
#include "base/strings/sys_string_conversions.h"
#include "base/task/sequenced_task_runner.h"
#include "base/task/thread_pool.h"
#include "base/time/time.h"
#include "base/types/cxx23_to_underlying.h"
#include "base/values.h"
#include "qorai/build/ios/mojom/cpp_transformations.h"
#include "qorai/components/qorai_rewards/core/engine/hash_prefix_store.h"
#include "qorai/components/qorai_rewards/core/engine/rewards_database.h"
#include "qorai/components/qorai_rewards/core/engine/rewards_engine.h"
#include "qorai/components/qorai_rewards/core/pref_names.h"
#include "qorai/components/qorai_rewards/core/remote_worker.h"
#include "qorai/components/qorai_rewards/core/rewards_flags.h"
#include "qorai/components/qorai_rewards/core/rewards_util.h"
#import "qorai/ios/browser/api/qorai_rewards/rewards.mojom.objc+private.h"
#import "qorai/ios/browser/api/qorai_rewards/rewards_client_bridge.h"
#import "qorai/ios/browser/api/qorai_rewards/rewards_client_ios.h"
#import "qorai/ios/browser/api/qorai_rewards/rewards_notification.h"
#import "qorai/ios/browser/api/qorai_rewards/rewards_observer.h"
#import "qorai/ios/browser/api/common/common_operations.h"
#include "qorai/ios/components/prefs/pref_service_bridge_impl.h"
#include "components/os_crypt/sync/os_crypt.h"
#include "components/prefs/pref_service.h"
#include "ios/chrome/browser/shared/model/application_context/application_context.h"
#include "ios/chrome/browser/shared/model/profile/profile_ios.h"
#include "ios/chrome/browser/shared/model/profile/profile_manager_ios.h"
#include "net/base/registry_controlled_domains/registry_controlled_domain.h"
#include "url/gurl.h"
#include "url/origin.h"

#if !defined(__has_feature) || !__has_feature(objc_arc)
#error "This file requires ARC support."
#endif

namespace {

using qorai_rewards::RemoteWorker;
using qorai_rewards::mojom::RewardsEngineClient;

class RewardsDatabaseWorker
    : public RemoteWorker<qorai_rewards::mojom::RewardsDatabase> {
 public:
  RewardsDatabaseWorker() : RemoteWorker(CreateTaskRunner()) {}
  ~RewardsDatabaseWorker() = default;

 private:
  static scoped_refptr<base::SequencedTaskRunner> CreateTaskRunner() {
    return base::ThreadPool::CreateSequencedTaskRunner(
        {base::MayBlock(), base::TaskPriority::USER_VISIBLE,
         base::TaskShutdownBehavior::BLOCK_SHUTDOWN});
  }
};

class HashPrefixStoreWorker
    : public RemoteWorker<qorai_rewards::mojom::HashPrefixStore> {
 public:
  HashPrefixStoreWorker() : RemoteWorker(CreateTaskRunner()) {}
  ~HashPrefixStoreWorker() = default;

 private:
  static scoped_refptr<base::SequencedTaskRunner> CreateTaskRunner() {
    return base::ThreadPool::CreateSequencedTaskRunner(
        {base::MayBlock(), base::TaskPriority::USER_VISIBLE,
         base::TaskShutdownBehavior::SKIP_ON_SHUTDOWN});
  }
};

class RewardsEngineWorker
    : public RemoteWorker<qorai_rewards::mojom::RewardsEngine> {
 public:
  RewardsEngineWorker() : RemoteWorker(CreateTaskRunner()) {}
  ~RewardsEngineWorker() = default;

 private:
  static scoped_refptr<base::SequencedTaskRunner> CreateTaskRunner() {
    // The `WithBaseSyncPrimitives` flag is required due to the usage of [Sync]
    // interface method calls by the Rewards engine.
    return base::ThreadPool::CreateSequencedTaskRunner(
        {base::MayBlock(), base::WithBaseSyncPrimitives(),
         base::TaskPriority::USER_VISIBLE,
         base::TaskShutdownBehavior::BLOCK_SHUTDOWN});
  }
};

}  // namespace

#define LLOG(verbose_level, format, ...)                  \
  [self log:(__FILE__)                                    \
       line:(__LINE__)verboseLevel:(verbose_level)message \
           :base::SysNSStringToUTF8(                      \
                [NSString stringWithFormat:(format), ##__VA_ARGS__])]

NSString* const QoraiRewardsErrorDomain = @"QoraiRewardsErrorDomain";
NSNotificationName const QoraiRewardsNotificationAdded =
    @"BATQoraiRewardsNotificationAdded";
NSString* const QoraiRewardsDisabledByPolicyPrefName =
    base::SysUTF8ToNSString(qorai_rewards::prefs::kDisabledByPolicy);

/// ---

@interface QoraiRewardsAPI () <RewardsClientBridge> {
  scoped_refptr<base::SequencedTaskRunner> _taskRunner;
  std::unique_ptr<RewardsClientIOS> _rewardsClient;
  RewardsEngineWorker _rewardsEngine;
  RewardsDatabaseWorker _rewardsDatabase;
  HashPrefixStoreWorker _creatorPrefixStore;
}

@property(nonatomic, copy) NSString* storagePath;
@property(nonatomic) QoraiRewardsRewardsParameters* rewardsParameters;
@property(nonatomic) QoraiRewardsBalance* balance;
@property(nonatomic) dispatch_queue_t fileWriteThread;
@property(nonatomic) NSMutableDictionary<NSString*, NSString*>* state;
@property(nonatomic) QoraiCommonOperations* commonOps;
@property(nonatomic) PrefService* profilePrefService;

@property(nonatomic) NSHashTable<RewardsObserver*>* observers;

@property(nonatomic, getter=isInitialized) BOOL initialized;
@property(nonatomic) BOOL initializing;
@property(nonatomic) BOOL dataMigrationFailed;
@property(nonatomic) QoraiRewardsResult initializationResult;
@property(nonatomic, getter=isLoadingPublisherList) BOOL loadingPublisherList;
@property(nonatomic, getter=isInitializingWallet) BOOL initializingWallet;

/// Temporary blocks

@end

@implementation QoraiRewardsAPI

+ (BOOL)isSupported:(id<PrefServiceBridge>)prefService {
  PrefServiceBridgeImpl* holder =
      base::apple::ObjCCastStrict<PrefServiceBridgeImpl>(prefService);
  return qorai_rewards::IsSupported(holder.prefService);
}

- (instancetype)initWithStateStoragePath:(NSString*)path {
  if ((self = [super init])) {
    _taskRunner = base::SequencedTaskRunner::GetCurrentDefault();

    self.storagePath = path;
    self.commonOps =
        [[QoraiCommonOperations alloc] initWithStoragePath:path
                                                taskRunner:_taskRunner];
    [self initProfilePrefService];
    [self maybeMigrateProfilePrefs];

    self.state = [[NSMutableDictionary alloc]
                     initWithContentsOfFile:self.randomStatePath]
                     ?: [[NSMutableDictionary alloc] init];
    self.fileWriteThread =
        dispatch_queue_create("com.rewards.file-write", DISPATCH_QUEUE_SERIAL);
    self.observers = [NSHashTable weakObjectsHashTable];

    _rewardsClient = std::make_unique<RewardsClientIOS>(self);

    _rewardsEngine.BindRemote<qorai_rewards::internal::RewardsEngine>(
        _rewardsClient->MakeRemote(),
        [self handleFlags:qorai_rewards::RewardsFlags::ForCurrentProcess()]);

    _rewardsDatabase.BindRemote<qorai_rewards::internal::RewardsDatabase>(
        base::FilePath(base::SysNSStringToUTF8([self rewardsDatabasePath])));

    _creatorPrefixStore.BindRemote<qorai_rewards::internal::HashPrefixStore>(
        base::FilePath(base::SysNSStringToUTF8([self creatorPrefixStorePath])));
  }
  return self;
}

- (void)dealloc {
  [NSNotificationCenter.defaultCenter removeObserver:self];
}

- (qorai_rewards::mojom::RewardsEngineOptions)handleFlags:
    (const qorai_rewards::RewardsFlags&)flags {
  qorai_rewards::mojom::RewardsEngineOptions options;
  if (flags.environment) {
    switch (*flags.environment) {
      case qorai_rewards::RewardsFlags::Environment::kDevelopment:
        options.environment = qorai_rewards::mojom::Environment::kDevelopment;
        break;
      case qorai_rewards::RewardsFlags::Environment::kStaging:
        options.environment = qorai_rewards::mojom::Environment::kStaging;
        break;
      case qorai_rewards::RewardsFlags::Environment::kProduction:
        options.environment = qorai_rewards::mojom::Environment::kProduction;
        break;
    }
  }

  if (flags.reconcile_interval) {
    options.reconcile_interval = *flags.reconcile_interval;
  }

  if (flags.retry_interval) {
    options.retry_interval = *flags.retry_interval;
  }

  return options;
}

- (void)postSelfTask:(void (^)(QoraiRewardsAPI*))task {
  auto __weak weakSelf = self;
  _taskRunner->PostTask(FROM_HERE, base::BindOnce(^{
                          if (weakSelf) {
                            task(weakSelf);
                          }
                        }));
}

- (void)initializeRewardsService:(nullable void (^)())completion {
  [self postSelfTask:^(QoraiRewardsAPI* selfPtr) {
    [selfPtr initializeRewardsServiceInternal:completion];
  }];
}

- (void)initializeRewardsServiceInternal:(nullable void (^)())completion {
  if (self.initialized || self.initializing) {
    return;
  }
  self.initializing = YES;

  auto __weak weakSelf = self;
  auto callback = base::BindOnce(^(qorai_rewards::mojom::Result result) {
    auto strongSelf = weakSelf;
    if (!strongSelf) {
      return;
    }
    strongSelf.initialized =
        (result == qorai_rewards::mojom::Result::OK ||
         result == qorai_rewards::mojom::Result::NO_LEGACY_STATE ||
         result == qorai_rewards::mojom::Result::NO_PUBLISHER_STATE);
    strongSelf.initializing = NO;
    if (strongSelf.initialized) {
      [strongSelf getRewardsParameters:nil];
      [strongSelf fetchBalance:nil];
    } else {
      LLOG(0, @"Rewards Initialization Failed with error: %d",
           base::to_underlying(result));
    }
    strongSelf.initializationResult = static_cast<QoraiRewardsResult>(result);
    if (completion) {
      completion();
    }
    for (RewardsObserver* observer in [strongSelf.observers copy]) {
      if (observer.walletInitalized) {
        observer.walletInitalized(strongSelf.initializationResult);
      }
    }
  });

  _rewardsEngine->Initialize(std::move(callback));
}

- (NSString*)rewardsDatabasePath {
  return [self.storagePath stringByAppendingPathComponent:@"Rewards.db"];
}

- (NSString*)creatorPrefixStorePath {
  return
      [self.storagePath stringByAppendingPathComponent:@"RewardsCreators.db"];
}

- (void)resetRewardsDatabase {
  const auto dbPath = [self rewardsDatabasePath];
  [NSFileManager.defaultManager removeItemAtPath:dbPath error:nil];
  [NSFileManager.defaultManager
      removeItemAtPath:[dbPath stringByAppendingString:@"-journal"]
                 error:nil];
  _rewardsDatabase.BindRemote<qorai_rewards::internal::RewardsDatabase>(
      base::FilePath(base::SysNSStringToUTF8(dbPath)));

  const auto prefixPath = [self creatorPrefixStorePath];
  [NSFileManager.defaultManager removeItemAtPath:prefixPath error:nil];
  _creatorPrefixStore.BindRemote<qorai_rewards::internal::HashPrefixStore>(
      base::FilePath(base::SysNSStringToUTF8(prefixPath)));
}

- (NSString*)randomStatePath {
  return
      [self.storagePath stringByAppendingPathComponent:@"random_state.plist"];
}

#pragma mark - Observers

- (void)addObserver:(RewardsObserver*)observer {
  [self.observers addObject:observer];
}

- (void)removeObserver:(RewardsObserver*)observer {
  [self.observers removeObject:observer];
}

#pragma mark - Wallet

- (void)createWallet:(void (^)(NSError* _Nullable))completion {
  [self postSelfTask:^(QoraiRewardsAPI* selfPtr) {
    [selfPtr createWalletInternal:completion];
  }];
}

- (void)createWalletInternal:(void (^)(NSError* _Nullable))completion {
  using qorai_rewards::mojom::CreateRewardsWalletResult;

  // Results that can come from CreateRewardsWallet():
  //   - OK: Good to go
  //   - ERROR: Already initialized
  //   - BAD_REGISTRATION_RESPONSE: Request credentials call failure or
  //   malformed data
  //   - REGISTRATION_VERIFICATION_FAILED: Missing master user token
  self.initializingWallet = YES;

  auto __weak weakSelf = self;

  auto callback = base::BindOnce(^(CreateRewardsWalletResult create_result) {
    auto strongSelf = weakSelf;
    if (!strongSelf) {
      return;
    }
    qorai_rewards::mojom::Result result =
        create_result == CreateRewardsWalletResult::kSuccess
            ? qorai_rewards::mojom::Result::OK
            : qorai_rewards::mojom::Result::FAILED;

    NSError* error = nil;
    if (result != qorai_rewards::mojom::Result::OK) {
      std::map<qorai_rewards::mojom::Result, std::string> errorDescriptions{
          {qorai_rewards::mojom::Result::FAILED,
           "The wallet was already initialized"},
          {qorai_rewards::mojom::Result::BAD_REGISTRATION_RESPONSE,
           "Request credentials call failure or malformed data"},
          {qorai_rewards::mojom::Result::REGISTRATION_VERIFICATION_FAILED,
           "Missing master user token from registered persona"},
      };
      NSDictionary* userInfo = @{};
      const auto description =
          errorDescriptions[static_cast<qorai_rewards::mojom::Result>(result)];
      if (description.length() > 0) {
        userInfo =
            @{NSLocalizedDescriptionKey : base::SysUTF8ToNSString(description)};
      }
      error = [NSError errorWithDomain:QoraiRewardsErrorDomain
                                  code:static_cast<NSInteger>(result)
                              userInfo:userInfo];
    }

    strongSelf.initializingWallet = NO;

    if (completion) {
      completion(error);
    }

    for (RewardsObserver* observer in [strongSelf.observers copy]) {
      if (observer.walletInitalized) {
        observer.walletInitalized(static_cast<QoraiRewardsResult>(result));
      }
    }
  });

  _rewardsEngine->CreateRewardsWallet("", std::move(callback));
}

- (void)currentWalletInfo:
    (void (^)(QoraiRewardsRewardsWallet* _Nullable wallet))completion {
  [self postSelfTask:^(QoraiRewardsAPI* selfPtr) {
    selfPtr->_rewardsEngine->GetRewardsWallet(
        base::BindOnce(^(qorai_rewards::mojom::RewardsWalletPtr wallet) {
          const auto bridgedWallet = wallet.get() != nullptr
                                         ? [[QoraiRewardsRewardsWallet alloc]
                                               initWithRewardsWallet:*wallet]
                                         : nil;
          completion(bridgedWallet);
        }));
  }];
}

- (void)getRewardsParameters:
    (void (^)(QoraiRewardsRewardsParameters* _Nullable))completion {
  [self postSelfTask:^(QoraiRewardsAPI* selfPtr) {
    auto __weak weakSelf = selfPtr;
    selfPtr->_rewardsEngine->GetRewardsParameters(
        base::BindOnce(^(qorai_rewards::mojom::RewardsParametersPtr info) {
          auto strongSelf = weakSelf;
          if (!strongSelf) {
            return;
          }
          if (info) {
            strongSelf.rewardsParameters =
                [[QoraiRewardsRewardsParameters alloc]
                    initWithRewardsParametersPtr:std::move(info)];
          } else {
            strongSelf.rewardsParameters = nil;
          }
          if (completion) {
            completion(strongSelf.rewardsParameters);
          }
        }));
  }];
}

- (void)fetchBalance:(void (^)(QoraiRewardsBalance* _Nullable))completion {
  [self postSelfTask:^(QoraiRewardsAPI* selfPtr) {
    auto __weak weakSelf = selfPtr;
    selfPtr->_rewardsEngine->FetchBalance(
        base::BindOnce(^(qorai_rewards::mojom::BalancePtr balance) {
          auto strongSelf = weakSelf;
          if (!strongSelf) {
            return;
          }
          if (balance) {
            strongSelf.balance = [[QoraiRewardsBalance alloc]
                initWithBalancePtr:std::move(balance)];
          }
          if (completion) {
            completion(strongSelf.balance);
          }
        }));
  }];
}

#pragma mark - Publishers

- (void)listActivityInfoFromStart:(unsigned int)start
                            limit:(unsigned int)limit
                           filter:(QoraiRewardsActivityInfoFilter*)filter
                       completion:
                           (void (^)(NSArray<QoraiRewardsPublisherInfo*>*))
                               completion {
  [self postSelfTask:^(QoraiRewardsAPI* selfPtr) {
    auto cppFilter = filter ? filter.cppObjPtr
                            : qorai_rewards::mojom::ActivityInfoFilter::New();
    if (filter.excluded == QoraiRewardsExcludeFilterFilterExcluded) {
      selfPtr->_rewardsEngine->GetExcludedList(base::BindOnce(
          ^(std::vector<qorai_rewards::mojom::PublisherInfoPtr> list) {
            const auto publishers = NSArrayFromVector(
                &list, ^QoraiRewardsPublisherInfo*(
                    const qorai_rewards::mojom::PublisherInfoPtr& info) {
                  return [[QoraiRewardsPublisherInfo alloc]
                      initWithPublisherInfo:*info];
                });
            completion(publishers);
          }));
    } else {
      selfPtr->_rewardsEngine->GetActivityInfoList(
          start, limit, std::move(cppFilter),
          base::BindOnce(
              ^(std::vector<qorai_rewards::mojom::PublisherInfoPtr> list) {
                const auto publishers = NSArrayFromVector(
                    &list, ^QoraiRewardsPublisherInfo*(
                        const qorai_rewards::mojom::PublisherInfoPtr& info) {
                      return [[QoraiRewardsPublisherInfo alloc]
                          initWithPublisherInfo:*info];
                    });
                completion(publishers);
              }));
    }
  }];
}

- (void)fetchPublisherActivityFromURL:(NSURL*)URL
                           faviconURL:(nullable NSURL*)faviconURL
                        publisherBlob:(nullable NSString*)publisherBlob
                                tabId:(uint64_t)tabId {
  [self postSelfTask:^(QoraiRewardsAPI* selfPtr) {
    if (!URL.absoluteString) {
      return;
    }

    GURL parsedUrl(base::SysNSStringToUTF8(URL.absoluteString));

    if (!parsedUrl.is_valid()) {
      return;
    }

    url::Origin origin = url::Origin::Create(parsedUrl);
    std::string baseDomain = GetDomainAndRegistry(
        origin.host(),
        net::registry_controlled_domains::INCLUDE_PRIVATE_REGISTRIES);

    if (baseDomain == "") {
      return;
    }

    qorai_rewards::mojom::VisitDataPtr visitData =
        qorai_rewards::mojom::VisitData::New();
    visitData->domain = visitData->name = baseDomain;
    visitData->path = parsedUrl.PathForRequest();
    visitData->url = origin.Serialize();

    if (faviconURL.absoluteString) {
      visitData->favicon_url =
          base::SysNSStringToUTF8(faviconURL.absoluteString);
    }

    std::string blob = std::string();
    if (publisherBlob) {
      blob = base::SysNSStringToUTF8(publisherBlob);
    }

    selfPtr->_rewardsEngine->NotifyPublisherPageVisit(
        tabId, std::move(visitData), blob);
  }];
}

- (void)refreshPublisherWithId:(NSString*)publisherId
                    completion:(void (^)(QoraiRewardsPublisherStatus status))
                                   completion {
  if (self.loadingPublisherList) {
    completion(QoraiRewardsPublisherStatusNotVerified);
    return;
  }
  [self postSelfTask:^(QoraiRewardsAPI* selfPtr) {
    selfPtr->_rewardsEngine->RefreshPublisher(
        base::SysNSStringToUTF8(publisherId),
        base::BindOnce(^(qorai_rewards::mojom::PublisherStatus status) {
          completion(static_cast<QoraiRewardsPublisherStatus>(status));
        }));
  }];
}

#pragma mark - Tips

- (void)listRecurringTips:
    (void (^)(NSArray<QoraiRewardsPublisherInfo*>*))completion {
  [self postSelfTask:^(QoraiRewardsAPI* selfPtr) {
    selfPtr->_rewardsEngine->GetRecurringTips(base::BindOnce(
        ^(std::vector<qorai_rewards::mojom::PublisherInfoPtr> list) {
          const auto publishers = NSArrayFromVector(
              &list, ^QoraiRewardsPublisherInfo*(
                  const qorai_rewards::mojom::PublisherInfoPtr& info) {
                return [[QoraiRewardsPublisherInfo alloc]
                    initWithPublisherInfo:*info];
              });
          completion(publishers);
        }));
  }];
}

- (void)removeRecurringTipForPublisherWithId:(NSString*)publisherId {
  [self postSelfTask:^(QoraiRewardsAPI* selfPtr) {
    selfPtr->_rewardsEngine->RemoveRecurringTip(
        base::SysNSStringToUTF8(publisherId), base::DoNothing());
  }];
}

#pragma mark - Reconcile

- (void)onReconcileComplete:(qorai_rewards::mojom::Result)result
               contribution:
                   (qorai_rewards::mojom::ContributionInfoPtr)contribution {
  // TODO we changed from probi to amount, so from string to double
  if (result == qorai_rewards::mojom::Result::OK) {
    [self fetchBalance:nil];
  }
}

#pragma mark - Misc

- (void)rewardsInternalInfo:
    (void (^)(QoraiRewardsRewardsInternalsInfo* _Nullable info))completion {
  [self postSelfTask:^(QoraiRewardsAPI* selfPtr) {
    selfPtr->_rewardsEngine->GetRewardsInternalsInfo(
        base::BindOnce(^(qorai_rewards::mojom::RewardsInternalsInfoPtr info) {
          auto bridgedInfo = info.get() != nullptr
                                 ? [[QoraiRewardsRewardsInternalsInfo alloc]
                                       initWithRewardsInternalsInfo:*info.get()]
                                 : nil;
          completion(bridgedInfo);
        }));
  }];
}

- (void)allContributions:
    (void (^)(NSArray<QoraiRewardsContributionInfo*>* contributions))
        completion {
  [self postSelfTask:^(QoraiRewardsAPI* selfPtr) {
    selfPtr->_rewardsEngine->GetAllContributions(base::BindOnce(
        ^(std::vector<qorai_rewards::mojom::ContributionInfoPtr> list) {
          const auto convetedList = NSArrayFromVector(
              &list, ^QoraiRewardsContributionInfo*(
                  const qorai_rewards::mojom::ContributionInfoPtr& info) {
                return [[QoraiRewardsContributionInfo alloc]
                    initWithContributionInfo:*info];
              });
          completion(convetedList);
        }));
  }];
}

#pragma mark - Preferences

- (void)setMinimumVisitDuration:(int)minimumVisitDuration {
  [self postSelfTask:^(QoraiRewardsAPI* selfPtr) {
    selfPtr->_rewardsEngine->SetPublisherMinVisitTime(minimumVisitDuration);
  }];
}

- (void)setMinimumNumberOfVisits:(int)minimumNumberOfVisits {
  [self postSelfTask:^(QoraiRewardsAPI* selfPtr) {
    selfPtr->_rewardsEngine->SetPublisherMinVisits(minimumNumberOfVisits);
  }];
}

- (void)setUserPreferenceValue:(const std::string&)path
                         value:(base::Value)value
                      callback:
                          (RewardsEngineClient::SetUserPreferenceValueCallback)
                              callback {
  self.profilePrefService->Set(path, std::move(value));
  std::move(callback).Run();
}

- (void)userPreferenceValue:(const std::string&)path
                   callback:
                       (RewardsEngineClient::GetUserPreferenceValueCallback)
                           callback {
  std::move(callback).Run(self.profilePrefService->GetValue(path).Clone());
}

- (void)
    clearUserPreferenceValue:(const std::string&)path
                    callback:
                        (RewardsEngineClient::ClearUserPreferenceValueCallback)
                            callback {
  self.profilePrefService->ClearPref(path);
  std::move(callback).Run();
}

- (void)initProfilePrefService {
  std::vector<ProfileIOS*> profiles =
      GetApplicationContext()->GetProfileManager()->GetLoadedProfiles();
  CHECK(!profiles.empty());
  _profilePrefService = profiles.front()->GetPrefs();
  CHECK(_profilePrefService);
}

- (void)maybeMigrateProfilePrefs {
  // Migrates "leger_pref.plist" data into PrefService preferences.
  NSString* legacyProfilePrefsPath =
      [self.storagePath stringByAppendingPathComponent:@"ledger_pref.plist"];
  NSDictionary* legacyProfilePrefs = [[NSMutableDictionary alloc]
      initWithContentsOfFile:legacyProfilePrefsPath];
  if (!legacyProfilePrefs) {
    return;
  }

  LLOG(1, @"Migrating profile prefs");
  CHECK(self.profilePrefService);

  if ([legacyProfilePrefs objectForKey:@"wallets.qorai"]) {
    auto json = (NSString*)legacyProfilePrefs[@"wallets.qorai"];
    if (json) {
      self.profilePrefService->SetString(qorai_rewards::prefs::kWalletQorai,
                                         base::SysNSStringToUTF8(json));
    }
  }

  if ([legacyProfilePrefs objectForKey:@"creation_stamp"]) {
    auto value = [legacyProfilePrefs[@"creation_stamp"] unsignedLongLongValue];
    self.profilePrefService->SetUint64(qorai_rewards::prefs::kCreationStamp,
                                       value);
  }

  if ([legacyProfilePrefs objectForKey:@"publisher_prefix_list_stamp"]) {
    auto value = [legacyProfilePrefs[@"publisher_prefix_list_stamp"]
        unsignedLongLongValue];
    self.profilePrefService->SetUint64(
        qorai_rewards::prefs::kServerPublisherListStamp, value);
  }

  NSError* error = nil;
  [[NSFileManager defaultManager] removeItemAtPath:legacyProfilePrefsPath
                                             error:&error];
  if (error) {
    LLOG(0, @"Failed to remove legacy prefs: %@", error);
  }
}

#pragma mark - Notifications

- (void)clearAllNotifications {
  // Not used on iOS
}

#pragma mark - Network

- (NSString*)customUserAgent {
  return self.commonOps.customUserAgent;
}

- (void)setCustomUserAgent:(NSString*)customUserAgent {
  self.commonOps.customUserAgent = [customUserAgent
      stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
}

- (void)loadUrl:(qorai_rewards::mojom::UrlRequestPtr)request
       callback:(RewardsEngineClient::LoadURLCallback)callback {
  std::map<qorai_rewards::mojom::UrlMethod, std::string> methodMap{
      {qorai_rewards::mojom::UrlMethod::GET, "GET"},
      {qorai_rewards::mojom::UrlMethod::POST, "POST"},
      {qorai_rewards::mojom::UrlMethod::PUT, "PUT"},
      {qorai_rewards::mojom::UrlMethod::DEL, "DELETE"}};

  if (!request) {
    request = qorai_rewards::mojom::UrlRequest::New();
  }

  const auto copiedURL = base::SysUTF8ToNSString(request->url);

  auto cb = std::make_shared<decltype(callback)>(std::move(callback));
  return [self.commonOps
      loadURLRequest:request->url
             headers:request->headers
             content:request->content
        content_type:request->content_type
              method:methodMap[request->method]
            callback:^(
                const std::string& errorDescription, int statusCode,
                NSData* responseData,
                const base::flat_map<std::string, std::string>& headers) {
              std::string response;
              if (responseData && responseData.length > 0) {
                response =
                    std::string(static_cast<const char*>(responseData.bytes),
                                responseData.length);
              }

              auto url_response = qorai_rewards::mojom::UrlResponse::New();
              url_response->url = base::SysNSStringToUTF8(copiedURL);
              url_response->error = errorDescription;
              url_response->status_code = statusCode;
              url_response->body = response;
              url_response->headers = headers;

              if (cb) {
                std::move(*cb).Run(std::move(url_response));
              }
            }];
}

- (void)fetchFavIcon:(const std::string&)url
          faviconKey:(const std::string&)faviconKey
            callback:(RewardsEngineClient::FetchFavIconCallback)callback {
  std::move(callback).Run(NO, std::string());
}

#pragma mark - Logging

- (void)log:(const std::string&)file
            line:(int32_t)line
    verboseLevel:(int32_t)verboseLevel
         message:(const std::string&)message {
  const int vlog_level =
      logging::GetVlogLevelHelper(file.c_str(), file.length());
  if (verboseLevel <= vlog_level) {
    logging::LogMessage(file.c_str(), line, -verboseLevel).stream() << message;
  }
}

#pragma mark - Publisher Database

- (void)publisherListNormalized:
    (std::vector<qorai_rewards::mojom::PublisherInfoPtr>)list {
  // Not used on iOS
}

- (void)onPanelPublisherInfo:(qorai_rewards::mojom::Result)result
               publisherInfo:
                   (qorai_rewards::mojom::PublisherInfoPtr)publisher_info
                    windowId:(uint64_t)windowId {
  if (publisher_info.get() == nullptr ||
      result != qorai_rewards::mojom::Result::OK) {
    return;
  }
  auto info =
      [[QoraiRewardsPublisherInfo alloc] initWithPublisherInfo:*publisher_info];
  for (RewardsObserver* observer in [self.observers copy]) {
    if (observer.fetchedPanelPublisher) {
      observer.fetchedPanelPublisher(info, windowId);
    }
  }
}

- (void)onPublisherRegistryUpdated {
  // Not used on iOS
}

- (void)onPublisherUpdated:(const std::string&)publisherId {
  // Not used on iOS
}

- (void)showNotification:(const std::string&)type
                    args:(std::vector<std::string>)args
                callback:
                    (RewardsEngineClient::ShowNotificationCallback)callback {
  // Not used on iOS
}

- (void)reconcileStampReset {
  // Not used on iOS
}

- (void)runDbTransaction:(qorai_rewards::mojom::DBTransactionPtr)transaction
                callback:
                    (RewardsEngineClient::RunDBTransactionCallback)callback {
  _rewardsDatabase->RunDBTransaction(std::move(transaction),
                                     std::move(callback));
}

- (void)
    updateCreatorPrefixStore:
        (qorai_rewards::mojom::HashPrefixDataPtr)prefix_data
                    callback:
                        (RewardsEngineClient::UpdateCreatorPrefixStoreCallback)
                            callback {
  _creatorPrefixStore->UpdatePrefixes(std::move(prefix_data),
                                      std::move(callback));
}

- (void)creatorPrefixStoreContains:(const std::string&)value
                          callback:
                              (RewardsEngineClient::
                                   CreatorPrefixStoreContainsCallback)callback {
  _creatorPrefixStore->ContainsPrefix(value, std::move(callback));
}

- (void)walletDisconnected:(const std::string&)wallet_type {
  // Not used on iOS
}

- (void)deleteLog:(RewardsEngineClient::DeleteLogCallback)callback {
  std::move(callback).Run(qorai_rewards::mojom::Result::OK);
}

- (void)encryptString:(const std::string&)value
             callback:(RewardsEngineClient::EncryptStringCallback)callback {
  std::string encrypted_value;
  if (!OSCrypt::EncryptString(value, &encrypted_value)) {
    std::move(callback).Run(std::nullopt);
    return;
  }
  std::move(callback).Run(std::make_optional(encrypted_value));
}

- (void)decryptString:(const std::string&)value
             callback:(RewardsEngineClient::DecryptStringCallback)callback {
  std::string decrypted_value;
  if (!OSCrypt::DecryptString(value, &decrypted_value)) {
    std::move(callback).Run(std::nullopt);
    return;
  }
  std::move(callback).Run(std::make_optional(decrypted_value));
}

- (void)externalWalletConnected {
  // Not used on iOS
}

- (void)externalWalletLoggedOut {
  // Not used on iOS
}

- (void)externalWalletReconnected {
  // Not used on iOS
}

- (void)externalWalletDisconnected {
  // Not used on iOS
}

@end
