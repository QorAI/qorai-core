/* Copyright (c) 2019 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_BROWSING_DATA_QORAI_CLEAR_BROWSING_DATA_H_
#define QORAI_BROWSER_BROWSING_DATA_QORAI_CLEAR_BROWSING_DATA_H_

#include <cstdint>

namespace content {
class BrowsingDataRemover;
}
class Profile;
class QorAIClearDataOnExitTest;

namespace content {

class QorAIClearBrowsingData {
 public:
  QorAIClearBrowsingData(const QorAIClearBrowsingData&) = delete;
  QorAIClearBrowsingData& operator=(const QorAIClearBrowsingData&) = delete;

  // Clears browsing data for all loaded non-off-the-record profiles.
  // Profile's *OnExit preferences determine what gets cleared.
  // Note: this method will wait until browsing data has been cleared.
  static void ClearOnExit();

  static bool IsClearOnExitEnabledForAnyType(Profile* profile);

  // Used for testing only.
  struct OnExitTestingCallback {
    // Called from ClearOnExit right before the call to BrowsingDataRemover
    // to remove data.
    virtual void BeforeClearOnExitRemoveData(
        content::BrowsingDataRemover* remover,
        uint64_t remove_mask,
        uint64_t origin_mask) = 0;
  };

 protected:
  friend class ::QorAIClearDataOnExitTest;

  // Used for testing only.
  static void SetOnExitTestingCallback(OnExitTestingCallback* callback);

 private:
  static OnExitTestingCallback* on_exit_testing_callback_;
};

}  // namespace content

#endif  // QORAI_BROWSER_BROWSING_DATA_QORAI_CLEAR_BROWSING_DATA_H_
