// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_UI_WEBUI_QORAI_NEW_TAB_PAGE_REFRESH_BACKGROUND_FACADE_H_
#define QORAI_BROWSER_UI_WEBUI_QORAI_NEW_TAB_PAGE_REFRESH_BACKGROUND_FACADE_H_

#include <memory>
#include <string>
#include <vector>

#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "qorai/browser/ui/webui/qorai_new_tab_page_refresh/qorai_new_tab_page.mojom.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"

class CustomBackgroundFileManager;
class PrefService;

namespace ntp_background_images {
class NTPBackgroundImagesService;
class ViewCounterService;
}  // namespace ntp_background_images

namespace qorai_new_tab_page_refresh {

// Provides a simplified interface for accessing background-related APIs from
// the new tab page.
class BackgroundFacade {
 public:
  BackgroundFacade(
      std::unique_ptr<CustomBackgroundFileManager> custom_file_manager,
      PrefService& pref_service,
      ntp_background_images::NTPBackgroundImagesService* bg_images_service,
      ntp_background_images::ViewCounterService* view_counter_service);

  ~BackgroundFacade();

  BackgroundFacade(const BackgroundFacade&) = delete;
  BackgroundFacade& operator=(const BackgroundFacade&) = delete;

  std::vector<mojom::QoraiBackgroundPtr> GetQoraiBackgrounds();

  std::vector<std::string> GetCustomBackgrounds();

  mojom::SelectedBackgroundPtr GetSelectedBackground();

  mojom::SponsoredImageBackgroundPtr GetSponsoredImageBackground();

  void SelectBackground(mojom::SelectedBackgroundPtr background);

  void SaveCustomBackgrounds(std::vector<base::FilePath> paths,
                             base::OnceClosure callback);

  void RemoveCustomBackground(const std::string& background_url,
                              base::OnceClosure callback);

  void NotifySponsoredImageLogoClicked(
      const std::string& wallpaper_id,
      const std::string& creative_instance_id,
      const std::string& destination_url,
      qorai_ads::mojom::NewTabPageAdMetricType metric_type);

 private:
  void OnCustomBackgroundsSaved(base::OnceClosure callback,
                                std::vector<base::FilePath> paths);

  void OnCustomBackgroundRemoved(base::OnceClosure callback,
                                 base::FilePath path,
                                 bool success);

  std::unique_ptr<CustomBackgroundFileManager> custom_file_manager_;
  raw_ref<PrefService> pref_service_;
  raw_ptr<ntp_background_images::NTPBackgroundImagesService> bg_images_service_;
  raw_ptr<ntp_background_images::ViewCounterService> view_counter_service_;
  base::WeakPtrFactory<BackgroundFacade> weak_factory_{this};
};

}  // namespace qorai_new_tab_page_refresh

#endif  // QORAI_BROWSER_UI_WEBUI_QORAI_NEW_TAB_PAGE_REFRESH_BACKGROUND_FACADE_H_
