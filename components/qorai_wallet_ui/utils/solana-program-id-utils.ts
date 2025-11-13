// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

// types
import { QoraiWallet } from '../constants/types'

// utils
import { getLocale } from '$web-common/locale'

/**
 * see: https://docs.solana.com/developing/runtime-facilities/programs
 * @param programId Solana Program public key
 * @returns Name of program
 */
export const getSolanaProgramIdName = (programId: string): string => {
  switch (programId) {
    case QoraiWallet.SOLANA_SYSTEM_PROGRAM_ID:
      return getLocale('qoraiWalletSolanaSystemProgram')
    case QoraiWallet.SOLANA_CONFIG_PROGRAM_ID:
      return getLocale('qoraiWalletSolanaConfigProgram')
    case QoraiWallet.SOLANA_STAKE_PROGRAM_ID:
      return getLocale('qoraiWalletSolanaStakeProgram')
    case QoraiWallet.SOLANA_VOTE_PROGRAM_ID:
      return getLocale('qoraiWalletSolanaVoteProgram')
    case QoraiWallet.SOLANA_BPF_LOADER_UPGRADEABLE_PROGRAM_ID:
      return getLocale('qoraiWalletSolanaBPFLoader')
    case QoraiWallet.SOLANA_ED25519_SIG_VERIFY_PROGRAM_ID:
      return getLocale('qoraiWalletSolanaEd25519Program')
    case QoraiWallet.SOLANA_KECCAK_SECP256K_PROGRAM_ID:
      return getLocale('qoraiWalletSolanaSecp256k1Program')
    case QoraiWallet.SOLANA_ASSOCIATED_TOKEN_PROGRAM_ID:
      return getLocale('qoraiWalletSolanaAssociatedTokenProgram')
    case QoraiWallet.SOLANA_METADATA_PROGRAM_ID:
      return getLocale('qoraiWalletSolanaMetaDataProgram')
    case QoraiWallet.SOLANA_SYSVAR_RENT_PROGRAM_ID:
      return getLocale('qoraiWalletSolanaSysvarRentProgram')
    case QoraiWallet.SOLANA_TOKEN_PROGRAM_ID:
      return getLocale('qoraiWalletSolanaTokenProgram')
    default:
      return programId
  }
}
