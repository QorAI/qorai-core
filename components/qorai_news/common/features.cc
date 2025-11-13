/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_news/common/features.h"

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"
#include "build/buildflag.h"

namespace qorai_news::features {

BASE_FEATURE(kQoraiNewsCardPeekFeature,
             "QoraiNewsCardPeek",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kQoraiNewsFeedUpdate,
#if BUILDFLAG(IS_ANDROID)
             base::FEATURE_DISABLED_BY_DEFAULT

#else
             base::FEATURE_ENABLED_BY_DEFAULT
#endif
);
const base::FeatureParam<int> kQoraiNewsMinBlockCards{&kQoraiNewsFeedUpdate,
                                                      "min-block-cards", 1};

const base::FeatureParam<int> kQoraiNewsMaxBlockCards{&kQoraiNewsFeedUpdate,
                                                      "max-block-cards", 5};

const base::FeatureParam<double> kQoraiNewsPopScoreHalfLife{
    &kQoraiNewsFeedUpdate, "pop-score-half-life", 18};
const base::FeatureParam<double> kQoraiNewsPopScoreMin{
    &kQoraiNewsFeedUpdate, "pop-score-fallback", 0.5};

const base::FeatureParam<double> kQoraiNewsInlineDiscoveryRatio{
    &kQoraiNewsFeedUpdate, "inline-discovery-ratio", 0.1};

const base::FeatureParam<double> kQoraiNewsSourceSubscribedBoost{
    &kQoraiNewsFeedUpdate, "source-subscribed-boost", 1.0};
const base::FeatureParam<double> kQoraiNewsChannelSubscribedBoost{
    &kQoraiNewsFeedUpdate, "channel-subscribed-boost", 1.0};

const base::FeatureParam<double> kQoraiNewsSourceVisitsMin{
    &kQoraiNewsFeedUpdate, "source-visits-min", 0.2};

const base::FeatureParam<double> kQoraiNewsCategoryTopicRatio{
    &kQoraiNewsFeedUpdate, "category-topic-ratio", 0.5};

}  // namespace qorai_news::features
