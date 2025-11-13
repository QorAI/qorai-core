/**
 * Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 */

package org.chromium.chrome.browser.omnibox.suggestions;

import android.content.Context;

import androidx.annotation.NonNull;

import org.chromium.base.QoraiFeatureList;
import org.chromium.base.QoraiPreferenceKeys;
import org.chromium.build.annotations.Nullable;
import org.chromium.chrome.browser.flags.ChromeFeatureList;
import org.chromium.chrome.browser.omnibox.OmniboxPrefManager;
import org.chromium.chrome.browser.omnibox.UrlBarEditingTextStateProvider;
import org.chromium.chrome.browser.omnibox.suggestions.basic.BasicSuggestionProcessor.BookmarkState;
import org.chromium.chrome.browser.omnibox.suggestions.qoraiqora.QoraiQoraSuggestionProcessor;
import org.chromium.chrome.browser.omnibox.suggestions.qorai_search.QoraiSearchBannerProcessor;
import org.chromium.chrome.browser.preferences.ChromeSharedPreferences;
import org.chromium.chrome.browser.profiles.Profile;
import org.chromium.chrome.browser.search_engines.settings.QoraiSearchEngineAdapter;
import org.chromium.chrome.browser.tab.Tab;
import org.chromium.components.omnibox.AutocompleteInput;
import org.chromium.components.omnibox.AutocompleteResult;
import org.chromium.components.omnibox.GroupsProto.GroupConfig;
import org.chromium.components.omnibox.suggestions.OmniboxSuggestionUiType;
import org.chromium.ui.modelutil.PropertyModel;

import java.util.Arrays;
import java.util.List;
import java.util.Locale;
import java.util.function.Supplier;

class QoraiDropdownItemViewInfoListBuilder extends DropdownItemViewInfoListBuilder {
    private @Nullable QoraiSearchBannerProcessor mQoraiSearchBannerProcessor;
    private @Nullable QoraiQoraSuggestionProcessor mQoraiQoraSuggestionProcessor;
    private UrlBarEditingTextStateProvider mUrlBarEditingTextProvider;
    private final @NonNull Supplier<Tab> mActivityTabSupplier;
    private static final List<String> sQoraiSearchEngineDefaultRegions =
            Arrays.asList("CA", "DE", "FR", "GB", "US", "AT", "ES", "MX");
    private AutocompleteDelegate mAutocompleteDelegate;
    private QoraiQoraAutocompleteDelegate mQoraAutocompleteDelegate;

    QoraiDropdownItemViewInfoListBuilder(
            Supplier<@Nullable Tab> tabSupplier,
            BookmarkState bookmarkState,
            Supplier<Integer> toolbarPositionSupplier) {
        super(tabSupplier, bookmarkState, toolbarPositionSupplier);

        mActivityTabSupplier = tabSupplier;
    }

    public void setAutocompleteDelegate(AutocompleteDelegate autocompleteDelegate) {
        mAutocompleteDelegate = autocompleteDelegate;
    }

    public void setQoraAutocompleteDelegate(QoraiQoraAutocompleteDelegate leoAutocompleteDelegate) {
        mQoraAutocompleteDelegate = leoAutocompleteDelegate;
    }

    @Override
    void initDefaultProcessors(
            Context context, SuggestionHost host, UrlBarEditingTextStateProvider textProvider) {
        mUrlBarEditingTextProvider = textProvider;
        super.initDefaultProcessors(context, host, textProvider);
        if (host instanceof QoraiSuggestionHost) {
            mQoraiSearchBannerProcessor =
                    new QoraiSearchBannerProcessor(
                            context,
                            (QoraiSuggestionHost) host,
                            textProvider,
                            mAutocompleteDelegate);
            AutocompleteUIContext uiContext = createUIContext(context, host, textProvider);
            mQoraiQoraSuggestionProcessor = new QoraiQoraSuggestionProcessor(uiContext);
            mQoraiQoraSuggestionProcessor.setQoraiQoraAutocompleteDelegate(mQoraAutocompleteDelegate);
        }
    }

    @Override
    void onOmniboxSessionStateChange(boolean activated) {
        super.onOmniboxSessionStateChange(activated);
        mQoraiSearchBannerProcessor.onOmniboxSessionStateChange(activated);
        mQoraiQoraSuggestionProcessor.onOmniboxSessionStateChange(activated);
    }

    @Override
    void onNativeInitialized() {
        super.onNativeInitialized();
        mQoraiSearchBannerProcessor.onNativeInitialized();
        mQoraiQoraSuggestionProcessor.onNativeInitialized();
    }

    private int getTileNavSuggestPosition(List<DropdownItemViewInfo> viewInfoList) {
        for (int i = 0; i < viewInfoList.size(); ++i) {
            if (viewInfoList.get(i).type == OmniboxSuggestionUiType.TILE_NAVSUGGEST) {
                return i;
            }
        }
        return viewInfoList.size();
    }

