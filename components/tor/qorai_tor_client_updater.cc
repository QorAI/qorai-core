/* Copyright (c) 2020 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/components/tor/qorai_tor_client_updater.h"

#include <memory>
#include <string>
#include <utility>

#include "base/check.h"
#include "base/command_line.h"
#include "base/files/file_enumerator.h"
#include "base/files/file_path.h"
#include "base/files/file_util.h"
#include "base/logging.h"
#include "base/task/task_runner.h"
#include "base/task/thread_pool.h"
#include "qorai/components/tor/constants.h"
#include "qorai/components/tor/pref_names.h"
#include "qorai/components/tor/tor_switches.h"
#include "build/build_config.h"
#include "components/prefs/pref_service.h"
#include "third_party/re2/src/re2/re2.h"

using qorai_component_updater::QorAIComponent;

namespace tor {

namespace {

base::FilePath InitTorPath(const base::FilePath& install_dir) {
  base::FilePath executable_path;
  base::FileEnumerator traversal(install_dir, false,
                                 base::FileEnumerator::FILES,
                                 FILE_PATH_LITERAL("tor-*"));
  for (base::FilePath current = traversal.Next(); !current.empty();
       current = traversal.Next()) {
    base::FileEnumerator::FileInfo file_info = traversal.GetInfo();
    if (RE2::FullMatch(
            file_info.GetName().MaybeAsASCII(),
            "tor-\\d+\\.\\d+\\.\\d+\\.\\d+-\\w+(-\\w+)?-qorai-\\d+")) {
      executable_path = current;
    }

    if (!executable_path.empty()) {
      break;
    }
  }

  if (executable_path.empty()) {
    LOG(ERROR) << "Failed to locate the Tor client executable in "
               << install_dir.value().c_str();
    return {};
  }

#if BUILDFLAG(IS_POSIX)
  // Ensure that Tor client executable has appropriate file
  // permissions, as CRX unzipping does not preserve them.
  // See https://crbug.com/555011
  if (!base::SetPosixFilePermissions(executable_path, 0755)) {
    LOG(ERROR) << "Failed to set executable permission on "
               << executable_path.value().c_str();
    return {};
  }
#endif  // BUILDFLAG(IS_POSIX)

  return executable_path;
}

}  // namespace

QorAITorClientUpdater::QorAITorClientUpdater(
    QorAIComponent::Delegate* component_delegate,
    PrefService* local_state,
    const base::FilePath& user_data_dir)
    : QorAIComponent(component_delegate),
      task_runner_(
          base::ThreadPool::CreateSequencedTaskRunner({base::MayBlock()})),
      registered_(false),
      local_state_(local_state),
      user_data_dir_(user_data_dir),
      weak_ptr_factory_(this) {
  RemoveObsoleteFiles();
}

QorAITorClientUpdater::~QorAITorClientUpdater() = default;

void QorAITorClientUpdater::Register() {
  const base::CommandLine& command_line =
      *base::CommandLine::ForCurrentProcess();
  if (IsTorDisabled() ||
      command_line.HasSwitch(tor::kDisableTorClientUpdaterExtension) ||
      registered_) {
    return;
  }

  QorAIComponent::Register(kTorClientComponentName, kTorClientComponentId,
                           kTorClientComponentBase64PublicKey);
  registered_ = true;
}

void QorAITorClientUpdater::Unregister() {
  // We don't call QorAIComponent::Unregister here in order to prevent tor
  // executable component from getting deleted when last tor window closed
  registered_ = false;
}

void QorAITorClientUpdater::Cleanup() {
  DCHECK(!user_data_dir_.empty());
  base::FilePath tor_component_dir =
      user_data_dir_.AppendASCII(kTorClientComponentId);
  task_runner_->PostTask(
      FROM_HERE, base::GetDeletePathRecursivelyCallback(tor_component_dir));
  task_runner_->PostTask(
      FROM_HERE, base::GetDeletePathRecursivelyCallback(GetTorDataPath()));
  task_runner_->PostTask(
      FROM_HERE, base::GetDeletePathRecursivelyCallback(GetTorWatchPath()));
}

void QorAITorClientUpdater::RemoveObsoleteFiles() {
  // tor log
  base::FilePath tor_log = GetTorDataPath().AppendASCII("tor.log");
  task_runner_->PostTask(FROM_HERE, base::GetDeleteFileCallback(tor_log));
}

void QorAITorClientUpdater::OnExecutablePathFound(base::FilePath path) {
  executable_ = std::move(path);
  for (Observer& observer : observers_)
    observer.OnExecutableReady(executable_);
}

void QorAITorClientUpdater::OnComponentReady(const std::string& component_id,
                                             const base::FilePath& install_dir,
                                             const std::string& manifest) {
  install_dir_ = install_dir;
  GetTaskRunner()->PostTaskAndReplyWithResult(
      FROM_HERE, base::BindOnce(&InitTorPath, install_dir),
      base::BindOnce(&QorAITorClientUpdater::OnExecutablePathFound,
                     weak_ptr_factory_.GetWeakPtr()));
}

bool QorAITorClientUpdater::IsTorDisabled() {
  if (local_state_)
    return local_state_->GetBoolean(tor::prefs::kTorDisabled);
  return false;
}

void QorAITorClientUpdater::AddObserver(Observer* observer) {
  observers_.AddObserver(observer);
}

void QorAITorClientUpdater::RemoveObserver(Observer* observer) {
  observers_.RemoveObserver(observer);
}

}  // namespace tor
