/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_PUBLISHER_UTILS_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_PUBLISHER_UTILS_H_

#include <optional>
#include <string>
#include <string_view>

#include "url/gurl.h"

namespace qorai_rewards {

// Returns a value indicating whether the specified URL is a social media
// platform that can host Rewards publisher content.
bool IsMediaPlatformURL(const GURL& url);

// Returns the media platform associated with the specified publisher ID.
std::optional<std::string> GetMediaPlatformFromPublisherId(
    std::string_view publisher_id);

// Returns the publisher ID associated with the specified URL, or `nullopt` if
// the publisher ID cannot be statically determined from the URL. For example,
// a `nullopt` will be returned if the URL points to a configured social media
// platform where multiple publishers can be registered.
std::optional<std::string> GetPublisherIdFromURL(const GURL& url);

// Returns the publisher domain for the specified URL. For social media
// platforms, the site domain will be returned (e.g "twitter.com").
std::optional<std::string> GetPublisherDomainFromURL(const GURL& url);

}  // namespace qorai_rewards

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_PUBLISHER_UTILS_H_
