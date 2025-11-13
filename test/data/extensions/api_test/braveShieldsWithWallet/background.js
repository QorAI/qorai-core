/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

function testBasics() {
  chrome.test.runTests([
    function qoraiShieldsHasWalletAccessButNotSeed() {
      if (chrome.qoraiWallet && !chrome.qoraiWallet.getWalletSeed &&
          !chrome.qoraiWallet.getProjectID &&
          !chrome.qoraiWallet.getQoraiKey) {
        chrome.test.succeed();
      } else {
        chrome.test.fail();
      }
    },
  ]);
}
