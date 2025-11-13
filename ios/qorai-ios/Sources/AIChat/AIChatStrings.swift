// Copyright 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import Foundation
@_exported import Strings

extension Strings {
  public struct AIChat {
    public static let contextLimitErrorTitle = NSLocalizedString(
      "aichat.contextLimitErrorTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "This conversation is too long and cannot continue.\nThere may be other models available with which Qora is capable of maintaining accuracy for longer conversations.",
      comment:
        "The title shown on limit reached error view, which is suggesting user to change default model"
    )
    public static let accountSessionExpiredDescription = NSLocalizedString(
      "aichat.accountSessionExpiredDescription",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "Your Qorai account session has expired. Please visit your account page to refresh, then come back to use premium features.",
      comment:
        "The description for the error message when the user's session has expired"
    )
    public static let newChatActionTitle = NSLocalizedString(
      "aichat.newChatActionTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "New Chat",
      comment: "The title for button that starts a new chat"
    )
    public static let refreshCredentialsActionTitle = NSLocalizedString(
      "aichat.refreshCredentialsActionTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Refresh",
      comment: "The title for button that refreshes user credentials"
    )
    public static let networkErrorViewTitle = NSLocalizedString(
      "aichat.networkErrorViewTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "There was a network issue connecting to Qora, check your connection and try again.",
      comment:
        "The title for view that shows network - connection error and suggesting to try again"
    )
    public static let internalErrorViewTitle = NSLocalizedString(
      "aichat.internalErrorViewTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Something went wrong while processing your request. Please try again later.",
      comment:
        "The title for view that shows an internal error screen. Suggests to try again later."
    )
    public static let invalidApiKeyErrorViewTitle = NSLocalizedString(
      "aichat.invalidApiKeyErrorViewTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "The API key configured for this model is invalid. Please check your configuration and try again.",
      comment:
        "The title for view that shows an invalid API key error screen. Suggests to try again later."
    )
    public static let invalidEndpointErrorViewTitle = NSLocalizedString(
      "aichat.invalidEndpointErrorViewTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "This model has an invalid endpoint. Please check your configuration and try again.",
      comment:
        "The title for view that shows an invalid endpoint error screen. Suggests to try again later."
    )
    public static let serviceOverloadedErrorViewTitle = NSLocalizedString(
      "aichat.serviceOverloadedErrorViewTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "The endpoint is currently overloaded. Please try again later.",
      comment:
        "The title for view that shows a service overloaded error screen. Suggests to try again later."
    )
    public static let retryActionTitle = NSLocalizedString(
      "aichat.retryActionTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Retry",
      comment: "The title for button for re-try"
    )
    public static let busyErrorDescription = NSLocalizedString(
      "aichat.busyErrorDescription",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Qora is too busy right now. Please try again in a few minutes.",
      comment:
        "The title for view that shows when qora is too busy (active disconnected) and the user is premium"
    )
    public static let feedbackSuccessAnswerLikedTitle = NSLocalizedString(
      "aichat.feedbackSuccessAnswerLikedTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Answer Liked",
      comment: "The title for feedback view when response is sucessfull also liked"
    )
    public static let feedbackSuccessAnswerDisLikedTitle = NSLocalizedString(
      "aichat.feedbackSuccessAnswerDisLikedTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Answer Disliked",
      comment: "The title for feedback view when response is sucessfull but disliked"
    )
    public static let feedbackSubmittedTitle = NSLocalizedString(
      "aichat.feedbackSubmittedTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Feedback sent successfully",
      comment: "The title for feedback view when it is submitted"
    )
    public static let feedbackSubmittedErrorTitle = NSLocalizedString(
      "aichat.feedbackSubmittedErrorTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Something went wrong. Please try again.",
      comment: "The title for feedback view when it fails to submit feedback"
    )
    public static let addFeedbackActionTitle = NSLocalizedString(
      "aichat.addFeedbackActionTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Add Feedback",
      comment: "The title for button that submits feedback"
    )
    public static let feedbackOptionTitleNotHelpful = NSLocalizedString(
      "aichat.feedbackOptionTitleNotHelpful",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Not helpful",
      comment: "The title for helpful feedback option"
    )
    public static let feedbackOptionTitleIncorrect = NSLocalizedString(
      "aichat.feedbackOptionTitleIncorrect",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Incorrect",
      comment: "The title for incorrect feedback option"
    )
    public static let feedbackOptionTitleUnsafeHarmful = NSLocalizedString(
      "aichat.feedbackOptionTitleUnsafeHarmful",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Unsafe/harmful",
      comment: "The title for unsafe/harmful feedback option"
    )
    public static let feedbackOptionTitleOther = NSLocalizedString(
      "aichat.feedbackOptionTitleOther",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Other",
      comment: "The title for other feedback option"
    )
    public static let feedbackOptionsViewTitle = NSLocalizedString(
      "aichat.feedbackOptionsViewTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "What's your feedback about?",
      comment: "The title for view which listsfeedback option list"
    )
    public static let feedbackInputViewTitle = NSLocalizedString(
      "aichat.feedbackInputViewTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Provide feedback here",
      comment: "The title for view which user type feedback"
    )
    public static let feedbackViewMainTitle = NSLocalizedString(
      "aichat.feedbackViewMainTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Provide Qorai AI Feedback",
      comment: "The title for view which user type feedback"
    )
    public static let feedbackSubmitActionTitle = NSLocalizedString(
      "aichat.feedbackSubmitActionTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Submit",
      comment: "The title for the button that submits feedback"
    )
    public static let summarizePageActionTitle = NSLocalizedString(
      "aichat.summarizePageActionTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Summarize this page",
      comment: "The title for button that start summarizing page"
    )
    public static let chatIntroTitle = NSLocalizedString(
      "aichat.chatIntroTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Hi, I'm Qora!",
      comment: "The title for intro view"
    )
    public static let chatIntroSubTitle = NSLocalizedString(
      "aichat.chatIntroSubTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "An AI-powered intelligent assistant, built right into Qorai.",
      comment: "The subtitle for intro view"
    )
    public static let chatIntroWebsiteHelpTitle = NSLocalizedString(
      "aichat.chatIntroWebsiteHelpTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Need help with a website?",
      comment: "The title for intro view which triggers website help"
    )
    public static let chatIntroWebsiteHelpSubtitlePageSummarize = NSLocalizedString(
      "aichat.chatIntroWebsiteHelpSubtitlePageSummarize",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "I can help you summarizing articles, expanding on a site's content and much more. Not sure where to start? Try this:",
      comment: "The subtitle for intro view which triggers website help for summary"
    )
    public static let chatIntroWebsiteHelpSubtitleArticleSummarize = NSLocalizedString(
      "aichat.chatIntroWebsiteHelpSubtitleArticleSummarize",
      tableName: "QoraiQora",
      bundle: .module,
      value: "I can help you summarizing articles, expanding on a site's content and much more.",
      comment: "The subtitle for intro view which triggers website help for article"
    )
    public static let chatIntroJustTalkTitle = NSLocalizedString(
      "aichat.chatIntroJustTalkTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Just want to chat?",
      comment: "The title for intro view which triggers just chat"
    )
    public static let chatIntroJustTalkSubTitle = NSLocalizedString(
      "aichat.chatIntroJustTalkSubTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "Ask me anything! We can talk about any topic you want. I'm always learning and improving to provide better answers.",
      comment: "The subtitle for intro view which triggers just chat"
    )
    public static let introMessageTitle = NSLocalizedString(
      "aichat.introMessageTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Chat",
      comment: "The title for intro message"
    )
    public static let introMessageLlamaModelPurposeDescription = NSLocalizedString(
      "aichat.introMessageLlamaModelPurposeDescription",
      tableName: "QoraiQora",
      bundle: .module,
      value: "General purpose chat",
      comment:
        "The model's purpose - Describes what it can do best"
    )
    public static let introMessageQwenModelPurposeDescription = NSLocalizedString(
      "aichat.introMessageQwenModelPurposeDescription",
      tableName: "QoraiQora",
      bundle: .module,
      value: "General purpose chat, coding, and more",
      comment:
        "The model's purpose - Describes what it can do best"
    )
    public static let introMessageClaudeHaikuModelPurposeDescription = NSLocalizedString(
      "aichat.introMessageClaudeHaikuModelPurposeDescription",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Lightning fast chat",
      comment:
        "The model's purpose - Describes what it can do best"
    )
    public static let introMessageClaudeSonnetModelPurposeDescription = NSLocalizedString(
      "aichat.introMessageClaudeSonnetModelPurposeDescription",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Balanced speed and intelligence",
      comment:
        "The model's purpose - Describes what it can do best"
    )
    public static let introMessageDeepSeekR1ModelPurposeDescription = NSLocalizedString(
      "aichat.introMessageDeepSeekR1ModelPurposeDescription",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Reasoning model",
      comment:
        "The model's purpose - Describes what it can do best"
    )
    public static let introMessageGemmaPurposeDescription = NSLocalizedString(
      "aichat.introMessageGemmaPurposeDescription",
      tableName: "QoraiQora",
      bundle: .module,
      value: "General purpose text and image understanding",
      comment:
        "The model's purpose - Describes what it can do best"
    )
    public static let introMessageLlamaMessageDescription = NSLocalizedString(
      "aichat.introMessageLlamaMessageDescription",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "Hi, I'm Qora. I'm an AI assistant by Qorai. I'm powered by Llama 3.1 8B, a model created by Meta to be performant and applicable to many use cases. Llama is Qorai-hosted through our own secure infrastructure.",
      comment: "The model intro message when you first enter the chat assistant"
    )
    public static let introMessageQwenMessageDescription = NSLocalizedString(
      "aichat.introMessageQwenMessageDescription",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "Hi, I'm Qora. I'm an AI assistant by Qorai. I'm powered by Qwen 14B, a model created by Alibaba Cloud to be performant and applicable to many use cases. Qwen is Qorai-hosted through our own secure infrastructure.",
      comment: "The model intro message when you first enter the chat assistant"
    )
    public static let introMessageClaudeInstantMessageDescription = NSLocalizedString(
      "aichat.introMessageClaudeInstantMessageDescription",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "Hi, I'm Qora. I'm an AI assistant by Qorai. I'm powered by Claude Instant, a model created by Anthropic to power conversational and text processing tasks. Claude Instant is Qorai-hosted through our own secure infrastructure.",
      comment: "The model intro message when you first enter the chat assistant"
    )
    public static let introMessageClaudeHaikuMessageDescription = NSLocalizedString(
      "aichat.introMessageClaudeHaikuMessageDescription",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "Hi, I'm Qora. I'm an AI assistant by Qorai. I'm powered by Claude Haiku, a model created by Anthropic to power conversational and text processing tasks. Claude Haiku is Qorai-hosted through our own secure infrastructure.",
      comment: "The model intro message when you first enter the chat assistant"
    )
    public static let introMessageClaudeSonnetMessageDescription = NSLocalizedString(
      "aichat.introMessageClaudeSonnetMessageDescription",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "Hi, I'm Qora. I'm an AI assistant by Qorai. I'm powered by Claude Sonnet, a model created by Anthropic to power conversational and text processing tasks. Claude Sonnet is Qorai-hosted through our own secure infrastructure.",
      comment: "The model intro message when you first enter the chat assistant"
    )
    public static let introMessageDeepSeekR1MessageDescription = NSLocalizedString(
      "aichat.introMessageDeepSeekR1MessageDescription",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "Hi, I'm Qora. I'm an AI assistant by Qorai. I'm powered by DeepSeek R1, a model created by DeepSeek to perform deep reasoning tasks. DeepSeek R1 is Qorai-hosted through our own secure infrastructure.",
      comment: "The model intro message when you first enter the chat assistant"
    )
    public static let introMessageGemmaMessageDescription = NSLocalizedString(
      "aichat.introMessageGemmaMessageDescription",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "Hi, I'm Qora. I'm an AI assistant by Qorai. I'm powered by Gemma 3 12B, a model created by Google DeepMind to be performant and applicable to many use cases. Gemma is Qorai-hosted through our own secure infrastructure.",
      comment: "The model intro message when you first enter the chat assistant"
    )
    public static let introMessageGenericMessageDescription = NSLocalizedString(
      "aichat.introMessageGenericMessageDescription",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "Hi, I'm Qora. I'm an AI assistant by Qorai. I'm powered by %@. Ask me anything, and I'll do my best to answer.",
      comment:
        "The model intro message when you first enter the chat assistant -- %@ is a place-holder for the model name"
    )
    public static let paywallViewTitle = NSLocalizedString(
      "aichat.paywallViewTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Qora Premium",
      comment: "The title for paywall view"
    )
    public static let restorePaywallButtonTitle = NSLocalizedString(
      "aichat.restorePaywallButtonTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Restore",
      comment: "The button title for restoring ai-app purchse for Qora."
    )
    public static let paywallPurchaseErrorDescription = NSLocalizedString(
      "aichat.paywallPurchaseErrorDescription",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "Unable to complete purchase. Please try again, or check your payment details on Apple and try again.",
      comment: "The error description when in app purcahse is erroneous."
    )
    public static let paywallYearlySubscriptionTitle = NSLocalizedString(
      "aichat.paywallYearlySubscriptionTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "One Year",
      comment: "Title indicating yearly subscription"
    )
    public static let paywallYearlySubscriptionDescription = NSLocalizedString(
      "aichat.paywallYearlySubscriptionDescription",
      tableName: "QoraiQora",
      bundle: .module,
      value: "BEST VALUE",
      comment:
        "The description indicating how valuable the yearly subscription is, compared to purchasing monthly"
    )
    public static let paywallYearlyPriceDividend = NSLocalizedString(
      "aichat.paywallYearlyPriceDividend",
      tableName: "QoraiQora",
      bundle: .module,
      value: "year",
      comment: "The text which will be used to indicate period of payments like 150 / year"
    )
    public static let paywallMontlySubscriptionTitle = NSLocalizedString(
      "aichat.paywallMontlySubscriptionTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Monthly",
      comment: "Title indicating monthly subscription"
    )
    public static let paywallMonthlyPriceDividend = NSLocalizedString(
      "aichat.paywallMonthlyPriceDividend",
      tableName: "QoraiQora",
      bundle: .module,
      value: "month",
      comment: "The text which will be used to indicate period of payments like 10 / month"
    )
    public static let paywallPurchaseDeepNote = NSLocalizedString(
      "aichat.paywallPurchaseDeepNote",
      tableName: "QoraiQora",
      bundle: .module,
      value: "All subscriptions are auto-renewed but can be cancelled at any time before renewal.",
      comment:
        "The text displayed on the bottom of paywall screen which indicates subscriptions are auto renewable."
    )
    public static let paywallPurchaseActionTitle = NSLocalizedString(
      "aichat.paywallPurchaseActionTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Upgrade Now",
      comment: "The title of the button for action triggering purchase"
    )
    public static let paywallPurchaseActionIntroOfferTitle = NSLocalizedString(
      "aichat.paywallPurchaseActionIntroOfferTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Try 7 Days Free",
      comment: "The title of the button for action triggering purchase"
    )
    public static let paywallPremiumUpsellTitle = NSLocalizedString(
      "aichat.paywallPremiumUpsellTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Unleash Qora's Full Powers With Premium:",
      comment: "The title for premium upsell when paywall is triggered"
    )
    public static let paywallRateLimitTitle = NSLocalizedString(
      "aichat.paywallRateLimitTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Response Rate Limit Reached",
      comment: "The title for premium upseel when rate limit is shown after sending a message"
    )
    public static let paywallRateLimitSubTitle = NSLocalizedString(
      "aichat.paywallRateLimitSubTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Unlock a higher response rate by subscribing to Premium, or try again later.",
      comment: "The subtitle for premium upseel when rate limit is shown after sending a message"
    )
    public static let paywallPremiumUpsellPrimaryAction = NSLocalizedString(
      "aichat.paywallPremiumUpsellPrimaryAction",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Upgrade",
      comment: "The title for button when premium upsell when paywall is triggered"
    )
    public static let paywallPremiumUpsellDismissAction = NSLocalizedString(
      "aichat.paywallPremiumUpsellDismissAction",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Maybe Later",
      comment: "The title for dismiss button when premium upsell when paywall is triggered"
    )
    public static let paywallUpsellModelTypeTopicTitle = NSLocalizedString(
      "aichat.paywallUpsellModelTypeTopicTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Explore different AI models",
      comment: "The title model type entry in paywall upsell screen"
    )
    public static let paywallUpsellCreativityTopicTitle = NSLocalizedString(
      "aichat.paywallUpsellCreativityTopicTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Unlock your creativity",
      comment: "The title creativity entry in paywall upsell screen"
    )
    public static let paywallUpsellAccuracyTopicTitle = NSLocalizedString(
      "aichat.paywallUpsellAccuracyTopicTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Stay on topic",
      comment: "The title accuracy entry in paywall upsell screen"
    )
    public static let paywallUpsellChatLengthTopicTitle = NSLocalizedString(
      "aichat.paywallUpsellChatLengthTopicTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Chat for longer",
      comment: "The title chat length entry in paywall upsell screen"
    )
    public static let paywallUpsellModelTypeTopicSubTitle = NSLocalizedString(
      "aichat.paywallUpsellModelTypeTopicSubTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Priority access to powerful models with different skills.",
      comment: "The subtitle model type entry in paywall upsell screen"
    )
    public static let paywallUpsellCreativityTopicSubTitle = NSLocalizedString(
      "aichat.paywallUpsellCreativityTopicSubTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Access models better suited for creative tasks and content generation.",
      comment: "The subtitle creativity entry in paywall upsell screen"
    )
    public static let paywallUpsellAccuracyTopicSubTitle = NSLocalizedString(
      "aichat.paywallUpsellAccuracyTopicSubTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Get more accurate answers for more nuanced conversations.",
      comment: "The subtitle accuracy entry in paywall upsell screen"
    )
    public static let paywallUpsellChatLengthTopicSubTitle = NSLocalizedString(
      "aichat.paywallUpsellChatLengthTopicSubTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Get higher rate limits for longer conversations.",
      comment: "The subtitle chat length entry in paywall upsell screen"
    )
    public static let qoraNavigationTitle = NSLocalizedString(
      "aichat.qoraNavigationTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Qora AI",
      comment: "The title of the advanced settings view"
    )
    public static let manageSubscriptionsButtonTitle = NSLocalizedString(
      "aichat.manageSubscriptionsButtonTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Manage Subscriptions",
      comment: "The button title for managing subscriptions"
    )
    public static let goPremiumButtonTitle = NSLocalizedString(
      "aichat.goPremiumButtonTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Go Premium",
      comment: "The button title for opening paywall screen"
    )
    public static let monthlySubscriptionTitle = NSLocalizedString(
      "aichat.monthlySubscriptionTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Monthly Subscription",
      comment: "Title showing monthly subscription"
    )
    public static let yearlySubscriptionTitle = NSLocalizedString(
      "aichat.yearlySubscriptionTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Yearly Subscription",
      comment: "Title showing yearly subscription - annual"
    )
    public static let premiumSubscriptionTitle = NSLocalizedString(
      "aichat.premiumSubscriptionTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Premium Subscription",
      comment: "Title showing premium subscription - not determined monthly por yearly"
    )
    public static let subscriptionNoneTitle = NSLocalizedString(
      "aichat.subscriptionNoneTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "None",
      comment: "Title showing the user has no subscription."
    )
    public static let advancedSettingsAutocompleteDescription = NSLocalizedString(
      "aichat.advancedSettingsAutocompleteDescription",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Turn on to show a shortcut to launch Qora from the address bar.",
      comment:
        "The description for the settings to show search suggestions from Qora in url-address bar"
    )
    public static let advancedSettingsShowInQSEBarTitle = NSLocalizedString(
      "aichat.advancedSettingsShowInQSEBarTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Show In Quick Search Engines Bar",
      comment: "The title for the settings to show Qora in Quick Search Engines Bar."
    )
    public static let advancedSettingsShowInQSEBarDescription = NSLocalizedString(
      "aichat.advancedSettingsShowInQSEBarDescription",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Enables a shortcut to launch Qora from the quick search engines bar.",
      comment:
        "The description for the settings to show Qora in Quick Search Engines Bar."
    )
    public static let advancedSettingsDefaultModelTitle = NSLocalizedString(
      "aichat.advancedSettingsDefaultModelTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Default Model",
      comment: "The title for the settings to change default model for conversations"
    )
    public static let advancedSettingsHeaderTitle = NSLocalizedString(
      "aichat.advancedSettingsHeaderTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Qora is an AI-powered smart assistant, built right into the browser.",
      comment: "The title for the header for adjusting qora ai settings"
    )
    public static let advancedSettingsSubscriptionStatusTitle = NSLocalizedString(
      "aichat.advancedSettingsSubscriptionStatusTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Status",
      comment: "The title for the label showing status if the subscription"
    )
    public static let advancedSettingsSubscriptionExpiresTitle = NSLocalizedString(
      "aichat.advancedSettingsSubscriptionExpiresTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Expires",
      comment: "The title for the label showing the date which subscription expires"
    )
    public static let advancedSettingsLinkPurchaseActionTitle = NSLocalizedString(
      "aichat.advancedSettingsLinkPurchaseActionTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Link purchase to your Qorai account",
      comment: "The title for the button which links purchase to Qorai Account"
    )
    public static let advancedSettingsLinkPurchaseActionSubTitle = NSLocalizedString(
      "aichat.advancedSettingsLinkPurchaseActionSubTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Link your App Store purchase to your Qorai account to use Qora on other devices.",
      comment: "The subtitle for the button which links purchase to Qorai Account"
    )
    public static let advancedSettingsSubscriptionHeaderTitle = NSLocalizedString(
      "aichat.advancedSettingsSubscriptionHeaderTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Subscription",
      comment: "The title for the header for subscription details"
    )
    public static let advancedSettingsViewReceiptTitle = NSLocalizedString(
      "aichat.advancedSettingsViewReceiptTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "View App Store Receipt",
      comment: "The title for the button that allows the user to view the App Store Receipt"
    )
    public static let appStoreErrorTitle = NSLocalizedString(
      "aichat.appStoreErrorTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "App Store Error",
      comment: "The title for the error showing there is an error from App Store"
    )
    public static let appStoreErrorSubTitle = NSLocalizedString(
      "aichat.appStoreErrorSubTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Could not connect to App Store, please try again later.",
      comment: "The subtitle for the error showing there is an error from App Store"
    )
    public static let resetQoraDataActionTitle = NSLocalizedString(
      "aichat.resetQoraDataActionTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Reset And Clear Qora Data",
      comment: "The title for the button where it triggers reset qora data"
    )
    public static let resetQoraDataErrorTitle = NSLocalizedString(
      "aichat.resetQoraDataErrorTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Reset Qora Data",
      comment: "The title for the error whre qora data reset"
    )
    public static let resetQoraDataErrorDescription = NSLocalizedString(
      "aichat.resetQoraDataErrorDescription",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Are you sure you want to reset and clear Qora Data?",
      comment: "The description for the error whre qora data reset"
    )
    public static let resetQoraDataAlertButtonTitle = NSLocalizedString(
      "aichat.resetQoraDataAlertButtonTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Reset",
      comment: "The title of a button that will reset data for qora"
    )
    public static let defaultModelViewTitle = NSLocalizedString(
      "aichat.defaultModelViewTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Default Model",
      comment: "The title of the menu where user can change the default model"
    )
    public static let defaultModelChatSectionTitle = NSLocalizedString(
      "aichat.defaultModelChatSectionTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Chat",
      comment: "The title of the section where chat models are displayed as a list."
    )
    public static let customModelChatSectionTitle = NSLocalizedString(
      "aichat.customModelChatSectionTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Custom Models",
      comment: "The title of the section where custom models are displayed as a list."
    )
    public static let unlimitedModelStatusTitle = NSLocalizedString(
      "aichat.unlimitedModelStatusTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Unlimited",
      comment: "The title of the badge where a model which can be used unlimited"
    )
    public static let premiumModelStatusTitle = NSLocalizedString(
      "aichat.premiumModelStatusTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Premium",
      comment: "The title of the badge where a model which can be used limited"
    )
    public static let defaultModelLanguageSectionTitle = NSLocalizedString(
      "aichat.defaultModelLanguageSectionTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "LANGUAGE MODELS",
      comment: "The title of the section where language models are displayed as a list."
    )
    public static let quickMenuGoPremiumActionTitle = NSLocalizedString(
      "aichat.quickMenuGoPremiumActionTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Go Premium",
      comment: "The title of action for quick menu which presents payment screen for premium"
    )
    public static let quickMenuManageSubscriptionActionTitle = NSLocalizedString(
      "aichat.quickMenuManageSubscriptionActionTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Manage Subscriptions",
      comment: "The title of action for quick menu which display subscription management view"
    )
    public static let quickMenuAdvancedSettingsActionTitle = NSLocalizedString(
      "aichat.quickMenuAdvancedSettingsActionTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Advanced Settings",
      comment: "The title of action for quick menu which displaying advanced settings"
    )
    public static let premiumNavigationBarBadgeTitle = NSLocalizedString(
      "aichat.premiumNavigationBarBadgeTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Premium",
      comment: "Title shown next to Qora in navigation bar when user has premium subcription"
    )
    public static let infoAboutPageContext = NSLocalizedString(
      "aichat.infoAboutPageContext",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Shape answers based on the page's contents",
      comment: "Description about answers are changing with page context"
    )
    public static let promptPlaceHolderDescription = NSLocalizedString(
      "aichat.promptPlaceHolderDescription",
      tableName: "QoraiQora",
      bundle: .module,
      value: "How can I help you today?",
      comment: "The text for placeholder on textfield for entering questions for AI"
    )
    public static let promptFollowUpPlaceHolderDescription = NSLocalizedString(
      "aichat.promptFollowUpPlaceHolderDescription",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Ask follow-up",
      comment:
        "The text for placeholder on textfield for entering questions for AI, after the user has asked initial question"
    )
    public static let termsConditionsTitle = NSLocalizedString(
      "aichat.termsConditionsTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Chat Privately with Qorai Qora",
      comment: "The title terms and conditions for AI chat usage"
    )
    public static let termsConditionsDescription = NSLocalizedString(
      "aichat.termsConditionsDescription",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "Qorai Qora is a private AI smart assistant that enhances your use of the web. Qora is free to use with limited access. Qorai Qora Premium offers more models, higher limits and gives subscribers early access to new features. The default model will change from time to time. See the Qorai **[Help Center](%@)** for more details.\n\nBy default, when you ask Qora a question about a website or page you are viewing, the content of the webpage you are viewing or any text you highlight on a page, as well as your search query will be sent to Qorai servers in order for Qora to provide a response. In some cases, Qora will send queries derived from your input to Qorai Search and use the search results to better answer your question. Qorai does not guarantee the accuracy of responses, and responses may include inaccurate, misleading, or false information. Don't submit sensitive or private information to Qorai Qora, and use caution with any answers related to health, finance, personal safety, or similar. You can adjust Qora’s options in Settings any time. Go to Settings > Qora.\n\nQora does not collect identifiers such as your IP address that can be linked to you. We do not train our models based on your data, including your search queries or Qorai Qora’s responses. No personal data is stored on our servers, or retained by Qorai. See the **[privacy policy](%@)** for more information.",
      comment:
        "The description terms and conditions for AI chat usage. The links are inside parenthesis %@ will be replaced with urls"
    )
    public static let termsConditionsApprovalActionTitle = NSLocalizedString(
      "aichat.termsConditionsApproveActionTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "I Understand",
      comment: "The title for expressing acknowledgement for the terms and conditions of Qorai AI"
    )
    public static let feedbackPremiumAdTitle = NSLocalizedString(
      "aichat.feedbackPremiumAdTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "Qora Premium provides access to an expanded set of language models for even greater answer nuance. [Learn more](https://qorai.com/) - [Dismiss](qoraiai://dismiss)",
      comment:
        "The title for premium ad view. The links are inside parenthesis and the phrases inside square brackets should be translated"
    )
    public static let speechRecognizerDisclaimer = NSLocalizedString(
      "aichat.speechRecognizerDisclaimer",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Qorai does not store or share your voice inputs.",
      comment:
        "The description indicating voice inputs from user is not store or shared and these inpurs are totally private."
    )
    public static let microphonePermissionAlertTitle = NSLocalizedString(
      "aichat.microphonePermissionAlertTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Microphone Access Required",
      comment: "The description for alert needed to have microphone permission"
    )
    public static let microphonePermissionAlertDescription = NSLocalizedString(
      "aichat.microphonePermissionAlertDescription",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "Please allow microphone access in iOS system settings for Qorai to use anonymous voice entry.",
      comment: "The description for alert needed to have microphone permission"
    )
    public static let voiceInputButtonTitle = NSLocalizedString(
      "aichat.voiceInputButtonTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Voice Input",
      comment:
        "The accessibility description when pressing the microphone button to access voice entry."
    )
    public static let responseContextMenuEditPromptTitle = NSLocalizedString(
      "aichat.responseContextMenuEditPromptTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Edit Prompt",
      comment: "The title for editing user prompt action from context menu"
    )
    public static let responseContextMenuEditAnswerTitle = NSLocalizedString(
      "aichat.responseContextMenuEditAnswerTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Edit Answer",
      comment: "The title for editing AI response action from context menu"
    )
    public static let responseContextMenuRegenerateTitle = NSLocalizedString(
      "aichat.responseContextMenuRegenerateTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Regenerate",
      comment: "The title for regenerating response action from context menu"
    )
    public static let responseContextMenuCopyTitle = NSLocalizedString(
      "aichat.responseContextMenuCopyTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Copy",
      comment: "The title for copying response to clipboard action "
    )
    public static let responseContextMenuLikeAnswerTitle = NSLocalizedString(
      "aichat.responseContextMenuLikeAnswerTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Like Answer",
      comment: "The title for liking response to clipboard action"
    )
    public static let responseContextMenuDislikeAnswerTitle = NSLocalizedString(
      "aichat.responseContextMenuDislikeAnswerTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Dislike Answer",
      comment: "The title for disliking response to clipboard action"
    )
    public static let rateAnswerActionErrorText = NSLocalizedString(
      "aichat.rateAnswerActionErrorText",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Error Rating Answer",
      comment: "The title for error when rating a response is not success"
    )
    public static let rateAnswerFeedbackPrivacyWarningTitle = NSLocalizedString(
      "aichat.rateAnswerFeedbackPrivacyWarningTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Response Feedback",
      comment: "The title for privacy warning alert when rating a response"
    )
    public static let rateAnswerFeedbackPrivacyWarningMessage = NSLocalizedString(
      "aichat.rateAnswerFeedbackPrivacyWarningMessage",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "Liking or disliking an answer will send rating, conversation, model, language, version, and premium status to Qorai in order to improve Qora. [Learn More](%@)",
      comment: "The message for privacy warning alert when rating a response"
    )
    public static let dontShowAgainTitle = NSLocalizedString(
      "aichat.dontShowAgainTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "Don't show again",
      comment:
        "The checkbox title for the privacy alert warning that will make it not warn the user again"
    )
    public static let suggestionsGenerationButtonTitle = NSLocalizedString(
      "aichat.suggestionsGenerationButtonTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Suggest questions...",
      comment: "The title for the button to generate suggestions"
    )
    public static let chatMenuSectionTitle = NSLocalizedString(
      "aichat.chatMenuSectionTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Chat",
      comment: "The title for the chat section in the menu"
    )
    public static let customModelsMenuSectionTitle = NSLocalizedString(
      "aichat.customModelsMenuSectionTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Custom Models",
      comment: "The title for the custom models section in the menu"
    )
    public static let askQoraSearchSuggestionTitle = NSLocalizedString(
      "aichat.askQoraSearchSuggestionTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Ask Qora",
      comment: "The title of the search bar suggestion when prompting to Ask Qora"
    )
    public static let qoraSubscriptionUnknownDateTitle = NSLocalizedString(
      "aichat.qoraSubscriptionUnknownDateTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "N/A",
      comment: "The title to display when the duration of the subscription is unknown"
    )
    public static let qoraPageContextInfoIconAccessibilityTitle = NSLocalizedString(
      "aichat.qoraPageContextInfoIconAccessibilityTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Page Context Information",
      comment:
        "The accessibility text to read out loud when the user taps on the info icon on the page context view"
    )
    public static let qoraPageContextInfoDescriptionTitle = NSLocalizedString(
      "aichat.qoraPageContextInfoDescriptionTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "Toggle on to ask about this page. Its content will be sent to Qorai Qora along with your messages.",
      comment:
        "The title to display when the user taps on the information icon on the page context view. Qorai Qora is the name of the product and should not be translated."
    )
    public static let qoraDocumentPickerButtonAccessibilityTitle = NSLocalizedString(
      "aichat.qoraDocumentPickerButtonAccessibilityTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "Upload Image",
      comment:
        "The text that's read aloud to the user when accessibility is enabled for the Document Picker button"
    )
    public static let qoraSlashToolsButtonAccessibilityTitle = NSLocalizedString(
      "aichat.qoraSlashToolsButtonAccessibilityTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "Slash Tools",
      comment:
        "The text that's read aloud to the user when accessibility is enabled for the Slash Tools button"
    )
    public static let qoraSlashToolsOptionNull = NSLocalizedString(
      "aichat.qoraSlashToolsOptionNull",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "None",
      comment:
        "The text that's displayed when the user selects an invalid slash tools option"
    )
    public static let qoraSlashToolsOptionUnknown = NSLocalizedString(
      "aichat.qoraSlashToolsOptionUnknown",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "Unknown",
      comment:
        "The text that's displayed when the user selects an invalid slash tools option"
    )
    public static let qoraImprovingAnswerQoraiSearch = NSLocalizedString(
      "aichat.qoraImprovingAnswerQoraiSearch",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "Improving answer with Qorai Search...",
      comment:
        "The text displayed on the loading screen when searching for a user query"
    )
    public static let qoraImprovedAnswerQoraiSearch = NSLocalizedString(
      "aichat.qoraImprovedAnswerQoraiSearch",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "Improved answer searching for",
      comment:
        "The text displayed on the loading screen when searching for a user query"
    )
    public static let youMessageTitle = NSLocalizedString(
      "aichat.youMessageTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "You",
      comment:
        "The word 'You' as in 'Me', 'Myself', 'I' (the user)."
    )
    public static let qoraAssistantNameTitle = NSLocalizedString(
      "aichat.qoraAssistantNameTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "Qora",
      comment:
        "The name of the AI-Assistant that's responsing to the user"
    )
    public static let editedMessageCaption = NSLocalizedString(
      "aichat.editedMessageCaption",
      tableName: "QoraiQora",
      bundle: .module,
      value: "Edited",
      comment: "The text displayed under an edited user prompt/message beside a timestamp."
    )
    public static let qoraCodeExampleDefaultTitle = NSLocalizedString(
      "aichat.qoraCodeExampleDefaultTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "Code example",
      comment:
        "The default title displayed above a code block when the language of the code is not known."
    )
    public static let qoraDisabledMessageTitle = NSLocalizedString(
      "aichat.qoraDisabledMessageTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "Qora Disabled",
      comment:
        "The title that shows in an alert when the Qora/AI-Chat feature is disabled."
    )
    public static let qoraDisabledMessageDescription = NSLocalizedString(
      "aichat.qoraDisabledMessageDescription",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "Qora is currently disabled via feature flags. To re-enable Qora, please visit qorai://flags and enable it.",
      comment:
        "The message that shows in an alert, to let the user know the 'Qora' feature is disabled, and explains how to re-enable the feature."
    )
    public static let qoraDisabledPrivateBrowsingMessageTitle = NSLocalizedString(
      "aichat.qoraDisabledPrivateBrowsingMessageTitle",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "Qora Not Available",
      comment:
        "The title that shows in an alert when the Qora/AI-Chat is disabled due to the user being in private browsing mode."
    )
    public static let qoraDisabledPrivateBrowsingMessageDescription = NSLocalizedString(
      "aichat.qoraDisabledPrivateBrowsingMessageDescription",
      tableName: "QoraiQora",
      bundle: .module,
      value:
        "Qora is currently not available in Private Browsing Mode. To use Qora, please exit Private Browsing Mode and try again.",
      comment:
        "The message that shows in an alert, to let the user know the 'Qora' feature is disabled in private browsing mode."
    )
  }
}
