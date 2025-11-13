/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_P3A_HISTOGRAMS_QORAIIZER_H_
#define QORAI_COMPONENTS_P3A_HISTOGRAMS_QORAIIZER_H_

#include <memory>
#include <vector>

#include "base/memory/ref_counted.h"
#include "base/metrics/histogram_base.h"
#include "base/metrics/statistics_recorder.h"

namespace p3a {

class HistogramsQoraiizer
    : public base::RefCountedThreadSafe<HistogramsQoraiizer> {
 public:
  static scoped_refptr<p3a::HistogramsQoraiizer> Create();

  HistogramsQoraiizer();

  HistogramsQoraiizer(const HistogramsQoraiizer&) = delete;
  HistogramsQoraiizer& operator=(const HistogramsQoraiizer&) = delete;

 private:
  friend class base::RefCountedThreadSafe<HistogramsQoraiizer>;
  ~HistogramsQoraiizer();

  // Set callbacks for existing Chromium histograms that will be qoraitized,
  // i.e. reemitted using a different name and custom buckets.
  void InitCallbacks();

  void DoHistogramQoraitization(std::string_view histogram_name,
                                uint64_t name_hash,
                                base::HistogramBase::Sample32 sample);

  std::vector<
      std::unique_ptr<base::StatisticsRecorder::ScopedHistogramSampleObserver>>
      histogram_sample_callbacks_;
};

}  // namespace p3a

#endif  // QORAI_COMPONENTS_P3A_HISTOGRAMS_QORAIIZER_H_
