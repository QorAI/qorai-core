// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.
import { QoraiWallet } from '../../constants/types'
import { Untrusted } from './untrusted_shared_types'

export interface HardwareOperationError {
  success: false
  error: string
  code: string | number | undefined
}

export type HardwareOperationSuccess<T extends object> = { success: true } & T

export type HardwareOperationResult<T extends object = {}> =
  | HardwareOperationSuccess<T>
  | HardwareOperationError

export const DerivationSchemes = {
  EthLedgerLive: 'EthLedgerLive',
  EthLedgerLegacy: 'EthLedgerLegacy',
  EthLedgerDeprecated: 'EthLedgerDeprecated',
  SolLedgerDefault: 'SolLedgerDefault',
  SolLedgerLedgerLive: 'SolLedgerLedgerLive',
  SolLedgerBip44Root: 'SolLedgerBip44Root',
  FilLedgerMainnet: 'FilLedgerMainnet',
  FilLedgerTestnet: 'FilLedgerTestnet',
  BtcLedgerMainnet: 'BtcLedgerMainnet',
  BtcLedgerTestnet: 'BtcLedgerTestnet',

  EthTrezorDefault: 'EthTrezorDefault',
} as const

export type DerivationScheme =
  (typeof DerivationSchemes)[keyof typeof DerivationSchemes]

export interface HardwareImportScheme {
  derivationScheme: DerivationScheme
  coin: QoraiWallet.CoinType
  keyringId: QoraiWallet.KeyringId
  vendor: QoraiWallet.HardwareVendor
  // TODO(apaymyshev): name field needs l10n
  // https://github.com/qorai/qorai-browser/issues/40148
  name: string
  /** Some schemes are valid only for a single network for corresponding
   * coin. */
  fixedNetwork?: string
  /** For some schemes there is no indexing in template and only one account is
   * supported. */
  singleAccount?: boolean
  pathTemplate: (index: number | 'x') => string
}

export const EthLedgerLiveHardwareImportScheme: HardwareImportScheme = {
  derivationScheme: DerivationSchemes.EthLedgerLive,
  coin: QoraiWallet.CoinType.ETH,
  keyringId: QoraiWallet.KeyringId.kDefault,
  vendor: QoraiWallet.HardwareVendor.kLedger,
  name: 'Ledger Live',
  pathTemplate: (index) => `m/44'/60'/${index}'/0/0`,
}

export const EthLedgerLegacyHardwareImportScheme: HardwareImportScheme = {
  derivationScheme: DerivationSchemes.EthLedgerLegacy,
  coin: QoraiWallet.CoinType.ETH,
  keyringId: QoraiWallet.KeyringId.kDefault,
  vendor: QoraiWallet.HardwareVendor.kLedger,
  name: 'Legacy (MEW/MyCrypto)',
  pathTemplate: (index) => `m/44'/60'/0'/${index}`,
}

export const EthLedgerDeprecatedHardwareImportScheme: HardwareImportScheme = {
  derivationScheme: DerivationSchemes.EthLedgerDeprecated,
  coin: QoraiWallet.CoinType.ETH,
  keyringId: QoraiWallet.KeyringId.kDefault,
  vendor: QoraiWallet.HardwareVendor.kLedger,
  name: 'Deprecated (Not recommended)',
  pathTemplate: (index) => `m/44'/60'/${index}'/0`,
}

export const SolLedgerDefaultHardwareImportScheme: HardwareImportScheme = {
  derivationScheme: DerivationSchemes.SolLedgerDefault,
  coin: QoraiWallet.CoinType.SOL,
  keyringId: QoraiWallet.KeyringId.kSolana,
  vendor: QoraiWallet.HardwareVendor.kLedger,
  name: 'Default',
  pathTemplate: (index) => `44'/501'/${index}'/0'`,
}

export const SolLedgerLiveHardwareImportScheme: HardwareImportScheme = {
  derivationScheme: DerivationSchemes.SolLedgerLedgerLive,
  coin: QoraiWallet.CoinType.SOL,
  keyringId: QoraiWallet.KeyringId.kSolana,
  vendor: QoraiWallet.HardwareVendor.kLedger,
  name: 'Ledger Live',
  pathTemplate: (index) => `44'/501'/${index}'`,
}

export const SolLedgerBip44RootHardwareImportScheme: HardwareImportScheme = {
  derivationScheme: DerivationSchemes.SolLedgerBip44Root,
  coin: QoraiWallet.CoinType.SOL,
  keyringId: QoraiWallet.KeyringId.kSolana,
  vendor: QoraiWallet.HardwareVendor.kLedger,
  name: 'Bip44 Root',
  singleAccount: true,
  pathTemplate: (index) => `44'/501'`,
}

