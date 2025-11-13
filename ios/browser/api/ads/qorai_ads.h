/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_API_ADS_QORAI_ADS_H_
#define QORAI_IOS_BROWSER_API_ADS_QORAI_ADS_H_

#import <Foundation/Foundation.h>
#import <UserNotifications/UserNotifications.h>
#import "qorai_ads.mojom.objc.h"

NS_ASSUME_NONNULL_BEGIN

OBJC_EXPORT NSString* const kQoraiAdsFirstRunAtPrefName;

@class NotificationAdIOS, InlineContentAdIOS, NewTabPageAdIOS;

OBJC_EXPORT
@protocol QoraiAdsNotificationHandler
@required
/// Returns `true` if notification ads can be shown.
- (BOOL)canShowNotificationAds;
/// Show notification `ad`.
- (void)showNotificationAd:(NotificationAdIOS*)ad;
/// Close the notification ad for the specified `placement_id`.
- (void)closeNotificationAd:(NSString*)placementId;
@end

OBJC_EXPORT
@protocol QoraiAdsCaptchaHandler
@required
/// Handle an adaptive captcha request for a given payment ID and captcha ID
- (void)handleAdaptiveCaptchaForPaymentId:(NSString*)paymentId
                                captchaId:(NSString*)captchaId;
@end

OBJC_EXPORT
@interface QoraiAds : NSObject

/// The notifications handler.
///
/// @see QoraiAdsNotificationHandler
@property(nonatomic, weak, nullable) id<QoraiAdsNotificationHandler>
    notificationsHandler;

/// An object to handle adaptive captcha requests
///
/// @see QoraiAdsCaptchaHandler
@property(nonatomic, weak, nullable) id<QoraiAdsCaptchaHandler> captchaHandler;

#pragma mark -

/// Returns `true` if ads are supported for the user's current country otherwise
/// returns `false`.
+ (BOOL)isSupportedRegion;

/// Returns `true` if the ads service is running otherwise returns `false`.
- (BOOL)isServiceRunning;

/// Returns `true` if should show Sponsored Images & Videos option in settings.
/// This function will be deprecated once Sponsored Video is available globally.
- (BOOL)shouldShowSponsoredImagesAndVideosSetting;

/// Returns `true` if the user opted-in to search result ads.
- (BOOL)isOptedInToSearchResultAds;

/// Returns `true` if the privacy notice infobar should be displayed when a user
/// clicks on a search result ad. This should be called before calling
/// `triggerSearchResultAdClickedEvent`.
- (BOOL)shouldShowSearchResultAdClickedInfoBar;

/// Returns `true` if the new tab takeover infobar should be displayed
/// when a user views a new tab takeover. This should be called before calling
/// `triggerNewTabPageAdEvent` for the `kViewedImpression` event type.
- (BOOL)shouldDisplayNewTabTakeoverInfobar;

/// Records that the new tab takeover infobar was displayed.
- (void)recordNewTabTakeoverInfobarWasDisplayed;

/// Suppresses the new tab takeover infobar.
- (void)suppressNewTabTakeoverInfobar;

/// Used to notify the ads service that the user has opted-in/opted-out to
/// Qorai News.
- (void)notifyQoraiNewsIsEnabledPreferenceDidChange:(BOOL)isEnabled;

/// Used to notify the ads service that the user has opted-in/opted-out to
/// sponsored images.
- (void)notifySponsoredImagesIsEnabledPreferenceDidChange:(BOOL)isEnabled;

/// Indicates if the user has opted-in to survey panelist.
@property(nonatomic) BOOL isSurveyPanelistEnabled;

/// Whether or not Qorai Ads is enabled and the user should receive
/// notification-style ads and be rewarded for it
@property(nonatomic, assign, getter=isEnabled)
    BOOL enabled NS_SWIFT_NAME(isEnabled);

#pragma mark - Initialization / Shutdown

- (void)initServiceWithSysInfo:(QoraiAdsSysInfo*)sysInfo
              buildChannelInfo:(QoraiAdsBuildChannelInfo*)buildChannelInfo
                    walletInfo:(nullable QoraiAdsWalletInfo*)walletInfo
                    completion:(void (^)(bool))completion;

