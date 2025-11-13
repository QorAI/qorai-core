/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_NEWS_COMMON_FEATURES_H_
#define QORAI_COMPONENTS_QORAI_NEWS_COMMON_FEATURES_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"

namespace qorai_news::features {

BASE_DECLARE_FEATURE(kQoraiNewsCardPeekFeature);

BASE_DECLARE_FEATURE(kQoraiNewsFeedUpdate);
// The minimum number of cards (following the hero) in a block.
extern const base::FeatureParam<int> kQoraiNewsMinBlockCards;

// The maximum number of cards (following the hero) in a block.
extern const base::FeatureParam<int> kQoraiNewsMaxBlockCards;

// Every N hours the popRecency will halve. I.e, if this was 24, then every day
// the popularity score will be halved.
extern const base::FeatureParam<double> kQoraiNewsPopScoreHalfLife;

// Used as the fallback |pop_score| value for articles we
// don't have a |pop_score| for, such as articles from a direct feed, or just
// articles that Qorai Search doesn't have enough information about.
extern const base::FeatureParam<double> kQoraiNewsPopScoreMin;

// The ratio at which inline cards present discovery options (i.e. a source the
// user has not visited before).
// For example, this is 1:3 by default, so 0.25
extern const base::FeatureParam<double> kQoraiNewsInlineDiscoveryRatio;

// The minimum subscription weight for sources the user is not subscribed to,
// and is not subscribed to a channel containing. Note: If the user has
// explicitly stated they don't want to see a source, the source will have a
// zero weight here. This allows sources the user is not subscribed to to show
// up in the feed (i.e. for discover cards). It should be a small, but non-zero
// value.
extern const base::FeatureParam<double> kQoraiNewsSourceSubscribedMin;

// The boost which is applied to sources that the user has explicitly followed.
// This also applies to direct feeds.
extern const base::FeatureParam<double> kQoraiNewsSourceSubscribedBoost;

// The boost which is applied to sources where the user is following a channel
// containing the source. Ideally this is a smaller value than the subscribed
// boost, as that provides a stronger signal of interest.
extern const base::FeatureParam<double> kQoraiNewsChannelSubscribedBoost;

// The minimum visit weighting to apply to sources (i.e. unvisited sources).
// This value is used so unvisited sources still show up in the feed. Source
// visits are calculated as the normalized visit count (i.e. 0 - 1) + this
// offset.
extern const base::FeatureParam<double> kQoraiNewsSourceVisitsMin;

// The ratio of category to topic clusters. For example 0.8 would indicate that
// 80% of the clusters should be categories and 20% topics.
extern const base::FeatureParam<double> kQoraiNewsCategoryTopicRatio;

}  // namespace qorai_news::features

#endif  // QORAI_COMPONENTS_QORAI_NEWS_COMMON_FEATURES_H_
