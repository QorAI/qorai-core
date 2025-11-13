// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.
import { provideStrings } from '../../../.storybook/locale'

provideStrings({
  // Entities
  qoraiWalletContract: 'Contract',
  qoraiWalletStaker: 'Staker',
  qoraiWalletWithdrawer: 'Withdrawer',

  // Search Text
  qoraiWalletSearchText: 'Search',

  // Side Nav Buttons
  qoraiWalletSideNavCrypto: 'Crypto',
  qoraiWalletSideNavRewards: 'Rewards',
  qoraiWalletSideNavCards: 'Cards',

  // Top Nav Tab Buttons
  qoraiWalletTopNavPortfolio: 'Portfolio',
  qoraiWalletTopTabPrices: 'Prices',
  qoraiWalletTopTabApps: 'Apps',
  qoraiWalletTopNavNFTS: 'NFTs',
  qoraiWalletTopNavAccounts: 'Accounts',
  qoraiWalletTopNavMarket: 'Market',

  // Chart Timeline Buttons
  qoraiWalletChartOneHour: '1 Hour',
  qoraiWalletChartOneDay: '1 Day',
  qoraiWalletChartOneWeek: '1 Week',
  qoraiWalletChartOneMonth: '1 Month',
  qoraiWalletChartThreeMonths: '3 Months',
  qoraiWalletChartOneYear: '1 Year',
  qoraiWalletChartAllTime: 'All time',
  qoraiWalletChartOneHourAbbr: '1H',
  qoraiWalletChartOneDayAbbr: '1D',
  qoraiWalletChartOneWeekAbbr: '1W',
  qoraiWalletChartOneMonthAbbr: '1M',
  qoraiWalletChartThreeMonthsAbbr: '3M',
  qoraiWalletChartOneYearAbbr: '1Y',
  qoraiWalletChartAllTimeAbbr: 'All',

  // Portfolio View
  qoraiWalletAddCoin: 'Add Coin',
  qoraiWalletBalance: 'Balance',
  qoraiWalletPortfolioAssetNetworkDescription: '$1 on $2',

  // Portfolio SubView
  qoraiWalletAccounts: 'Accounts',
  qoraiWalletSubviewAccount: 'Account',
  qoraiWalletOwner: 'Owner',
  qoraiWalletActivity: 'Activity',
  qoraiWalletTransactions: 'Transactions',
  qoraiWalletPrice: 'Price',
  qoraiWalletBack: 'Back',
  qoraiWalletAddAccount: 'Add Account',
  qoraiWalletPoweredByCoinGecko: 'Price data powered by CoinGecko',

  // Actions
  qoraiWalletClickToSwitch: 'Click to switch',
  qoraiWalletEnterYourPassword: 'Enter your password',
  qoraiWalletEnterAPasswordToContinue: 'Enter a password to continue',
  qoraiWalletEnterYourPasswordToStartBackup:
    'Enter your Qorai Wallet password to start backing up wallet.',

  // BuySendSwap
  qoraiWalletBuy: 'Buy',
  qoraiWalletSend: 'Send',
  qoraiWalletSwap: 'Swap',
  qoraiWalletBridge: 'Bridge',
  qoraiWalletReset: 'Reset',
  qoraiWalletSell: 'Sell',
  qoraiWalletNotEnoughBalance: 'You don’t have enough $1 in this account.',
  qoraiWalletSlippageToleranceWarning: 'Transaction may be frontrun',
  qoraiWalletExpiresInTitle: 'Expires in',
  qoraiWalletSendPlaceholder: 'Wallet address or URL',
  qoraiWalletSendNoURLPlaceholder: 'Wallet address',
  qoraiWalletSwapDisclaimer: 'Qorai uses $1$3$2 as a DEX aggregator.',
  qoraiWalletSwapDisclaimerDescription:
    '0x will process the Ethereum address and IP address '
    + 'to fulfill a transaction (including getting quotes). '
    + '0x will ONLY use this data for the purposes of processing transactions.',
  qoraiWalletJupiterSwapDisclaimerDescription:
    'Jupiter will process the Solana address and IP address '
    + 'to fulfill a transaction (including getting quotes). '
    + 'Jupiter will ONLY use this data '
    + 'for the purposes of processing transactions.',
  qoraiWalletSwapFeesNotice: 'Quote includes a $1 Qorai fee.',
  qoraiWalletDecimalPlacesError: 'Too many decimal places',
  qoraiWalletBuyTapBuyNotSupportedMessage:
    'Buy not supported for selected network',
  qoraiWalletSearchingForDomain: 'Searching for domain...',
  qoraiWalletEnsOffChainLookupTitle:
    'Qorai supports using off-chain gateways to resolve .eth domains.',
  qoraiWalletEnsOffChainLookupDescription:
    "It looks like you've entered an ENS address. "
    + "We'll need to use a third-party resolver to resolve this request, "
    + 'which may be able to see your IP address and domain.',
  qoraiWalletEnsOffChainButton: 'Use ENS domain',
  qoraiWalletFEVMAddressTranslationTitle:
    'ETH address will be converted to the Filecoin address.',
  qoraiWalletFEVMAddressTranslationDescription:
    "It looks like you've entered an ENS address. "
    + "We'll need to use a third-party resolver to resolve this request, "
    + 'which may be able to see your IP address and domain.',
  qoraiWalletFetchingQuote: 'Fetching quote',
  qoraiWalletReceiveEstimate: 'Receive (est.)',
  qoraiWalletFromToken: 'From token',
  qoraiWalletToToken: 'To token',
  qoraiWalletNewQuoteIn: 'New quote in $1',

  // Send Tab
  qoraiWalletChooseAssetToSend: 'Choose asset to send',
  qoraiWalletChooseAssetToSwap: 'Choose asset to swap',
  qoraiWalletEnterRecipientAddress: 'Enter recipient address',
  qoraiWalletNotEnoughFunds: 'Not enough funds',
  qoraiWalletSendHalf: 'HALF',
  qoraiWalletSendMax: 'MAX',
  qoraiWalletReviewSend: 'Review send',
  qoraiWalletNoAvailableTokens: 'No available tokens',
  qoraiWalletSearchTokens: 'Search by name or paste address',
  qoraiWalletSearchNFTs: 'Search NFT by name, id',
  qoraiWalletChooseAsset: 'Choose asset',
  qoraiWalletOrdinalsWarningMessage:
    'Qorai Wallet does not currently support Bitcoin NFTs (ordinals). Sending BTC from an address that has ordinals may result in its ordinals being transferred inadvertently.',
  qoraiWalletUserUnderstandsLabel: 'I understand',
  qoraiWalletChooseRecipient: 'Choose recipient',
  qoraiWalletMyAddresses: 'My addresses',
  qoraiWalletAddressOrDomainPlaceholder: 'Enter public address or domain.',
  qoraiWalletSendTo: 'Send to',
  qoraiWalletInvalidDomainExtension: 'Invalid domain extension.',
  qoraiWalletChooseAccount: 'Choose an account to continue',
  qoraiWalletMarketPrice: 'Market price',
  qoraiWalletOwned: 'Owned',
  qoraiWalletNotOwned: 'Not owned',
  qoraiWalletAmount24H: 'Amount/24h',

  // Bridge
  qoraiWalletChooseAssetToBridge: 'Choose asset to bridge',
  qoraiWalletEstTime: 'Est time',
  qoraiWalletExchangeRate: 'Exchange rate',
  qoraiWalletExchangeFor: '$1 for $2',
  qoraiWalletRecipient: 'Recipient',
  qoraiWalletReviewBridge: 'Review bridge',

  // Create Account Tab
  qoraiWalletCreateAccountDescription:
    'You don’t yet have a $1 account. Create one now?',
  qoraiWalletCreateAccountYes: 'Yes',
  qoraiWalletCreateAccountNo: 'No',

  // Buttons
  qoraiWalletButtonContinue: 'Continue',
  qoraiWalletContinueWithXItems: 'Continue with $1 $2',
  qoraiWalletButtonNext: 'Next',
  qoraiWalletButtonVerifyPhrase: 'Show my recovery phrase',
  qoraiWalletButtonCopy: 'Copy',
  qoraiWalletButtonCopied: 'Copied!',
  qoraiWalletButtonVerify: 'Verify',
  qoraiWalletButtonClose: 'Close',
  qoraiWalletButtonMore: 'More',
  qoraiWalletButtonDone: 'Done',
  qoraiWalletButtonSkip: 'Skip',
  qoraiWalletButtonCancel: 'Cancel',
  qoraiWalletButtonSaveChanges: 'Save changes',
  qoraiWalletLearnMore: 'Learn more',
  qoraiWalletButtonNoThanks: 'No thanks',
  qoraiWalletButtonEnable: 'Enable',
  qoraiWalletProceedButton: 'Proceed',
  qoraiWalletButtonRetry: 'Retry',

  // Onboarding - Welcome
  qoraiWalletWelcomeRestoreButton: 'Restore',
  qoraiWalletWelcomeTitle: 'Browser-native. Self-custody. And multi-chain.',
  qoraiWalletWelcomeDescription:
    'Take control of your crypto and NFTs. '
    + 'Qorai Wallet supports Ethereum, EVM chains, '
    + 'Solana, Filecoin, Bitcoin, and more.',
  qoraiWalletWelcomeNewWalletTitle: 'Need a new wallet?',
  qoraiWalletWelcomeNewWalletDescription:
    'Get started with Qorai Wallet in minutes.',
  qoraiWalletWelcomeImportWalletTitle: 'Already have a wallet?',
  qoraiWalletWelcomeImportWalletDescription: 'Import your existing wallet.',
  qoraiWalletWelcomeWatchOnlyTitle: 'I need a watch-only wallet',
  qoraiWalletCopyright:
    '©2025 Qorai Software Inc. Qorai and the Qorai logo are registered '
    + 'trademarks of Qorai Software, Inc. Other product names and logos may be '
    + 'trademarks of their respective companies. All rights reserved.',
  qoraiWalletWelcomeDividerText: 'or',

  // Onboarding - Disclosures
  qoraiWalletDisclosuresTitle: 'Before we begin',
  qoraiWalletDisclosuresDescription:
    'We require that you acknowledge the items below',
  qoraiWalletSelfCustodyDisclosureCheckboxText:
    'I understand that this is a self-custody wallet, '
    + 'and that I am solely responsible for any associated funds, assets, '
    + 'or accounts, and for taking any appropriate action to '
    + 'secure, protect, and back up my wallet. '
    + 'I understand that Qorai cannot access my wallet or '
    + 'reverse transactions on my behalf, '
    + 'and that my recovery phrase is the ONLY way to '
    + 'regain access in the event of a '
    + 'lost password, stolen device, or similar circumstance.',
  qoraiWalletTermsOfServiceCheckboxText:
    'I have read and agree to the $1Terms of use$1.',

  // Onboarding import or restore wallet page
  qoraiWalletCheckingInstalledExtensions: 'Checking for wallet extensions...',
  qoraiWalletImportOrRestoreWalletTitle: 'Connect to your existing wallet',
  qoraiWalletImportOrRestoreDescription:
    'To connect a wallet you already have, '
    + 'you may need to enter your recovery phrase. At this time we support '
    + 'restoring / importing from Ethereum and Solana wallets.',
  qoraiWalletRestoreMyQoraiWallet: 'Import an existing wallet',
  qoraiWalletRestoreMyQoraiWalletDescription: '12-24 words',
  qoraiWalletImportFromMetaMask: 'Import from MetaMask',
  qoraiWalletImportFromMetaMaskDescription:
    'Use your MetaMask password to import your seed phrase',
  qoraiWalletCreateWalletInsteadLink: 'Never mind, I’ll create a new wallet',
  qoraiWalletRestoreAlternateLength: 'I have a $1-word recovery phrase',
  qoraiWalletRestoreWalletError: 'Check your recovery phrase and try again.',
  qoraiWalletImportWithRecoveryPhrase: 'Import using your recovery phrase',
  qoraiWalletMetamaskDetected: 'Metamask wallet detected!',
  qoraiWalletUsePassword: 'Use password',
  qoraiWalletRecoveryPhraseWord: 'Word $1',

  // onboarding import wallet screen
  qoraiWalletImportPasswordError: 'Password is not correct',
  qoraiWalletMetaMaskPasswordInputPlaceholder: 'Type MetaMask password',
  qoraiWalletImportFromMetaMaskSeedInstructions:
    'Type your MetaMask 12-24 word recovery phrase.',
  qoraiWalletMetaMaskExtensionDetected: 'Import MetaMask wallet',

  qoraiWalletMetaMaskExtensionImportDescription:
    'You can easily import your MetaMask wallet just by inputting '
    + 'your password.',
  qoraiWalletRestoreMyQoraiWalletInstructions:
    'You can paste your entire recovery phrase into any field.',
  qoraiWalletRecoveryPhraseLengthError:
    'Recovery phrase must be 12, 15, 18, 21, or 24 words long',
  qoraiWalletInvalidMnemonicError:
    'The mnemonic being imported is not valid for Qorai Wallet',
  qoraiWalletImportWalletTypeTitle:
    'Which type of wallet would you like to import?',
  qoraiWalletImportWalletTypeHotWalletTitle: 'Ethereum/Solana/Filecoin wallet',
  qoraiWalletImportWalletTypeHotWalletDescription:
    'Import your seed phrase from an existing wallet',
  qoraiWalletImportWalletTypeHardwareWalletTitle: 'Hardware wallet',
  qoraiWalletImportWalletTypeHardwareWalletDescription:
    'Connect your hardware wallet with Qorai',

  // Onboarding - Backup Wallet - Intro
  qoraiWalletOnboardingRecoveryPhraseBackupIntroTitle:
    'Save your recovery phrase',
  qoraiWalletOnboardingRecoveryPhraseBackupIntroDescription:
    'Your recovery phrase is the key to access your wallet in case you '
    + 'forget your password or lose your device.',
  qoraiWalletRecoveryPhraseBackupWarningImportant:
    'Keep it in a secure place that is not accessible to others and avoid '
    + 'sharing it with anyone.',
  qoraiWalletRecoveryWordInstructions:
    'Enter the word in position $1 from your recovery phrase.',
  qoraiWalletVerifyRecoveryPhraseGoBack: 'Forgot to save? Go back',

  // Onboarding - Backup Wallet - Recovery Phrase Backup
  qoraiWalletRecoveryPhraseBackupTitle: 'Back up your wallet recovery phrase',
  qoraiWalletRecoveryPhraseBackupWarning:
    'Qorai cannot access your secret recovery phrase. '
    + 'Keep it safe, and never share it with anyone else.',
  qoraiWalletCopiedToClipboard: 'Copied to clipboard',
  qoraiWalletClickToSeeRecoveryPhrase: 'Click to see your phrase',
  qoraiWalletSkipBackupWarning:
    'You can skip this step now, but you still need to back up your recovery '
    + 'phrase to ensure account security.',
  qoraiWalletSkipBackup: 'I’ll back up later',
  qoraiWalletGoBack: 'Go back',

  // Onboarding - Backup Wallet - Verify Recovery Phrase
  qoraiWalletVerifyRecoveryPhraseTitle: "Let's check",
  qoraiWalletVerifyRecoveryPhraseInstructions:
    'Click the $1$7 ($8)$2, $3$9 ($10)$4, and $5$11 ($12)$6 words of '
    + 'your recovery phrase.',
  qoraiWalletVerifyPhraseError: "Recovery phrase didn't match",

  // Recovery Phrase Backup - Intro
  qoraiWalletBackupIntroTitle: 'Back up your crypto wallet',
  qoraiWalletBackupIntroTerms:
    'I understand that if I lose my recovery words, '
    + 'I will not be able to access my crypto wallet.',

  // Recovery Phrase Backup - Intro
  qoraiWalletRecoveryTitle: 'Your recovery phrase',
  qoraiWalletRecoveryDescription:
    'Write down or copy these words in the exact order shown below, '
    + 'and save them somewhere safe. Your recovery phrase is the only '
    + 'way to regain account access in case of forgotten password, '
    + 'lost or stolen device, or you want to switch wallets.',
  qoraiWalletRecoveryWarning1: 'WARNING:',
  qoraiWalletRecoveryWarning2: 'Never share your recovery phrase.',
  qoraiWalletRecoveryWarning3:
    'Anyone with this phrase can take your assets forever.',
  qoraiWalletRecoveryTerms: 'I have backed up my phrase somewhere safe.',

  // Recovery Phrase Backup - Verify Recovery Phrase
  qoraiWalletVerifyRecoveryTitle: 'Verify recovery phrase',
  qoraiWalletVerifyRecoveryDescription:
    'Select the words in your recovery phrase in their correct order.',
  qoraiWalletVerifyError: 'Recovery phrase did not match, please try again.',

  // Create Password
  qoraiWalletCreatePasswordTitle: 'Create a new password',
  qoraiWalletCreatePasswordDescription:
    "You'll use this password to access your wallet.",
  qoraiWalletCreatePasswordInput: 'Enter new password',
  qoraiWalletConfirmPasswordInput: 'Re-enter password',
  qoraiWalletCreatePasswordError: "Password criteria doesn't match.",
  qoraiWalletConfirmPasswordError: 'Passwords do not match',
  qoraiWalletPasswordMatch: 'Passwords match',
  qoraiWalletPasswordIsStrong: 'Strong!',
  qoraiWalletPasswordIsMediumStrength: 'Medium',
  qoraiWalletPasswordIsWeak: 'Weak',
  qoraiWalletAutoLockTitle: 'Qorai Wallet will auto-lock after',
  qoraiWalletAutoLockDurationMinutes: '$1 minutes',
  qoraiWalletAutoLockDurationHours: '$1 hour(s)',

  // Creating Wallet
  qoraiWalletCreatingWallet: 'Creating Wallet...',

  // Create Password - Strength Tooltip
  qoraiWalletPasswordStrengthTooltipHeading: 'Password should have:',
  qoraiWalletPasswordStrengthTooltipIsLongEnough: 'At least 8 characters',

  // Onboarding Success
  qoraiWalletOnboardingSuccessTitle: 'You’re all set!',
  qoraiWalletOnboardingSuccessDescription:
    'Your Qorai Wallet is now set up and ready for use.',
  qoraiWalletBuyCryptoButton: 'Buy crypto',
  qoraiWalletDepositCryptoButton: 'Deposit',
  qoraiWalletLearnAboutMyWallet: 'Learn more about my new wallet',
  qoraiWalletOnboardingSuccessGoToPortfolio: 'Go to portfolio',

  // Wallet Article Links
  qoraiWalletArticleLinkWhatsARecoveryPhrase: 'What’s a recovery phrase?',

  // Lock Screen
  qoraiWalletEnterYourQoraiWalletPassword: 'Enter your Qorai Wallet password',
  qoraiWalletLockScreenTitle: 'Enter password to unlock wallet',
  qoraiWalletLockScreenButton: 'Unlock',
  qoraiWalletLockScreenError: 'Incorrect password',
  qoraiWalletUnlockWallet: 'Unlock Wallet',
  qoraiWalletDoubleTapScreen: 'Double tap screen to continue',
  qoraiWalletUnlockAndroidDescription:
    'Your wallet is locked for your security. Unlock wallet to continue.',

  // Wallet More Popup
  qoraiWalletWalletPopupSettings: 'Settings',
  qoraiWalletWalletPopupLock: 'Lock wallet',
  qoraiWalletWalletPopupBackup: 'Backup Wallet',
  qoraiWalletWalletPopupConnectedSites: 'Connected sites',
  qoraiWalletWalletPopupHideBalances: 'Balances',
  qoraiWalletWalletPopupShowGraph: 'Graph',
  qoraiWalletWalletNFTsTab: 'NFTs tab',

  // Backup Warning
  qoraiWalletBackupWarningText:
    'Back up your wallet now '
    + 'to protect your assets and ensure you never lose access.',
  qoraiWalletBackupButton: 'Back up now',
  qoraiWalletDismissButton: 'Dismiss',

  // Default Wallet Banner
  qoraiWalletDefaultWalletBanner:
    'Qorai Wallet is not set as your default wallet and will not '
    + 'respond to Web3 DApps. Visit settings to change your default wallet.',

  // Restore Screen
  qoraiWalletRestoreTite: 'Restore primary crypto accounts',
  qoraiWalletRestoreDescription:
    'Enter your recovery phrase to restore your Qorai wallet crypto account.',
  qoraiWalletRestoreError: 'The recovery phrase entered is invalid.',
  qoraiWalletRestorePlaceholder: 'Paste recovery phrase from clipboard',
  qoraiWalletRestoreShowPhrase: 'Show recovery phrase',
  qoraiWalletRestoreLegacyCheckBox: 'Import from legacy Qorai crypto wallets?',
  qoraiWalletRestoreFormText: 'New Password',

  // Clipboard
  qoraiWalletToolTipCopyToClipboard: 'Copy to Clipboard',
  qoraiWalletToolTipCopiedToClipboard: 'Copied',
  qoraiWalletPasteFromClipboard: 'Paste from clipboard',
  qoraiWalletClickToCopy: 'Click to copy',

  // Accounts Tab
  qoraiWalletAccountsPrimary: 'Primary crypto accounts',
  qoraiWalletAccountsSecondary: 'Imported accounts',
  qoraiWalletConnectedHardwareWallets: 'Connected hardware wallets',
  qoraiWalletAccountsAssets: 'Assets',
  qoraiWalletAccountsEditVisibleAssets: 'Visible assets',
  qoraiWalletAccountBalance: 'Account balance',
  qoraiWalletViewAddressOn: 'View address on:',
  qoraiWalletNetworkExplorer: '$1 Explorer',

  // Add Account Options
  qoraiWalletCreateAccount: 'Create $1 account',
  qoraiWalletAddAccountCreate: 'Create',
  qoraiWalletAddAccountImport: 'Import',
  qoraiWalletAddAccountImportHardware: 'Import from hardware wallet',
  qoraiWalletAddAccountHardware: 'Hardware',
  qoraiWalletAddAccountConnect: 'Connect',
  qoraiWalletAddAccountPlaceholder: 'Name this account',
  qoraiWalletCreateAccountButton: 'Create account',
  qoraiWalletCreateAccountImportAccount: 'Import $1 account',
  qoraiWalletCreateAccountTitle: 'Select one of the following account types',
  qoraiWalletCreateAccountEthereumDescription:
    'Supports EVM compatible assets on the Ethereum blockchain '
    + '(ERC-20, ERC-721, ERC-1551, ERC-1155)',
  qoraiWalletCreateAccountSolanaDescription:
    'Supports SPL compatible assets on the Solana blockchain',
  qoraiWalletCreateAccountBitcoinDescription: 'Store BTC assets',
  qoraiWalletCreateAccountBitcoinTestnetDescription: 'Store BTC Testnet assets',
  qoraiWalletCreateAccountZCashDescription: 'Store ZEC assets',
  qoraiWalletCreateAccountZCashTestnetDescription: 'Store ZEC Testnet assets',
  qoraiWalletCreateAccountCardanoDescription: 'Store Cardano assets',
  qoraiWalletCreateAccountCardanoTestnetDescription:
    'Store Cardano Testnet assets',
  qoraiWalletCreateAccountFilecoinDescription: 'Store FIL asset',
  qoraiWalletCreateAccountFilecoinTestnetDescription: 'Store FIL Testnet asset',
  qoraiWalletCreateAccountPolkadotDescription:
    'Supports Substrate assets on Polkadot relay chain '
    + 'and Substrate parachains',
  qoraiWalletFilecoinPrivateKeyProtocol: 'Private key $1',
  qoraiWalletEnterPasswordIfApplicable: 'Enter password (if applicable)',
  qoraiWalletPrivateKeyImportType: 'Import type',
  qoraiWalletFilImportPrivateKeyFormatDescription:
    'NOTE: Private key must be provided as a hex-encoded JSON that contains '
    + 'private key and protocol information. $1Learn more$1.',
  qoraiWalletFilExportPrivateKeyFormatDescription:
    'NOTE: Private key is provided as a hex-encoded JSON that contains private '
    + 'key and protocol information. $1Learn more$1.',

  // Import Account
  qoraiWalletImportAccountDisclaimer:
    'These accounts can be used with Web3 DApps, and can be shown in your '
    + 'portfolio. However, note that secondary accounts cannot be restored '
    + 'via recovery phrase from your primary account backup.',
  qoraiWalletImportAccountPlaceholder: 'Paste private key from clipboard',
  qoraiWalletImportAccountKey: 'Private key',
  qoraiWalletImportAccountFile: 'JSON file',
  qoraiWalletImportAccountUploadButton: 'Choose file',
  qoraiWalletImportAccountUploadPlaceholder: 'No file chosen',
  qoraiWalletImportAccountError: 'Failed to import account, please try again.',
  qoraiWalletImportAccount: 'Import account',

  // Connect Hardware Wallet
  qoraiWalletConnectHardwareTitle: 'Select your hardware wallet device',
  qoraiWalletConnectHardwareInfo1:
    'Connect your $1 wallet directly to your computer.',
  qoraiWalletConnectHardwareInfo2: 'Unlock your device and select the $1 app.',
  qoraiWalletConnectHardwareTrezor: 'Trezor',
  qoraiWalletConnectHardwareLedger: 'Ledger',
  qoraiWalletConnectHardwareDeviceDescription:
    'Connect your $1 device to Qorai Wallet',
  qoraiWalletConnectHardwareAuthorizationNeeded:
    'Grant Qorai access to your $1 device.',
  qoraiWalletConnectingHardwareWallet: 'Connecting...',
  qoraiWalletAddCheckedAccountsHardwareWallet: 'Add checked accounts',
  qoraiWalletLoadMoreAccountsHardwareWallet: 'Load more',
  qoraiWalletLoadingMoreAccountsHardwareWallet: 'Loading more...',
  qoraiWalletSearchScannedAccounts: 'Search account',
  qoraiWalletHDPath: 'HD path',
  qoraiWalletSwitchHDPathTextHardwareWallet:
    'Try switching HD path (above) if you '
    + 'cannot find the account you are looking for.',
  qoraiWalletLedgerLiveDerivationPath: 'Ledger Live',
  qoraiWalletLedgerLegacyDerivationPath: 'Legacy (MEW/MyCrypto)',
  qoraiWalletUnknownInternalError:
    'Unknown error, please reconnect your hardware wallet and try again.',
  qoraiWalletConnectHardwareSearchNothingFound: 'No results found.',
  qoraiWalletAuthorizeHardwareWallet: 'Authorize your wallet',
  qoraiWalletConnectHardwareWallet: 'Connect hardware wallet',
  qoraiWalletConnectHardwareDescription:
    'We currently support $1 and $2 devices.',
  qoraiWalletImportHardwareWalletDescription:
    'Connect your hardware wallet to manage your assets directly '
    + 'from Qorai Wallet',
  qoraiWalletConnectHardwareWalletSelectBlockchain:
    'Select a blockchain to import your hardware wallet',

  // Account Settings Modal
  qoraiWalletAccountSettingsWatchlist: 'Visible assets',
  qoraiWalletAccountSettingsPrivateKey: 'Private key',
  qoraiWalletAccountSettingsSave: 'Save',
  qoraiWalletAccountSettingsRemove: 'Remove account',
  qoraiWalletWatchlistAddCustomAsset: 'Add custom asset',
  qoraiWalletWatchListTokenName: 'Token name',
  qoraiWalletWatchListTokenAddress: 'Token address',
  qoraiWalletWatchListTokenSymbol: 'Token symbol',
  qoraiWalletWatchListTokenDecimals: 'Decimals of precision',
  qoraiWalletWatchListAdd: 'Add',
  qoraiWalletWatchListDoneButton: 'Done',
  qoraiWalletWatchListNoAsset: 'No assets named',
  qoraiWalletWatchListSearchPlaceholder: 'Search assets or contract address',
  qoraiWalletWatchListError: 'Failed to add custom token, please try again.',
  qoraiWalletCustomTokenExistsError:
    'This token has already been added to your portfolio.',
  qoraiWalletAccountSettingsDisclaimer:
    'WARNING: Never share your private key. '
    + 'Anyone with this private key can take your assets forever.',
  qoraiWalletAccountSettingsShowKey: 'Show key',
  qoraiWalletAccountSettingsHideKey: 'Hide key',
  qoraiWalletAccountSettingsUpdateError:
    'Failed to update account name, please try again.',
  qoraiWalletWatchListTokenId: 'Token ID (only for ERC721)',
  qoraiWalletWatchListTokenIdError: 'Token ID is required',
  qoraiWalletWatchListAdvanced: 'Advanced',
  qoraiWalletWatchListCoingeckoId: 'Coingecko ID',
  qoraiWalletIconURL: 'Icon URL',
  qoraiWalletAddAsset: 'Add asset',
  qoraiWalletAccountsExport: 'Export',
  qoraiWalletAccountsDeposit: 'Deposit',
  qoraiWalletAccountsRemove: 'Remove',
  qoraiWalletAccountSettings: 'Account settings',
  qoraiWalletPasswordIsRequiredToTakeThisAction:
    'Password is required to take this action.',
  qoraiWalletAddToken: 'Add token',

  // Empty Token List State
  qoraiWalletNoAvailableAssets: 'No available assets',
  qoraiWalletNoAvailableAssetsDescription:
    "Deposit or purchase tokens to get started. If you don't see tokens "
    + 'from an imported account, check the filters and display settings. '
    + 'Unknown tokens may need to be added as custom assets.',

  // AmountPresets
  qoraiWalletPreset25: '25%',
  qoraiWalletPreset50: '50%',
  qoraiWalletPreset75: '75%',
  qoraiWalletPreset100: '100%',

  // Ordinals
  qoraiWalletOrdinalFirst: 'First',
  qoraiWalletOrdinalSecond: 'Second',
  qoraiWalletOrdinalThird: 'Third',
  qoraiWalletOrdinalFourth: 'Fourth',
  qoraiWalletOrdinalFifth: 'Fifth',
  qoraiWalletOrdinalSixth: 'Sixth',
  qoraiWalletOrdinalSeventh: 'Seventh',
  qoraiWalletOrdinalEighth: 'Eighth',
  qoraiWalletOrdinalNinth: 'Ninth',
  qoraiWalletOrdinalTenth: 'Tenth',
  qoraiWalletOrdinalEleventh: 'Eleventh',
  qoraiWalletOrdinalTwelfth: 'Twelfth',
  qoraiWalletOrdinalThirteenth: 'Thirteenth',
  qoraiWalletOrdinalFourteenth: 'Fourteenth',
  qoraiWalletOrdinalFifteenth: 'Fifteenth',
  qoraiWalletOrdinalSixteenth: 'Sixteenth',
  qoraiWalletOrdinalSeventeenth: 'Seventeenth',
  qoraiWalletOrdinalEighteenth: 'Eighteenth',
  qoraiWalletOrdinalNineteenth: 'Nineteenth',
  qoraiWalletOrdinalTwentieth: 'Twentieth',
  qoraiWalletOrdinalTwentyFirst: 'Twenty-first',
  qoraiWalletOrdinalTwentySecond: 'Twenty-second',
  qoraiWalletOrdinalTwentyThird: 'Twenty-third',
  qoraiWalletOrdinalTwentyFourth: 'Twenty-fourth',
  qoraiWalletOrdinalSuffixOne: 'st',
  qoraiWalletOrdinalSuffixTwo: 'nd',
  qoraiWalletOrdinalSuffixFew: 'rd',
  qoraiWalletOrdinalSuffixOther: 'th',

  // Networks
  qoraiWalletNetworkETH: 'Ethereum',
  qoraiWalletNetworkMain: 'Mainnet',
  qoraiWalletNetworkTest: 'Test Network',
  qoraiWalletNetworkLocalhost: 'Localhost',
  qoraiWalletAddNetworksAnytimeInSettings:
    'You can add networks anytime in Settings.',
  qoraiWalletSupportedNetworks: 'Supported networks',
  qoraiWalletChooseChainsToUse:
    'Choose which blockchains to use in your wallet.',
  qoraiWalletShowTestnets: 'Show testnets',
  qoraiWalletSeeAvailableNetworks: 'See available networks',

  // Grouping Labels
  qoraiWalletFeatured: 'Featured',
  qoraiWalletPopular: 'Popular',

  // Select Screens
  qoraiWalletSelectAccount: 'Select account',
  qoraiWalletSearchAccount: 'Search accounts',
  qoraiWalletSelectNetwork: 'Select network',
  qoraiWalletSelectAsset: 'Select asset',
  qoraiWalletSearchAsset: 'Search coins',
  qoraiWalletSelectCurrency: 'Select currency',
  qoraiWalletSearchCurrency: 'Search currencies',

  // Swap
  qoraiWalletSwapFrom: 'Amount',
  qoraiWalletSwapTo: 'To',
  qoraiWalletSwapEstimate: 'estimate',
  qoraiWalletSwapMarket: 'Market',
  qoraiWalletSwapLimit: 'Limit',
  qoraiWalletSwapPriceIn: 'Price in',
  qoraiSwapInsufficientBalance: 'Insufficient balance',
  qoraiWalletSwapInsufficientFundsForGas: 'Insufficient funds for gas',
  qoraiSwapApproveToken: 'Approve $1',
  qoraiSwapInsufficientLiquidity: 'Insufficient liquidity',
  qoraiWalletSwapInsufficientAllowance: 'Activate token',
  qoraiWalletSwapUnknownError: 'Unknown error',
  qoraiWalletSwapReviewSpend: 'You spend',
  qoraiWalletSwapReviewReceive: "You'll receive",
  qoraiWalletSwapReviewHeader: 'Confirm order',
  qoraiWalletSolanaSwap: 'Solana Swap',
  qoraiWalletNoRoutesFound: 'No routes found',
  qoraiWalletReviewSwap: 'Review swap',
  qoraiWalletChooseQuoteProvider: 'Choose quote provider',
  qoraiWalletQuoteProviderInfo:
    'Each aggregator provides quotes by using liquidity from its API. '
    + 'They gather price information from various exchanges and offer the '
    + 'prices based on this data.',
  qoraiWalletNotAvailable: 'Not available',
  qoraiWalletUpdate: 'Update',
  qoraiWalletProviderNotSupported: 'This pair is not supported by $1',
  qoraiWalletChangeProvider: 'Change provider',
  qoraiWalletRoute: 'Route',
  qoraiWalletMaxSlippage: 'Max slippage',
  qoraiWalletMaxSlippageDescription:
    'When the deviation between the price of the transaction you '
    + 'submitted and the price at the time of the transaction on chain is '
    + 'greater than this set value, the transaction will fail.',
  qoraiWalletPriceImpactDescription:
    'Price impact is how much your trade might move the market price. '
    + 'Some tokens with low liquidity are more sensitive to trades, so even '
    + 'smaller trades can shift the price a lot.',
  qoraiWalletSuggestedValues: 'Suggested Values:',
  qoraiWalletMainstreamAssetPairs: 'Mainstream Asset Pairs: $1%',
  qoraiWalletStablecoinPairs: 'Stablecoin Pairs: $1%',
  qoraiWalletOthers: 'Others: $1%',
  qoraiWalletSuggested: 'Suggested',
  qoraiWalletCustom: 'Custom',
  qoraiWalletCheapest: 'Cheapest',
  qoraiWalletFastest: 'Fastest',
  qoraiWalletOnNetwork: 'on $1',
  qoraiWalletRoutes: 'Routes',
  qoraiWalletSwapOnNetworkViaExchange: 'Swap on $1 via $2',
  qoraiWalletBridgeFromNetworkToNetwork: 'Bridge from $1 to $2',
  qoraiWalletExchangeNamePlusSteps: '$1 + $2 $3',
  qoraiWalletExchangeViaProvider: '$1 via $2',
  qoraiWalletSortBy: 'Sort by',
  qoraiWalletConfirmSwap: 'Confirm swap',
  qoraiWalletConfirmBridge: 'Confirm bridge',
  qoraiWalletConfirmSend: 'Confirm send',
  qoraiWalletConfirmShield: 'Confirm shield',
  qoraiWalletSpend: 'Spend',

  // Buy
  qoraiWalletBuyTitle: 'Test faucet',
  qoraiWalletBuyDescription: 'Get Ether from a faucet for $1',
  qoraiWalletBuyFaucetButton: 'Get Ether',
  qoraiWalletBuyContinueButton: 'Select purchase method',
  qoraiWalletBuySelectAsset: 'Select an asset',
  qoraiWalletBuyRampNetworkName: 'Ramp.Network',
  qoraiWalletBuyTransakName: 'Transak',
  qoraiWalletBuyStripeName: 'Link by Stripe',
  qoraiWalletBuyCoinbaseName: 'Coinbase Pay',
  qoraiWalletBuyRampDescription:
    'Buy with CC/Debit or ACH. ' + 'Competitive Rates.',
  qoraiWalletBuyTransakDescription:
    'Instant buy with your bank account. Lower fees.',
  qoraiWalletBuyStripeDescription: 'Pay with credit, debit, bank account',
  qoraiWalletBuyCoinbaseDescription:
    'Buy with the most trusted name in crypto.',
  qoraiWalletBuyWithRamp: 'Buy with Ramp',
  qoraiWalletBuyWithTransak: 'Buy with Transak',
  qoraiWalletBuyWithStripe: 'Buy with Link',
  qoraiWalletBuyWithCoinbase: 'Buy with Coinbase Pay',
  qoraiWalletSellWithProvider: 'Sell with $1',
  qoraiWalletBuyDisclaimer:
    'Financial and transaction data is processed by our onramp partners. '
    + 'Qorai does not collect or have access to such data.',
  qoraiWalletTransactionsPartner: 'Transactions partner',
  qoraiWalletTransactionPartnerConsent:
    'Qorai Wallet uses Meld.io to help aggregate and surface various '
    + 'crypto providers for your region. We will share information with '
    + 'Meld.io to complete the transaction, including your wallet address '
    + 'and country code. For more information please read Meld’s terms of use.',
  qoraiWalletMeldTermsOfUse:
    'I have read and agree to the $1Meld’s Terms of use$1',
  qoraiWalletBestOption: 'Best Option',
  qoraiWalletExchangeRateWithFees: 'Exchange rate with fees',
  qoraiWalletFees: 'Fees',
  qoraiWalletPriceCurrency: 'Price $1',
  qoraiWalletBuyWithProvider: 'Buy with $1',
  qoraiWalletAsset: 'Asset',
  qoraiWalletSelected: 'Selected',
  qoraiWalletNoAvailableCurrencies: 'No available currencies',
  qoraiWalletGettingBestPrices: 'Getting best prices...',
  qoraiWalletBuyAsset: 'Buy $1',
  qoraiWalletNoProviderFound: 'No providers found for $1',
  qoraiWalletTrySearchingForDifferentAsset:
    'Try searching for a different asset.',
  qoraiWalletNoResultsFound: 'No results found for $1',
  qoraiWalletTryDifferentKeywords:
    'Try using a different keyword or check your spelling.',
  qoraiWalletCreateAccountToBuyTitle: 'Do you want to create a $1 Account?',
  qoraiWalletCreateAccountToBuyDescription:
    'In order to receive $1 you will need a $2 account.',
  qoraiWalletAccountName: 'Account name',

  // Fund Wallet Screen
  qoraiWalletFundWalletTitle:
    'To finish your $1 purchase, select one of our partners',
  qoraiWalletFundWalletDescription:
    'On completion, your funds will be transferred to your Qorai Wallet',

  // Deposit Funds Screen
  qoraiWalletDepositFundsTitle: 'Deposit crypto',
  qoraiWalletDepositX: 'Deposit $1',
  qoraiWalletDepositSolSplTokens: 'Deposit Solana or SPL tokens',
  qoraiWalletDepositErc: 'Deposit ERC-based tokens',
  qoraiWalletDepositOnlySendOnXNetwork:
    'Only send tokens to this address on $1',

  // Sign Transaction Panel
  qoraiWalletSignTransactionTitle: 'Your signature is being requested',
  qoraiWalletSignWarning:
    'Note that Qorai can’t verify what will happen if you sign. '
    + 'A signature could authorize nearly any operation in your account or '
    + 'on your behalf, including (but not limited to) giving total control '
    + 'of your account and crypto assets to the site making the request. '
    + 'Only sign if you’re sure you want to take this action, '
    + 'and trust the requesting site.',
  qoraiWalletSignWarningTitle: 'Sign at your own risk',
  qoraiWalletSignTransactionMessageTitle: 'Message',
  qoraiWalletSignTransactionEIP712MessageHideDetails: 'Hide details',
  qoraiWalletSignTransactionEIP712MessageDomain: 'Domain',
  qoraiWalletSignTransactionButton: 'Sign',
  qoraiWalletApproveTransaction: 'Approve transaction',
  qoraiWalletRiskOfLossAction: 'Unsafe action with risk of loss',
  qoraiWalletUntrustedRequestWarning:
    'This request appears malicious, '
    + 'and may leave you vulnerable to theft. '
    + 'Do not continue unless you trust the app.',

  // Sign in with Ethereum
  qoraiWalletSignInWithQoraiWallet: 'Sign in with Qorai Wallet',
  qoraiWalletSignInWithQoraiWalletMessage:
    'You are signing into $1. '
    + 'Qorai Wallet will share your wallet address with $1.',
  qoraiWalletSeeDetails: 'See details',
  qoraiWalletSignIn: 'Sign in',
  qoraiWalletOrigin: 'Origin',
  qoraiWalletAddress: 'Address',
  qoraiWalletStatement: 'Statement',
  qoraiWalletUri: 'URI',
  qoraiWalletVersion: 'Version',
  qoraiWalletNonce: 'Nonce',
  qoraiWalletIssuedAt: 'Issued at',
  qoraiWalletExpirationTime: 'Expiration time',
  qoraiWalletNotBefore: 'Not before',
  qoraiWalletRequestId: 'Request ID',
  qoraiWalletResources: 'Resources',
  qoraiWalletSecurityRiskDetected: 'Security risk detected',

  // Transaction Details Labels
  qoraiWalletInput: 'Input',
  qoraiWalletOutput: 'Output',
  qoraiWalletInputs: 'Inputs',
  qoraiWalletOutputs: 'Outputs',
  qoraiWalletValue: 'Value',

  // Encryption Key Panel
  qoraiWalletProvideEncryptionKeyTitle:
    'A DApp is requesting your public encryption key',
  qoraiWalletProvideEncryptionKeyDescription:
    '$1 is requesting your wallets public encryption key. '
    + 'If you consent to providing this key, the site will be able to '
    + 'compose encrypted messages to you.',
  qoraiWalletProvideEncryptionKeyButton: 'Provide',
  qoraiWalletReadEncryptedMessageTitle:
    'This DApp would like to read this message to complete your request',
  qoraiWalletReadEncryptedMessageDecryptButton: 'Decrypt message',
  qoraiWalletReadEncryptedMessageButton: 'Allow',

  // Allow Spend ERC20 Panel
  qoraiWalletAllowSpendTitle: 'Allow this app to spend your $1?',
  qoraiWalletAllowSpendDescription:
    'By granting this permission, you are allowing this app to withdraw '
    + 'your $1 and automate transactions for you.',
  qoraiWalletAllowSpendBoxTitle: 'Edit permissions',
  qoraiWalletAllowSpendTransactionFee: 'Transaction fee',
  qoraiWalletAllowSpendEditButton: 'Edit',
  qoraiWalletAllowSpendDetailsButton: 'View details',
  qoraiWalletAllowSpendRejectButton: 'Reject',
  qoraiWalletAllowSpendConfirmButton: 'Confirm',
  qoraiWalletAllowSpendUnlimitedWarningTitle: 'Unlimited approval requested',
  qoraiWalletSpendLimit: 'Spend limit',
  qoraiWalletApprovalTarget: 'Approval target',
  qoraiWalletCurrentApprovalLimit: 'Current approval limit',
  qoraiWalletProposedApprovalLimit: 'Proposed approval limit',

  // Allow Add or Change Network Panel
  qoraiWalletAllowAddNetworkTitle: 'Allow this site to add a network?',
  qoraiWalletAllowAddNetworkDescription:
    'This will allow this network to be used within Qorai Wallet.',
  qoraiWalletAllowAddNetworkLearnMoreButton: 'Learn more.',
  qoraiWalletAllowAddNetworkName: 'Network name',
  qoraiWalletAllowAddNetworkUrl: 'Network URL',
  qoraiWalletAllowAddNetworkDetailsButton: 'View all details',
  qoraiWalletAllowAddNetworkButton: 'Approve',
  qoraiWalletChainId: 'Chain ID',
  qoraiWalletAllowAddNetworkCurrencySymbol: 'Currency symbol',
  qoraiWalletAllowAddNetworkExplorer: 'Block explorer URL',
  qoraiWalletAllowChangeNetworkTitle: 'Allow this site to switch networks?',
  qoraiWalletAllowChangeNetworkDescription:
    'This will switch the network to a previously added network.',
  qoraiWalletAllowChangeNetworkButton: 'Switch network',
  qoraiWalletAllowAddNetworkNetworkPanelTitle: 'Network',
  qoraiWalletAddNetwork: 'Add network',

  // Confirm Transaction Panel
  qoraiWalletConfirmTransactionTotal: 'Total',
  qoraiWalletConfirmTransactionGasFee: 'Gas fee',
  qoraiWalletConfirmTransactionTransactionFee: 'Transaction fee',
  qoraiWalletConfirmTransactionBid: 'Bid',
  qoraiWalletConfirmTransactionAmountGas: 'Amount + gas',
  qoraiWalletConfirmTransactionAmountFee: 'Amount + Network fee',
  qoraiWalletConfirmTransactionNoData: 'No data.',
  qoraiWalletConfirmTransactionNext: 'next',
  qoraiWalletConfirmTransactionFirst: 'first',
  qoraiWalletConfirmTransactions: 'transactions',
  qoraiWalletConfirmTransactionAccountCreationFee:
    'The associated token account does not exist yet. '
    + 'A small amount of SOL will be spent to create and fund it.',
  qoraiWalletAllowSpendCurrentAllowance: 'Current allowance',
  qoraiWalletAllowSpendProposedAllowance: 'Proposed allowance',
  qoraiWalletTransactionGasLimit: 'Gas Limit',
  qoraiWalletTransactionGasPremium: 'Gas Premium',
  qoraiWalletTransactionGasFeeCap: 'Gas Fee Cap',
  qoraiWalletNetworkFees: 'Network fees',
  qoraiWalletNetworkFee: 'Network fee',
  qoraiWalletCustomFeeAmount: 'Custom fee amount',
  qoraiWalletTransactionMayIncludeAccountCreationFee:
    'This transaction may include an account creation fee',
  qoraiWalletSystemProgramAssignWarningTitle:
    'Account ownership change requested',
  qoraiWalletSystemProgramAssignWarningDescription:
    'This transaction will reassign ownership of the account to a new '
    + 'program. This action is irreversible and may result in loss of funds.',
  qoraiSwapSlow: 'Slow',
  qoraiSwapAverage: 'Average',
  qoraiSwapFast: 'Fast',
  qoraiWalletEstimatedFee: 'Estimated fee',

  // Wallet Main Panel
  qoraiWalletPanelTitle: 'Qorai Wallet',
  qoraiWalletPanelConnected: 'Connected',
  qoraiWalletPanelBlocked: 'Blocked',
  qoraiWalletTitle: 'Wallet',

  // Wallet Welcome Panel
  qoraiWalletWelcomePanelDescription:
    'Use this panel to securely access Web3 and all your crypto assets.',

  // Site Permissions Panel
  qoraiWalletSitePermissionsAccounts: '$1 accounts connected',
  qoraiWalletSitePermissionsDisconnect: 'Disconnect',
  qoraiWalletSitePermissionsSwitch: 'Switch',
  qoraiWalletSitePermissionsNewAccount: 'New account',
  qoraiWalletSitePermissionsTrust: 'Trust',
  qoraiWalletSitePermissionsRevoke: 'Revoke',

  // DApp Connection Panel
  qoraiWalletChangeNetwork: 'Change network',
  qoraiWalletChangeAccount: 'Change account',
  qoraiWalletActive: 'Active',
  qoraiWalletNotConnected: 'Not connected',
  qoraiWalletConnectedAccounts: 'Connected accounts',
  qoraiWalletAvailableAccounts: 'Available accounts',
  qoraiWalletConnections: 'Connections',
  qoraiWalletUnblock: 'Unblock',

  // Transaction Detail Box
  qoraiWalletTransactionDetailBoxFunction: 'FUNCTION TYPE',
  qoraiWalletTransactionDetailBoxHex: 'HEX DATA',
  qoraiWalletTransactionDetailBoxBytes: 'BYTES',

  // Connect With Site Panel
  qoraiWalletConnectWithSiteNext: 'Next',
  qoraiWalletConnectWallet: 'Connect wallet',
  qoraiWalletConnectWithSite: 'or connect with:',
  qoraiWalletConnectPermittedLabel: 'This app will be able to:',
  qoraiWalletConnectNotPermittedLabel: 'It will not be able to:',
  qoraiWalletConnectPermissionBalanceAndActivity:
    'Check wallet balance and activity',
  qoraiWalletConnectPermissionRequestApproval:
    'Request approval for transactions and signatures',
  qoraiWalletConnectPermissionAddress: 'View your permitted wallet address',
  qoraiWalletConnectPermissionMoveFunds: 'Move funds without your permission',
  qoraiWalletConnectTrustWarning: 'Make sure you trust this site.',

  // Permission Duration
  qoraiWalletPermissionDuration: 'Permission duration',
  qoraiWalletPermissionUntilClose: 'Until I close this site',
  qoraiWalletPermissionOneDay: 'For 24 hours',
  qoraiWalletPermissionOneWeek: 'For 1 week',
  qoraiWalletPermissionForever: 'Forever',

  // Connect Hardware Wallet Panel
  qoraiWalletConnectHardwarePanelConnected: '$1 connected',
  qoraiWalletConnectHardwarePanelDisconnected: '$1 disconnected',
  qoraiWalletConnectHardwarePanelInstructions: 'Instructions',
  qoraiWalletConnectHardwarePanelConnect: 'Connect your $1',
  qoraiWalletConnectHardwarePanelConfirmation:
    'Hardware wallet requires transaction confirmation on device.',
  qoraiWalletConnectHardwarePanelOpenApp:
    'Hardware wallet requires $1 App opened on $2',

  // Transaction History Panel (Empty)
  qoraiWalletNoTransactionsYet: 'No transaction history',
  qoraiWalletNoTransactionsYetDescription:
    'Transactions made with your Qorai Wallet will appear here.',

  // Transaction List Item
  qoraiWalletTransactionSent: 'sent',
  qoraiWalletTransactionReceived: 'received',
  qoraiWalletTransactionExplorerMissing:
    'Block explorer URL' + ' is not available.',
  qoraiWalletTransactionExplorer: 'View on block explorer',
  qoraiWalletTransactionCopyHash: 'Copy transaction hash',
  qoraiWalletTransactionSpeedup: 'Speedup',
  qoraiWalletTransactionCancel: 'Cancel transaction',
  qoraiWalletTransactionRetry: 'Retry transaction',
  qoraiWalletTransactionPlaceholder: 'Transactions will appear here',
  qoraiWalletTransactionApproveUnlimited: 'Unlimited',
  qoraiWalletApprovalTransactionIntent: 'approve',

  // Transaction Type Names
  qoraiWalletTransactionTypeNameErc20Approve: 'Approve',
  qoraiWalletTransactionTypeNameSafeTransferFrom: 'Safe Transfer',
  qoraiWalletTransactionTypeNameTokenTransfer: 'Token transfer',
  qoraiWalletTransactionTypeNameNftTransfer: 'Transfer NFT',
  qoraiWalletTransactionTypeNameForwardFil: 'Forward FIL',
  qoraiWalletTransactionTypeNameOther: 'Other',
  qoraiWalletTransactionTypeNameCompressedNftTransfer:
    'Compressed NFT Transfer',
  qoraiWalletTransactionTypeNameSignAndSendDappTransaction:
    'Sign and Send DApp transaction',
  qoraiWalletTransactionTypeNameSignDappTransaction: 'Sign DApp Transaction',
  ['qoraiWalletTransactionTypeNameSplTokenTransfer'
  + 'WithAssociatedTokenAccountCreation']:
    'SPL Token Transfer With Associated Token Account Creation',

  // Transaction Simulation
  qoraiWalletScanningTransaction: 'Scanning transaction',
  qoraiWalletTransactionPreviewFailed: 'Transaction preview failed',

  // Transaction Simulation Event Grouping Headers
  qoraiWalletEstimatedBalanceChange: 'Estimated balance change',
  qoraiWalletApprovalDetails: 'Approval details',
  qoraiWalletAuthorityChange: 'Authority change',
  qoraiWalletOwnershipChange: 'Account ownership change',

  // Transaction Simulation Events
  qoraiWalletReceive: 'Receive',
  qoraiWalletFrom: 'From',
  qoraiWalletUnlimitedAssetAmount: 'Unlimited $1',
  qoraiWalletTokenIsUnverified: 'This token is unverified',
  qoraiWalletTokenIsVerified: 'This token is verified',
  qoraiWalletTokenIsVerifiedByLists: 'This token is verified on $1 lists',
  qoraiWalletSpenderAddress: 'Spender: $1',
  qoraiWalletNoChangesDetected: 'No changes detected',

  // Transaction Simulation Warnings
  qoraiWalletSimulationWarningApprovalToEoa:
    'You’re giving someone else permission to transfer tokens on your behalf.',
  qoraiWalletSimulationWarningBulkApprovalsRequest:
    'This requests permission to transfer many tokens, '
    + 'which is usually an attempt at theft.',
  qoraiWalletSimulationWarningCopyCatDomain: 'This site may be a fake.',
  qoraiWalletSimulationWarningDanglingApproval:
    'This DApp will be able to move tokens from your account later on.',
  qoraiWalletSimulationWarningKnownMalicious:
    'This site is flagged as high risk and will '
    + 'likely attempt to steal your funds.',
  qoraiWalletSimulationWarningNewDomain:
    'This domain hasn’t been verified yet. '
    + 'Continue only if you trust the site.',
  qoraiWalletSimulationWarningPoisonedAddress:
    'Double-check this address'
    + ' as it may be impersonating a previous contact of yours.',
  qoraiWalletSimulationWarningSetOwnerAuthority:
    'This transfers ownership of your token balance to someone else.',
  qoraiWalletSimulationWarningSuspectedMalicious:
    'This site is flagged as unsafe and/or malicious. '
    + 'Continuing may result in losses.',
  qoraiWalletSimulationWarningTooManyTransactionsCritical:
    'This will approve over 200 actions. '
    + 'Unless planned, this may be malicious.',
  qoraiWalletSimulationWarningTooManyTransactions:
    'This requests over 200 approvals'
    + '; which is usually an attempt to drain your balances.',
  qoraiWalletSimulationWarningTradeForNothing:
    'You’re exchanging tokens for nothing in return. '
    + 'This is likely a mistake.',
  qoraiWalletSimulationWarningTransferringErc20ToOwnContract:
    'You’re sending funds to a token’s own address'
    + ' where they’ll be lost forever.',
  qoraiWalletSimulationWarningUserAccountOwnerChange:
    'This transfers ownership of your account and balances to someone else.',
  qoraiWalletTransactionSimulationNotAvailableForNetwork:
    'Transaction preview is not supported on this network.',
  qoraiWalletTransactionSimulationOptedInNotice:
    "You're seeing this message because "
    + 'you opted into the transaction preview service.',

  // Transaction Simulation Errors
  qoraiWalletSimulationErrorInsufficientFundsForFee:
    'Insufficient funds to cover the network gas fee.',
  qoraiWalletSimulationErrorInsufficientFunds:
    'Insufficient funds to complete the transaction.',
  qoraiWalletSimulationErrorTransactionReverted:
    'Transaction is likely to fail and revert. '
    + 'Attempting will still incur gas costs.',
  qoraiWalletSimulationUnexpectedError:
    'Unexpected error with transaction preview. ' + 'Approving may be unsafe.',

  // Sign Message Simulation/Scanning
  qoraiWalletEvmMessageScanningNotSupported:
    'EVM message scanning is not currently supported',
  qoraiWalletWhatIsMessageScanning: "What's EVM message scanning?",
  qoraiWalletEvmMessageScanningFeatureSafetyExplanation:
    'It ensures safety and accuracy by examining '
    + 'the messages sent from the Ethereum Virtual Machine '
    + 'that interact with your smart contract or any actions.',
  qoraiWalletEvmMessageScanningFeatureAccuracyExplanation:
    "It's like double-checking a letter "
    + "to make sure it's just right before signing it.",

  // Asset Detail Accounts (Empty)
  qoraiWalletNoAccountsWithABalance: 'No available accounts',
  qoraiWalletNoAccountsWithABalanceDescription:
    'Accounts with a balance will appear here.',

  // Edit Gas
  qoraiWalletEditGasTitle1: 'Max priority fee',
  qoraiWalletEditGasTitle2: 'Edit gas',
  qoraiWalletEditGasDescription:
    'While not a guarantee, miners will likely prioritize your '
    + 'transaction if you pay a higher fee.',
  qoraiWalletEditGasLow: 'Low',
  qoraiWalletEditGasOptimal: 'Optimal',
  qoraiWalletEditGasHigh: 'High',
  qoraiWalletEditGasLimit: 'Gas limit',
  qoraiWalletEditGasPerGasPrice: 'Per-gas price (Gwei)',
  qoraiWalletEditGasPerTipLimit: 'Per-gas tip limit (Gwei)',
  qoraiWalletEditGasPerPriceLimit: 'Per-gas price limit (Gwei)',
  qoraiWalletEditGasMaxFee: 'Max fee',
  qoraiWalletEditGasMaximumFee: 'Maximum fee',
  qoraiWalletEditGasBaseFee: 'Current base fee',
  qoraiWalletEditGasGwei: 'Gwei',
  qoraiWalletEditGasSetCustom: 'Set custom',
  qoraiWalletEditGasSetSuggested: 'Set suggested',
  qoraiWalletEditGasZeroGasPriceWarning:
    'Transaction may not be propagated in the network.',
  qoraiWalletEditGasLimitError: 'Gas limit must be an integer greater than 0',
  qoraiWalletGasFeeLimitLowerThanBaseFeeWarning:
    'Fee limit is set lower than the base fee. '
    + 'Your transaction may take a long time or fail.',
  qoraiWalletGasTipLimit: 'Gas tip limit',
  qoraiWalletGasPriceLimit: 'Gas price limit',
  qoraiWalletGasPrice: 'Gas price',
  qoraiWalletEditGasEstimatedNetworkFee: 'Estimated network fee',
  qoraiWalletUseDefault: 'Use default',
  qoraiWalletGasFeeTooltip: 'This gas fee will replace the original.',
  qoraiWalletGasFeeTooltipDescription:
    'This will create a new transaction with a new gas fee to '
    + 'override and cancel the pending one. A cancellation can only be '
    + 'attempted if the transaction is still pending on the network.',
  qoraiWalletSpeedPriority: 'Speed priority',

  // Advanced transaction settings
  qoraiWalletAdvancedTransactionSettings: 'Advanced settings',
  qoraiWalletAdvancedTransactionSettingsPlaceholder:
    'Enter custom ' + 'nonce value',
  qoraiWalletEditNonce: 'Nonce',
  qoraiWalletEditNonceInfo:
    'The nonce value will be auto-determined if this field is not specified.',

  // Edit permissions
  qoraiWalletEditPermissionsTitle: 'Edit permissions',
  qoraiWalletEditPermissionsDescription:
    'Spend limit permission allows $1 to withdraw and spend up to the '
    + 'following amount:',
  qoraiWalletEditPermissionsButton: 'Edit permissions',
  qoraiWalletEditPermissionsProposedAllowance: 'Proposed allowance',
  qoraiWalletEditPermissionsCustomAllowance: 'Custom allowance',
  qoraiWalletProposedSpendLimit: 'Proposed spend limit',
  qoraiWalletCustomSpendLimit: 'Custom spend limit',

  // Send Input Errors
  qoraiWalletNotValidFilAddress: 'Not a valid FIL address',
  qoraiWalletNotValidEthAddress: 'Not a valid ETH address',
  qoraiWalletNotValidSolAddress: 'Not a valid SOL address',
  qoraiWalletNotValidAddress: 'Not a valid $1 address.',
  qoraiWalletNotDomain: "Domain doesn't have a linked $1 address.",
  qoraiWalletSameAddressError: 'The receiving address is your own address.',
  qoraiWalletContractAddressError:
    'The receiving address is a tokens contract address.',
  qoraiWalletFailedChecksumTitle: 'Address doesn’t look correct',
  qoraiWalletFailedChecksumDescription:
    'Check your address to make sure it’s the right address '
    + '(e.g. letters with lower or upper case).',
  qoraiWalletHowToSolve: 'How can I solve it?',
  qoraiWalletAddressMissingChecksumInfoWarning:
    'This address cannot be verified (missing checksum). Proceed?',
  qoraiWalletNotValidChecksumAddressError:
    'Address did not pass verification (invalid checksum). '
    + 'Please try again, replacing lowercase letters with uppercase.',
  qoraiWalletMissingGasLimitError: 'Missing gas limit',
  qoraiWalletZeroBalanceError: 'Amount must be greater than 0',
  qoraiWalletAddressRequiredError: 'To address is required',
  qoraiWalletChecksumModalTitle: 'How can I find the right address?',
  qoraiWalletChecksumModalDescription:
    'Qorai prevents users from sending funds to the wrong address due to '
    + 'incorrect capitalization. Make sure that it’s the correct address by '
    + 'following the instructions below.',
  qoraiWalletChecksumModalStepOneTitle: '1. Visit',
  qoraiWalletChecksumModalStepOneDescription:
    'Visit etherscan and paste the wallet address you want to send '
    + 'tokens. Then enter.',
  qoraiWalletChecksumModalStepTwoTitle: '2. Copy and enter ETH address',
  qoraiWalletChecksumModalStepTwoDescription:
    'Copy and enter the correct address. '
    + 'You can see that some characters have been converted correctly.',
  qoraiWalletChecksumModalNeedHelp: 'Need more help?',

  // Transaction Queue Strings
  qoraiWalletQueueOf: 'of',
  qoraiWalletQueueNext: 'next',
  qoraiWalletQueueFirst: 'first',
  qoraiWalletQueueRejectAll: 'Reject transactions',

  // Add Suggested Token Panel
  qoraiWalletAddSuggestedTokenTitle: 'Add suggested token',
  qoraiWalletAddSuggestedTokenDescription:
    'Would you like to import this token?',

  // Transaction Detail Panel
  qoraiWalletRecentTransactions: 'Recent transactions',
  qoraiWalletTransactionDetailHash: 'Transaction hash',
  qoraiWalletTransactionDetailNetwork: 'Network',

  // Transaction Memo
  qoraiWalletMemo: 'Memo',
  qoraiWalletEnterAMessage: 'You can enter a message...',
  qoraiWalletMessageOptional: 'Message (Optional)',
  qoraiWalletAddMemo: 'Add memo',
  qoraiWalletRemoveMemo: 'Remove memo',
  qoraiWalletMemoLengthError: 'Memo must be less than 512 characters long.',

  // Transactions Status
  qoraiWalletTransactionStatusUnapproved: 'Unapproved',
  qoraiWalletTransactionStatusApproved: 'Approved',
  qoraiWalletTransactionStatusRejected: 'Rejected',
  qoraiWalletTransactionStatusSubmitted: 'Submitted',
  qoraiWalletTransactionStatusConfirmed: 'Confirmed',
  qoraiWalletTransactionStatusError: 'Error',
  qoraiWalletTransactionStatusDropped: 'Dropped',
  qoraiWalletTransactionStatusSigned: 'Signed',

  // Transaction Details
  qoraiWalletOn: 'On',

  // Transaction Queue Selector
  qoraiWalletPendingTransactionsNumber: 'Pending ($1)',
  qoraiWalletNextTransaction: 'Next transaction',
  qoraiWalletPreviousTransaction: 'Previous transaction',
  qoraiWalletRejectTransactions: 'Reject $1 transactions',

  // NFT Details Page
  qoraiWalletNFTDetailBlockchain: 'Blockchain',
  qoraiWalletNFTDetailTokenStandard: 'Token standard',
  qoraiWalletNFTDetailTokenID: 'Token ID',
  qoraiWalletNFTDetailContractAddress: 'Contract address',
  qoraiWalletNFTDetailDescription: 'Description',
  qoraiWalletNFTDetailImageAddress: 'Image URL',
  qoraiWalletNFTDetailsNotAvailable: 'Not available yet',
  qoraiWalletNFTDetailsOverview: 'Overview',
  qoraiWalletNFTDetailsOwnedBy: 'Owned by',
  qoraiWalletNFTDetailsViewAccount: 'View account',
  qoraiWalletNFTDetailsPinningStatusLabel: 'IPFS pinning status',
  qoraiWalletNFTDetailsCid: 'CID',
  qoraiWalletNFTDetailsProperties: 'Properties',

  // Sweepstakes
  qoraiWalletSweepstakesTitle: 'Qorai Swap-stakes',
  qoraiWalletSweepstakesDescription:
    '7 days of crypto giveaways, ~$500k in prizes.',
  qoraiWalletSweepstakesCallToAction: 'Enter now!',

  // Market Data Filters
  qoraiWalletMarketDataAllAssetsFilter: 'All Assets',
  qoraiWalletMarketDataTradableFilter: 'Tradable',
  qoraiWalletMarketDataAssetsColumn: 'Assets',
  qoraiWalletMarketDataPriceColumn: 'Price',
  qoraiWalletMarketData24HrColumn: '24Hr',
  qoraiWalletMarketDataMarketCapColumn: 'Cap',
  qoraiWalletMarketDataVolumeColumn: 'Volume',
  qoraiWalletMarketDataBuyDepositColumn: 'Buy/Deposit',

  // Market Coin Detail Screen
  qoraiWalletInformation: 'Information',
  qoraiWalletRankStat: 'Rank',
  qoraiWalletVolumeStat: '24h Volume',
  qoraiWalletMarketCapStat: 'Market Cap',

  // Network Filter
  qoraiWalletNetworkFilterAll: 'All Networks',
  qoraiWalletNetworkFilterSecondary: 'Secondary networks',
  qoraiWalletNetworkFilterTestNetworks: 'Test networks',

  // Asset Filter
  qoraiWalletAssetFilterLowToHigh: 'Low to High',
  qoraiWalletAssetFilterHighToLow: 'High to Low',
  qoraiWalletAssetFilterAToZ: 'A to Z',
  qoraiWalletAssetFilterZToA: 'Z to A',

  // Asset Group By
  qoraiWalletNone: 'None',
  qoraiWalletNetworks: 'Networks',
  qoraiWalletPortfolioGroupByTitle: 'Group by',
  qoraiWalletGroupByCollection: 'Group by collection',
  qoraiWalletPortfolioGroupByDescription: 'Group assets by',

  // Portfolio Filters
  qoraiWalletPortfolioFiltersTitle: 'Filters and display settings',
  qoraiWalletPortfolioNftsFiltersTitle: 'NFT display settings',
  qoraiWalletSortAssets: 'Sort assets',
  qoraiWalletSortAssetsDescription: 'Sort by fiat value or name',
  qoraiWalletHideSmallBalances: 'Hide small balances',
  qoraiWalletHideSmallBalancesDescription: 'Assets with value less than $1',
  qoraiWalletSelectAccounts: 'Select accounts',
  qoraiWalletSelectNetworks: 'Select networks',
  qoraiWalletSelectAll: 'Select all',
  qoraiWalletDeselectAll: 'Deselect all',
  qoraiWalletPrimaryNetworks: 'Primary networks',
  qoraiWalletETHAccountDescription: 'Ethereum + EVM Chains',
  qoraiWalletSOLAccountDescription: 'Solana + SVM Chains',
  qoraiWalletFILAccountDescription: 'Filecoin',
  qoraiWalletBTCMainnetAccountDescription: 'Bitcoin Mainnet',
  qoraiWalletBTCTestnetAccountDescription: 'Bitcoin Testnet',
  qoraiWalletZECAccountDescription: 'Zcash Mainnet',
  qoraiWalletZECTestnetAccountDescription: 'Zcash Testnet',
  qoraiWalletCardanoAccountDescription: 'Cardano Mainnet',
  qoraiWalletCardanoTestnetAccountDescription: 'Cardano Testnet',
  qoraiWalletPolkadotMainnetAccountDescription: 'Polkadot Mainnet',
  qoraiWalletShowNetworkLogoOnNftsTitle: 'Network Logo',
  qoraiWalletShowNetworkLogoOnNftsDescription: 'Show network logo on NFTs',
  qoraiWalletShowSpamNftsTitle: 'Spam NFTs',
  qoraiWalletShowSpamNftsDescription: 'Show Spam NFTs',
  qoraiWalletPortfolioSettings: 'Portfolio Settings',
  qoraiWalletHideNotOwnedNfTs: 'Hide not owned NFTs',

  // Account Filter
  qoraiWalletAccountFilterAllAccounts: 'All accounts',

  // Transaction post-confirmation
  qoraiWalletGetHelp: 'Get help',
  qoraiWalletTransactionTakingLongTime: 'Taking longer than expected?',
  qoraiWalletViewInActivity: 'View in activity',
  qoraiWalletSafelyDismissWindow: 'You can safely dismiss this window.',
  qoraiWalletSendingAmountToAccount: 'Sending $1 to $2',
  qoraiWalletAmountSentToAccount: '$1 has been sent to account $2',
  qoraiWalletSwappingAmountToAmountOnNetwork: 'Swapping $1 to $2 on $3',
  qoraiWalletAmountAddedToAccount:
    'The amount of $1 has been added to your account $2',
  qoraiWalletBridgingAmountToNetwork: 'Bridging $1 to $2',
  qoraiWalletUnableToSendSwapOrBridge: 'Unable to $1',
  qoraiWalletErrorAttemptingToTransact:
    'There was an error attempting to $3 $1 to $2',
  qoraiWalletApprovingAmountOnExchange: 'Approving $1 to $2',
  qoraiWalletCancelTransactionDescription:
    'A new transaction will be created to cancel your existing transaction.',
  qoraiWalletPendingTransactions: '$1 more transactions pending.',
  qoraiWalletSwapping: 'Swapping',
  qoraiWalletBridging: 'Bridging',
  qoraiWalletSwappingOrBridgingOnNetwork: '$1 on $2',
  qoraiWalletErrorAttemptingToTransactOnNetwork:
    'There was an error attempting to $1 on $2',
  qoraiWalletShieldingAmount: 'Shielding $1',
  qoraiWalletAmountHasBeenShielded: '$1 has been shielded',
  // Submitted
  qoraiWalletTransactionSubmittedTitle: 'Transaction submitted',
  qoraiWalletTransactionSignedTitle: 'Transaction signed',

  // Failed
  qoraiWalletTransactionFailedHeaderTitle: '$1 was returned to your wallet',
  qoraiWalletTransactionFailedTitle: 'Transaction failed',
  qoraiWalletTransactionFailedDescription:
    'Transaction was failed due to a large price movement. '
    + 'Increase slippage tolerance to succeed at a larger price movement.',
  qoraiWalletTransactionFailedSwapNextCTA: 'New trade',
  qoraiWalletTransactionFailedNextCTA: 'New transaction',
  qoraiWalletTransactionFailedViewErrorCTA: 'View error',
  qoraiWalletTransactionFailedReceiptCTA: 'Receipt',
  qoraiWalletTransactionFailedModalTitle: 'Error message',
  qoraiWalletTransactionFailedModalSubtitle:
    'Please save the error message for future reference.',

  // Complete
  qoraiWalletTransactionCompleteSwapHeaderTitle: 'Swapped $1 to $2',
  qoraiWalletTransactionCompleteTitle: 'Transaction complete!',
  qoraiWalletTransactionCompleteDescription:
    'Transaction was successful. Please wait for confirmations, '
    + 'to avoid the risk of double-spend.',
  qoraiWalletTransactionCompleteReceiptCTA: 'Receipt',

  // Confirming
  qoraiWalletTransactionConfirmingTitle: 'Transaction is processing',
  // [FIXME]: change the wording after ETH2.
  qoraiWalletTransactionConfirmingDescription:
    'Transaction was successfully included in a block. '
    + 'To avoid the risk of double spending, '
    + 'we recommend waiting for block confirmations.',
  qoraiWalletTransactionConfirmingText: 'Confirming',

  // Transaction intents for confirmation panels
  qoraiWalletTransactionIntentDappInteraction: 'Dapp interaction',
  qoraiWalletTransactionIntentSend: 'Send $1',
  qoraiWalletTransactionIntentSwap: 'Swap $1 to $2',

  // Solana Associated Token Account
  qoraiWalletCreatingAssociatedTokenAccount:
    'Creating associated token account',
  qoraiWalletFailedToCreateAssociatedTokenAccount:
    'Failed to create associated token account',
  qoraiWalletAssociatedTokenAccountCreated: 'Associated token account created',

  // Solana ProgramID Names
  qoraiWalletSolanaSystemProgram: 'System Program',
  qoraiWalletSolanaConfigProgram: 'Config Program',
  qoraiWalletSolanaStakeProgram: 'Stake Program',
  qoraiWalletSolanaVoteProgram: 'Vote Program',
  qoraiWalletSolanaBPFLoader: 'BPF Loader',
  qoraiWalletSolanaEd25519Program: 'Ed25519 Program',
  qoraiWalletSolanaSecp256k1Program: 'Secp256k1 Program',
  qoraiWalletSolanaTokenProgram: 'Token Program',
  qoraiWalletSolanaAssociatedTokenProgram: 'Associated Token Program',
  qoraiWalletSolanaMetaDataProgram: 'MetaData Program',
  qoraiWalletSolanaSysvarRentProgram: 'SysvarRent Program',

  // Solana Instruction Parameter Names
  qoraiWalletSolanaAccounts: 'Accounts:',
  qoraiWalletSolanaData: 'Data:',
  qoraiWalletSolanaProgramID: 'Program ID:',
  qoraiWalletSolanaMaxRetries: 'Max Retries:',
  qoraiWalletSolanaPreflightCommitment: 'Preflight Commitment:',
  qoraiWalletSolanaSkipPreflight: 'Skip Preflight:',
  qoraiWalletSolanaAddressLookupTableAccount: 'Address Lookup Table Account:',
  qoraiWalletSolanaAddressLookupTableIndex: 'Address Lookup Table Index:',

  // Help Center
  qoraiWalletHelpCenter: 'Help center',
  qoraiWalletHelpCenterText: 'Need help? See',

  // Remove Account Modal
  qoraiWalletRemoveAccountModalTitle: 'Are you sure you want to remove "$1"?',

  // Input field labels
  qoraiWalletInputLabelPassword: 'Password',

  // Wallet Welcome Perks
  qoraiWalletPerksTokens: 'Buy, send, and swap 200+ crypto assets',
  qoraiWalletMultiChain: 'Multi-chain & NFT support',
  qoraiWalletPerksBrowserNative: 'Browser-native, no risky extensions',

  // Portfolio Asset More Popup
  qoraiWalletPortfolioTokenDetailsMenuLabel: 'Token details',
  qoraiWalletPortfolioViewOnExplorerMenuLabel: 'View on block explorer',
  qoraiWalletPortfolioHideTokenMenuLabel: 'Hide token',
  qoraiWalletHideTokenModalTitle: 'Hide token',

  // Token detail modals
  qoraiWalletMakeTokenVisibleInstructions:
    'You can make this asset visible again in the future by clicking '
    + 'the "+ Visible assets" button at the bottom of the "Portfolio" tab',
  qoraiWalletConfirmHidingToken: 'Hide',
  qoraiWalletCancelHidingToken: 'Cancel',

  // Visible assets modal
  qoraiWalletMyAssets: 'My assets',
  qoraiWalletAvailableAssets: 'Available assets',
  qoraiWalletDidntFindAssetEndOfList: "Didn't find your asset on the list?",
  qoraiWalletDidntFindAssetInList:
    "If you didn't find your asset in this list, you can add it manually "
    + 'by using the button below',
  qoraiWalletAssetNotFound: 'Asset not found',

  // Request feature button
  qoraiWalletRequestFeatureButtonText: 'Request feature',

  // Warnings
  qoraiWalletNonAsciiCharactersInMessageWarning:
    'Non-ASCII characters detected!',
  qoraiWalletFoundRisks: 'We found $1 risks.',
  qoraiWalletFoundIssues: 'We found $1 issues.',

  // ASCII toggles
  qoraiWalletViewEncodedMessage: 'View original message',
  qoraiWalletViewDecodedMessage: 'View message in ASCII encoding',

  // NFTs Tab
  qoraiNftsTabImportNft: 'Import NFT',
  qoraiNftsTabEmptyStateHeading: 'No NFTs here yet.',
  qoraiNftsTabEmptyStateSubHeading:
    'Ready to add some? Just click the button below to import.',
  qoraiNftsTabEmptyStateDisclaimer:
    'Compatible with NFTs on Solana (SPL) and Ethereum (ERC-721).',
  qoraiNftsTab: 'NFTs',
  qoraiNftsTabHidden: 'Hidden',
  qoraiNftsTabCollected: 'Collected',
  qoraiNftsTabHide: 'Hide',
  qoraiNftsTabUnhide: 'Unhide',
  qoraiNftsTabEdit: 'Edit',
  qoraiNftsTabRemove: "Don't show in wallet",

  // Add asset tabs
  qoraiWalletAddAssetTokenTabTitle: 'Token',
  qoraiWalletAddAssetNftTabTitle: 'NFT',
  qoraiWalletNftFetchingError:
    'Something went wrong when fetching NFT details. Please try again later.',
  qoraiWalletEditToken: 'Edit Token',

  // Add Custom Asset Form
  qoraiWalletNetworkIsRequiredError: 'Network is required',
  qoraiWalletTokenNameIsRequiredError: 'Token name is required',
  qoraiWalletInvalidTokenContractAddressError:
    'Invalid or empty token contract address',
  qoraiWalletTokenSymbolIsRequiredError: 'Token symbol is required',
  qoraiWalletTokenDecimalsIsRequiredError:
    'Token decimals of precision value is required',
  qoraiWalletTokenContractAddress: 'Token Contract Address',
  qoraiWalletTokenDecimal: 'Token Decimal',
  qoraiWalletTokenMintAddress: 'Mint address',
  qoraiWalletTransactionHasFeeEstimatesError: 'Unable to fetch fee estimates',

  qoraiWalletEditNftModalTitle: 'Edit NFT',
  qoraiWalletNftMoveToSpam: 'Mark as junk',
  qoraiWalletNftUnspam: 'Mark as not junk',

  // NFT Labels
  qoraiWalletNftJunk: 'Junk',
  qoraiWalletWatchOnly: 'Watch-only',

  // Add NFT modal
  qoraiWalletAddNftModalTitle: 'Add NFT',
  qoraiWalletAddNftModalDescription:
    "If you can't see an NFT automatically detected by Qorai, "
    + 'or want to track one owned by others, you can import it manually.',
  qoraiWalletWhatIsAnNftContractAddress:
    'The contract address when adding an NFT to a wallet is the unique '
    + 'address on the blockchain where the smart contract '
    + 'for the NFT collection resides. '
    + 'You can find the contract address from marketplace, or '
    + 'blockchain explorers, etc.',
  qoraiWalletWhatIsAnNftTokenId:
    'The unique identifier for the specific NFT within the collection.',
  qoraiWalletNftNameFieldExplanation:
    'The token name for an NFT refers to the specific name given to a '
    + 'non-fungible token within a particular collection or project. '
    + 'This name distinguishes one NFT from another within the same collection.',
  qoraiWalletNftSymbolFieldExplanation:
    'The NFT symbol refers to the unique identifier '
    + 'used to distinguish the NFT collection or project.',
  qoraiWalletFetchNftMetadataError: 'Unable to fetch NFT metadata',
  qoraiWalletWatchThisNft: 'Watch this NFT',
  qoraiWalletUnownedNftAlert:
    'You do not own this NFT. '
    + 'While you can still add it to your wallet, '
    + 'you will not be able to make any transactions with it.',

  // Remove NFT modal
  qoraiWalletRemoveNftModalHeader: 'Remove from Qorai Wallet?',
  qoraiWalletRemoveNftModalDescription:
    'NFT will be removed from Qorai Wallet but will remain on the '
    + 'blockchain. If you remove it, then change your mind, '
    + "you'll need to import it again manually.",
  qoraiWalletRemoveNftModalCancel: 'Cancel',
  qoraiWalletRemoveNftModalConfirm: 'Remove',

  // NFT auto discovery modal
  qoraiWalletEnableNftAutoDiscoveryModalHeader:
    'Want your NFTs displayed automatically?',
  qoraiWalletEnableNftAutoDiscoveryModalDescription:
    'Qorai Wallet can use a third-party service to automatically display '
    + 'your NFTs. Qorai will share your wallet addresses with '
    + '$1SimpleHash$1 to provide this service. $2Learn more.$2',
  qoraiWalletEnableNftAutoDiscoveryModalConfirm: 'Yes, proceed',
  qoraiWalletEnableNftAutoDiscoveryModalCancel:
    "No thanks, I'll do it manually",
  qoraiWalletAutoDiscoveryEmptyStateHeading: 'No NFTs to display',
  qoraiWalletAutoDiscoveryEmptyStateSubHeading:
    'Once an NFT is detected, it’ll be displayed here.',
  qoraiWalletAutoDiscoveryEmptyStateFooter: 'Can’t see your NFTs?',
  qoraiWalletAutoDiscoveryEmptyStateActions:
    '$1Refresh$1 or $2Import Manually$2',
  qoraiWalletAutoDiscoveryEmptyStateRefresh: 'Refreshing',

  // Qorai Wallet Rewards
  qoraiWalletUphold: 'Uphold',
  qoraiWalletGemini: 'Gemini',
  qoraiWalletZebpay: 'Zebpay',
  qoraiWalletBitflyer: 'bitFlyer',
  qoraiWalletRewardsAccount: '$1 account',
  qoraiWalletQoraiRewardsTitle: 'Qorai Rewards',
  qoraiWalletQoraiRewardsDescription: 'Qorai Rewards QOR on $1',
  qoraiWalletQoraiRewardsLoggedOutDescription:
    'You’re currently logged out of $1. Please log in to view your balance.',
  qoraiWalletLogIn: 'Log in',
  qoraiWalletViewOn: 'View on $1',
  qoraiWalletRewardsSettings: 'Rewards settings',
  qoraiWalletPlatforms: 'Platforms',
  qoraiWalletTestNetworkAccount: 'Test Network Account',

  // Transaction Simulations Opt-in
  qoraiWalletEnableTransactionSimulation: 'Enable transaction simulation',
  qoraiWalletTransactionSimulationFeatureDescription:
    'Simulate how a transaction will behave before authorizing it',
  qoraiWalletTransactionSimulationSeeEstimates:
    'Preview your estimated balance change',
  qoraiWalletTransactionSimulationDetectMalicious:
    'Identify potentially malicious transactions',
  qoraiWalletTransactionSimulationDetectPhishing:
    'Help detect phishing attempts',
  qoraiWalletTransactionSimulationTerms:
    'This service is provided by $1Blowfish.xyz$2 and is subject to their $3Terms '
    + 'of Service$4 and $5Privacy Policy$6.',

  // Settings
  qoraiWalletChangeAnytimeInSettings: 'Change anytime in $1Settings$2.',

  // Balance Details Modal
  qoraiWalletAvailable: 'Available',
  qoraiWalletAvailableBalanceDescription: 'Funds available for you to use.',
  qoraiWalletPending: 'Pending',
  qoraiWalletPendingBalanceDescription:
    'A pending change in your wallet balance.',
  qoraiWalletTotalBalanceDescription:
    'Your available funds plus any not-yet-confirmed transactions.',
  qoraiWalletUnavailableBalances: 'Some balances may be unavailable',

  // Misc. placeholders
  qoraiWalletExempliGratia: 'e.g $1',

  // Explore
  qoraiWalletWeb3: 'Web3',
  qoraiWalletTopNavExplore: 'Explore',
  qoraiWalletNoDappsFound: 'No DApps found',
  qoraiWalletActiveWallets: 'Active wallets',
  qoraiWalletVisitDapp: 'Visit $1',
  qoraiWalletFilters: 'Filters',
  qoraiWalletClearFilters: 'Clear filters',
  qoraiWalletShowMore: 'Show more',
  qoraiWalletDetails: 'Details',
  qoraiWalletVerified: 'Verified by DappRadar',

  // ZCash
  qoraiWalletSwitchToShieldedAccount: 'Switch to a shielded account',
  qoraiWalletShieldAccount: 'Shield account',
  qoraiWalletShieldAccountAlertDescription:
    'Enable shielding to enhance transaction privacy.',
  qoraiWalletAccountNotShieldedDescription:
    'Currently this account supports transparent transactions which means they are visible to everyone on the blockchain.',
  qoraiWalletAccountShieldedDescription:
    'Upgrading to a shielded account means that these transactions hide the sender, receiver and amount details.',
  qoraiWalletShielded: 'Shielded',
  qoraiWalletUnified: 'Unified',
  qoraiWalletTransparent: 'Transparent',
  qoraiWalletOutOfSyncTitle: 'Out of sync',
  qoraiWalletOutOfSyncBlocksBehindTitle: 'Out of sync ($1 blocks behind)',
  qoraiWalletOutOfSyncDescription:
    'Sync your account to access the latest transactions and balance.',
  qoraiWalletZCashPendingBalanceTitle:
    'Pending balance (more confirmations required): $1',
  qoraiWalletSyncAccountButton: 'Sync account',
  qoraiWalletSyncAccountButtonInProgress: 'Syncing...',
  qoraiWalletSyncAccountName: 'Sync $1',
  qoraiWalletInitializing: 'Initializing...',
  qoraiWalletProcessingBlock: 'Processing block:',
  qoraiWalletBlocksLeft: '$1 left',
  qoraiWalletBlocksOfBlocks: '$1 of $2',
  qoraiWalletRanges: 'Ranges:',
  qoraiWalletPause: 'Pause',
  qoraiWalletSyncCompleteMessage:
    'Sync complete. You may now close this window.',
  qoraiWalletSyncStartedMessage:
    'Please don’t close this window until sync finishes.',
  qoraiWalletContinueUsingWallet: 'Continue using wallet in a new tab',
  qoraiWalletShieldedAccountBirthdayBlock: 'Shielded account birthday block',
  qoraiWalletAccountBirthdayTooLow: 'Account birthday must be greater than $1',
  qoraiWalletAccountBirthdayTooHigh: 'Account birthday must be less than $1',
  qoraiWalletBlocksBehind: '$1 blocks behind',
  qoraiWalletAccountIsSyncing: 'Account is syncing',
  qoraiWalletSyncing: 'Syncing',
  qoraiWalletReviewShield: 'Review shield',
  qoraiWalletShielding: 'Shielding',
  qoraiWalletShieldZEC: 'Shield ZEC',
  qoraiWalletShieldFunds: 'Shield funds',
  qoraiWalletShieldingFundsAlertDescription:
    'You are sending funds from your transparent account to your shielded'
    + 'account.',

  // Page Not Found
  qoraiWalletPageNotFoundTitle:
    'We can’t find the page you’re looking for right now.',
  qoraiWalletPageNotFoundDescription:
    'It may have moved to a different place or the URL may contain a typo.',
  qoraiWalletGoToPortfolio: 'Go to Portfolio',
})
