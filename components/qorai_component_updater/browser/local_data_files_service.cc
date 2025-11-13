/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_component_updater/browser/local_data_files_service.h"

#include "qorai/components/qorai_component_updater/browser/local_data_files_observer.h"

using qorai_component_updater::QoraiComponent;

namespace qorai_component_updater {

LocalDataFilesService::LocalDataFilesService(QoraiComponent::Delegate* delegate)
  : QoraiComponent(delegate),
    initialized_(false) {}

LocalDataFilesService::~LocalDataFilesService() {
  for (auto& observer : observers_)
    observer.OnLocalDataFilesServiceDestroyed();
}

bool LocalDataFilesService::Start() {
  if (initialized_)
    return true;
  Register(kLocalDataFilesComponentName, kLocalDataFilesComponentId,
           kLocalDataFilesComponentBase64PublicKey);
  initialized_ = true;
  return true;
}

void LocalDataFilesService::OnComponentReady(
    const std::string& component_id,
    const base::FilePath& install_dir,
    const std::string& manifest) {
  for (auto& observer : observers_)
    observer.OnComponentReady(component_id, install_dir, manifest);
}

void LocalDataFilesService::AddObserver(LocalDataFilesObserver* observer) {
  observers_.AddObserver(observer);
}

void LocalDataFilesService::RemoveObserver(LocalDataFilesObserver* observer) {
  observers_.RemoveObserver(observer);
}

///////////////////////////////////////////////////////////////////////////////

std::unique_ptr<LocalDataFilesService>
LocalDataFilesServiceFactory(QoraiComponent::Delegate* delegate) {
  return std::make_unique<LocalDataFilesService>(delegate);
}

}  // namespace qorai_component_updater
