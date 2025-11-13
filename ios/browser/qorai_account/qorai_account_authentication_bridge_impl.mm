/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/ios/browser/qorai_account/qorai_account_authentication_bridge_impl.h"

#include "base/apple/foundation_util.h"
#include "base/check_deref.h"
#include "base/strings/sys_string_conversions.h"
#include "qorai/components/qorai_account/qorai_account_service.h"
#include "qorai/components/qorai_account/mojom/qorai_account.mojom.h"
#include "qorai/components/qorai_account/pref_names.h"
#include "qorai/ios/browser/api/profile/profile_bridge.h"
#include "qorai/ios/browser/api/profile/profile_bridge_impl.h"
#include "qorai/ios/browser/qorai_account/qorai_account_service_factory_ios.h"
#include "ios/chrome/browser/shared/model/profile/profile_ios.h"
#include "mojo/public/cpp/bindings/remote.h"

NSString* const QoraiAccountAuthenticationTokenPref =
    base::SysUTF8ToNSString(qorai_account::prefs::kAuthenticationToken);
NSString* const QoraiAccountVerificationTokenPref =
    base::SysUTF8ToNSString(qorai_account::prefs::kVerificationToken);

@implementation QoraiAccountAuthenticationBridgeImpl {
  mojo::Remote<qorai_account::mojom::Authentication> _authentication;
}

- (instancetype)initWithProfile:(id<ProfileBridge>)profileBridge {
  if ((self = [super init])) {
    ProfileBridgeImpl* holder =
        base::apple::ObjCCastStrict<ProfileBridgeImpl>(profileBridge);
    auto* qorai_account_service =
        qorai_account::QoraiAccountServiceFactoryIOS::GetFor(holder.profile);
    CHECK_DEREF(qorai_account_service)
        .BindInterface(_authentication.BindNewPipeAndPassReceiver());
  }
  return self;
}

- (void)resendConfirmationEmail {
  _authentication->ResendConfirmationEmail();
}

- (void)cancelRegistration {
  _authentication->CancelRegistration();
}

- (void)logOut {
  _authentication->LogOut();
}

@end
