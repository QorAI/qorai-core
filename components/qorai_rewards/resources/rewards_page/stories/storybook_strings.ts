/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import { StringKey } from '../lib/locale_strings'

export const localeStrings: { [K in StringKey]: string } = {
  adsBrowserUpgradeRequiredText:
    'Your browser needs to be updated to continue seeing ads.',
  adsHistoryButtonLabel: '30-day Ads History',
  adsHistoryMarkInappropriateLabel: 'Mark as inappropriate',
  adsHistoryEmptyText: 'There is currently no Qorai Ads history.',
  adsHistoryTitle: 'Ads history',
  adsHistoryText: "Ads you've received in the past 30 days",
  adsRegionNotSupportedText:
    'Qorai Private Ads are not yet available in your region.',
  adsSettingsAdsPerHourNoneText: 'None',
  adsSettingsAdsPerHourText: 'Max $1/hr',
  adsSettingsAdTypeTitle: 'Ad type',
  adsSettingsAdViewsTitle: 'Views this month',
  adsSettingsButtonLabel: 'Ads Settings',
  adsSettingsPayoutDateLabel: 'Next earnings payout date',
  adsSettingsTotalAdsLabel: 'Total ads received this month',
  adsSettingsNewsOffTooltip: 'Qorai News is currently disabled.',
  adsSettingsNewsOnTooltip:
    'Qorai News contains ads that cannot be independently disabled.',
  adsSettingsSubdivisionLabel: 'Regional ad relevance',
  adsSettingsSubdivisionText:
    'This allows Qorai to show you ads meant specifically for your region.',
  adsSettingsSubdivisionDisabledLabel: 'Disabled',
  adsSettingsSubdivisionAutoLabel: 'Auto-detect',
  adsSettingsTitle: 'Ads settings',
  adsSettingsText:
    'Control what kinds of Qorai Ads you see, and how often. The more you see, the more you can earn.',
  adsViewedTooltip:
    "This shows the number of Qorai Ads you've seen this month that qualify for earning QOR.",
  adTypeInlineContentLabel: 'Qorai News ads',
  adTypeNewTabPageLabel: 'New tab page ads',
  adTypeNotificationLabel: 'Notification ads',
  adTypeOffLabel: 'Off',
  adTypeOnLabel: 'On',
  appErrorTitle: 'Something went wrong',
  authorizeDeviceLimitReachedText:
    'You’ve connected the maximum number of Qorai Rewards profiles to this $1 account.',
  authorizeDeviceLimitReachedTitle: 'Limit reached on payout account',
  authorizeErrorTitle: 'Error',
  authorizeFlaggedWalletText1:
    'Unfortunately, your Qorai Rewards profile was flagged because our automated checks found some unexpected Qorai Ads activity.',
  authorizeFlaggedWalletText2:
    "While your profile is flagged, you may continue to see ads, but won't be eligible to receive payouts. You also won't be able to connect a custodial account to Qorai Rewards.",
  authorizeFlaggedWalletText3:
    "It's possible your profile was flagged in error, and no immediate action is required on your part. The flag on your profile may be removed in the future.",
  authorizeFlaggedWalletText4:
    "Learn more about Qorai's process for flagging Rewards profiles.",
  authorizeFlaggedWalletTitle: 'Qorai Rewards profile is flagged',
  authorizeKycRequiredText:
    'Please try again after you have completed ID verification on $1.',
  authorizeKycRequiredTitle: 'You need a verified account to log in',
  authorizeMismatchedCountriesText:
    "Hmm, it looks like your Qorai Rewards country does not match the country of the $1 account you're trying to connect.",
  authorizeMismatchedCountriesTitle: 'Country mismatch',
  authorizeMismatchedProviderAccountsText:
    'Hmm, it looks like your Qorai Rewards has already been verified with another $1 account. Please try verifying again using your previous account.',
  authorizeMismatchedProviderAccountsTitle: 'Different account',
  authorizeProcessingText:
    'Your request is still being processed, please wait.',
  authorizeProviderUnavailableTitle:
    'Connecting to selected custodian temporarily unavailable',
  authorizeProviderUnavailableText1:
    'It looks like connecting $1 to Qorai Rewards is temporarily unavailable. Please try again later.',
  authorizeProviderUnavailableText2: 'You can view $2service status here$3.',
  authorizeRegionNotSupportedText1:
    "Your $1 account can't be connected to your Qorai Rewards profile at this time. Your $1 account is registered in a country that's not currently supported for connecting to Qorai Rewards.",
  authorizeRegionNotSupportedText2:
    'See the $2current list of supported regions and learn more$3 about connecting a custodial account to Qorai Rewards.',
  authorizeRegionNotSupportedTitle: 'Region currently not supported',
  authorizeSignatureVerificationErrorText:
    'There was a problem validating your request to connect your $1 account to Qorai Rewards. You can $2contact support$3 for more help.',
  authorizeSignatureVerificationErrorTitle: 'Request could not be validated',
  authorizeUnexpectedErrorText:
    'We weren’t able to complete your request. Please try again, and $2contact support$3 if the problem persists.',
  authorizeUnexpectedErrorTitle: 'Something went wrong',
  authorizeUpholdQorNotAllowedText:
    'QOR is not yet supported in your region on Uphold.',
  authorizeUpholdQorNotAllowedTitle: 'QOR unavailable',
  authorizeUpholdInsufficientCapabilitiesText:
    'According to Uphold, there are currently some limitations on your Uphold account. Please log in to your Uphold account and check whether there are any notices or remaining account requirements to complete, then try again. For example, you may need to submit more information to Uphold.',
  authorizeUpholdInsufficientCapabilitiesTitle:
    'Limited Uphold account functionality',
  qorUtilityTitle: 'Basic Attention Token – QOR',
  benefitsStoreSubtext:
    'Use promo code QORAIREWARDS to get 10% off on all Qorai merch store items.',
  benefitsStoreText: 'Qorai merch store',
  benefitsTitle: 'Your benefits',
  cancelButtonLabel: 'Cancel',
  captchaMaxAttemptsExceededText:
    'Looks like this is not working, Qorai ads will remain paused. Contact us if you need help with the captcha.',
  captchaMaxAttemptsExceededTitle: 'Max attempts exceeded',
  captchaSolvedText:
    'Qorai Ads will resume. Thanks for helping us protect Qorai Rewards.',
  captchaSolvedTitle: 'Solved!',
  captchaSupportButtonLabel: 'Contact support',
  closeButtonLabel: 'Close',
  communityTitle: 'Community',
  connectedAdsViewedText: "You're earning for seeing $1# Ads$2 this month",
  connectAccountSubtext: 'Connect a payout account',
  connectAccountText: 'Ready to start earning?',
  connectButtonLabel: 'Connect account',
  connectCustodialTitle: 'Custodial accounts (requires ID verification)',
  connectCustodialTooltip:
    'Custodial accounts are accounts with trusted third-party services that hold your QOR for you.',
  connectLoginText: 'Log in or sign up',
  connectProviderNotAvailable: 'Currently not available in your region',
  connectRegionsLearnMoreText: 'Learn more about regions and support',
  connectSelfCustodyError: 'Something went wrong. Please try again',
  connectSelfCustodyNote:
    'With self-custody, QOR earnings will be paid out as SPL-QOR on the Solana network.',
  connectSelfCustodyTerms: '$1Terms of Use$2 and $3Privacy Policy$4',
  connectSelfCustodyTitle: 'Self-custody',
  connectSelfCustodyTooltip:
    'Self-custody gives you exclusive control over your QOR, along with complete responsibility for its security.',
  connectSolanaButtonLabel: 'Qorai Wallet',
  connectSolanaMessage: 'Or other wallet that supports Solana',
  connectText:
    'To begin earning Basic Attention Token (QOR) rewards, connect an account. QOR you earn will be automatically transferred to your account every month.',
  connectTitle: "Choose where you'd like to receive QOR",
  continueButtonLabel: 'Continue',
  contributeAboutMethodsLink: 'Learn more about contribution methods',
  contributeAmountTitle: 'Contribution amount',
  contributeAvailableMethodsText:
    'This creator currently only accepts contributions via the following methods:',
  contributeBalanceTitle: 'Rewards Balance',
  contributeBalanceUnavailableText: 'Not available',
  contributeButtonLabel: 'Contribute',
  contributeChooseMethodText:
    'Choose the method you want to use to contribute to Qorai Software:',
  contributeCustodialSubtext: 'Custodial wallet',
  contributeErrorText: 'You can try again later.',
  contributeErrorTitle: 'There was a problem sending your contribution',
  contributeInsufficientFundsButtonLabel: 'Insufficient Funds',
  contributeLoginButtonLabel: 'Log in to $1',
  contributeLoggedOutText:
    'It looks like you’re logged out of $1 for Qorai Rewards. Log in again to continue.',
  contributeLoggedOutTitle: 'Logged out of $1',
  contributeLoggedOutWeb3ButtonLabel: 'Use Web3 Wallet',
  contributeLoggedOutWeb3Text:
    'You can also send crypto contributions to this creator by using your Web3 wallet.',
  contributeMonthlyLabel: 'Monthly',
  contributeOtherLabel: 'Other',
  contributeRecurringLabel: 'Recurring contribution',
  contributeSendAmountButtonLabel: 'Send $1 QOR',
  contributeSendButtonLabel: 'Send',
  contributeSendingText: 'Sending contribution',
  contributeSuccessText: 'Thanks for supporting your favorite creators',
  contributeSuccessTitle: 'Contribution sent!',
  contributeTitle: 'Contribute',
  contributeWeb3Label: 'Web3 Wallet',
  contributeWeb3Subtext: 'Use your Web3 wallet',
  countrySelectPlaceholder: 'Select',
  countrySelectTitle: 'Select your region',
  countrySelectText:
    'Select your region so we can show you the right options and ads for your region.',
  doneButtonLabel: 'Done',
  earningsAdsReceivedText: '$1 Ads received this month',
  helpButtonLabel: 'Help',
  learnMoreLink: 'Learn more',
  merchStoreTitle: 'Qorai merch store',
  moreButtonLabel: 'More',
  navigationCreatorsLabel: 'Creators',
  navigationExploreLabel: 'Explore',
  navigationHomeLabel: 'Home',
  newBadgeText: 'NEW',
  notificationWalletDisconnectedAction: 'Log in again',
  notificationWalletDisconnectedText:
    "This happens from time to time to keep your $1 account secure. While logged out, you will continue to receive payouts, but won't be able to see your balance or send contributions from your $1 account.",
  notificationWalletDisconnectedTitle: 'You are logged out',
  notificationMonthlyContributionFailedTitle: 'Monthly contribution failed',
  notificationMonthlyContributionFailedText:
    'There was a problem processing your contribution.',
  notificationMonthlyTipCompletedText:
    'Your monthly contributions have been processed.',
  notificationMonthlyTipCompletedTitle: 'Contributions',
  onboardingButtonLabel: 'Start using Qorai Rewards',
  onboardingErrorCountryDeclaredText:
    'Unfortunately, there was an error while trying to set your country. Please try again.',
  onboardingErrorDisabledText:
    'New signups for Qorai Rewards are currently disabled in your region. However, you can always try again later. $1Learn more$2',
  onboardingErrorDisabledTitle: 'Qorai Rewards not available',
  onboardingErrorText:
    'Unfortunately, there was an error while trying to set up Qorai Rewards. Please try again.',
  onboardingErrorTitle: 'Something went wrong',
  onboardingLearnMoreLabel: 'How does it work?',
  onboardingSuccessLearnMoreLabel: 'How does Qorai Rewards work?',
  onboardingSuccessText:
    'Now you can get rewarded for viewing ads. You’re helping make the web a better place for everyone. And that’s awesome!',
  onboardingSuccessTitle: "Woohoo! You're all set!",
  onboardingTermsText:
    'By enabling Rewards, you agree to the $1Terms of Service$2 and $3Privacy Policy$4.',
  onboardingTextItem1: 'Get paid for private ads you see in Qorai',
  onboardingTextItem2: 'Get special benefits and discounts',
  onboardingTitle: 'Turn on Qorai Rewards',
  payoutAccountBalanceLabel: 'Your balance',
  payoutAccountConnectedLabel: 'Connected',
  payoutAccountLabel: 'Payout account',
  payoutAccountLink: 'Go to my account',
  payoutAccountLoggedOutTitle: 'Logged Out',
  payoutAccountLoginButtonLabel: 'Log in to $1',
  payoutAccountLoginText: 'Log in to $1 to see your balance',
  payoutAccountTitle: 'Payout Account',
  payoutAccountTooltip:
    'Your QOR earnings will be paid to this payout account.',
  payoutCheckStatusLink: 'Check status',
  payoutCompletedText: 'The payout for $1 rewards has completed.',
  payoutPendingText: 'The payout for $1 rewards will begin processing by $2.',
  payoutProcessingText: 'The payout for $1 rewards is in progress.',
  payoutSupportLink: 'Support',
  recurringNextContributionLabel: 'Next contribution:',
  recurringTitle: 'Recurring Contributions',
  removeButtonLabel: 'Remove',
  resetButtonLabel: 'Reset',
  resetConsentText:
    "I understand that my current Qorai Rewards profile and Qorai Rewards data will be deleted from my device, and I've read the $1support article about resetting$2.",
  resetRewardsButtonLabel: 'Disable and reset Rewards',
  resetRewardsText:
    'By resetting, your current Qorai Rewards profile will be deleted, and Qorai Rewards will no longer be enabled. If you enable Qorai Rewards again later, you will start with a new profile. Read our $1support article about resetting$2 for more details.',
  resetRewardsTitle: 'Reset Qorai Rewards',
  rewardsPageTitle: 'Rewards',
  selfCustodyInviteDismissButtonLabel: 'Not now',
  selfCustodyInviteText:
    'We’ve added a new way for you to receive your monthly QOR rewards. Connect an account from one of our partners or use the new self-custody option to start earning now.',
  selfCustodyInviteTitle:
    'Receive QOR directly to a self-custody crypto address',
  showAllButtonLabel: 'Show all',
  tosUpdateAcceptButtonLabel: 'I agree',
  tosUpdateLink: 'See $1Qorai Rewards Terms of Service$2',
  tosUpdateRequiredText:
    'We’ve updated the Terms of Service for Qorai Rewards. We’ve made these updates to clarify our terms and ensure they cover new features. If you continue to use Qorai Rewards, you are agreeing to the updated Terms of Service. If you do not agree, you can $1reset$2 Qorai Rewards, which will disable the feature.',
  tosUpdateRequiredTitle: 'Updated Terms of Service',
  unconnectedAdsViewedText: "You've seen $1# Ads$2 this month",
  unsupportedRegionText1:
    'Unfortunately, it looks like you’re in a region where Qorai Rewards is not available.',
  unsupportedRegionText2: 'Don’t worry.',
  unsupportedRegionText3: 'You can still browse privately!',
  unsupportedRegionTitle: 'Sorry, Qorai Rewards is not available',
  viewStoreLink: 'View Store',
  wdpCheckboxLabel:
    'Yes, I’d also like to contribute to Qorai Search and opt in to $1Web Discovery Project$2.',
  wdpOptInText:
    'Contribute some anonymous search and browsing data to refine Qorai Search with Web Discovery Project. It’s completely open-source.',
  wdpOptInTitle: 'Web Discovery Project',
}
