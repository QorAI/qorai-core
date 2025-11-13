/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/global_state/global_state_holder.h"

#include "base/check.h"
#include "base/threading/sequence_local_storage_slot.h"
#include "qorai/components/qorai_ads/core/internal/global_state/global_state.h"

namespace qorai_ads {

namespace {

GlobalState*& GetGlobalStateInstance() {
  static base::SequenceLocalStorageSlot<GlobalState*> global_state_instance;
  return global_state_instance.GetOrCreateValue();
}

}  // namespace

GlobalStateHolder::GlobalStateHolder(GlobalState* const global_state) {
  GlobalState*& global_state_instance = GetGlobalStateInstance();
  CHECK(!global_state_instance);
  global_state_instance = global_state;
}

GlobalStateHolder::~GlobalStateHolder() {
  GlobalState*& global_state_instance = GetGlobalStateInstance();
  CHECK(global_state_instance);
  global_state_instance = nullptr;
}

// static
GlobalState* GlobalStateHolder::GetGlobalState() {
  GlobalState* global_state_instance = GetGlobalStateInstance();
  return global_state_instance;
}

}  // namespace qorai_ads
