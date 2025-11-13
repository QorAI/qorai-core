/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/targeting/contextual/text_classification/resource/text_classification_resource.h"

#include <memory>
#include <utility>

#include "base/files/file.h"
#include "base/files/file_path.h"
#include "qorai/components/qorai_ads/core/internal/common/resources/language_components_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/common/resources/resource_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/common/test/file_path_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/prefs/pref_util.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings_test_util.h"
#include "qorai/components/qorai_ads/core/internal/targeting/contextual/text_classification/resource/text_classification_resource_constants.h"
#include "qorai/components/qorai_ads/core/public/prefs/pref_names.h"
#include "qorai/components/qorai_news/common/pref_names.h"
#include "qorai/components/ntp_background_images/common/pref_names.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsTextClassificationResourceTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    resource_ = std::make_unique<TextClassificationResource>();
  }

  std::unique_ptr<TextClassificationResource> resource_;
};

TEST_F(QoraiAdsTextClassificationResourceTest, IsResourceNotLoaded) {
  // Act & Assert
  EXPECT_FALSE(resource_->GetManifestVersion());
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(QoraiAdsTextClassificationResourceTest, LoadResource) {
  // Arrange
  NotifyResourceComponentDidChange(test::kLanguageComponentManifestVersion,
                                   test::kLanguageComponentId);

  // Act & Assert
  EXPECT_TRUE(resource_->IsLoaded());
}

TEST_F(QoraiAdsTextClassificationResourceTest, DoNotLoadMalformedResource) {
  // Arrange
  ASSERT_TRUE(CopyFileFromTestDataPathToProfilePath(
      /*from_path=*/test::kMalformedResourceId,
      /*to_path=*/kTextClassificationResourceId));

  NotifyResourceComponentDidChange(test::kLanguageComponentManifestVersion,
                                   test::kLanguageComponentId);

  // Act & Assert
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(QoraiAdsTextClassificationResourceTest, DoNotLoadMissingResource) {
  // Arrange
  ON_CALL(ads_client_mock_, LoadResourceComponent(kTextClassificationResourceId,
                                                  /*version=*/::testing::_,
                                                  /*callback=*/::testing::_))
      .WillByDefault([](const std::string& /*id*/, int /*version*/,
                        LoadFileCallback callback) {
        const base::FilePath path =
            test::ResourceComponentsDataPath().AppendASCII(
                test::kMissingResourceId);

        base::File file(
            path, base::File::Flags::FLAG_OPEN | base::File::Flags::FLAG_READ);
        std::move(callback).Run(std::move(file));
      });

  NotifyResourceComponentDidChange(test::kLanguageComponentManifestVersion,
                                   test::kLanguageComponentId);

  // Act & Assert
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(QoraiAdsTextClassificationResourceTest,
       DoNotLoadResourceWithInvalidLanguageComponentId) {
  NotifyResourceComponentDidChange(test::kLanguageComponentManifestVersion,
                                   test::kInvalidLanguageComponentId);

  // Act & Assert
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(QoraiAdsTextClassificationResourceTest,
       DoNotLoadResourceForNonRewardsUser) {
  // Arrange
  test::DisableQoraiRewards();

  NotifyResourceComponentDidChange(test::kLanguageComponentManifestVersion,
                                   test::kLanguageComponentId);

  // Act & Assert
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(QoraiAdsTextClassificationResourceTest,
       DoNotLoadResourceIfOptedOutOfAllAds) {
  // Arrange
  test::OptOutOfAllAds();

  NotifyResourceComponentDidChange(test::kLanguageComponentManifestVersion,
                                   test::kLanguageComponentId);

  // Act & Assert
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(QoraiAdsTextClassificationResourceTest,
       DoNotLoadResourceWhenOptingInToQoraiNewsAds) {
  // Arrange
  test::OptOutOfAllAds();

  NotifyResourceComponentDidChange(test::kLanguageComponentManifestVersion,
                                   test::kLanguageComponentId);
  ASSERT_FALSE(resource_->IsLoaded());

  // Act
  SetProfileBooleanPref(qorai_news::prefs::kQoraiNewsOptedIn, true);
  SetProfileBooleanPref(qorai_news::prefs::kNewTabPageShowToday, true);

  // Assert
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(QoraiAdsTextClassificationResourceTest,
       DoNotLoadResourceWhenOptingInToNewTabPageAds) {
  // Arrange
  test::OptOutOfAllAds();

  NotifyResourceComponentDidChange(test::kLanguageComponentManifestVersion,
                                   test::kLanguageComponentId);
  ASSERT_FALSE(resource_->IsLoaded());

  // Act
  SetProfileBooleanPref(
      ntp_background_images::prefs::kNewTabPageShowBackgroundImage, true);
  SetProfileBooleanPref(ntp_background_images::prefs::
                            kNewTabPageShowSponsoredImagesBackgroundImage,
                        true);

  // Assert
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(QoraiAdsTextClassificationResourceTest,
       LoadResourceWhenOptingInToNotificationAds) {
  // Arrange
  test::OptOutOfAllAds();

  NotifyResourceComponentDidChange(test::kLanguageComponentManifestVersion,
                                   test::kLanguageComponentId);
  ASSERT_FALSE(resource_->IsLoaded());

  // Act
  SetProfileBooleanPref(prefs::kOptedInToNotificationAds, true);

  // Assert
  EXPECT_TRUE(resource_->IsLoaded());
}

TEST_F(QoraiAdsTextClassificationResourceTest,
       DoNotResetResourceIfAlreadyOptedInToNotificationAds) {
  // Arrange
  test::OptOutOfQoraiNewsAds();
  test::OptOutOfNewTabPageAds();
  test::OptOutOfSearchResultAds();

  NotifyResourceComponentDidChange(test::kLanguageComponentManifestVersion,
                                   test::kLanguageComponentId);
  ASSERT_TRUE(resource_->IsLoaded());

  // Act
  SetProfileBooleanPref(prefs::kOptedInToNotificationAds, true);

  // Assert
  EXPECT_TRUE(resource_->IsLoaded());
}

TEST_F(QoraiAdsTextClassificationResourceTest,
       DoNotLoadResourceWhenOptingInToSearchResultAds) {
  // Arrange
  test::OptOutOfAllAds();

  NotifyResourceComponentDidChange(test::kLanguageComponentManifestVersion,
                                   test::kLanguageComponentId);
  ASSERT_FALSE(resource_->IsLoaded());

  // Act
  SetProfileBooleanPref(prefs::kOptedInToSearchResultAds, true);

  // Assert
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(
    QoraiAdsTextClassificationResourceTest,
    DoNotResetResourceForOnResourceComponentDidChangeWithInvalidLanguageComponentId) {
  // Arrange
  NotifyResourceComponentDidChange(test::kLanguageComponentManifestVersion,
                                   test::kLanguageComponentId);
  ASSERT_TRUE(resource_->IsLoaded());

  // Act
  NotifyResourceComponentDidChange(test::kLanguageComponentManifestVersion,
                                   test::kInvalidLanguageComponentId);

  // Assert
  EXPECT_TRUE(resource_->IsLoaded());
}

TEST_F(
    QoraiAdsTextClassificationResourceTest,
    DoNotResetResourceForOnResourceComponentDidChangeWithExistingManifestVersion) {
  // Arrange
  NotifyResourceComponentDidChange(test::kLanguageComponentManifestVersion,
                                   test::kLanguageComponentId);
  ASSERT_TRUE(resource_->IsLoaded());

  // Act
  NotifyResourceComponentDidChange(test::kLanguageComponentManifestVersion,
                                   test::kLanguageComponentId);

  // Assert
  EXPECT_TRUE(resource_->IsLoaded());
}

TEST_F(
    QoraiAdsTextClassificationResourceTest,
    DoNotResetResourceForOnResourceComponentDidChangeWithNewManifestVersion) {
  // Arrange
  NotifyResourceComponentDidChange(test::kLanguageComponentManifestVersion,
                                   test::kLanguageComponentId);
  ASSERT_TRUE(resource_->IsLoaded());
  ASSERT_EQ(test::kLanguageComponentManifestVersion,
            resource_->GetManifestVersion());

  // Act
  NotifyResourceComponentDidChange(
      test::kLanguageComponentManifestVersionUpdate,
      test::kLanguageComponentId);

  // Assert
  EXPECT_TRUE(resource_->IsLoaded());
  EXPECT_EQ(test::kLanguageComponentManifestVersionUpdate,
            resource_->GetManifestVersion());
}

TEST_F(QoraiAdsTextClassificationResourceTest,
       ResetResourceForOnNotifyDidUnregisterResourceComponent) {
  // Arrange
  NotifyResourceComponentDidChange(test::kLanguageComponentManifestVersion,
                                   test::kLanguageComponentId);
  ASSERT_TRUE(resource_->IsLoaded());

  // Act
  NotifyDidUnregisterResourceComponent(test::kLanguageComponentId);

  // Assert
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(
    QoraiAdsTextClassificationResourceTest,
    DoNotResetResourceForOnNotifyDidUnregisterResourceComponentWithInvalidLanguageComponentId) {
  // Arrange
  NotifyResourceComponentDidChange(test::kLanguageComponentManifestVersion,
                                   test::kLanguageComponentId);
  ASSERT_TRUE(resource_->IsLoaded());

  // Act
  NotifyDidUnregisterResourceComponent(test::kInvalidLanguageComponentId);

  // Assert
  EXPECT_TRUE(resource_->IsLoaded());
}

}  // namespace qorai_ads
