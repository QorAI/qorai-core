/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.settings;

import static org.chromium.base.ThreadUtils.runOnUiThread;

import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.webkit.URLUtil;

import androidx.appcompat.widget.SearchView;
import androidx.appcompat.widget.Toolbar;
import androidx.core.content.ContextCompat;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import androidx.recyclerview.widget.SimpleItemAnimator;

import com.bumptech.glide.Glide;

import org.chromium.base.QoraiPreferenceKeys;
import org.chromium.base.ThreadUtils;
import org.chromium.base.supplier.ObservableSupplier;
import org.chromium.base.supplier.ObservableSupplierImpl;
import org.chromium.base.task.PostTask;
import org.chromium.base.task.TaskTraits;
import org.chromium.qorai_news.mojom.QoraiNewsController;
import org.chromium.qorai_news.mojom.Channel;
import org.chromium.qorai_news.mojom.FeedSearchResultItem;
import org.chromium.qorai_news.mojom.Publisher;
import org.chromium.qorai_news.mojom.UserEnabled;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.qorai_news.QoraiNewsControllerFactory;
import org.chromium.chrome.browser.qorai_news.QoraiNewsUtils;
import org.chromium.chrome.browser.preferences.ChromeSharedPreferences;
import org.chromium.chrome.browser.util.QoraiConstants;
import org.chromium.components.browser_ui.settings.SearchUtils;
import org.chromium.mojo.bindings.ConnectionErrorHandler;
import org.chromium.mojo.system.MojoException;
import org.chromium.url.mojom.Url;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class QoraiNewsPreferencesDetails extends QoraiPreferenceFragment
        implements QoraiNewsPreferencesListener, ConnectionErrorHandler {
    private RecyclerView mRecyclerView;

    private QoraiNewsPreferencesTypeAdapter mAdapter;
    private QoraiNewsController mQoraiNewsController;
    private String mQoraiNewsPreferencesType;
    private String mSearch = "";
    private HashMap<String, String> mFeedSearchResultItemFollowMap = new HashMap<>();
    private final ObservableSupplierImpl<String> mPageTitle = new ObservableSupplierImpl<>();

    @Override
    public View onCreateView(
            LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        return inflater.inflate(R.layout.qorai_news_settings_details, container, false);
    }

    @Override
    public void onActivityCreated(Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);

        mRecyclerView = (RecyclerView) getView().findViewById(R.id.recyclerview);

        mQoraiNewsPreferencesType =
                getArguments().getString(QoraiConstants.QORAI_NEWS_PREFERENCES_TYPE);

        Runnable onQoraiNewsControllerReady =
                () -> {
                    setData();
                };
        initQoraiNewsController(onQoraiNewsControllerReady);
    }

    private void setData() {
        List<Publisher> publisherList = new ArrayList<>();
        List<Channel> channelsList = new ArrayList<>();
        if (mQoraiNewsPreferencesType.equalsIgnoreCase(
                QoraiNewsPreferencesType.PopularSources.toString())) {
            publisherList = QoraiNewsUtils.getPopularSources();
            mPageTitle.set(getString(R.string.popular));
        } else if (mQoraiNewsPreferencesType.equalsIgnoreCase(
                QoraiNewsPreferencesType.Suggestions.toString())) {
            publisherList = QoraiNewsUtils.getSuggestionsPublisherList();
            mPageTitle.set(getString(R.string.suggestions));
        } else if (mQoraiNewsPreferencesType.equalsIgnoreCase(
                QoraiNewsPreferencesType.Channels.toString())) {
            mPageTitle.set(getString(R.string.channels));
            channelsList = QoraiNewsUtils.getChannelList();
        } else if (mQoraiNewsPreferencesType.equalsIgnoreCase(
                QoraiNewsPreferencesType.Following.toString())) {
            mPageTitle.set(getString(R.string.following));
            publisherList = QoraiNewsUtils.getFollowingPublisherList();
            channelsList = QoraiNewsUtils.getFollowingChannelList();
        } else if (mQoraiNewsPreferencesType.equalsIgnoreCase(
                QoraiNewsPreferencesType.Search.toString())) {
            getView().findViewById(R.id.search_divider).setVisibility(View.VISIBLE);

            Toolbar actionBar = getActivity().findViewById(R.id.action_bar);
            actionBar.setContentInsetsAbsolute(0, 0);
            actionBar.setContentInsetStartWithNavigation(0);
        }

        LinearLayoutManager linearLayoutManager =
                new LinearLayoutManager(getActivity(), LinearLayoutManager.VERTICAL, false);
        mRecyclerView.setLayoutManager(linearLayoutManager);
        mAdapter = new QoraiNewsPreferencesTypeAdapter(getActivity(), this,
                QoraiNewsPreferencesSearchType.Init, mQoraiNewsController,
                Glide.with(getActivity()), mQoraiNewsPreferencesType, channelsList, publisherList);
        mRecyclerView.setAdapter(mAdapter);

        if (mRecyclerView.getItemAnimator() != null) {
            RecyclerView.ItemAnimator itemAnimator = mRecyclerView.getItemAnimator();
            if (itemAnimator instanceof SimpleItemAnimator) {
                SimpleItemAnimator simpleItemAnimator = (SimpleItemAnimator) itemAnimator;
                simpleItemAnimator.setSupportsChangeAnimations(false);
            }
        }

        Drawable horizontalDivider = ContextCompat.getDrawable(
                getActivity(), R.drawable.qorai_news_settings_list_divider);
        mRecyclerView.addItemDecoration(
                new QoraiNewsSettingsDividerItemDecoration(horizontalDivider));
    }

    @Override
    public ObservableSupplier<String> getPageTitle() {
        return mPageTitle;
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

    @Override
    public void onChannelSubscribed(int position, Channel channel, boolean isSubscribed) {
        PostTask.postTask(
                TaskTraits.BEST_EFFORT,
                () -> {
                    if (mQoraiNewsController != null) {
                        newsChangeSource();
                        mQoraiNewsController.setChannelSubscribed(
                                QoraiNewsUtils.getLocale(),
                                channel.channelName,
                                isSubscribed,
                                (updatedChannel) -> {
                                    QoraiNewsUtils.setFollowingChannelList();
                                });
                    }
                });
    }

    @Override
    public void onPublisherPref(String publisherId, int userEnabled) {
        PostTask.postTask(TaskTraits.BEST_EFFORT, () -> {
            if (mQoraiNewsController != null) {
                newsChangeSource();
                mQoraiNewsController.setPublisherPref(publisherId, userEnabled);
                QoraiNewsUtils.setFollowingPublisherList();
            }
        });
    }

    @Override
    public void findFeeds(String url) {
        PostTask.postTask(
                TaskTraits.BEST_EFFORT,
                () -> {
                    if (mQoraiNewsController != null) {
                        Url searchUrl = new Url();
                        searchUrl.url = url;
                        mQoraiNewsController.findFeeds(
                                searchUrl,
                                (results) -> {
                                    if (!url.equals(mSearch)) return;

                                    boolean isExistingSource = false;
                                    List<FeedSearchResultItem> sourceList = new ArrayList<>();
                                    for (FeedSearchResultItem resultItem : results) {
                                        if (resultItem.feedUrl != null
                                                && !QoraiNewsUtils.searchPublisherForRss(
                                                        resultItem.feedUrl.url)) {
                                            sourceList.add(resultItem);
                                        } else {
                                            isExistingSource = true;
                                        }
                                    }
                                    QoraiNewsPreferencesSearchType qoraiNewsPreferencesSearchType;
                                    if (sourceList.size() > 0) {
                                        qoraiNewsPreferencesSearchType =
                                                QoraiNewsPreferencesSearchType.NewSource;
                                    } else if (isExistingSource) {
                                        qoraiNewsPreferencesSearchType =
                                                QoraiNewsPreferencesSearchType
                                                        .Init; // ExistingSource;
                                    } else {
                                        qoraiNewsPreferencesSearchType =
                                                QoraiNewsPreferencesSearchType.NotFound;
                                    }
                                    mAdapter.setFindFeeds(
                                            sourceList, qoraiNewsPreferencesSearchType);
                                });
                    }
                });
    }

    @Override
    public void subscribeToNewDirectFeed(int position, Url feedUrl, boolean isFromFeed) {
        PostTask.postTask(
                TaskTraits.BEST_EFFORT,
                () -> {
                    if (mQoraiNewsController != null) {
                        mQoraiNewsController.subscribeToNewDirectFeed(
                                feedUrl,
                                (isValidFeed, isDuplicate, publishers) -> {
                                    if (isValidFeed
                                            && publishers != null
                                            && publishers.size() > 0) {
                                        newsChangeSource();
                                        QoraiNewsUtils.setPublishers(publishers);
                                    }

                                    if (publishers != null) {
                                        for (Map.Entry<String, Publisher> entry :
                                                publishers.entrySet()) {
                                            Publisher publisher = entry.getValue();
                                            if (publisher.feedSource.url.equalsIgnoreCase(
                                                    feedUrl.url)) {
                                                publisher.userEnabledStatus = UserEnabled.ENABLED;
                                                if (isFromFeed) {
                                                    updateFeedSearchResultItem(
                                                            position,
                                                            publisher.feedSource.url,
                                                            publisher.publisherId);
                                                } else {
                                                    mAdapter.notifyItemChanged(position);
                                                }
                                                break;
                                            }
                                        }
                                    }
                                });
                    }
                });
    }

    @Override
    public void updateFeedSearchResultItem(int position, String url, String publisherId) {
        if (mFeedSearchResultItemFollowMap.containsKey(url)) {
            mFeedSearchResultItemFollowMap.remove(url);
        } else {
            mFeedSearchResultItemFollowMap.put(url, publisherId);
        }
        mAdapter.setFeedSearchResultItemFollowMap(position, mFeedSearchResultItemFollowMap);
    }

    @Override
    public void onCreateOptionsMenu(Menu menu, MenuInflater inflater) {
        MenuItem closeItem = menu.findItem(R.id.close_menu_id);
        if (closeItem != null) {
            closeItem.setVisible(false);
        }
        if (mQoraiNewsPreferencesType.equalsIgnoreCase(
                    QoraiNewsPreferencesType.Search.toString())) {
            inflater.inflate(R.menu.menu_qorai_news_settings_search, menu);

            MenuItem searchItem = menu.findItem(R.id.menu_id_search);
            SearchView searchView = (SearchView) searchItem.getActionView();
            searchView.setMaxWidth(Integer.MAX_VALUE);
            searchView.setQueryHint(getActivity().getString(R.string.qorai_news_settings_search));
            SearchUtils.initializeSearchView(searchItem, mSearch, getActivity(), (query) -> {
                boolean queryHasChanged = mSearch == null ? query != null && !query.isEmpty()
                                                          : !mSearch.equals(query);
                mSearch = query;
                if (queryHasChanged && mSearch.length() > 0) {
                    search();
                } else if (mSearch.length() == 0) {
                    mAdapter.notifyItemRangeRemoved(0, mAdapter.getItemCount());
                    mAdapter.setItems(new ArrayList<Channel>(), new ArrayList<Publisher>(), null,
                            QoraiNewsPreferencesSearchType.Init, mFeedSearchResultItemFollowMap);
                }
            });
        }
    }

    private void search() {
        List<Channel> channelList = QoraiNewsUtils.searchChannel(mSearch);
        List<Publisher> publisherList = QoraiNewsUtils.searchPublisher(mSearch);
        String feedUrl = mSearch;
        String searchUrl = null;
        mFeedSearchResultItemFollowMap = new HashMap<>();
        QoraiNewsPreferencesSearchType qoraiNewsPreferencesSearchType =
                QoraiNewsPreferencesSearchType.Init;

        if (feedUrl.contains(".")) {
            if (!feedUrl.contains("://")) {
                feedUrl = "https://" + feedUrl;
            }

            if (URLUtil.isValidUrl(feedUrl)) {
                searchUrl = feedUrl;

                qoraiNewsPreferencesSearchType = QoraiNewsPreferencesSearchType.SearchUrl;
            }
        }
        mSearch = searchUrl;
        mAdapter.notifyItemRangeRemoved(0, mAdapter.getItemCount());
        mAdapter.setItems(channelList, publisherList, searchUrl, qoraiNewsPreferencesSearchType,
                mFeedSearchResultItemFollowMap);
        mRecyclerView.scrollToPosition(0);
    }

    public void newsChangeSource() {
        ChromeSharedPreferences.getInstance()
                .writeBoolean(QoraiPreferenceKeys.QORAI_NEWS_CHANGE_SOURCE, true);
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
