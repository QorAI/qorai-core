/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_PURCHASE_INTENT_PROCESSOR_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_PURCHASE_INTENT_PROCESSOR_H_

#include <cstdint>
#include <map>
#include <optional>
#include <string>

#include "base/memory/raw_ref.h"
#include "qorai/components/qorai_ads/core/internal/segments/segment_alias.h"
#include "qorai/components/qorai_ads/core/internal/tabs/tab_manager_observer.h"
#include "qorai/components/qorai_ads/core/internal/targeting/behavioral/purchase_intent/keyphrase/purchase_intent_keyphrase_alias.h"

class GURL;

namespace qorai_ads {

class PurchaseIntentResource;
struct PurchaseIntentFunnelInfo;
struct PurchaseIntentSignalInfo;
struct TabInfo;

class PurchaseIntentProcessor final : public TabManagerObserver {
 public:
  explicit PurchaseIntentProcessor(PurchaseIntentResource& resource);

  PurchaseIntentProcessor(const PurchaseIntentProcessor&) = delete;
  PurchaseIntentProcessor& operator=(const PurchaseIntentProcessor&) = delete;

  ~PurchaseIntentProcessor() override;

  void Process(const GURL& url);

 private:
  bool ShouldProcess(int32_t tab_id, const GURL& url) const;
  void MaybeProcess(int32_t tab_id, const GURL& url);

  std::optional<PurchaseIntentSignalInfo> MaybeExtractSignal(
      const GURL& url) const;
  std::optional<PurchaseIntentSignalInfo> MaybeExtractSignalForSearchQuery(
      const std::string& search_query) const;
  std::optional<SegmentList> MaybeGetSegmentsForSearchQuery(
      const KeywordList& search_query_keywords) const;
  int ComputeFunnelKeyphraseWeightForSearchQuery(
      const KeywordList& search_query_keywords) const;

  std::optional<PurchaseIntentSignalInfo> MaybeExtractSignalForUrl(
      const GURL& url) const;
  std::optional<PurchaseIntentFunnelInfo> MaybeGetFunnelForUrl(
      const GURL& url) const;

  // TabManagerObserver:
  void OnDidOpenNewTab(const TabInfo& tab) override;
  void OnTabDidChange(const TabInfo& tab) override;
  void OnDidCloseTab(int32_t tab_id) override;

  std::map</*tab_id*/ int32_t, GURL> tabs_;

  const raw_ref<PurchaseIntentResource> resource_;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_PURCHASE_INTENT_PROCESSOR_H_
