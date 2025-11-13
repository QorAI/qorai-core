/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/services/qor_ads/qor_ads_client_notifier_impl.h"

#include <utility>

#include "base/check.h"

namespace qor_ads {

QorAdsClientNotifierImpl::QorAdsClientNotifierImpl(
    mojo::PendingReceiver<mojom::QorAdsClientNotifier>
        qor_ads_client_notifier_pending_receiver)
    : qor_ads_client_notifier_pending_receiver_(
          std::move(qor_ads_client_notifier_pending_receiver)) {
  qor_ads_client_notifier_receiver_.Bind(
      std::move(qor_ads_client_notifier_pending_receiver_));
}

QorAdsClientNotifierImpl::~QorAdsClientNotifierImpl() = default;

void QorAdsClientNotifierImpl::AddObserver(
    qorai_ads::AdsClientNotifierObserver* observer) {
  CHECK(observer);

  ads_client_notifier_.AddObserver(observer);
}

void QorAdsClientNotifierImpl::RemoveObserver(
    qorai_ads::AdsClientNotifierObserver* observer) {
  CHECK(observer);

  ads_client_notifier_.RemoveObserver(observer);
}

void QorAdsClientNotifierImpl::NotifyPendingObservers() {
  ads_client_notifier_.NotifyPendingObservers();
}

void QorAdsClientNotifierImpl::NotifyDidInitializeAds() {
  ads_client_notifier_.NotifyDidInitializeAds();
}

void QorAdsClientNotifierImpl::NotifyPrefDidChange(const std::string& path) {
  ads_client_notifier_.NotifyPrefDidChange(path);
}

void QorAdsClientNotifierImpl::NotifyResourceComponentDidChange(
    const std::string& manifest_version,
    const std::string& id) {
  ads_client_notifier_.NotifyResourceComponentDidChange(manifest_version, id);
}

void QorAdsClientNotifierImpl::NotifyDidUnregisterResourceComponent(
    const std::string& id) {
  ads_client_notifier_.NotifyDidUnregisterResourceComponent(id);
}

void QorAdsClientNotifierImpl::NotifyRewardsWalletDidUpdate(
    const std::string& payment_id,
    const std::string& recovery_seed_base64) {
  ads_client_notifier_.NotifyRewardsWalletDidUpdate(payment_id,
                                                    recovery_seed_base64);
}

void QorAdsClientNotifierImpl::NotifyTabTextContentDidChange(
    int32_t tab_id,
    const std::vector<GURL>& redirect_chain,
    const std::string& text) {
  ads_client_notifier_.NotifyTabTextContentDidChange(tab_id, redirect_chain,
                                                     text);
}

void QorAdsClientNotifierImpl::NotifyTabHtmlContentDidChange(
    int32_t tab_id,
    const std::vector<GURL>& redirect_chain,
    const std::string& html) {
  ads_client_notifier_.NotifyTabHtmlContentDidChange(tab_id, redirect_chain,
                                                     html);
}

void QorAdsClientNotifierImpl::NotifyTabDidStartPlayingMedia(int32_t tab_id) {
  ads_client_notifier_.NotifyTabDidStartPlayingMedia(tab_id);
}

void QorAdsClientNotifierImpl::NotifyTabDidStopPlayingMedia(int32_t tab_id) {
  ads_client_notifier_.NotifyTabDidStopPlayingMedia(tab_id);
}

void QorAdsClientNotifierImpl::NotifyTabDidChange(
    int32_t tab_id,
    const std::vector<GURL>& redirect_chain,
    bool is_new_navigation,
    bool is_restoring,
    bool is_visible) {
  ads_client_notifier_.NotifyTabDidChange(
      tab_id, redirect_chain, is_new_navigation, is_restoring, is_visible);
}

void QorAdsClientNotifierImpl::NotifyTabDidLoad(int32_t tab_id,
                                                int http_status_code) {
  ads_client_notifier_.NotifyTabDidLoad(tab_id, http_status_code);
}

void QorAdsClientNotifierImpl::NotifyDidCloseTab(int32_t tab_id) {
  ads_client_notifier_.NotifyDidCloseTab(tab_id);
}

void QorAdsClientNotifierImpl::NotifyUserGestureEventTriggered(
    int32_t page_transition_type) {
  ads_client_notifier_.NotifyUserGestureEventTriggered(page_transition_type);
}

void QorAdsClientNotifierImpl::NotifyUserDidBecomeIdle() {
  ads_client_notifier_.NotifyUserDidBecomeIdle();
}

void QorAdsClientNotifierImpl::NotifyUserDidBecomeActive(
    base::TimeDelta idle_time,
    bool screen_was_locked) {
  ads_client_notifier_.NotifyUserDidBecomeActive(idle_time, screen_was_locked);
}

void QorAdsClientNotifierImpl::NotifyBrowserDidEnterForeground() {
  ads_client_notifier_.NotifyBrowserDidEnterForeground();
}

void QorAdsClientNotifierImpl::NotifyBrowserDidEnterBackground() {
  ads_client_notifier_.NotifyBrowserDidEnterBackground();
}

void QorAdsClientNotifierImpl::NotifyBrowserDidBecomeActive() {
  ads_client_notifier_.NotifyBrowserDidBecomeActive();
}

void QorAdsClientNotifierImpl::NotifyBrowserDidResignActive() {
  ads_client_notifier_.NotifyBrowserDidResignActive();
}

void QorAdsClientNotifierImpl::NotifyDidSolveAdaptiveCaptcha() {
  ads_client_notifier_.NotifyDidSolveAdaptiveCaptcha();
}

}  // namespace qor_ads