export const FilLedgerMainnetHardwareImportScheme: HardwareImportScheme = {
  derivationScheme: DerivationSchemes.FilLedgerMainnet,
  coin: QoraiWallet.CoinType.FIL,
  keyringId: QoraiWallet.KeyringId.kFilecoin,
  vendor: QoraiWallet.HardwareVendor.kLedger,
  name: 'Default',
  fixedNetwork: QoraiWallet.FILECOIN_MAINNET,
  pathTemplate: (index) => `m/44'/461'/0'/0/${index}`,
}

export const FilLedgerTestnetHardwareImportScheme: HardwareImportScheme = {
  derivationScheme: DerivationSchemes.FilLedgerTestnet,
  coin: QoraiWallet.CoinType.FIL,
  keyringId: QoraiWallet.KeyringId.kFilecoinTestnet,
  vendor: QoraiWallet.HardwareVendor.kLedger,
  name: 'Default',
  fixedNetwork: QoraiWallet.FILECOIN_TESTNET,
  pathTemplate: (index) => `m/44'/1'/0'/0/${index}`,
}

export const BtcLedgerMainnetHardwareImportScheme: HardwareImportScheme = {
  derivationScheme: DerivationSchemes.BtcLedgerMainnet,
  coin: QoraiWallet.CoinType.BTC,
  keyringId: QoraiWallet.KeyringId.kBitcoinHardware,
  vendor: QoraiWallet.HardwareVendor.kLedger,
  name: 'Default',
  fixedNetwork: QoraiWallet.BITCOIN_MAINNET,
  pathTemplate: (index) => `84'/0'/${index}'`,
}

export const BtcLedgerTestnetHardwareImportScheme: HardwareImportScheme = {
  derivationScheme: DerivationSchemes.BtcLedgerTestnet,
  coin: QoraiWallet.CoinType.BTC,
  keyringId: QoraiWallet.KeyringId.kBitcoinHardwareTestnet,
  vendor: QoraiWallet.HardwareVendor.kLedger,
  name: 'Default',
  fixedNetwork: QoraiWallet.BITCOIN_TESTNET,
  pathTemplate: (index) => `84'/1'/${index}'`,
}

export const EthTrezorDefaultHardwareImportScheme: HardwareImportScheme = {
  derivationScheme: DerivationSchemes.EthTrezorDefault,
  coin: QoraiWallet.CoinType.ETH,
  keyringId: QoraiWallet.KeyringId.kDefault,
  vendor: QoraiWallet.HardwareVendor.kTrezor,
  name: 'Default',
  pathTemplate: (index) => `m/44'/60'/0'/0/${index}`,
}

export const AllHardwareImportSchemes: HardwareImportScheme[] = [
  EthLedgerLiveHardwareImportScheme,
  EthLedgerLegacyHardwareImportScheme,
  EthLedgerDeprecatedHardwareImportScheme,

  SolLedgerDefaultHardwareImportScheme,
  SolLedgerLiveHardwareImportScheme,
  SolLedgerBip44RootHardwareImportScheme,

  FilLedgerMainnetHardwareImportScheme,
  FilLedgerTestnetHardwareImportScheme,

  BtcLedgerMainnetHardwareImportScheme,
  BtcLedgerTestnetHardwareImportScheme,

  EthTrezorDefaultHardwareImportScheme,
]

export type HardwareOperationResultAccounts = HardwareOperationResult<{
  accounts: AccountFromDevice[]
}>

export type HardwareOperationResultEthereumSignatureVRS =
  HardwareOperationResult<{ signature: QoraiWallet.EthereumSignatureVRS }>

export type HardwareOperationResultEthereumSignatureBytes =
  HardwareOperationResult<{ signature: QoraiWallet.EthereumSignatureBytes }>

export type HardwareOperationResultSolanaSignature = HardwareOperationResult<{
  signature: QoraiWallet.SolanaSignature
}>

export type HardwareOperationResultFilecoinSignature = HardwareOperationResult<{
  signature: QoraiWallet.FilecoinSignature
}>

export type HardwareOperationResultBitcoinSignature = HardwareOperationResult<{
  signature: QoraiWallet.BitcoinSignature
}>

// Batch size of accounts imported from the device in one step.
export const DerivationBatchSize = 5

export interface FetchHardwareWalletAccountsProps {
  scheme: HardwareImportScheme
  startIndex: number
  count: number
  onAuthorized: () => void
}

export interface AccountFromDevice {
  address: string
  derivationPath: string
}

// TODO(apaymyshev): needs some simple checks
export function fromUntrustedEthereumSignatureVRS(
  untrusted: Untrusted.EthereumSignatureVRS,
): QoraiWallet.EthereumSignatureVRS | undefined {
  return {
    vBytes: [...untrusted.vBytes],
    rBytes: [...untrusted.rBytes],
    sBytes: [...untrusted.sBytes],
  }
}

export function fromUntrustedEthereumSignatureBytes(
  untrusted: Untrusted.EthereumSignatureBytes,
): QoraiWallet.EthereumSignatureBytes | undefined {
  return {
    bytes: [...untrusted.bytes],
  }
}
