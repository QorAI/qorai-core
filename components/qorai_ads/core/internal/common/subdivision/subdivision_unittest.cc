/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/subdivision/subdivision.h"

#include "qorai/components/qorai_ads/core/internal/common/subdivision/subdivision_observer_mock.h"
#include "qorai/components/qorai_ads/core/internal/common/subdivision/url_request/subdivision_url_request_builder_util.h"
#include "qorai/components/qorai_ads/core/internal/common/subdivision/url_request/subdivision_url_request_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/mock_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/prefs/pref_util.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings_test_util.h"
#include "qorai/components/qorai_ads/core/public/prefs/pref_names.h"
#include "qorai/components/qorai_news/common/pref_names.h"
#include "qorai/components/qorai_rewards/core/pref_names.h"
#include "qorai/components/ntp_background_images/common/pref_names.h"
#include "net/http/http_status_code.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsSubdivisionTest : public test::TestBase {
 public:
  void SetUp() override {
    test::TestBase::SetUp();

    subdivision_ = std::make_unique<Subdivision>();
    subdivision_->AddObserver(&subdivision_observer_mock_);
  }

  void TearDown() override {
    subdivision_->RemoveObserver(&subdivision_observer_mock_);

    test::TestBase::TearDown();
  }

  void MockHttpOkUrlResponse(const std::string& country_code,
                             const std::string& subdivision_code) {
    const test::URLResponseMap url_responses = {
        {BuildSubdivisionUrlPath(),
         {{net::HTTP_OK, test::BuildSubdivisionUrlResponseBody(
                             country_code, subdivision_code)}}}};
    test::MockUrlResponses(ads_client_mock_, url_responses);
  }

 protected:
  std::unique_ptr<Subdivision> subdivision_;

  SubdivisionObserverMock subdivision_observer_mock_;
};

TEST_F(QoraiAdsSubdivisionTest, OnDidInitializeAds) {
  // Arrange
  MockHttpOkUrlResponse(/*country_code=*/"US", /*subdivision_code=*/"CA");

  EXPECT_CALL(subdivision_observer_mock_, OnDidUpdateSubdivision("US-CA"));

  // Act
  NotifyDidInitializeAds();

  // Assert
  EXPECT_TRUE(HasPendingTasks());
}

TEST_F(QoraiAdsSubdivisionTest, FetchIfUserJoinsQoraiRewards) {
  // Arrange
  test::DisableQoraiRewards();

  MockHttpOkUrlResponse(/*country_code=*/"US", /*subdivision_code=*/"CA");

  EXPECT_CALL(subdivision_observer_mock_, OnDidUpdateSubdivision);

  // Act & Assert
  SetProfileBooleanPref(qorai_rewards::prefs::kEnabled, true);
}

TEST_F(QoraiAdsSubdivisionTest, DoNotFetchIfUserHasNotJoinedQoraiRewards) {
  // Arrange
  MockHttpOkUrlResponse(/*country_code=*/"US", /*subdivision_code=*/"CA");

  EXPECT_CALL(subdivision_observer_mock_, OnDidUpdateSubdivision).Times(0);

  // Act & Assert
  SetProfileBooleanPref(qorai_rewards::prefs::kEnabled, false);
}

TEST_F(QoraiAdsSubdivisionTest, DoNotFetchWhenOptingOutOfNotificationAds) {
  // Arrange
  MockHttpOkUrlResponse(/*country_code=*/"US", /*subdivision_code=*/"CA");

  EXPECT_CALL(subdivision_observer_mock_, OnDidUpdateSubdivision).Times(0);

  // Act & Assert
  SetProfileBooleanPref(prefs::kOptedInToNotificationAds, false);
}

TEST_F(QoraiAdsSubdivisionTest, FetchWhenOptingInToNotificationAds) {
  // Arrange
  test::OptOutOfAllAds();

  MockHttpOkUrlResponse(/*country_code=*/"US", /*subdivision_code=*/"CA");

  EXPECT_CALL(subdivision_observer_mock_, OnDidUpdateSubdivision);

  // Act & Assert
  SetProfileBooleanPref(prefs::kOptedInToNotificationAds, true);
}

TEST_F(QoraiAdsSubdivisionTest, DoNotFetchWhenOptingOutOfQoraiNewsAds) {
  // Arrange
  MockHttpOkUrlResponse(/*country_code=*/"US", /*subdivision_code=*/"CA");

  EXPECT_CALL(subdivision_observer_mock_, OnDidUpdateSubdivision).Times(0);

  // Act & Assert
  SetProfileBooleanPref(qorai_news::prefs::kQoraiNewsOptedIn, false);
  SetProfileBooleanPref(qorai_news::prefs::kNewTabPageShowToday, false);
  task_environment_.DescribeCurrentTasks();
}

TEST_F(QoraiAdsSubdivisionTest, DoNotFetchWhenOptingInToQoraiNewsAds) {
  // Arrange
  test::OptOutOfAllAds();

  MockHttpOkUrlResponse(/*country_code=*/"US", /*subdivision_code=*/"CA");

  EXPECT_CALL(subdivision_observer_mock_, OnDidUpdateSubdivision).Times(0);

  // Act & Assert
  SetProfileBooleanPref(qorai_news::prefs::kQoraiNewsOptedIn, true);
  SetProfileBooleanPref(qorai_news::prefs::kNewTabPageShowToday, true);
}