/// Returns false if the ad service is already running.
- (void)shutdownService:(nullable void (^)())completion;

#pragma mark - Ads

// See `components/qorai_ads/core/internal/ads_impl.h`.

- (void)getStatementOfAccounts:
    (void (^)(NSInteger adsReceived,
              double estimatedEarnings,
              NSDate* _Nullable nextPaymentDate))completion;

- (void)maybeServeInlineContentAd:(NSString*)dimensions
                       completion:
                           (void (^)(NSString* dimensions,
                                     InlineContentAdIOS* _Nullable))completion;

- (void)triggerInlineContentAdEvent:(NSString*)placementId
                 creativeInstanceId:(NSString*)creativeInstanceId
                          eventType:(QoraiAdsInlineContentAdEventType)eventType
                         completion:(void (^)(BOOL success))completion;

- (void)triggerNewTabPageAdEvent:(NSString*)wallpaperId
              creativeInstanceId:(NSString*)creativeInstanceId
                      metricType:(QoraiAdsNewTabPageAdMetricType)metricType
                       eventType:(QoraiAdsNewTabPageAdEventType)eventType
                      completion:(void (^)(BOOL success))completion;

- (void)maybeGetNotificationAd:(NSString*)identifier
                    completion:
                        (void (^)(NotificationAdIOS* _Nullable))completion;

- (void)triggerNotificationAdEvent:(NSString*)placementId
                         eventType:(QoraiAdsNotificationAdEventType)eventType
                        completion:(void (^)(BOOL success))completion;

- (void)triggerPromotedContentAdEvent:(NSString*)placementId
                   creativeInstanceId:(NSString*)creativeInstanceId
                            eventType:
                                (QoraiAdsPromotedContentAdEventType)eventType
                           completion:(void (^)(BOOL success))completion;

- (void)triggerSearchResultAdClickedEvent:(NSString*)placementId
                               completion:(void (^)(BOOL success))completion;

- (void)triggerSearchResultAdViewedEvent:
            (QoraiAdsCreativeSearchResultAdInfo*)searchResultAd
                              completion:(void (^)(BOOL success))completion;

- (void)purgeOrphanedAdEventsForType:(QoraiAdsAdType)adType
                          completion:(void (^)(BOOL success))completion;

- (void)clearData:(void (^)())completion;

#pragma mark - New Tab Page Ad

- (nullable NewTabPageAdIOS*)maybeGetPrefetchedNewTabPageAd;

- (void)onFailedToPrefetchNewTabPageAd:(NSString*)placementId
                    creativeInstanceId:(NSString*)creativeInstanceId
    NS_SWIFT_NAME(onFailedToPrefetchNewTabPageAd(placementId:creativeInstanceId:));

#pragma mark - Ads client notifier

// See `components/qorai_ads/core/public/ads_client/ads_client_notifier.h`.

- (void)notifyRewardsWalletDidUpdate:(NSString*)paymentId
                          base64Seed:(NSString*)base64Seed;

- (void)notifyTabTextContentDidChange:(NSInteger)tabId
                        redirectChain:(NSArray<NSURL*>*)redirectChain
                                 text:(NSString*)text;

- (void)notifyTabHtmlContentDidChange:(NSInteger)tabId
                        redirectChain:(NSArray<NSURL*>*)redirectChain
                                 html:(NSString*)html;

- (void)notifyTabDidStartPlayingMedia:(NSInteger)tabId;

- (void)notifyTabDidStopPlayingMedia:(NSInteger)tabId;

- (void)notifyTabDidChange:(NSInteger)tabId
             redirectChain:(NSArray<NSURL*>*)redirectChain
           isNewNavigation:(BOOL)isNewNavigation
               isRestoring:(BOOL)isRestoring
                isSelected:(BOOL)isSelected;

- (void)notifyTabDidLoad:(NSInteger)tabId
          httpStatusCode:(NSInteger)httpStatusCode;

- (void)notifyDidCloseTab:(NSInteger)tabId;

#pragma mark -

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithStateStoragePath:(NSString*)path;

@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_API_ADS_QORAI_ADS_H_
