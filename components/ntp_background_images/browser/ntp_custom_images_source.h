// Copyright (c) 2022 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_NTP_BACKGROUND_IMAGES_BROWSER_NTP_CUSTOM_IMAGES_SOURCE_H_
#define QORAI_COMPONENTS_NTP_BACKGROUND_IMAGES_BROWSER_NTP_CUSTOM_IMAGES_SOURCE_H_

#include <string>

#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "content/public/browser/url_data_source.h"

namespace base {
class FilePath;
}  // namespace base

namespace ntp_background_images {

class QorAINTPCustomBackgroundService;

// This serves background image data.
class NTPCustomImagesSource : public content::URLDataSource {
 public:
  explicit NTPCustomImagesSource(
      QorAINTPCustomBackgroundService* custom_background_service);
  ~NTPCustomImagesSource() override;

  NTPCustomImagesSource(const NTPCustomImagesSource&) = delete;
  NTPCustomImagesSource& operator=(const NTPCustomImagesSource&) = delete;

 private:
  // content::URLDataSource overrides:
  std::string GetSource() override;
  void StartDataRequest(const GURL& url,
                        const content::WebContents::Getter& wc_getter,
                        GotDataCallback callback) override;
  std::string GetMimeType(const GURL& url) override;
  bool AllowCaching() override;

  void GetImageFile(const base::FilePath& image_file_path,
                    GotDataCallback callback);
  void OnGotImageFile(GotDataCallback callback, const std::string& input);

  raw_ptr<QorAINTPCustomBackgroundService, DanglingUntriaged>
      custom_background_service_ = nullptr;  // Not owned.

  base::WeakPtrFactory<NTPCustomImagesSource> weak_factory_{this};
};

}  // namespace ntp_background_images

#endif  // QORAI_COMPONENTS_NTP_BACKGROUND_IMAGES_BROWSER_NTP_CUSTOM_IMAGES_SOURCE_H_
