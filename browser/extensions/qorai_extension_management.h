/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_EXTENSIONS_QORAI_EXTENSION_MANAGEMENT_H_
#define QORAI_BROWSER_EXTENSIONS_QORAI_EXTENSION_MANAGEMENT_H_

#include "base/scoped_observation.h"
#include "chrome/browser/extensions/extension_management.h"
#include "components/prefs/pref_change_registrar.h"
#include "extensions/browser/extension_registry.h"
#include "extensions/browser/extension_registry_observer.h"

namespace extensions {

class QoraiExtensionManagement : public ExtensionManagement,
                                 public ExtensionRegistryObserver {
 public:
  explicit QoraiExtensionManagement(Profile* profile);
  QoraiExtensionManagement(const QoraiExtensionManagement&) = delete;
  QoraiExtensionManagement& operator=(const QoraiExtensionManagement&) = delete;
  ~QoraiExtensionManagement() override;

 private:
  void OnTorDisabledChanged();
  void OnTorPluggableTransportChanged();
  void Cleanup(content::BrowserContext* browser_context);

  PrefChangeRegistrar local_state_pref_change_registrar_;

  base::ScopedObservation<ExtensionRegistry, ExtensionRegistryObserver>
      extension_registry_observer_{this};
};

}  // namespace extensions

#endif  // QORAI_BROWSER_EXTENSIONS_QORAI_EXTENSION_MANAGEMENT_H_
