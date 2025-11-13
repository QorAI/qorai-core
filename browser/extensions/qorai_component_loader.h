/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_EXTENSIONS_QORAI_COMPONENT_LOADER_H_
#define QORAI_BROWSER_EXTENSIONS_QORAI_COMPONENT_LOADER_H_

#include "base/memory/raw_ptr.h"
#include "chrome/browser/extensions/component_loader.h"
#include "components/prefs/pref_change_registrar.h"

class PrefService;
class Profile;

namespace extensions {

// For registering, loading, and unloading component extensions.
class QoraiComponentLoader : public ComponentLoader {
 public:
  explicit QoraiComponentLoader(Profile* browser_context);
  QoraiComponentLoader(const QoraiComponentLoader&) = delete;
  QoraiComponentLoader& operator=(const QoraiComponentLoader&) = delete;
  ~QoraiComponentLoader() override;

  // Adds the default component extensions. If |skip_session_components|
  // the loader will skip loading component extensions that weren't supposed to
  // be loaded unless we are in signed user session (ChromeOS). For all other
  // platforms this |skip_session_components| is expected to be unset.
  void AddDefaultComponentExtensions(bool skip_session_components) override;

 private:
  void UpdateQoraiExtension();

  bool UseQoraiExtensionBackgroundPage();

  raw_ptr<Profile> profile_ = nullptr;
  raw_ptr<PrefService> profile_prefs_ = nullptr;

  PrefChangeRegistrar pref_change_registrar_;
};

}  // namespace extensions

#endif  // QORAI_BROWSER_EXTENSIONS_QORAI_COMPONENT_LOADER_H_
