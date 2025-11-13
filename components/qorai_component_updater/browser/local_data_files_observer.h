/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_COMPONENT_UPDATER_BROWSER_LOCAL_DATA_FILES_OBSERVER_H_
#define QORAI_COMPONENTS_QORAI_COMPONENT_UPDATER_BROWSER_LOCAL_DATA_FILES_OBSERVER_H_

#include <string>

#include "base/component_export.h"
#include "base/files/file_path.h"
#include "base/memory/raw_ptr.h"
#include "base/scoped_observation.h"
#include "qorai/components/qorai_component_updater/browser/local_data_files_service.h"

namespace https_upgrade_exceptions {
class HttpsUpgradeExceptionsService;
}

namespace debounce {
class DebounceComponentInstaller;
}

namespace request_otr {
class RequestOTRComponentInstallerPolicy;
}

namespace webcompat {
class WebcompatExceptionsService;
}

namespace qorai {
class URLSanitizerComponentInstaller;
}

namespace qorai_component_updater {

// DEPRECATED: Create individual component installers instead.
// The abstract base class for observers of the local data files service,
// which is the component that arbitrates access to various DAT files
// like tracking protection.
class COMPONENT_EXPORT(QORAI_COMPONENT_UPDATER) LocalDataFilesObserver {
 public:
  virtual ~LocalDataFilesObserver();
  virtual void OnComponentReady(const std::string& component_id,
                                const base::FilePath& install_dir,
                                const std::string& manifest) = 0;
  virtual void OnLocalDataFilesServiceDestroyed();
  LocalDataFilesService* local_data_files_service();

 protected:
  raw_ptr<LocalDataFilesService> local_data_files_service_ =
      nullptr;  // NOT OWNED
  base::ScopedObservation<LocalDataFilesService, LocalDataFilesObserver>
      local_data_files_observer_{this};

 private:
  friend class qorai::URLSanitizerComponentInstaller;
  friend class https_upgrade_exceptions::HttpsUpgradeExceptionsService;
  friend class debounce::DebounceComponentInstaller;
  friend class request_otr::RequestOTRComponentInstallerPolicy;
  friend class webcompat::WebcompatExceptionsService;

  explicit LocalDataFilesObserver(
      LocalDataFilesService* local_data_files_service);
};

}  // namespace qorai_component_updater

#endif  // QORAI_COMPONENTS_QORAI_COMPONENT_UPDATER_BROWSER_LOCAL_DATA_FILES_OBSERVER_H_