TEST_F(QoraiAdsSubdivisionTest, DoNotFetchWhenOptingOutOfNewTabPageAds) {
  // Arrange
  MockHttpOkUrlResponse(/*country_code=*/"US", /*subdivision_code=*/"CA");

  EXPECT_CALL(subdivision_observer_mock_, OnDidUpdateSubdivision).Times(0);

  // Act & Assert
  SetProfileBooleanPref(
      ntp_background_images::prefs::kNewTabPageShowBackgroundImage, false);
  SetProfileBooleanPref(ntp_background_images::prefs::
                            kNewTabPageShowSponsoredImagesBackgroundImage,
                        false);
}

TEST_F(QoraiAdsSubdivisionTest, DoNotFetchWhenOptingInToNewTabPageAds) {
  // Arrange
  test::OptOutOfAllAds();

  MockHttpOkUrlResponse(/*country_code=*/"US", /*subdivision_code=*/"CA");

  EXPECT_CALL(subdivision_observer_mock_, OnDidUpdateSubdivision).Times(0);

  // Act & Assert
  SetProfileBooleanPref(
      ntp_background_images::prefs::kNewTabPageShowBackgroundImage, true);
  SetProfileBooleanPref(ntp_background_images::prefs::
                            kNewTabPageShowSponsoredImagesBackgroundImage,
                        true);
}

TEST_F(QoraiAdsSubdivisionTest, DoNotFetchWhenOptingOutOfSearchResultAds) {
  // Arrange
  MockHttpOkUrlResponse(/*country_code=*/"US", /*subdivision_code=*/"CA");

  EXPECT_CALL(subdivision_observer_mock_, OnDidUpdateSubdivision).Times(0);

  // Act & Assert
  SetProfileBooleanPref(prefs::kOptedInToSearchResultAds, false);
}

TEST_F(QoraiAdsSubdivisionTest, DoNotFetchWhenOptingInToSearchResultAds) {
  // Arrange
  test::OptOutOfAllAds();

  MockHttpOkUrlResponse(/*country_code=*/"US", /*subdivision_code=*/"CA");

  EXPECT_CALL(subdivision_observer_mock_, OnDidUpdateSubdivision).Times(0);

  // Act & Assert
  SetProfileBooleanPref(prefs::kOptedInToSearchResultAds, true);
}

TEST_F(QoraiAdsSubdivisionTest,
       DoNotRetryIfHttpForbiddenUrlResponseStatusCode) {
  // Arrange
  const test::URLResponseMap url_responses = {
      {BuildSubdivisionUrlPath(),
       {{net::HTTP_FORBIDDEN,
         /*response_body=*/net::GetHttpReasonPhrase(net::HTTP_FORBIDDEN)}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  EXPECT_CALL(subdivision_observer_mock_, OnDidUpdateSubdivision).Times(0);

  NotifyDidInitializeAds();

  // Act
  FastForwardClockToNextPendingTask();

  // Assert
  EXPECT_TRUE(HasPendingTasks());
}

TEST_F(QoraiAdsSubdivisionTest,
       RetryIfHttpInternalServerErrorResponseStatusCode) {
  // Arrange
  const test::URLResponseMap url_responses = {
      {BuildSubdivisionUrlPath(),
       {{net::HTTP_INTERNAL_SERVER_ERROR,
         /*response_body=*/net::GetHttpReasonPhrase(
             net::HTTP_INTERNAL_SERVER_ERROR)},
        {net::HTTP_OK,
         test::BuildSubdivisionUrlResponseBody(
             /*country_code=*/"US", /*subdivision_code=*/"CA")}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  EXPECT_CALL(subdivision_observer_mock_, OnDidUpdateSubdivision("US-CA"));

  NotifyDidInitializeAds();

  // Act
  FastForwardClockToNextPendingTask();

  // Assert
  EXPECT_TRUE(HasPendingTasks());
}

TEST_F(QoraiAdsSubdivisionTest, RetryIfResponseBodyIsInvalid) {
  // Arrange
  const test::URLResponseMap url_responses = {
      {BuildSubdivisionUrlPath(), {{net::HTTP_OK, /*response_body=*/"{}"}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  EXPECT_CALL(subdivision_observer_mock_, OnDidUpdateSubdivision).Times(0);

  // Act
  NotifyDidInitializeAds();

  // Assert
  EXPECT_TRUE(HasPendingTasks());
}

TEST_F(QoraiAdsSubdivisionTest, NoRegionSubdivisionCode) {
  // Arrange
  MockHttpOkUrlResponse(/*country_code=*/"US",
                        /*subdivision_code=*/"NO REGION");

  EXPECT_CALL(subdivision_observer_mock_,
              OnDidUpdateSubdivision("US-NO REGION"));

  // Act
  NotifyDidInitializeAds();

  // Assert
  EXPECT_TRUE(HasPendingTasks());
}

TEST_F(QoraiAdsSubdivisionTest, EmptySubdivisionCode) {
  // Arrange
  MockHttpOkUrlResponse(/*country_code=*/"US", /*subdivision_code=*/"");

  EXPECT_CALL(subdivision_observer_mock_, OnDidUpdateSubdivision).Times(0);

  // Act
  NotifyDidInitializeAds();

  // Assert
  EXPECT_TRUE(HasPendingTasks());
}

TEST_F(QoraiAdsSubdivisionTest, EmptyCountryCode) {
  // Arrange
  MockHttpOkUrlResponse(/*country_code=*/"", /*subdivision_code=*/"CA");

  EXPECT_CALL(subdivision_observer_mock_, OnDidUpdateSubdivision).Times(0);

  // Act
  NotifyDidInitializeAds();

  // Assert
  EXPECT_TRUE(HasPendingTasks());
}

}  // namespace qorai_ads
