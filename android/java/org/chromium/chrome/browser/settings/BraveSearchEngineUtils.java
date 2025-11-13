/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.settings;

import androidx.annotation.Nullable;

import org.chromium.base.shared_preferences.SharedPreferencesManager;
import org.chromium.chrome.browser.preferences.ChromeSharedPreferences;
import org.chromium.chrome.browser.profiles.Profile;
import org.chromium.chrome.browser.profiles.ProfileManager;
import org.chromium.chrome.browser.search_engines.TemplateUrlServiceFactory;
import org.chromium.chrome.browser.search_engines.settings.QoraiSearchEngineAdapter;
import org.chromium.chrome.browser.tabmodel.TabModel;
import org.chromium.chrome.browser.tabmodel.TabModelSelector;
import org.chromium.components.search_engines.TemplateUrl;
import org.chromium.components.search_engines.TemplateUrlService;

public class QoraiSearchEngineUtils {
    public static void initializeQoraiSearchEngineStates(TabModelSelector tabModelSelector) {
        tabModelSelector
                .getCurrentTabModelSupplier()
                .addObserver(
                        (@Nullable TabModel newModel) -> {
                            if (newModel == null) {
                                return;
                            }

                            if (newModel.getProfile().isOffTheRecord()) {
                                QoraiSearchEngineUtils.initializeQoraiSearchEngineStates(
                                        newModel.getProfile());
                            } else {
                                QoraiSearchEngineUtils.updateActiveDSE(newModel.getProfile(), null);
                            }
                        });

        // For first-run initialization, it needs default TemplateUrl,
        // so do it after TemplateUrlService is loaded to get it if it isn't loaded yet.
        // Init on regular profile only, leave the rest to listener, since
        // user shouldn't be able to go directly into a private tab on first run.
        final Profile profile = ProfileManager.getLastUsedRegularProfile();
        initializeQoraiSearchEngineStates(profile);
    }

    public static void initializeQoraiSearchEngineStates(Profile profile) {
        final TemplateUrlService templateUrlService =
                TemplateUrlServiceFactory.getForProfile(profile);

        if (!templateUrlService.isLoaded()) {
            templateUrlService.registerLoadListener(
                    new TemplateUrlService.LoadListener() {
                        @Override
                        public void onTemplateUrlServiceLoaded() {
                            templateUrlService.unregisterLoadListener(this);
                            doInitializeQoraiSearchEngineStates(profile, null);
                        }
                    });
            templateUrlService.load();
        } else {
            doInitializeQoraiSearchEngineStates(profile, templateUrlService);
        }
    }

    private static void initializeDSEPrefs(Profile profile) {
        // At first run, we should set initial default prefs to each standard/private DSE prefs.
        // Those pref values will be used until user change DES options explicitly.
        final String notInitialized = "notInitialized";
        SharedPreferencesManager sharedPreferences = ChromeSharedPreferences.getInstance();
        if (notInitialized.equals(
                sharedPreferences.readString(
                        QoraiSearchEngineAdapter.STANDARD_DSE_SHORTNAME, notInitialized))) {
            final TemplateUrlService templateUrlService =
                    TemplateUrlServiceFactory.getForProfile(profile);

            TemplateUrl templateUrl = templateUrlService.getDefaultSearchEngineTemplateUrl();
            sharedPreferences.writeString(
                    QoraiSearchEngineAdapter.STANDARD_DSE_SHORTNAME, templateUrl.getShortName());
            sharedPreferences.writeString(
                    QoraiSearchEngineAdapter.PRIVATE_DSE_SHORTNAME, templateUrl.getShortName());
        }
    }

    private static void doInitializeQoraiSearchEngineStates(
            Profile profile, TemplateUrlService templateUrlServiceArg) {
        final TemplateUrlService templateUrlService =
                templateUrlServiceArg != null
                        ? templateUrlServiceArg
                        : TemplateUrlServiceFactory.getForProfile(profile);
        assert templateUrlService.isLoaded();

        initializeDSEPrefs(profile);
        updateActiveDSE(profile, templateUrlService);
    }

    public static void setDSEPrefs(TemplateUrl templateUrl, Profile profile) {
        QoraiSearchEngineAdapter.setDSEPrefs(templateUrl, profile);
    }

    public static void updateActiveDSE(Profile profile, TemplateUrlService templateUrlServiceArg) {
        QoraiSearchEngineAdapter.updateActiveDSE(profile, templateUrlServiceArg);
    }

    public static String getDSEShortName(Profile profile, boolean javaOnly) {
        return QoraiSearchEngineAdapter.getDSEShortName(profile, javaOnly, null);
    }

    public static TemplateUrl getTemplateUrlByShortName(Profile profile, String name) {
        return QoraiSearchEngineAdapter.getTemplateUrlByShortName(profile, name, null);
    }
}
