/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.crypto_wallet.fragments.dapps;

import android.app.Activity;

import androidx.fragment.app.Fragment;

import org.chromium.qorai_wallet.mojom.QoraiWalletService;
import org.chromium.qorai_wallet.mojom.JsonRpcService;
import org.chromium.qorai_wallet.mojom.KeyringService;
import org.chromium.chrome.browser.crypto_wallet.activities.QoraiWalletBaseActivity;

public class BaseDAppsFragment extends Fragment {
    public QoraiWalletService getQoraiWalletService() {
        Activity activity = getActivity();
        if (activity instanceof QoraiWalletBaseActivity) {
            return ((QoraiWalletBaseActivity) activity).getQoraiWalletService();
        }

        return null;
    }

    public KeyringService getKeyringService() {
        Activity activity = getActivity();
        if (activity instanceof QoraiWalletBaseActivity) {
            return ((QoraiWalletBaseActivity) activity).getKeyringService();
        }

        return null;
    }

    public JsonRpcService getJsonRpcService() {
        Activity activity = getActivity();
        if (activity instanceof QoraiWalletBaseActivity) {
            return ((QoraiWalletBaseActivity) activity).getJsonRpcService();
        }

        return null;
    }
}
