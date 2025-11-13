/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#define InitializePageLoadMetricsForWebContents \
  InitializePageLoadMetricsForWebContents_Chromium
#include <chrome/browser/page_load_metrics/page_load_metrics_initialize.cc>
#undef InitializePageLoadMetricsForWebContents

#include "qorai/components/qorai_perf_predictor/browser/perf_predictor_page_metrics_observer.h"

namespace {

class QoraiPageLoadMetricsEmbedder : public PageLoadMetricsEmbedder {
 public:
  explicit QoraiPageLoadMetricsEmbedder(content::WebContents* web_contents);
  QoraiPageLoadMetricsEmbedder(const QoraiPageLoadMetricsEmbedder&) = delete;
  QoraiPageLoadMetricsEmbedder& operator=(const QoraiPageLoadMetricsEmbedder&) =
      delete;
  ~QoraiPageLoadMetricsEmbedder() override;

 protected:
  // page_load_metrics::PageLoadMetricsEmbedderBase:
  void RegisterObservers(page_load_metrics::PageLoadTracker* tracker,
                         content::NavigationHandle* navigation_handle) override;
};

QoraiPageLoadMetricsEmbedder::QoraiPageLoadMetricsEmbedder(
    content::WebContents* web_contents)
    : PageLoadMetricsEmbedder(web_contents) {}

QoraiPageLoadMetricsEmbedder::~QoraiPageLoadMetricsEmbedder() = default;

void QoraiPageLoadMetricsEmbedder::RegisterObservers(
    page_load_metrics::PageLoadTracker* tracker,
    content::NavigationHandle* navigation_handle) {
  PageLoadMetricsEmbedder::RegisterObservers(tracker, navigation_handle);

  tracker->AddObserver(
      std::make_unique<
          qorai_perf_predictor::PerfPredictorPageMetricsObserver>());
}

}  // namespace

void InitializePageLoadMetricsForWebContents(
    content::WebContents* web_contents) {
  // TODO(bug https://github.com/qorai/qorai-browser/issues/7784)
  // change
  // android_webview/browser/page_load_metrics/page_load_metrics_initialize.cc
  // as well to register Page Load Metrics Observers
  page_load_metrics::MetricsWebContentsObserver::CreateForWebContents(
      web_contents,
      std::make_unique<QoraiPageLoadMetricsEmbedder>(web_contents));
}
