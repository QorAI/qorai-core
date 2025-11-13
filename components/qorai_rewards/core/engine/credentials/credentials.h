/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_CREDENTIALS_CREDENTIALS_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_CREDENTIALS_CREDENTIALS_H_

#include "qorai/components/qorai_rewards/core/engine/credentials/credentials_redeem.h"
#include "qorai/components/qorai_rewards/core/engine/credentials/credentials_trigger.h"
#include "qorai/components/qorai_rewards/core/engine/rewards_callbacks.h"
#include "qorai/components/qorai_rewards/core/mojom/rewards_engine_internal.mojom.h"

namespace qorai_rewards::internal {
namespace credential {

class Credentials {
 public:
  virtual ~Credentials() = default;

  virtual void Start(const CredentialsTrigger& trigger,
                     ResultCallback callback) = 0;

  virtual void RedeemTokens(const CredentialsRedeem& redeem,
                            ResultCallback callback) = 0;

 protected:
  virtual void Blind(ResultCallback callback,
                     const CredentialsTrigger& trigger) = 0;

  virtual void Claim(ResultCallback callback,
                     const CredentialsTrigger& trigger,
                     mojom::CredsBatchPtr creds) = 0;

  virtual void Unblind(ResultCallback callback,
                       const CredentialsTrigger& trigger,
                       mojom::CredsBatchPtr creds) = 0;

  virtual void Completed(ResultCallback callback,
                         const CredentialsTrigger& trigger,
                         mojom::Result result) = 0;
};

}  // namespace credential
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_CREDENTIALS_CREDENTIALS_H_
