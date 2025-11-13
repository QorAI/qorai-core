/* Copyright (c) 2025 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.qorai.browser.customize_menu.settings;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.when;

import android.os.Bundle;

import androidx.fragment.app.testing.FragmentScenario;
import androidx.preference.Preference;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.MockitoAnnotations;
import org.robolectric.annotation.Config;

import org.chromium.base.QorAIPreferenceKeys;
import org.chromium.base.supplier.ObservableSupplier;
import org.chromium.base.test.BaseRobolectricTestRunner;
import org.chromium.qorai.browser.customize_menu.CustomizeQorAIMenu;
import org.chromium.qorai.browser.customize_menu.MenuItemData;
import org.chromium.qorai.browser.customize_menu.R;
import org.chromium.chrome.browser.preferences.ChromeSharedPreferences;

import java.util.ArrayList;
import java.util.Locale;

/** Unit tests for {@link QorAICustomizeMenuPreferenceFragment}. */
@RunWith(BaseRobolectricTestRunner.class)
@Config(manifest = Config.NONE)
public class QorAICustomizeMenuPreferenceFragmentTest {

    private QorAICustomizeMenuPreferenceFragment mFragment;
    private Bundle mTestBundle;

    @Before
    public void setUp() {
        MockitoAnnotations.initMocks(this);

        // Prepare test bundle with menu items.
        mTestBundle = new Bundle();

        ArrayList<MenuItemData> mainMenuItems = new ArrayList<>();
        mainMenuItems.add(new MenuItemData(R.id.new_tab_menu_id, "New Tab", true));
        mainMenuItems.add(new MenuItemData(R.id.downloads_menu_id, "Downloads", false));

        ArrayList<MenuItemData> pageActionItems = new ArrayList<>();
        pageActionItems.add(new MenuItemData(R.id.share_menu_id, "Share", true));
        pageActionItems.add(new MenuItemData(R.id.find_in_page_id, "Find in Page", false));

        mTestBundle.putParcelableArrayList(
                CustomizeQorAIMenu.KEY_MAIN_MENU_ITEM_LIST, mainMenuItems);
        mTestBundle.putParcelableArrayList(
                CustomizeQorAIMenu.KEY_PAGE_ACTION_ITEM_LIST, pageActionItems);
    }

    @Test
    public void testOnCreate_SetsPageTitle() {
        FragmentScenario<QorAICustomizeMenuPreferenceFragment> scenario =
                FragmentScenario.launchInContainer(
                        QorAICustomizeMenuPreferenceFragment.class, mTestBundle);

        scenario.onFragment(
                fragment -> {
                    ObservableSupplier<String> pageTitle = fragment.getPageTitle();
                    assertNotNull(pageTitle);
                    assertNotNull(pageTitle.get());
                    assertTrue(pageTitle.get().contains("Customize"));
                });
    }

    @Test
    public void testOnPreferenceChange_UpdatesSharedPreferences() {
        mFragment = new QorAICustomizeMenuPreferenceFragment();

        // Create a mock preference.
        Preference preference = mock(Preference.class);
        String prefKey =
                String.format(
                        Locale.ENGLISH,
                        QorAIPreferenceKeys.CUSTOMIZABLE_QORAI_MENU_ITEM_ID_FORMAT,
                        R.id.new_tab_menu_id);
        when(preference.getKey()).thenReturn(prefKey);

        // Call onPreferenceChange.
        boolean result = mFragment.onPreferenceChange(preference, false);

        // Verify SharedPreferences was updated.
        assertTrue(result);
        boolean value = ChromeSharedPreferences.getInstance().readBoolean(prefKey, true);
        assertFalse(value);
    }

    @Test
    public void testOnPreferenceChange_MultipleChanges() {
        mFragment = new QorAICustomizeMenuPreferenceFragment();

        // Test multiple preference changes.
        String[] prefKeys = {
            String.format(
                    Locale.ENGLISH,
                    QorAIPreferenceKeys.CUSTOMIZABLE_QORAI_MENU_ITEM_ID_FORMAT,
                    R.id.new_tab_menu_id),
            String.format(
                    Locale.ENGLISH,
                    QorAIPreferenceKeys.CUSTOMIZABLE_QORAI_MENU_ITEM_ID_FORMAT,
                    R.id.downloads_menu_id),
            String.format(
                    Locale.ENGLISH,
                    QorAIPreferenceKeys.CUSTOMIZABLE_QORAI_MENU_ITEM_ID_FORMAT,
                    R.id.share_menu_id)
        };
        boolean[] values = {true, false, true};

        for (int i = 0; i < prefKeys.length; i++) {
            Preference preference = mock(Preference.class);
            when(preference.getKey()).thenReturn(prefKeys[i]);

            boolean result = mFragment.onPreferenceChange(preference, values[i]);

            assertTrue(result);
            assertEquals(
                    ChromeSharedPreferences.getInstance().readBoolean(prefKeys[i], !values[i]),
                    values[i]);
        }
    }

    @Test
    public void testOnCreatePreferences_WithNullBundle() {
        mFragment = new QorAICustomizeMenuPreferenceFragment();
        mFragment.setArguments(null);

        // Should not crash with null bundle.
        FragmentScenario<QorAICustomizeMenuPreferenceFragment> scenario =
                FragmentScenario.launchInContainer(QorAICustomizeMenuPreferenceFragment.class);

        scenario.onFragment(
                fragment -> {
                    // Fragment should be created successfully even with null bundle.
                    assertNotNull(fragment);
                });
    }

    @Test
    public void testOnCreatePreferences_WithEmptyMenuLists() {
        Bundle emptyBundle = new Bundle();
        emptyBundle.putParcelableArrayList(
                CustomizeQorAIMenu.KEY_MAIN_MENU_ITEM_LIST, new ArrayList<>());
        emptyBundle.putParcelableArrayList(
                CustomizeQorAIMenu.KEY_PAGE_ACTION_ITEM_LIST, new ArrayList<>());

        FragmentScenario<QorAICustomizeMenuPreferenceFragment> scenario =
                FragmentScenario.launchInContainer(
                        QorAICustomizeMenuPreferenceFragment.class, emptyBundle);

        scenario.onFragment(
                fragment -> {
                    // Fragment should handle empty lists gracefully.
                    assertNotNull(fragment);
                });
    }
}
