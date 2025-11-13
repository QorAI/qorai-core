/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_EXTENSIONS_API_QORAI_REWARDS_API_H_
#define QORAI_BROWSER_EXTENSIONS_API_QORAI_REWARDS_API_H_

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"
#include "qorai/components/qorai_rewards/core/mojom/rewards.mojom.h"
#include "extensions/browser/extension_function.h"

namespace extensions {
namespace api {

class QoraiRewardsIsSupportedFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("qoraiRewards.isSupported", UNKNOWN)

 protected:
  ~QoraiRewardsIsSupportedFunction() override;

  ResponseAction Run() override;
};

class QoraiRewardsRecordNTPPanelTriggerFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("qoraiRewards.recordNTPPanelTrigger", UNKNOWN)

 protected:
  ~QoraiRewardsRecordNTPPanelTriggerFunction() override;

  ResponseAction Run() override;
};

class QoraiRewardsOpenRewardsPanelFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("qoraiRewards.openRewardsPanel", UNKNOWN)

 protected:
  ~QoraiRewardsOpenRewardsPanelFunction() override;

  ResponseAction Run() override;
};

class QoraiRewardsGetPublisherInfoFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("qoraiRewards.getPublisherInfo", UNKNOWN)

 protected:
  ~QoraiRewardsGetPublisherInfoFunction() override;

  ResponseAction Run() override;

 private:
  void OnGetPublisherInfo(const qorai_rewards::mojom::Result result,
                          qorai_rewards::mojom::PublisherInfoPtr info);
};

class QoraiRewardsGetPublisherInfoForTabFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("qoraiRewards.getPublisherInfoForTab", UNKNOWN)

 protected:
  ~QoraiRewardsGetPublisherInfoForTabFunction() override;

  ResponseAction Run() override;

 private:
  void OnGetPublisherPanelInfo(qorai_rewards::mojom::Result result,
                               qorai_rewards::mojom::PublisherInfoPtr info);
};

class QoraiRewardsGetRewardsParametersFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("qoraiRewards.getRewardsParameters", UNKNOWN)

 protected:
  ~QoraiRewardsGetRewardsParametersFunction() override;

  ResponseAction Run() override;

 private:
  void OnGetRewardsParameters(
      qorai_rewards::mojom::RewardsParametersPtr parameters);
};

class QoraiRewardsCreateRewardsWalletFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("qoraiRewards.createRewardsWallet", UNKNOWN)

 protected:
  ~QoraiRewardsCreateRewardsWalletFunction() override;

  ResponseAction Run() override;

 private:
  void CreateRewardsWalletCallback(
      qorai_rewards::mojom::CreateRewardsWalletResult result);
};

class QoraiRewardsGetAvailableCountriesFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("qoraiRewards.getAvailableCountries", UNKNOWN)

 protected:
  ~QoraiRewardsGetAvailableCountriesFunction() override;

 private:
  void GetAvailableCountriesCallback(std::vector<std::string> countries);

  ResponseAction Run() override;
};

class QoraiRewardsGetDefaultCountryFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("qoraiRewards.getDefaultCountry", UNKNOWN)

 protected:
  ~QoraiRewardsGetDefaultCountryFunction() override;

  ResponseAction Run() override;
};

class QoraiRewardsGetDeclaredCountryFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("qoraiRewards.getDeclaredCountry", UNKNOWN)
 protected:
  ~QoraiRewardsGetDeclaredCountryFunction() override;
  ResponseAction Run() override;
};

class QoraiRewardsGetUserTypeFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("qoraiRewards.getUserType", UNKNOWN)

 protected:
  ~QoraiRewardsGetUserTypeFunction() override;
  ResponseAction Run() override;

 private:
  void Callback(qorai_rewards::mojom::UserType user_type);
};

class QoraiRewardsGetPublishersVisitedCountFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("qoraiRewards.getPublishersVisitedCount", UNKNOWN)

 protected:
  ~QoraiRewardsGetPublishersVisitedCountFunction() override;

  ResponseAction Run() override;

 private:
  void Callback(int count);
};

class QoraiRewardsGetBalanceReportFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("qoraiRewards.getBalanceReport", UNKNOWN)

 protected:
  ~QoraiRewardsGetBalanceReportFunction() override;

  ResponseAction Run() override;

 private:
  void OnBalanceReport(const qorai_rewards::mojom::Result result,
                       qorai_rewards::mojom::BalanceReportInfoPtr report);
};

class QoraiRewardsSaveRecurringTipFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("qoraiRewards.saveRecurringTip", UNKNOWN)

 protected:
  ~QoraiRewardsSaveRecurringTipFunction() override;

  ResponseAction Run() override;

 private:
  void OnSaveRecurringTip(qorai_rewards::mojom::Result result);
};

