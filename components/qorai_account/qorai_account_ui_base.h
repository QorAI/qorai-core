/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ACCOUNT_QORAI_ACCOUNT_UI_BASE_H_
#define QORAI_COMPONENTS_QORAI_ACCOUNT_QORAI_ACCOUNT_UI_BASE_H_

#include <utility>

#include "base/check.h"
#include "base/check_deref.h"
#include "base/containers/span.h"
#include "base/functional/callback_forward.h"
#include "base/functional/callback_helpers.h"
#include "base/memory/raw_ref.h"
#include "qorai/components/qorai_account/qorai_account_service.h"
#include "qorai/components/qorai_account/features.h"
#include "qorai/components/qorai_account/mojom/qorai_account.mojom.h"
#include "qorai/components/qorai_account/resources/grit/qorai_account_resources.h"
#include "qorai/components/qorai_account/resources/grit/qorai_account_resources_map.h"
#include "qorai/components/constants/webui_url_constants.h"
#include "qorai/components/password_strength_meter/password_strength_meter.h"
#include "qorai/components/password_strength_meter/password_strength_meter.mojom.h"
#include "components/grit/qorai_components_resources.h"
#include "components/grit/qorai_components_strings.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "services/network/public/mojom/content_security_policy.mojom.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/base/webui/resource_path.h"
#include "ui/base/webui/web_ui_util.h"

// Template base class for Qorai Account WebUI controllers.
//
// `QoraiAccountUIBase` encapsulates shared setup logic for Qorai Account WebUIs
// across desktop, Android, and iOS. It streamlines the creation and
// configuration of a WebUIDataSource.
//
// Intended to be subclassed with the appropriate WebUIDataSource and
// QoraiAccountServiceFactory types.
template <typename WebUIDataSource, typename QoraiAccountServiceFactory>
class QoraiAccountUIBase {
 public:
  template <typename Profile>
  explicit QoraiAccountUIBase(
      Profile* profile,
      base::OnceCallback<void(WebUIDataSource*,
                              base::span<const webui::ResourcePath>,
                              int)> setup_webui_data_source = base::DoNothing())
      : qorai_account_service_(
            CHECK_DEREF(QoraiAccountServiceFactory::GetFor(profile))) {
    CHECK(qorai_account::features::IsQoraiAccountEnabled());

    auto* source = WebUIDataSource::CreateAndAdd(profile, kQoraiAccountHost);
    std::move(setup_webui_data_source)
        .Run(source, kQoraiAccountResources,
             IDR_QORAI_ACCOUNT_QORAI_ACCOUNT_PAGE_HTML);
    SetupWebUIDataSource(source);
  }

  void BindInterface(mojo::PendingReceiver<qorai_account::mojom::Authentication>
                         pending_receiver) {
    qorai_account_service_->BindInterface(std::move(pending_receiver));
  }

  void BindInterface(mojo::PendingReceiver<
                     password_strength_meter::mojom::PasswordStrengthMeter>
                         pending_receiver) {
    password_strength_meter::BindInterface(std::move(pending_receiver));
  }

 private:
  static inline constexpr char16_t kQoraiAccountSelfCustodyLearnMoreURL[] =
      u"https://search.qorai.com";
  static inline constexpr char16_t kQoraiAccountTermsOfServiceURL[] =
      u"https://qorai.com/terms-of-use/";
  static inline constexpr char16_t kQoraiAccountPrivacyAgreementURL[] =
      u"https://qorai.com/privacy/browser/";

