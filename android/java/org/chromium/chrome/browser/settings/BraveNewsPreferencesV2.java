/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.settings;

import static org.chromium.base.ThreadUtils.runOnUiThread;

import android.graphics.PorterDuff;
import android.graphics.PorterDuffColorFilter;
import android.os.Bundle;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.appcompat.widget.SwitchCompat;
import androidx.core.content.ContextCompat;

import com.airbnb.lottie.LottieAnimationView;
import com.airbnb.lottie.LottieProperty;
import com.airbnb.lottie.model.KeyPath;

import org.chromium.base.QoraiPreferenceKeys;
import org.chromium.base.ThreadUtils;
import org.chromium.base.supplier.ObservableSupplier;
import org.chromium.base.supplier.ObservableSupplierImpl;
import org.chromium.base.task.PostTask;
import org.chromium.base.task.TaskTraits;
import org.chromium.qorai_news.mojom.QoraiNewsController;
import org.chromium.qorai_news.mojom.Channel;
import org.chromium.qorai_news.mojom.Publisher;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.qorai_news.QoraiNewsControllerFactory;
import org.chromium.chrome.browser.qorai_news.QoraiNewsUtils;
import org.chromium.chrome.browser.customtabs.CustomTabActivity;
import org.chromium.chrome.browser.night_mode.GlobalNightModeStateProviderHolder;
import org.chromium.chrome.browser.preferences.QoraiPrefServiceBridge;
import org.chromium.chrome.browser.preferences.ChromeSharedPreferences;
import org.chromium.chrome.browser.util.QoraiConstants;
import org.chromium.chrome.browser.util.QoraiTouchUtils;
import org.chromium.components.browser_ui.settings.FragmentSettingsNavigation;
import org.chromium.components.browser_ui.settings.SettingsNavigation;
import org.chromium.mojo.bindings.ConnectionErrorHandler;
import org.chromium.mojo.system.MojoException;

import java.util.List;

