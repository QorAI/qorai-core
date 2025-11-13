// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_NEWS_BROWSER_QORAI_NEWS_PREF_MANAGER_H_
#define QORAI_COMPONENTS_QORAI_NEWS_BROWSER_QORAI_NEWS_PREF_MANAGER_H_

#include <string>
#include <vector>

#include "base/containers/flat_map.h"
#include "base/observer_list.h"
#include "base/observer_list_types.h"
#include "qorai/components/qorai_news/common/qorai_news.mojom-forward.h"
#include "components/prefs/pref_change_registrar.h"
#include "components/prefs/pref_service.h"
#include "url/gurl.h"

namespace qorai_news {

class SubscriptionsSnapshot;
struct DirectFeed;

// Helper class providing a consistent interface for interacting with Qorai News
// storage and provides utilities for change notifications.
// Currently this backs onto PrefService.
class QoraiNewsPrefManager {
 public:
  class PrefObserver : public base::CheckedObserver {
   public:
    virtual void OnConfigChanged() {}
    virtual void OnPublishersChanged() {}
    virtual void OnChannelsChanged() {}
  };

  explicit QoraiNewsPrefManager(PrefService& prefs);
  ~QoraiNewsPrefManager();

  void AddObserver(PrefObserver* observer);
  void RemoveObserver(PrefObserver* observer);

  bool IsEnabled();
  qorai_news::mojom::ConfigurationPtr GetConfig();
  void SetConfig(qorai_news::mojom::ConfigurationPtr config);

  // Get everything teh user is subscribed to.
  SubscriptionsSnapshot GetSubscriptions();

  // Enables/disables/resets a publisher. When a direct feed is set to a
  // non-enabled state it is deleted.
  void SetPublisherSubscribed(const std::string& publisher_id,
                              qorai_news::mojom::UserEnabled enabled);

  // Adds a new entry for a DirectFeed. Direct feeds have a separate entry point
  // for adding new entries because we need to record the |url| and |title| of
  // the feed in order to retrieve it.
  std::string AddDirectPublisher(const GURL& url, const std::string& title);

  // Handles managing subscription to a channel in a locale.
  void SetChannelSubscribed(const std::string& locale,
                            const std::string& channel,
                            bool subscribed);

  // Clears all Qorai News related preferences.
  void ClearPrefs();

 private:
  std::vector<DirectFeed> GetDirectFeeds();
  base::flat_map<std::string, std::vector<std::string>> GetChannels();

  void NotifyPublishersChanged();
  void NotifyChannelsChanged();
  void NotifyConfigChanged();

  PrefChangeRegistrar pref_change_registrar_;
  base::ObserverList<PrefObserver> observers_;

  raw_ref<PrefService> prefs_;
};

}  // namespace qorai_news

#endif  // QORAI_COMPONENTS_QORAI_NEWS_BROWSER_QORAI_NEWS_PREF_MANAGER_H_
