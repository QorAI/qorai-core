/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/tabs/tab_manager.h"

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/tabs/tab_manager_observer_mock.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsTabManagerTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    TabManager::GetInstance().AddObserver(&tab_manager_observer_mock_);
  }

  void TearDown() override {
    TabManager::GetInstance().RemoveObserver(&tab_manager_observer_mock_);

    test::TestBase::TearDown();
  }

  ::testing::StrictMock<TabManagerObserverMock> tab_manager_observer_mock_;
};

TEST_F(QoraiAdsTabManagerTest, OpenNewTab) {
  // Act & Assert
  EXPECT_CALL(
      tab_manager_observer_mock_,
      OnDidOpenNewTab(TabInfo{/*id=*/1,
                              /*is_visible=*/true,
                              /*redirect_chain=*/{GURL("https://qorai.com")},
                              /*is_playing_media=*/false}));
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://qorai.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/true);
}

TEST_F(QoraiAdsTabManagerTest, DoNotChangeOccludedTabIfMatchingRedirectChain) {
  // Arrange
  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://qorai.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/false);

  // Act & Assert
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChange).Times(0);
  NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://qorai.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/false);
}

TEST_F(QoraiAdsTabManagerTest, DoNotChangeVisibleTabIfMatchingRedirectChain) {
  // Arrange
  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://qorai.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/true);

  // Act & Assert
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChange).Times(0);
  NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://qorai.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/true);
}

TEST_F(QoraiAdsTabManagerTest, DoNotNotifyForRestoredTabs) {
  // Act & Assert
  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab).Times(0);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChange).Times(0);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus).Times(0);
  NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://qorai.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/true, /*is_visible=*/true);
}

TEST_F(QoraiAdsTabManagerTest,
       DoNotNotifyTabDidChangeIfReturningToPreviouslyCommittedNavigation) {
  // Act & Assert
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChange).Times(0);
  NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://qorai.com")},
      /*is_new_navigation=*/false, /*is_restoring=*/true, /*is_visible=*/true);
}

TEST_F(QoraiAdsTabManagerTest, ChangeTabFocusToOccluded) {
  // Arrange
  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://qorai.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/true);

  // Act & Assert
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus(/*tab_id=*/1));
  NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://qorai.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/false);
}

TEST_F(QoraiAdsTabManagerTest, ChangeTabFocusToVisible) {
  // Arrange
  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://qorai.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/false);

  // Act & Assert
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus(/*tab_id=*/1));
  NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://qorai.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/true);
}