public class QoraiNewsPreferencesV2 extends QoraiPreferenceFragment
        implements QoraiNewsPreferencesDataListener,
                ConnectionErrorHandler,
                FragmentSettingsNavigation {
    public static final String PREF_SHOW_OPTIN = "show_optin";

    private LinearLayout mParentLayout;
    private LinearLayout mOptinLayout;
    private SwitchCompat mSwitchShowNews;
    private TextView mTvSearch;
    private TextView mTvFollowingCount;
    private Button mBtnTurnOnNews;
    private Button mBtnLearnMore;
    private View mLayoutSwitch;
    private View mDivider;
    private View mLayoutPopularSources;
    private View mLayoutSuggestions;
    private View mLayoutChannels;
    private View mLayoutFollowing;

    private boolean mIsSuggestionAvailable;
    private boolean mIsChannelAvailable;
    private boolean mIsPublisherAvailable;
    private QoraiNewsController mQoraiNewsController;

    // SettingsNavigation injected from main Settings Activity.
    private SettingsNavigation mSettingsLauncher;

    private final ObservableSupplierImpl<String> mPageTitle = new ObservableSupplierImpl<>();

    @Override
    public View onCreateView(
            LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        return inflater.inflate(R.layout.qorai_news_settings, container, false);
    }

    @Override
    public void onActivityCreated(Bundle savedInstanceState) {
        mPageTitle.set(getString(R.string.qorai_news_title));

        super.onActivityCreated(savedInstanceState);

        View view = getView();
        if (view != null) {
            mParentLayout = (LinearLayout) view.findViewById(R.id.layout_parent);
            mOptinLayout = (LinearLayout) view.findViewById(R.id.layout_optin_card);
            mSwitchShowNews = (SwitchCompat) view.findViewById(R.id.switch_show_news);
            mDivider = view.findViewById(R.id.divider);
            mLayoutSwitch = view.findViewById(R.id.layout_switch);
            mBtnTurnOnNews = (Button) view.findViewById(R.id.btn_turn_on_news);
            mBtnLearnMore = (Button) view.findViewById(R.id.btn_learn_more);
            mTvSearch = (TextView) view.findViewById(R.id.tv_search);
            mTvFollowingCount = (TextView) view.findViewById(R.id.tv_following_count);
            mLayoutPopularSources = (View) view.findViewById(R.id.layout_popular_sources);
            mLayoutSuggestions = (View) view.findViewById(R.id.layout_suggestions);
            mLayoutChannels = (View) view.findViewById(R.id.layout_channels);
            mLayoutFollowing = (View) view.findViewById(R.id.layout_following);

            QoraiTouchUtils.ensureMinTouchTarget(mBtnTurnOnNews);
            QoraiTouchUtils.ensureMinTouchTarget(mLayoutChannels);
            QoraiTouchUtils.ensureMinTouchTarget(mLayoutFollowing);
            QoraiTouchUtils.ensureMinTouchTarget(mLayoutPopularSources);
            QoraiTouchUtils.ensureMinTouchTarget(mLayoutSuggestions);
            QoraiTouchUtils.ensureMinTouchTarget(mTvSearch);
        }

        Runnable onQoraiNewsControllerReady =
                () -> {
                    if (view != null) {
                        setData();
                        onClickViews();
                    }
                };
        initQoraiNewsController(onQoraiNewsControllerReady);
    }

    @Override
    public ObservableSupplier<String> getPageTitle() {
        return mPageTitle;
    }

    private void setData() {
        if (!GlobalNightModeStateProviderHolder.getInstance().isInNightMode()
                && getView() != null) {
            LottieAnimationView lottieAnimationVIew =
                    (LottieAnimationView) getView().findViewById(R.id.animation_view);

            try {
                lottieAnimationVIew.addValueCallback(new KeyPath("newspaper", "**"),
                        LottieProperty.COLOR_FILTER,
                        frameInfo
                        -> new PorterDuffColorFilter(ContextCompat.getColor(getActivity(),
                                                             R.color.news_settings_optin_color),
                                PorterDuff.Mode.SRC_ATOP));
            } catch (Exception exception) {
                // if newspaper keypath changed in animation json
            }
        }

        if (!QoraiNewsUtils.getLocale().isEmpty()
                && QoraiNewsUtils.getSuggestionsPublisherList().size() > 0) {
            mIsSuggestionAvailable = true;
        }

        boolean isNewsEnable = QoraiNewsUtils.shouldDisplayNewsFeed();
        mSwitchShowNews.setChecked(isNewsEnable);
        onShowNewsToggle(isNewsEnable);
    }

    @Override
    public void onResume() {
        super.onResume();

        if (!QoraiNewsUtils.getLocale().isEmpty() && mSwitchShowNews.isChecked()) {
            updateFollowerCount();

            if (!mIsSuggestionAvailable) {
                PostTask.postTask(
                        TaskTraits.BEST_EFFORT,
                        () -> {
                            if (mQoraiNewsController != null) {
                                QoraiNewsUtils.getSuggestionsSources(
                                        mQoraiNewsController, this, null);
                            }
                        });
            }
        }
    }

    private void onClickViews() {
        mBtnTurnOnNews.setOnClickListener(view -> { mSwitchShowNews.setChecked(true); });

        mBtnLearnMore.setOnClickListener(view -> {
            CustomTabActivity.showInfoPage(getActivity(), QoraiConstants.QORAI_NEWS_LEARN_MORE_URL);
        });

        mSwitchShowNews.setOnCheckedChangeListener((compoundButton, b) -> { onShowNewsToggle(b); });

        mTvSearch.setOnClickListener(
                view -> { openQoraiNewsPreferencesDetails(QoraiNewsPreferencesType.Search); });

        mLayoutPopularSources.setOnClickListener(view -> {
            openQoraiNewsPreferencesDetails(QoraiNewsPreferencesType.PopularSources);
        });

        mLayoutSuggestions.setOnClickListener(
                view -> { openQoraiNewsPreferencesDetails(QoraiNewsPreferencesType.Suggestions); });

        mLayoutChannels.setOnClickListener(
                view -> {
                    openQoraiNewsPreferencesDetails(QoraiNewsPreferencesType.Channels);
                });

        mLayoutFollowing.setOnClickListener(
                view -> {
                    List<Publisher> followingPublisherList =
                            QoraiNewsUtils.getFollowingPublisherList();
                    List<Channel> followingChannelList = QoraiNewsUtils.getFollowingChannelList();
                    assert followingPublisherList != null;
                    assert followingChannelList != null;
                    if ((followingPublisherList != null && followingPublisherList.size() > 0)
                            || (followingChannelList != null && followingChannelList.size() > 0)) {
                        openQoraiNewsPreferencesDetails(QoraiNewsPreferencesType.Following);
                    }
                });
    }

    private void onShowNewsToggle(boolean isEnable) {
        QoraiPrefServiceBridge.getInstance().setShowNews(isEnable);

        ChromeSharedPreferences.getInstance()
                .writeBoolean(QoraiPreferenceKeys.QORAI_NEWS_PREF_SHOW_NEWS, isEnable);

        FrameLayout.LayoutParams parentLayoutParams = new FrameLayout.LayoutParams(
                FrameLayout.LayoutParams.MATCH_PARENT, FrameLayout.LayoutParams.WRAP_CONTENT);

        if (isEnable) {
            parentLayoutParams.gravity = Gravity.NO_GRAVITY;
            mParentLayout.setLayoutParams(parentLayoutParams);
            mOptinLayout.setVisibility(View.GONE);
            mLayoutSwitch.setVisibility(View.VISIBLE);
            mDivider.setVisibility(View.VISIBLE);
            if (QoraiNewsUtils.getChannelIcons().size() == 0) {
                QoraiNewsUtils.setChannelIcons();
            }
            if (QoraiNewsUtils.getLocale().isEmpty() && mQoraiNewsController != null) {
                QoraiNewsUtils.getQoraiNewsSettingsData(mQoraiNewsController, this, null);
            } else {
                mTvSearch.setVisibility(View.VISIBLE);
                mLayoutPopularSources.setVisibility(View.VISIBLE);
                mLayoutChannels.setVisibility(View.VISIBLE);
                mLayoutFollowing.setVisibility(View.VISIBLE);
                updateFollowerCount();
            }

            QoraiPrefServiceBridge.getInstance().setNewsOptIn(true);
            ChromeSharedPreferences.getInstance()
                    .writeBoolean(QoraiNewsPreferencesV2.PREF_SHOW_OPTIN, false);

            if (mIsSuggestionAvailable) {
                mLayoutSuggestions.setVisibility(View.VISIBLE);
            }

        } else {
            parentLayoutParams.gravity = Gravity.CENTER_VERTICAL;
            mParentLayout.setLayoutParams(parentLayoutParams);
            mOptinLayout.setVisibility(View.VISIBLE);
            mLayoutSwitch.setVisibility(View.GONE);
            mDivider.setVisibility(View.GONE);
            mTvSearch.setVisibility(View.GONE);
            mLayoutPopularSources.setVisibility(View.GONE);
            mLayoutSuggestions.setVisibility(View.GONE);
            mLayoutChannels.setVisibility(View.GONE);
            mLayoutFollowing.setVisibility(View.GONE);
        }
    }

    private void openQoraiNewsPreferencesDetails(
            QoraiNewsPreferencesType qoraiNewsPreferencesType) {
        Bundle fragmentArgs = new Bundle();
        fragmentArgs.putString(
                QoraiConstants.QORAI_NEWS_PREFERENCES_TYPE, qoraiNewsPreferencesType.toString());
        mSettingsLauncher.startSettings(
                getActivity(), QoraiNewsPreferencesDetails.class, fragmentArgs);
    }

    private void initQoraiNewsController(final Runnable action) {
        ThreadUtils.assertOnUiThread();
        if (mQoraiNewsController != null) {
            if (action != null) {
                action.run();
            }
            return;
        }

        QoraiNewsControllerFactory.getInstance()
                .getForProfile(getProfile(), this)
                .then(
                        qoraiNewsController -> {
                            // If there are future cases where this could be
                            // null for the original profile we need to adjust
                            // the UI to hide all qorai news related prefs
                            assert qoraiNewsController != null
                                    : "The service should always be available "
                                            + "for original profile";
                            if (qoraiNewsController == null) {
                                return;
                            }
                            mQoraiNewsController = qoraiNewsController;
                            if (action != null) {
                                action.run();
                            }
                        });
    }

    private void updateFollowerCount() {
        List<Publisher> followingPublisherList = QoraiNewsUtils.getFollowingPublisherList();
        List<Channel> followingChannelList = QoraiNewsUtils.getFollowingChannelList();
        int followingPublisherCount =
                followingPublisherList != null ? followingPublisherList.size() : 0;
        int followingChannelCount = followingChannelList != null ? followingChannelList.size() : 0;
        int followingCount = followingPublisherCount + followingChannelCount;
        if (mLayoutFollowing != null && mTvFollowingCount != null) {
            mTvFollowingCount.setText(String.valueOf(followingCount));
            mLayoutFollowing.setVisibility(View.VISIBLE);
        }
    }

    @Override
    public void onChannelReceived() {
        if (mSwitchShowNews != null && mSwitchShowNews.isChecked()) {
            if (mLayoutChannels != null) {
                mLayoutChannels.setVisibility(View.VISIBLE);
            }

            mIsChannelAvailable = true;
            if (mIsPublisherAvailable) {
                if (mTvSearch != null) {
                    mTvSearch.setVisibility(View.VISIBLE);
                }
                updateFollowerCount();
            }
        }
    }

    @Override
    public void onPublisherReceived() {
        if (mSwitchShowNews != null && mSwitchShowNews.isChecked()) {
            if (mLayoutPopularSources != null) {
                mLayoutPopularSources.setVisibility(View.VISIBLE);
            }
            mIsPublisherAvailable = true;
            if (mIsChannelAvailable) {
                if (mTvSearch != null) {
                    mTvSearch.setVisibility(View.VISIBLE);
                }
                updateFollowerCount();
            }
        }
    }

    @Override
    public void onSuggestionsReceived() {
        if (mSwitchShowNews != null && mSwitchShowNews.isChecked()
                && QoraiNewsUtils.getSuggestionsPublisherList().size() > 0) {
            if (mLayoutSuggestions != null) {
                mLayoutSuggestions.setVisibility(View.VISIBLE);
            }
        }
    }

    @Override
    public void setSettingsNavigation(SettingsNavigation settingsLauncher) {
        mSettingsLauncher = settingsLauncher;
    }

    @Override
    public void onConnectionError(MojoException e) {
        if (mQoraiNewsController != null) {
            mQoraiNewsController.close();
        }
        mQoraiNewsController = null;
        runOnUiThread(
                () -> {
                    initQoraiNewsController(null);
                });
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        if (mQoraiNewsController != null) {
            mQoraiNewsController.close();
        }
    }
}