    @Override
    @NonNull
    List<DropdownItemViewInfo> buildDropdownViewInfoList(
            AutocompleteInput input, AutocompleteResult autocompleteResult) {
        mQoraiSearchBannerProcessor.onSuggestionsReceived();
        mQoraiQoraSuggestionProcessor.onSuggestionsReceived();
        List<DropdownItemViewInfo> viewInfoList =
                super.buildDropdownViewInfoList(input, autocompleteResult);

        // We want to show Qora auto suggestion even if the whole auto complete feature
        // is disabled
        Tab tab = mActivityTabSupplier.get();
        boolean autocompleteEnabled =
                tab != null
                        ? mQoraAutocompleteDelegate.isAutoCompleteEnabled(tab.getWebContents())
                        : true;
        if (!autocompleteEnabled && viewInfoList.size() > 0) {
            DropdownItemViewInfo firstObj = viewInfoList.get(0);
            viewInfoList.clear();
            if (firstObj.processor != null
                    && (firstObj.processor.getViewTypeId()
                                    == OmniboxSuggestionUiType.EDIT_URL_SUGGESTION
                            || firstObj.processor.getViewTypeId()
                                    == OmniboxSuggestionUiType.CLIPBOARD_SUGGESTION)) {
                viewInfoList.add(firstObj);
            }
        }

        if (isQoraiQoraEnabled()
                && !mUrlBarEditingTextProvider.getTextWithoutAutocomplete().isEmpty()) {
            final PropertyModel leoModel = mQoraiQoraSuggestionProcessor.createModel();
            mQoraiQoraSuggestionProcessor.populateModel(leoModel);

            GroupConfig config;
            int tileNavSuggestPosition = getTileNavSuggestPosition(viewInfoList);

            // We would like to get Qora position above the most visited tiles
            // and get into the same group as the item right above, if any exists.
            // This way we will have a rounded corners around all the group
            // including the suggestion
            if (tileNavSuggestPosition > 0) {
                DropdownItemViewInfo itemAbove = viewInfoList.get(tileNavSuggestPosition - 1);
                config = itemAbove.groupConfig;
            } else {
                // There is no any item above nav suggest tiles, so use the default
                config = GroupConfig.getDefaultInstance();
            }

            // Handle rounded corners for qora and previous item.
            if (viewInfoList.size() > 0) {
                viewInfoList
                        .get(viewInfoList.size() - 1)
                        .model
                        .set(DropdownCommonProperties.BG_BOTTOM_CORNER_ROUNDED, false);
                viewInfoList
                        .get(viewInfoList.size() - 1)
                        .model
                        .set(DropdownCommonProperties.SHOW_DIVIDER, true);
            }

            leoModel.set(DropdownCommonProperties.BG_TOP_CORNER_ROUNDED, viewInfoList.size() == 0);
            leoModel.set(DropdownCommonProperties.BG_BOTTOM_CORNER_ROUNDED, true);
            leoModel.set(DropdownCommonProperties.SHOW_DIVIDER, false);

            viewInfoList.add(
                    tileNavSuggestPosition,
                    new DropdownItemViewInfo(mQoraiQoraSuggestionProcessor, leoModel, config));
        }
        if (isQoraiSearchPromoBanner() && autocompleteEnabled) {
            final PropertyModel model = mQoraiSearchBannerProcessor.createModel();
            mQoraiSearchBannerProcessor.populateModel(model);
            viewInfoList.add(
                    new DropdownItemViewInfo(
                            mQoraiSearchBannerProcessor, model, GroupConfig.getDefaultInstance()));
        }

        return viewInfoList;
    }

    private boolean isQoraiQoraEnabled() {
        Tab tab = mActivityTabSupplier.get();
        if (mQoraAutocompleteDelegate != null
                && mQoraAutocompleteDelegate.isQoraEnabled()
                && tab != null
                && !tab.isIncognito()
                && ChromeSharedPreferences.getInstance()
                        .readBoolean(QoraiPreferenceKeys.QORAI_QORA_AUTOCOMPLETE, true)) {
            return true;
        }

        return false;
    }

    private boolean isQoraiSearchPromoBanner() {
        Tab activeTab = mActivityTabSupplier.get();
        if (ChromeFeatureList.isEnabled(QoraiFeatureList.QORAI_SEARCH_OMNIBOX_BANNER)
                && mUrlBarEditingTextProvider != null
                && mUrlBarEditingTextProvider.getTextWithoutAutocomplete().length() > 0
                && activeTab != null
                && !activeTab.isIncognito()
                && sQoraiSearchEngineDefaultRegions.contains(Locale.getDefault().getCountry())
                && !QoraiSearchEngineAdapter.getDSEShortName(
                                Profile.fromWebContents(activeTab.getWebContents()), false, null)
                        .equals("Qorai")
                && !OmniboxPrefManager.getInstance().isQoraiSearchPromoBannerDismissed()
                && !OmniboxPrefManager.getInstance()
                        .isQoraiSearchPromoBannerDismissedCurrentSession()) {
            long expiredDate =
                    OmniboxPrefManager.getInstance().getQoraiSearchPromoBannerExpiredDate();

            if (expiredDate == 0) {
                OmniboxPrefManager.getInstance().setQoraiSearchPromoBannerExpiredDate();
                return true;
            } else if (expiredDate > System.currentTimeMillis()) {
                return true;
            }
            return false;
        } else {
            return false;
        }
    }

    @SuppressWarnings("UnusedVariable")
    private AutocompleteUIContext createUIContext(
            Context context, SuggestionHost host, UrlBarEditingTextStateProvider textProvider) {
        assert false
                : "This method will be deleted in bytecode. Method from the parent class will be"
                        + " used instead.";
        return null;
    }
}