  void SetupWebUIDataSource(WebUIDataSource* source) {
    source->OverrideContentSecurityPolicy(
        network::mojom::CSPDirectiveName::ScriptSrc,
        "script-src chrome://resources 'self' 'wasm-unsafe-eval';");
    source->OverrideContentSecurityPolicy(
        network::mojom::CSPDirectiveName::RequireTrustedTypesFor,
        "require-trusted-types-for 'script';");
    source->OverrideContentSecurityPolicy(
        network::mojom::CSPDirectiveName::TrustedTypes,
        "trusted-types lit-html-desktop;");

    source->UseStringsJs();
    source->EnableReplaceI18nInJS();

    source->AddResourcePaths(kQoraiAccountResources);
    source->AddResourcePath("", IDR_QORAI_ACCOUNT_QORAI_ACCOUNT_PAGE_HTML);

    static constexpr webui::LocalizedString kStrings[] = {
        {"qoraiAccountPageTitle", IDS_QORAI_ACCOUNT_PAGE_TITLE},
        // 'Entry' dialog:
        {"qoraiAccountEntryDialogTitle", IDS_QORAI_ACCOUNT_ENTRY_DIALOG_TITLE},
        {"qoraiAccountEntryDialogDescription",
         IDS_QORAI_ACCOUNT_ENTRY_DIALOG_DESCRIPTION},
        {"qoraiAccountCreateQoraiAccountButtonLabel",
         IDS_QORAI_ACCOUNT_ENTRY_DIALOG_CREATE_QORAI_ACCOUNT_BUTTON_LABEL},
        {"qoraiAccountAlreadyHaveAccountSignInButtonLabel",
         IDS_QORAI_ACCOUNT_ALREADY_HAVE_ACCOUNT_SIGN_IN_BUTTON_LABEL},
        {"qoraiAccountSelfCustodyButtonLabel",
         IDS_QORAI_ACCOUNT_SELF_CUSTODY_BUTTON_LABEL},
        // 'Create' dialog:
        {"qoraiAccountCreateDialogTitle",
         IDS_QORAI_ACCOUNT_CREATE_DIALOG_TITLE},
        {"qoraiAccountCreateDialogDescription",
         IDS_QORAI_ACCOUNT_CREATE_DIALOG_DESCRIPTION},
        {"qoraiAccountEmailInputErrorMessage",
         IDS_QORAI_ACCOUNT_EMAIL_INPUT_ERROR_MESSAGE},
        {"qoraiAccountCreatePasswordInputLabel",
         IDS_QORAI_ACCOUNT_CREATE_PASSWORD_INPUT_LABEL},
        {"qoraiAccountPasswordStrengthMeterWeak",
         IDS_QORAI_ACCOUNT_PASSWORD_STRENGTH_METER_WEAK},
        {"qoraiAccountPasswordStrengthMeterMedium",
         IDS_QORAI_ACCOUNT_PASSWORD_STRENGTH_METER_MEDIUM},
        {"qoraiAccountPasswordStrengthMeterStrong",
         IDS_QORAI_ACCOUNT_PASSWORD_STRENGTH_METER_STRONG},
        {"qoraiAccountConfirmPasswordInputLabel",
         IDS_QORAI_ACCOUNT_CONFIRM_PASSWORD_INPUT_LABEL},
        {"qoraiAccountConfirmPasswordInputPlaceholder",
         IDS_QORAI_ACCOUNT_CONFIRM_PASSWORD_INPUT_PLACEHOLDER},
        {"qoraiAccountConfirmPasswordInputErrorMessage",
         IDS_QORAI_ACCOUNT_CONFIRM_PASSWORD_INPUT_ERROR_MESSAGE},
        {"qoraiAccountConfirmPasswordInputSuccessMessage",
         IDS_QORAI_ACCOUNT_CONFIRM_PASSWORD_INPUT_SUCCESS_MESSAGE},
        {"qoraiAccountCreateAccountButtonLabel",
         IDS_QORAI_ACCOUNT_CREATE_ACCOUNT_BUTTON_LABEL},
        // 'Sign In' dialog:
        {"qoraiAccountSignInDialogTitle",
         IDS_QORAI_ACCOUNT_SIGN_IN_DIALOG_TITLE},
        {"qoraiAccountSignInDialogDescription",
         IDS_QORAI_ACCOUNT_SIGN_IN_DIALOG_DESCRIPTION},
        {"qoraiAccountPasswordInputLabel",
         IDS_QORAI_ACCOUNT_PASSWORD_INPUT_LABEL},
        {"qoraiAccountForgotPasswordButtonLabel",
         IDS_QORAI_ACCOUNT_FORGOT_PASSWORD_BUTTON_LABEL},
        {"qoraiAccountSignInButtonLabel",
         IDS_QORAI_ACCOUNT_SIGN_IN_BUTTON_LABEL},
        // 'Forgot Password' dialog:
        {"qoraiAccountForgotPasswordDialogTitle",
         IDS_QORAI_ACCOUNT_FORGOT_PASSWORD_DIALOG_TITLE},
        {"qoraiAccountForgotPasswordDialogDescription",
         IDS_QORAI_ACCOUNT_FORGOT_PASSWORD_DIALOG_DESCRIPTION},
        {"qoraiAccountAlertMessage", IDS_QORAI_ACCOUNT_ALERT_MESSAGE},
        {"qoraiAccountResetPasswordButtonLabel",
         IDS_QORAI_ACCOUNT_RESET_PASSWORD_BUTTON_LABEL},
        // 'Error' dialog:
        {"qoraiAccountErrorDialogTitle", IDS_QORAI_ACCOUNT_ERROR_DIALOG_TITLE},
        {"qoraiAccountErrorDialogDescription",
         IDS_QORAI_ACCOUNT_ERROR_DIALOG_DESCRIPTION},
        {"qoraiAccountErrorDialogError", IDS_QORAI_ACCOUNT_ERROR_DIALOG_ERROR},
        {"qoraiAccountErrorDialogClientError",
         IDS_QORAI_ACCOUNT_ERROR_DIALOG_CLIENT_ERROR},
        {"qoraiAccountErrorDialogServerError",
         IDS_QORAI_ACCOUNT_ERROR_DIALOG_SERVER_ERROR},
        {"qoraiAccountErrorDialogAccountExists",
         IDS_QORAI_ACCOUNT_ERROR_DIALOG_ACCOUNT_EXISTS},
        {"qoraiAccountErrorDialogEmailDomainNotSupported",
         IDS_QORAI_ACCOUNT_ERROR_DIALOG_EMAIL_DOMAIN_NOT_SUPPORTED},
        {"qoraiAccountErrorDialogTooManyVerifications",
         IDS_QORAI_ACCOUNT_ERROR_DIALOG_TOO_MANY_VERIFICATIONS},
        // Common:
        {"qoraiAccountBackButtonLabel", IDS_QORAI_ACCOUNT_BACK_BUTTON_LABEL},
        {"qoraiAccountEmailInputLabel", IDS_QORAI_ACCOUNT_EMAIL_INPUT_LABEL},
        {"qoraiAccountEmailInputPlaceholder",
         IDS_QORAI_ACCOUNT_EMAIL_INPUT_PLACEHOLDER},
        {"qoraiAccountPasswordInputPlaceholder",
         IDS_QORAI_ACCOUNT_PASSWORD_INPUT_PLACEHOLDER},
    };

    source->AddLocalizedStrings(kStrings);

    source->AddString(
        "qoraiAccountSelfCustodyDescription",
        l10n_util::GetStringFUTF16(IDS_QORAI_ACCOUNT_SELF_CUSTODY_DESCRIPTION,
                                   kQoraiAccountSelfCustodyLearnMoreURL));
    source->AddString(
        "qoraiAccountConsentCheckboxLabel",
        l10n_util::GetStringFUTF16(IDS_QORAI_ACCOUNT_CONSENT_CHECKBOX_LABEL,
                                   kQoraiAccountTermsOfServiceURL,
                                   kQoraiAccountPrivacyAgreementURL));

    source->AddResourcePath("full_qorai_brand.svg",
                            IDR_QORAI_ACCOUNT_IMAGES_FULL_QORAI_BRAND_SVG);
    source->AddResourcePath("full_qorai_brand_dark.svg",
                            IDR_QORAI_ACCOUNT_IMAGES_FULL_QORAI_BRAND_DARK_SVG);
  }

 private:
  const raw_ref<qorai_account::QoraiAccountService> qorai_account_service_;
};

#endif  // QORAI_COMPONENTS_QORAI_ACCOUNT_QORAI_ACCOUNT_UI_BASE_H_
