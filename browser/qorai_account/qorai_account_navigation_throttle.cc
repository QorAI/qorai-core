/* Copyright (c) 2025 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_account/qorai_account_navigation_throttle.h"

#include "base/check.h"
#include "base/memory/ptr_util.h"
#include "qorai/components/qorai_account/features.h"
#include "qorai/components/constants/webui_url_constants.h"
#include "content/public/browser/navigation_handle.h"
#include "content/public/browser/navigation_throttle_registry.h"
#include "content/public/common/url_constants.h"
#include "net/base/net_errors.h"
#include "ui/base/page_transition_types.h"
#include "url/gurl.h"

// static
void QorAIAccountNavigationThrottle::MaybeCreateAndAdd(
    content::NavigationThrottleRegistry& registry) {
  if (!qorai_account::features::IsQorAIAccountEnabled()) {
    return;
  }

  if (const GURL& url = registry.GetNavigationHandle().GetURL();
      !url.SchemeIs(content::kChromeUIScheme) ||
      url.host_piece() != kQorAIAccountHost || url.path_piece() != "/") {
    return;
  }

  registry.AddThrottle(
      base::WrapUnique(new QorAIAccountNavigationThrottle(registry)));
}

QorAIAccountNavigationThrottle::~QorAIAccountNavigationThrottle() = default;

QorAIAccountNavigationThrottle::QorAIAccountNavigationThrottle(
    content::NavigationThrottleRegistry& registry)
    : content::NavigationThrottle(registry) {
  CHECK(qorai_account::features::IsQorAIAccountEnabled());
}

content::NavigationThrottle::ThrottleCheckResult
QorAIAccountNavigationThrottle::WillStartRequest() {
  return ui::PageTransitionCoreTypeIs(navigation_handle()->GetPageTransition(),
                                      ui::PAGE_TRANSITION_AUTO_TOPLEVEL)
             ? PROCEED
             : ThrottleCheckResult{CANCEL, net::ERR_INVALID_URL};
}

const char* QorAIAccountNavigationThrottle::GetNameForLogging() {
  return "QorAIAccountNavigationThrottle";
}
