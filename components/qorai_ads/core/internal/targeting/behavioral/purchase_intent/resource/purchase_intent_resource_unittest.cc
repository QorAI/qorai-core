/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/targeting/behavioral/purchase_intent/resource/purchase_intent_resource.h"

#include <memory>
#include <utility>

#include "base/files/file.h"
#include "base/files/file_path.h"
#include "qorai/components/qorai_ads/core/internal/common/resources/country_components_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/common/resources/resource_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/common/test/file_path_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/prefs/pref_util.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings_test_util.h"
#include "qorai/components/qorai_ads/core/internal/targeting/behavioral/purchase_intent/resource/purchase_intent_resource_constants.h"
#include "qorai/components/qorai_ads/core/public/prefs/pref_names.h"
#include "qorai/components/qorai_news/common/pref_names.h"
#include "qorai/components/ntp_background_images/common/pref_names.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsPurchaseIntentResourceTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    resource_ = std::make_unique<PurchaseIntentResource>();
  }

  std::unique_ptr<PurchaseIntentResource> resource_;
};

TEST_F(QoraiAdsPurchaseIntentResourceTest, IsResourceNotLoaded) {
  // Act & Assert
  EXPECT_FALSE(resource_->GetManifestVersion());
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(QoraiAdsPurchaseIntentResourceTest, LoadResource) {
  // Arrange
  NotifyResourceComponentDidChange(test::kCountryComponentManifestVersion,
                                   test::kCountryComponentId);

  // Act & Assert
  EXPECT_TRUE(resource_->IsLoaded());
}

TEST_F(QoraiAdsPurchaseIntentResourceTest, DoNotLoadMalformedResource) {
  // Arrange
  ASSERT_TRUE(CopyFileFromTestDataPathToProfilePath(
      /*from_path=*/test::kMalformedResourceId,
      /*to_path=*/kPurchaseIntentResourceId));

  NotifyResourceComponentDidChange(test::kCountryComponentManifestVersion,
                                   test::kCountryComponentId);

  // Act & Assert
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(QoraiAdsPurchaseIntentResourceTest, DoNotLoadMissingResource) {
  // Arrange
  ON_CALL(ads_client_mock_, LoadResourceComponent(kPurchaseIntentResourceId,
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

  NotifyResourceComponentDidChange(test::kCountryComponentManifestVersion,
                                   test::kCountryComponentId);

  // Act & Assert
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(QoraiAdsPurchaseIntentResourceTest,
       DoNotLoadResourceWithInvalidCountryComponentId) {
  NotifyResourceComponentDidChange(test::kCountryComponentManifestVersion,
                                   test::kInvalidCountryComponentId);

  // Act & Assert
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(QoraiAdsPurchaseIntentResourceTest,
       DoNotLoadResourceIfOptedOutOfAllAds) {
  // Arrange
  test::OptOutOfAllAds();

  NotifyResourceComponentDidChange(test::kCountryComponentManifestVersion,
                                   test::kCountryComponentId);

  // Act & Assert
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(QoraiAdsPurchaseIntentResourceTest,
       DoNotLoadResourceWhenOptingInToQoraiNewsAds) {
  // Arrange
  test::OptOutOfAllAds();

  NotifyResourceComponentDidChange(test::kCountryComponentManifestVersion,
                                   test::kCountryComponentId);
  ASSERT_FALSE(resource_->IsLoaded());

  // Act
  SetProfileBooleanPref(qorai_news::prefs::kQoraiNewsOptedIn, true);
  SetProfileBooleanPref(qorai_news::prefs::kNewTabPageShowToday, true);

  // Assert
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(QoraiAdsPurchaseIntentResourceTest,
       DoNotLoadResourceWhenOptingInToNewTabPageAds) {
  // Arrange
  test::OptOutOfAllAds();

  NotifyResourceComponentDidChange(test::kCountryComponentManifestVersion,
                                   test::kCountryComponentId);
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

TEST_F(QoraiAdsPurchaseIntentResourceTest,
       LoadResourceWhenOptingInToNotificationAds) {
  // Arrange
  test::OptOutOfAllAds();

  NotifyResourceComponentDidChange(test::kCountryComponentManifestVersion,
                                   test::kCountryComponentId);
  ASSERT_FALSE(resource_->IsLoaded());

  // Act
  SetProfileBooleanPref(prefs::kOptedInToNotificationAds, true);

  // Assert
  EXPECT_TRUE(resource_->IsLoaded());
}

TEST_F(QoraiAdsPurchaseIntentResourceTest,
       DoNotResetResourceIfAlreadyOptedInToNotificationAds) {
  // Arrange
  test::OptOutOfQoraiNewsAds();
  test::OptOutOfNewTabPageAds();
  test::OptOutOfSearchResultAds();

  NotifyResourceComponentDidChange(test::kCountryComponentManifestVersion,
                                   test::kCountryComponentId);
  ASSERT_TRUE(resource_->IsLoaded());

  // Act
  SetProfileBooleanPref(prefs::kOptedInToNotificationAds, true);

  // Assert
  EXPECT_TRUE(resource_->IsLoaded());
}

TEST_F(QoraiAdsPurchaseIntentResourceTest,
       DoNotLoadResourceWhenOptingInToSearchResultAds) {
  // Arrange
  test::OptOutOfAllAds();

  NotifyResourceComponentDidChange(test::kCountryComponentManifestVersion,
                                   test::kCountryComponentId);
  ASSERT_FALSE(resource_->IsLoaded());

  // Act
  SetProfileBooleanPref(prefs::kOptedInToSearchResultAds, true);

  // Assert
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(
    QoraiAdsPurchaseIntentResourceTest,
    DoNotResetResourceForOnResourceComponentDidChangeWithInvalidCountryComponentId) {
  // Arrange
  NotifyResourceComponentDidChange(test::kCountryComponentManifestVersion,
                                   test::kCountryComponentId);
  ASSERT_TRUE(resource_->IsLoaded());

  // Act
  NotifyResourceComponentDidChange(test::kCountryComponentManifestVersion,
                                   test::kInvalidCountryComponentId);

  // Assert
  EXPECT_TRUE(resource_->IsLoaded());
}

TEST_F(
    QoraiAdsPurchaseIntentResourceTest,
    DoNotResetResourceForOnResourceComponentDidChangeWithExistingManifestVersion) {
  // Arrange
  NotifyResourceComponentDidChange(test::kCountryComponentManifestVersion,
                                   test::kCountryComponentId);
  ASSERT_TRUE(resource_->IsLoaded());

  // Act
  NotifyResourceComponentDidChange(test::kCountryComponentManifestVersion,
                                   test::kCountryComponentId);

  // Assert
  EXPECT_TRUE(resource_->IsLoaded());
}

TEST_F(
    QoraiAdsPurchaseIntentResourceTest,
    DoNotResetResourceForOnResourceComponentDidChangeWithNewManifestVersion) {
  // Arrange
  NotifyResourceComponentDidChange(test::kCountryComponentManifestVersion,
                                   test::kCountryComponentId);
  ASSERT_TRUE(resource_->IsLoaded());
  ASSERT_EQ(test::kCountryComponentManifestVersion,
            resource_->GetManifestVersion());

  // Act
  NotifyResourceComponentDidChange(test::kCountryComponentManifestVersionUpdate,
                                   test::kCountryComponentId);

  // Assert
  EXPECT_TRUE(resource_->IsLoaded());
  EXPECT_EQ(test::kCountryComponentManifestVersionUpdate,
            resource_->GetManifestVersion());
}

TEST_F(QoraiAdsPurchaseIntentResourceTest,
       ResetResourceForOnNotifyDidUnregisterResourceComponent) {
  // Arrange
  NotifyResourceComponentDidChange(test::kCountryComponentManifestVersion,
                                   test::kCountryComponentId);
  ASSERT_TRUE(resource_->IsLoaded());

  // Act
  NotifyDidUnregisterResourceComponent(test::kCountryComponentId);

  // Assert
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(
    QoraiAdsPurchaseIntentResourceTest,
    DoNotResetResourceForOnNotifyDidUnregisterResourceComponentWithInvalidCountryComponentId) {
  // Arrange
  NotifyResourceComponentDidChange(test::kCountryComponentManifestVersion,
                                   test::kCountryComponentId);
  ASSERT_TRUE(resource_->IsLoaded());

  // Act
  NotifyDidUnregisterResourceComponent(test::kInvalidCountryComponentId);

  // Assert
  EXPECT_TRUE(resource_->IsLoaded());
}

}  // namespace qorai_ads