TEST_F(QoraiAdsTabManagerTest, ChangeOccudedTabIfMismatchingRedirectChain) {
  // Arrange
  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://qorai.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/false);

  // Act & Assert
  EXPECT_CALL(tab_manager_observer_mock_,
              OnTabDidChange(TabInfo{
                  /*id=*/1,
                  /*is_visible=*/false,
                  /*redirect_chain=*/{GURL("https://basicattentiontoken.org")},
                  /*is_playing_media=*/
                  false}));
  NotifyTabDidChange(
      /*tab_id=*/1,
      /*redirect_chain=*/{GURL("https://basicattentiontoken.org")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/false);
}

TEST_F(QoraiAdsTabManagerTest, ChangeVisibleTabIfMismatchingRedirectChain) {
  // Arrange
  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://qorai.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/true);

  // Act & Assert
  EXPECT_CALL(tab_manager_observer_mock_,
              OnTabDidChange(TabInfo{
                  /*id=*/1,
                  /*is_visible=*/true,
                  /*redirect_chain=*/{GURL("https://basicattentiontoken.org")},
                  /*is_playing_media=*/
                  false}));
  NotifyTabDidChange(
      /*tab_id=*/1,
      /*redirect_chain=*/{GURL("https://basicattentiontoken.org")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/true);
}

TEST_F(QoraiAdsTabManagerTest, CloseTab) {
  // Arrange
  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://qorai.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/true);

  // Act & Assert
  EXPECT_CALL(tab_manager_observer_mock_, OnDidCloseTab(/*tab_id=*/1));
  NotifyDidCloseTab(/*tab_id=*/1);
}

TEST_F(QoraiAdsTabManagerTest, IsPlayingMedia) {
  // Arrange
  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://qorai.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/true);

  EXPECT_CALL(tab_manager_observer_mock_,
              OnTabDidStartPlayingMedia(/*tab_id=*/1));
  NotifyTabDidStartPlayingMedia(/*tab_id=*/1);

  // Act & Assert
  EXPECT_TRUE(TabManager::GetInstance().IsPlayingMedia(/*tab_id=*/1));
}

TEST_F(QoraiAdsTabManagerTest, IsNotPlayingMedia) {
  // Arrange
  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://qorai.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/true);

  // Act & Assert
  EXPECT_FALSE(TabManager::GetInstance().IsPlayingMedia(/*tab_id=*/1));
}

TEST_F(QoraiAdsTabManagerTest, StartPlayingMedia) {
  // Arrange
  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://qorai.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/true);

  // Act & Assert
  EXPECT_CALL(tab_manager_observer_mock_,
              OnTabDidStartPlayingMedia(/*tab_id=*/1));
  NotifyTabDidStartPlayingMedia(/*tab_id=*/1);
}

TEST_F(QoraiAdsTabManagerTest, DoNotStartPlayingMediaIfAlreadyPlaying) {
  // Arrange
  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://qorai.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false,
      /*is_visible=*/true);
  EXPECT_CALL(tab_manager_observer_mock_,
              OnTabDidStartPlayingMedia(/*tab_id=*/1));
  NotifyTabDidStartPlayingMedia(/*tab_id=*/1);

  // Act & Assert
  NotifyTabDidStartPlayingMedia(/*tab_id=*/1);
}

TEST_F(QoraiAdsTabManagerTest, StopPlayingMedia) {
  // Arrange
  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://qorai.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/true);

  EXPECT_CALL(tab_manager_observer_mock_,
              OnTabDidStartPlayingMedia(/*tab_id=*/1));
  NotifyTabDidStartPlayingMedia(/*tab_id=*/1);

  // Act & Assert
  EXPECT_CALL(tab_manager_observer_mock_,
              OnTabDidStopPlayingMedia(/*tab_id=*/1));
  NotifyTabDidStopPlayingMedia(/*tab_id=*/1);
}

TEST_F(QoraiAdsTabManagerTest, GetVisibleTab) {
  // Arrange
  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://qorai.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/true);

  // Act & Assert
  const TabInfo tab{/*id=*/1, /*is_visible=*/true,
                    /*redirect_chain=*/{GURL("https://qorai.com")},
                    /*is_playing_media=*/
                    false};
  EXPECT_EQ(tab, TabManager::GetInstance().MaybeGetVisible());
}

TEST_F(QoraiAdsTabManagerTest, DoNotGetVisibleTabIfNoTabs) {
  // Act & Assert
  EXPECT_FALSE(TabManager::GetInstance().MaybeGetVisible());
}

TEST_F(QoraiAdsTabManagerTest, GetTabForId) {
  // Arrange
  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://qorai.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/true);

  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  NotifyTabDidChange(
      /*tab_id=*/2,
      /*redirect_chain=*/{GURL("https://basicattentiontoken.org")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/true);

  // Act & Assert
  const TabInfo tab{
      /*id=*/2, /*is_visible=*/true,
      /*redirect_chain=*/{GURL("https://basicattentiontoken.org")},
      /*is_playing_media=*/
      false};
  EXPECT_EQ(tab, TabManager::GetInstance().MaybeGetForId(2));
}

TEST_F(QoraiAdsTabManagerTest, DoNotGetIfMissingTab) {
  // Arrange
  EXPECT_CALL(tab_manager_observer_mock_, OnDidOpenNewTab);
  EXPECT_CALL(tab_manager_observer_mock_, OnTabDidChangeFocus);
  NotifyTabDidChange(
      /*tab_id=*/1, /*redirect_chain=*/{GURL("https://qorai.com")},
      /*is_new_navigation=*/true, /*is_restoring=*/false, /*is_visible=*/true);

  // Act & Assert
  EXPECT_FALSE(TabManager::GetInstance().MaybeGetForId(2));
}

TEST_F(QoraiAdsTabManagerTest, DoNotGetIfNoTabs) {
  // Act & Assert
  EXPECT_FALSE(TabManager::GetInstance().MaybeGetForId(1));
}

}  // namespace qorai_ads
