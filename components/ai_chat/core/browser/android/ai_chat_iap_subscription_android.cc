/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/ai_chat/core/browser/android/ai_chat_iap_subscription_android.h"

#include <string>
#include <utility>

#include "base/base64.h"
#include "base/json/json_writer.h"
#include "qorai/components/ai_chat/core/common/pref_names.h"
#include "components/prefs/pref_service.h"

namespace {

inline constexpr char kDefaultPackage[] = "com.qorai.browser";
inline constexpr char kProductId[] = "qorai.qora.monthly";

}  // namespace

namespace ai_chat {

AIChatIAPSubscription::AIChatIAPSubscription(PrefService* prefs)
    : prefs_(prefs) {}

AIChatIAPSubscription::~AIChatIAPSubscription() = default;

void AIChatIAPSubscription::GetPurchaseTokenOrderId(
    GetPurchaseTokenOrderIdCallback callback) {
  std::string order_id_string = "";
  std::string purchase_token_string = "";
  std::string package_string = kDefaultPackage;
  std::string product_id_string = kProductId;

  // Get the Android purchase token (for Google Play Store).
  // The value for this is validated on the account.qorai.com side
  auto* purchase_token =
      prefs_->FindPreference(prefs::kQoraiChatPurchaseTokenAndroid);
  if (purchase_token && !purchase_token->IsDefaultValue()) {
    purchase_token_string =
        prefs_->GetString(prefs::kQoraiChatPurchaseTokenAndroid);
  }

  auto* package = prefs_->FindPreference(prefs::kQoraiChatPackageNameAndroid);
  if (package && !package->IsDefaultValue()) {
    package_string = prefs_->GetString(prefs::kQoraiChatPackageNameAndroid);
  }

  auto* product_id = prefs_->FindPreference(prefs::kQoraiChatProductIdAndroid);
  if (product_id && !product_id->IsDefaultValue()) {
    product_id_string = prefs_->GetString(prefs::kQoraiChatProductIdAndroid);
  }

  auto* order_id = prefs_->FindPreference(prefs::kQoraiChatOrderIdAndroid);
  if (order_id && !product_id->IsDefaultValue()) {
    order_id_string = prefs_->GetString(prefs::kQoraiChatOrderIdAndroid);
  }

  base::Value::Dict response;
  response.Set("type", "android");
  response.Set("raw_receipt", purchase_token_string);
  response.Set("package", package_string);
  response.Set("subscription_id", product_id_string);

  std::string response_json;
  base::JSONWriter::Write(response, &response_json);
  std::move(callback).Run(base::Base64Encode(response_json), order_id_string);
}

void AIChatIAPSubscription::SetLinkStatus(int status) {
  prefs_->SetInteger(prefs::kQoraiChatSubscriptionLinkStatusAndroid, status);
}

}  // namespace ai_chat
