// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import {
  AddressMessageInfoIds,
  AddressMessageInfo,
} from '../../../constants/types'

export const ENSOffchainLookupMessage: AddressMessageInfo = {
  title: 'qoraiWalletEnsOffChainLookupTitle',
  description: 'qoraiWalletEnsOffChainLookupDescription',
  url: 'https://github.com/qorai/qorai-browser/wiki/ENS-offchain-lookup',
  id: AddressMessageInfoIds.ensOffchainLookupWarning,
  type: 'info',
}

export const HasNoDomainAddressMessage: AddressMessageInfo = {
  title: '',
  description: 'qoraiWalletNotDomain',
  id: AddressMessageInfoIds.hasNoDomainAddress,
  type: 'error',
}

export const FailedChecksumMessage: AddressMessageInfo = {
  title: 'qoraiWalletFailedChecksumTitle',
  description: 'qoraiWalletFailedChecksumDescription',
  type: 'error',
  id: AddressMessageInfoIds.invalidChecksumError,
}

export const MissingChecksumMessage: AddressMessageInfo = {
  title: 'qoraiWalletFailedChecksumTitle',
  description: 'qoraiWalletFailedChecksumDescription',
  type: 'warning',
  id: AddressMessageInfoIds.missingChecksumWarning,
}

export const FEVMAddressConversionMessage: AddressMessageInfo = {
  title: 'qoraiWalletFEVMAddressTranslationTitle',
  description: 'qoraiWalletFEVMAddressTranslationDescription',
  url: 'https://docs.filecoin.io/smart-contracts/filecoin-evm-runtime/address-types/',
  type: 'warning',
  id: AddressMessageInfoIds.FEVMTranslationWarning,
}

export const InvalidAddressMessage: AddressMessageInfo = {
  title: '',
  description: 'qoraiWalletNotValidAddress',
  type: 'error',
  id: AddressMessageInfoIds.invalidAddressError,
}

export const SameAddressMessage: AddressMessageInfo = {
  title: '',
  description: 'qoraiWalletSameAddressError',
  type: 'error',
  id: AddressMessageInfoIds.sameAddressError,
}

export const ContractAddressMessage: AddressMessageInfo = {
  title: '',
  description: 'qoraiWalletContractAddressError',
  type: 'error',
  id: AddressMessageInfoIds.contractAddressError,
}

export const InvalidDomainExtensionMessage: AddressMessageInfo = {
  title: '',
  description: 'qoraiWalletInvalidDomainExtension',
  type: 'error',
  id: AddressMessageInfoIds.invalidDomainExtension,
}

// ZCash
export const ZCashInvalidTransparentAddressErrorMessage: AddressMessageInfo = {
  title: '',
  description: 'qoraiWalletZCashInvalidTransparentAddress',
  type: 'error',
  id: AddressMessageInfoIds.zcashInvalidTransparentAddressError,
}

export const ZCashInvalidUnifiedAddressErrorMessage: AddressMessageInfo = {
  title: '',
  description: 'qoraiWalletZCashInvalidUnifiedAddress',
  type: 'error',
  id: AddressMessageInfoIds.zcashInvalidUnifiedAddressError,
}

// eslint-disable-next-line max-len
export const ZCashInvalidUnifiedAddressMissingOrchardPartErrorMessage: AddressMessageInfo =
  {
    title: '',
    description: 'qoraiWalletZCashInvalidUnifiedAddressMissingOrchardPart',
    type: 'error',
    id: AddressMessageInfoIds.zcashInvalidUnifiedAddressMissingOrchardPartError,
  }

// eslint-disable-next-line max-len
export const ZCashInvalidUnifiedAddressMissingTransparentPartErrorMessage: AddressMessageInfo =
  {
    title: '',
    description: 'qoraiWalletZCashInvalidUnifiedAddressMissingTransparentPart',
    type: 'error',
    // eslint-disable-next-line max-len
    id: AddressMessageInfoIds.zcashInvalidUnifiedAddressMissingTransparentPartError,
  }

// eslint-disable-next-line max-len
export const ZCashInvalidAddressNetworkMismatchErrorMessage: AddressMessageInfo =
  {
    title: '',
    description: 'qoraiWalletZCashInvalidAddressNetworkMismatch',
    type: 'error',
    id: AddressMessageInfoIds.zcashInvalidAddressNetworkMismatchError,
  }

export const AddressValidationMessages = [
  ENSOffchainLookupMessage,
  HasNoDomainAddressMessage,
  FailedChecksumMessage,
  MissingChecksumMessage,
  FEVMAddressConversionMessage,
  InvalidAddressMessage,
  SameAddressMessage,
  ContractAddressMessage,
  InvalidDomainExtensionMessage,
  ZCashInvalidTransparentAddressErrorMessage,
  ZCashInvalidUnifiedAddressErrorMessage,
  ZCashInvalidUnifiedAddressMissingOrchardPartErrorMessage,
  ZCashInvalidUnifiedAddressMissingTransparentPartErrorMessage,
  ZCashInvalidAddressNetworkMismatchErrorMessage,
]
