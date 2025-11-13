// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

// Utils
import { isPersistanceOfPanelProhibited } from '../utils/local-storage-utils'

// Types
import {
  NavOption,
  WalletRoutes,
  AccountPageTabs,
  PanelTypes,
} from '../constants/types'

const PANEL_TYPES: PanelTypes[] = [
  'accounts',
  'approveTransaction',
  'assets',
  'buy',
  'connectHardwareWallet',
  'connectWithSite',
  'createAccount',
  'expanded',
  'main',
  'networks',
  'send',
  'settings',
  'sitePermissions',
  'swap',
  'activity', // Transactions
  'transactionStatus',
]

export const isValidPanelNavigationOption = (
  panelName: string,
): panelName is PanelTypes => {
  return (
    PANEL_TYPES.includes(panelName as PanelTypes)
    && !isPersistanceOfPanelProhibited(panelName as PanelTypes)
  )
}

const BridgeOption: NavOption = {
  id: 'bridge',
  name: 'qoraiWalletBridge',
  icon: 'web3-bridge',
  route: WalletRoutes.Bridge,
}

export const BuySendSwapDepositOptions: NavOption[] = [
  {
    id: 'buy',
    name: 'qoraiWalletBuy',
    icon: 'coins-alt1',
    route: WalletRoutes.FundWalletPageStart,
  },
  {
    id: 'send',
    name: 'qoraiWalletSend',
    icon: 'send',
    route: WalletRoutes.Send,
  },
  {
    id: 'swap',
    name: 'qoraiWalletSwap',
    icon: 'currency-exchange',
    route: WalletRoutes.Swap,
  },
  BridgeOption,
  {
    id: 'deposit',
    name: 'qoraiWalletDepositCryptoButton',
    icon: 'money-bag-coins',
    route: WalletRoutes.DepositFundsPageStart,
  },
]

const PortfolioActivityNavOption: NavOption = {
  id: 'activity',
  name: 'qoraiWalletActivity',
  icon: 'activity',
  route: WalletRoutes.PortfolioActivity,
}

const AssetsNavOption: NavOption = {
  id: 'assets',
  name: 'qoraiWalletAccountsAssets',
  icon: 'coins',
  route: WalletRoutes.PortfolioAssets,
}

const ExploreNavOption: NavOption = {
  id: 'explore',
  name: 'qoraiWalletTopNavExplore',
  icon: 'discover',
  route: WalletRoutes.Explore,
}

export const PanelNavOptions: NavOption[] = [
  {
    id: 'portfolio',
    name: 'qoraiWalletTopNavPortfolio',
    icon: 'coins',
    route: WalletRoutes.Portfolio,
  },
  {
    id: 'connections',
    name: 'qoraiWalletConnections',
    icon: 'link-normal',
    route: WalletRoutes.Connections,
  },
  {
    id: 'accounts',
    name: 'qoraiWalletTopNavAccounts',
    icon: 'user-accounts',
    route: WalletRoutes.Accounts,
  },
  ExploreNavOption,
]

export const NavOptions: NavOption[] = [
  {
    id: 'portfolio',
    name: 'qoraiWalletTopNavPortfolio',
    icon: 'coins',
    route: WalletRoutes.Portfolio,
  },
  {
    id: 'accounts',
    name: 'qoraiWalletTopNavAccounts',
    icon: 'user-accounts',
    route: WalletRoutes.Accounts,
  },
  ExploreNavOption,
]

export const AllNavOptions: NavOption[] = [
  ...NavOptions,
  ...BuySendSwapDepositOptions,
]

export const PortfolioNavOptions: NavOption[] = [
  AssetsNavOption,
  {
    id: 'nfts',
    name: 'qoraiWalletTopNavNFTS',
    icon: 'grid04',
    route: WalletRoutes.PortfolioNFTs,
  },
  PortfolioActivityNavOption,
]

export const PortfolioNavOptionsNoNFTsTab: NavOption[] = [
  AssetsNavOption,
  PortfolioActivityNavOption,
]

export const ExploreNavOptions: NavOption[] = [
  {
    id: 'market',
    name: 'qoraiWalletTopNavMarket',
    icon: 'discover',
    route: WalletRoutes.Market,
  },
  {
    id: 'web3',
    name: 'qoraiWalletWeb3',
    icon: 'discover',
    route: WalletRoutes.Web3,
  },
]

export const PortfolioAssetOptions: NavOption[] = [
  {
    id: 'accounts',
    name: 'qoraiWalletTopNavAccounts',
    icon: 'user-accounts',
    route: WalletRoutes.AccountsHash,
  },
  {
    id: 'transactions',
    name: 'qoraiWalletTransactions',
    icon: 'activity',
    route: WalletRoutes.TransactionsHash,
  },
]

export const EditVisibleAssetsOptions: NavOption[] = [
  {
    id: 'my_assets',
    name: 'qoraiWalletMyAssets',
    icon: '',
    route: WalletRoutes.MyAssetsHash,
  },
  {
    id: 'available_assets',
    name: 'qoraiWalletAvailableAssets',
    icon: '',
    route: WalletRoutes.AvailableAssetsHash,
  },
]

export const CreateAccountOptions: NavOption[] = [
  {
    id: 'accounts',
    name: 'qoraiWalletCreateAccountButton',
    icon: 'plus-add',
    route: WalletRoutes.CreateAccountModalStart,
  },
  {
    id: 'accounts',
    name: 'qoraiWalletImportAccount',
    icon: 'product-qorai-wallet',
    route: WalletRoutes.ImportAccountModalStart,
  },
  {
    id: 'accounts',
    name: 'qoraiWalletConnectHardwareWallet',
    icon: 'flashdrive',
    route: WalletRoutes.AddHardwareAccountModalStart,
  },
]

export const AccountDetailsOptions: NavOption[] = [
  {
    id: 'assets',
    name: 'qoraiWalletAccountsAssets',
    icon: '',
    route: AccountPageTabs.AccountAssetsSub,
  },
  {
    id: 'nfts',
    name: 'qoraiWalletTopNavNFTS',
    icon: '',
    route: AccountPageTabs.AccountNFTsSub,
  },
  {
    id: 'transactions',
    name: 'qoraiWalletTransactions',
    icon: '',
    route: AccountPageTabs.AccountTransactionsSub,
  },
]
