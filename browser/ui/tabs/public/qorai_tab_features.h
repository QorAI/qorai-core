// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_UI_TABS_PUBLIC_QORAI_TAB_FEATURES_H_
#define QORAI_BROWSER_UI_TABS_PUBLIC_QORAI_TAB_FEATURES_H_

#include <memory>

#include "qorai/components/psst/buildflags/buildflags.h"
#include "chrome/browser/ui/tabs/public/tab_features.h"

class Profile;

namespace ai_chat {
class TabDataWebContentsObserver;
}

#if BUILDFLAG(ENABLE_PSST)
namespace psst {
class PsstTabWebContentsObserver;
}
#endif

namespace tabs {

class TabInterface;

class QoraiTabFeatures : public TabFeatures {
 public:
  static QoraiTabFeatures* FromTabFeatures(TabFeatures* tab_features);
  QoraiTabFeatures();
  ~QoraiTabFeatures() override;

  void Init(TabInterface& tab, Profile* profile) override;

#if BUILDFLAG(ENABLE_PSST)
  psst::PsstTabWebContentsObserver* psst_web_contents_observer() {
    return psst_web_contents_observer_.get();
  }
#endif

 private:
  std::unique_ptr<ai_chat::TabDataWebContentsObserver> tab_data_observer_;
#if BUILDFLAG(ENABLE_PSST)
  std::unique_ptr<psst::PsstTabWebContentsObserver> psst_web_contents_observer_;
#endif
};

}  // namespace tabs
#endif  // QORAI_BROWSER_UI_TABS_PUBLIC_QORAI_TAB_FEATURES_H_
