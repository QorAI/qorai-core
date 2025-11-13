// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

// types
import { QoraiWallet } from '../constants/types'

// constants
import { BLOWFISH_URL_WARNING_KINDS } from '../common/constants/blowfish'

// utils
import { getLocale } from '../../common/locale'

interface GroupedEVMStateChanges {
  evmApprovals: QoraiWallet.BlowfishEVMStateChange[]
  evmTransfers: QoraiWallet.BlowfishEVMStateChange[]
}

interface GroupedSVMStateChanges {
  solStakeAuthorityChanges: QoraiWallet.BlowfishSolanaStateChange[]
  splApprovals: QoraiWallet.BlowfishSolanaStateChange[]
  svmTransfers: QoraiWallet.BlowfishSolanaStateChange[]
  accountOwnerChangeData: QoraiWallet.BlowfishSolanaStateChange[]
}

export const groupSimulatedEVMStateChanges = (
  evmStateChanges: QoraiWallet.BlowfishEVMStateChange[],
): GroupedEVMStateChanges => {
  const changes: GroupedEVMStateChanges = {
    evmApprovals: [],
    evmTransfers: [],
  }

  for (const stateChange of evmStateChanges) {
    const { data } = stateChange.rawInfo

    // approvals & approvals for all
    if (
      data.erc20ApprovalData
      || data.erc721ApprovalData
      || data.erc721ApprovalForAllData
      || data.erc1155ApprovalForAllData
    ) {
      changes.evmApprovals.push(stateChange)
    }

    // transfers
    if (
      data.erc20TransferData
      || data.erc721TransferData
      || data.erc1155TransferData
      || data.nativeAssetTransferData
    ) {
      changes.evmTransfers.push(stateChange)
    }
  }

  return changes
}

export const decodeSimulatedSVMStateChanges = (
  stateChanges: QoraiWallet.BlowfishSolanaStateChange[],
): GroupedSVMStateChanges => {
  const changes: GroupedSVMStateChanges = {
    solStakeAuthorityChanges: [],
    splApprovals: [],
    svmTransfers: [],
    accountOwnerChangeData: [],
  }

  for (const stateChange of stateChanges) {
    const { data } = stateChange.rawInfo

    // staking auth changes
    if (data.solStakeAuthorityChangeData) {
      changes.solStakeAuthorityChanges.push(stateChange)
    }

    // approvals
    if (data.splApprovalData) {
      changes.splApprovals.push(stateChange)
    }

    // transfers
    if (data.solTransferData || data.splTransferData) {
      changes.svmTransfers.push(stateChange)
    }

    // account ownership changes
    if (data.userAccountOwnerChangeData) {
      changes.accountOwnerChangeData.push(stateChange)
    }
  }

  return changes
}

export const isUrlWarning = (warningKind: QoraiWallet.BlowfishWarningKind) => {
  return BLOWFISH_URL_WARNING_KINDS.includes(warningKind)
}

const { BlowfishEVMErrorKind, BlowfishSolanaErrorKind: SolErrorKind } =
  QoraiWallet

export const translateSimulationWarning = (
  warning: QoraiWallet.BlowfishWarning | undefined,
) => {
  if (!warning) {
    return ''
  }

  switch (warning.kind) {
    case QoraiWallet.BlowfishWarningKind.kApprovalToEOA:
      return getLocale('qoraiWalletSimulationWarningApprovalToEoa')

    case QoraiWallet.BlowfishWarningKind.kBulkApprovalsRequest:
      return getLocale('qoraiWalletSimulationWarningBulkApprovalsRequest')

    case QoraiWallet.BlowfishWarningKind.kCopyCatDomain:
    case QoraiWallet.BlowfishWarningKind.kMultiCopyCatDomain:
      return getLocale('qoraiWalletSimulationWarningCopyCatDomain')

    case QoraiWallet.BlowfishWarningKind.kDanglingApproval:
      return getLocale('qoraiWalletSimulationWarningDanglingApproval')

    case QoraiWallet.BlowfishWarningKind.kKnownMalicious:
      return getLocale('qoraiWalletSimulationWarningKnownMalicious')

    case QoraiWallet.BlowfishWarningKind.kNewDomain:
      return getLocale('qoraiWalletSimulationWarningNewDomain')

    case QoraiWallet.BlowfishWarningKind.kPoisonedAddress:
      return getLocale('qoraiWalletSimulationWarningPoisonedAddress')

    case QoraiWallet.BlowfishWarningKind.kSetOwnerAuthority:
      return getLocale('qoraiWalletSimulationWarningSetOwnerAuthority')

    case QoraiWallet.BlowfishWarningKind.kSuspectedMalicious:
      return getLocale('qoraiWalletSimulationWarningSuspectedMalicious')

    case QoraiWallet.BlowfishWarningKind.kTooManyTransactions:
      return warning.severity === QoraiWallet.BlowfishWarningSeverity.kCritical
        ? getLocale('qoraiWalletSimulationWarningTooManyTransactionsCritical')
        : getLocale('qoraiWalletSimulationWarningTooManyTransactions')

    case QoraiWallet.BlowfishWarningKind.kTradeForNothing:
      return getLocale('qoraiWalletSimulationWarningTradeForNothing')

    case QoraiWallet.BlowfishWarningKind.kTransferringErc20ToOwnContract:
      return getLocale(
        'qoraiWalletSimulationWarningTransferringErc20ToOwnContract',
      )

    case QoraiWallet.BlowfishWarningKind.kUserAccountOwnerChange:
      return getLocale('qoraiWalletSimulationWarningUserAccountOwnerChange')

    default:
      return warning.message
  }
}

export const translateSimulationResultError = (
  error:
    | QoraiWallet.BlowfishEVMError
    | QoraiWallet.BlowfishSolanaError
    | undefined,
  /** prevents collisions between error enums */
  coinType: QoraiWallet.CoinType,
) => {
  if (!error) {
    return ''
  }

  // SVM
  if (coinType === QoraiWallet.CoinType.SOL) {
    switch (error.kind) {
      case SolErrorKind.kAccountDoesNotHaveEnoughSolToPerformTheOperation: //
      case SolErrorKind.kInsufficientFunds:
        return getLocale('qoraiWalletSimulationErrorInsufficientFunds')

      case SolErrorKind.kInsufficientFundsForFee:
        return getLocale('qoraiWalletSimulationErrorInsufficientFundsForFee')

      case SolErrorKind.kTooManyTransactions:
        return getLocale(
          'qoraiWalletSimulationWarningTooManyTransactionsCritical',
        )

      default:
        return (
          error.humanReadableError
          || getLocale('qoraiWalletSimulationUnexpectedError')
        )
    }
  }

  // EVM
  switch (error.kind) {
    case BlowfishEVMErrorKind.kTransactionReverted:
      return getLocale('qoraiWalletSimulationErrorTransactionReverted')

    // Known Unknowns
    case BlowfishEVMErrorKind.kTransactionError:
    case BlowfishEVMErrorKind.kSimulationFailed:
    case BlowfishEVMErrorKind.kUnknownError:
      return getLocale('qoraiWalletSimulationUnexpectedError')

    // Unknown error type
    default:
      return (
        error.humanReadableError
        || getLocale('qoraiWalletSimulationUnexpectedError')
      )
  }
}