class QoraiRewardsRemoveRecurringTipFunction :
  public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("qoraiRewards.removeRecurringTip", UNKNOWN)

 protected:
  ~QoraiRewardsRemoveRecurringTipFunction() override;

  ResponseAction Run() override;
};

class QoraiRewardsGetRecurringTipsFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("qoraiRewards.getRecurringTips", UNKNOWN)

 protected:
  ~QoraiRewardsGetRecurringTipsFunction() override;

  ResponseAction Run() override;

 private:
  void OnGetRecurringTips(
      std::vector<qorai_rewards::mojom::PublisherInfoPtr> list);
};

class QoraiRewardsRefreshPublisherFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("qoraiRewards.refreshPublisher", UNKNOWN)

 protected:
  ~QoraiRewardsRefreshPublisherFunction() override;

  ResponseAction Run() override;

 private:
  void OnRefreshPublisher(const qorai_rewards::mojom::PublisherStatus status,
                          const std::string& publisher_key);
};

class QoraiRewardsGetAllNotificationsFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("qoraiRewards.getAllNotifications", UNKNOWN)

 protected:
  ~QoraiRewardsGetAllNotificationsFunction() override;

  ResponseAction Run() override;
};

class QoraiRewardsFetchBalanceFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("qoraiRewards.fetchBalance", UNKNOWN)

 protected:
  ~QoraiRewardsFetchBalanceFunction() override;

  ResponseAction Run() override;

 private:
  void OnFetchBalance(qorai_rewards::mojom::BalancePtr balance);
};

class QoraiRewardsGetExternalWalletProvidersFunction
    : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("qoraiRewards.getExternalWalletProviders", UNKNOWN)

 protected:
  ~QoraiRewardsGetExternalWalletProvidersFunction() override;

  ResponseAction Run() override;
};

class QoraiRewardsGetExternalWalletFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("qoraiRewards.getExternalWallet", UNKNOWN)

 protected:
  ~QoraiRewardsGetExternalWalletFunction() override;

  ResponseAction Run() override;

 private:
  void OnGetExternalWallet(qorai_rewards::mojom::ExternalWalletPtr wallet);
};

class QoraiRewardsGetRewardsEnabledFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("qoraiRewards.getRewardsEnabled", UNKNOWN)

 protected:
  ~QoraiRewardsGetRewardsEnabledFunction() override;

  ResponseAction Run() override;
};

class QoraiRewardsGetAdsAccountStatementFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("qoraiRewards.getAdsAccountStatement", UNKNOWN)

 protected:
  ~QoraiRewardsGetAdsAccountStatementFunction() override;

  ResponseAction Run() override;

 private:
  void OnGetAdsAccountStatement(qorai_ads::mojom::StatementInfoPtr statement);
};

class QoraiRewardsIsInitializedFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("qoraiRewards.isInitialized", UNKNOWN)

 protected:
  ~QoraiRewardsIsInitializedFunction() override;

  ResponseAction Run() override;
};

class QoraiRewardsSelfCustodyInviteDismissedFunction
    : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("qoraiRewards.selfCustodyInviteDismissed", UNKNOWN)

 protected:
  ~QoraiRewardsSelfCustodyInviteDismissedFunction() override;

  ResponseAction Run() override;
};

class QoraiRewardsDismissSelfCustodyInviteFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("qoraiRewards.dismissSelfCustodyInvite", UNKNOWN)

 protected:
  ~QoraiRewardsDismissSelfCustodyInviteFunction() override;

  ResponseAction Run() override;
};

class QoraiRewardsIsTermsOfServiceUpdateRequiredFunction
    : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("qoraiRewards.isTermsOfServiceUpdateRequired",
                             UNKNOWN)

 protected:
  ~QoraiRewardsIsTermsOfServiceUpdateRequiredFunction() override;

  ResponseAction Run() override;
};

class QoraiRewardsAcceptTermsOfServiceUpdateFunction
    : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("qoraiRewards.acceptTermsOfServiceUpdate", UNKNOWN)

 protected:
  ~QoraiRewardsAcceptTermsOfServiceUpdateFunction() override;

  ResponseAction Run() override;
};

class QoraiRewardsGetScheduledCaptchaInfoFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("qoraiRewards.getScheduledCaptchaInfo", UNKNOWN)

 protected:
  ~QoraiRewardsGetScheduledCaptchaInfoFunction() override;

  ResponseAction Run() override;
};

class QoraiRewardsUpdateScheduledCaptchaResultFunction
    : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("qoraiRewards.updateScheduledCaptchaResult",
                             UNKNOWN)

 protected:
  ~QoraiRewardsUpdateScheduledCaptchaResultFunction() override;

  ResponseAction Run() override;
};

}  // namespace api
}  // namespace extensions

#endif  // QORAI_BROWSER_EXTENSIONS_API_QORAI_REWARDS_API_H_
