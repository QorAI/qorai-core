// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'

// Types
import { QoraiWallet } from '../../../constants/types'
import { ParsedTransaction } from '../../../utils/tx-utils'

// utils
import Amount from '../../../utils/amount'
import { getLocale } from '../../../../common/locale'

// hooks
import {
  useGetDefaultFiatCurrencyQuery, //
} from '../../../common/slices/api.slice'

// style
import {
  TransactionTitle,
  TransactionTypeText,
  TransactionText,
  Divider,
  SectionRow,
  SectionColumn,
  EditButton,
} from './style'
import { WarningBoxTitleRow } from '../shared-panel-styles'
import { Skeleton } from '../../shared/loading-skeleton/styles'
import { Column } from '../../shared/style'

interface TransactionInfoProps {
  onToggleEditGas?: () => void
  transactionDetails: ParsedTransaction | undefined
  isZCashTransaction: boolean
  isBitcoinTransaction: boolean
  isERC721SafeTransferFrom: boolean
  isERC721TransferFrom: boolean
  transactionsNetwork: QoraiWallet.NetworkInfo | undefined
  hasFeeEstimatesError: boolean
  isLoadingGasFee: boolean
  gasFee: string
  insufficientFundsError: boolean
  insufficientFundsForGasError: boolean

  // ERC20 Approve
  isERC20Approve?: boolean
  currentTokenAllowance?: string
  isCurrentAllowanceUnlimited?: boolean
}

export const TransactionInfo = ({
  onToggleEditGas,
  transactionDetails,
  isERC721SafeTransferFrom,
  isERC721TransferFrom,
  transactionsNetwork,
  hasFeeEstimatesError,
  isLoadingGasFee,
  gasFee,
  insufficientFundsError,
  insufficientFundsForGasError,
  isZCashTransaction,
  isBitcoinTransaction,
  isERC20Approve,
  isCurrentAllowanceUnlimited,
  currentTokenAllowance,
}: TransactionInfoProps) => {
  // queries
  const {
    isLoading: isLoadingDefaultFiatCurrency,
    data: defaultFiatCurrency = 'usd',
  } = useGetDefaultFiatCurrencyQuery()

  // exit early if no details
  if (!transactionDetails) {
    return null
  }

  const isLoadingGasFeeFiat = isLoadingDefaultFiatCurrency || isLoadingGasFee

  const { isSolanaTransaction, isFilecoinTransaction, isCardanoTransaction } =
    transactionDetails
  const feeLocale =
    isSolanaTransaction
    || isZCashTransaction
    || isBitcoinTransaction
    || isCardanoTransaction
      ? 'qoraiWalletConfirmTransactionTransactionFee'
      : 'qoraiWalletConfirmTransactionGasFee'

  const memoText = String.fromCharCode(...(transactionDetails.zcashMemo ?? []))

  // render
  return (
    <>
      {isFilecoinTransaction ? (
        <>
          {transactionDetails.gasPremium && (
            <SectionColumn>
              <TransactionTitle>
                {getLocale('qoraiWalletTransactionGasPremium')}
              </TransactionTitle>
              <TransactionTypeText>
                {transactionsNetwork
                  && new Amount(transactionDetails.gasPremium)
                    .divideByDecimals(transactionsNetwork.decimals)
                    .formatAsAsset(6, transactionsNetwork.symbol)}
              </TransactionTypeText>
            </SectionColumn>
          )}

          {transactionDetails.gasLimit && (
            <SectionColumn>
              <TransactionTitle>
                {getLocale('qoraiWalletTransactionGasLimit')}
              </TransactionTitle>
              <TransactionTypeText>
                {transactionsNetwork
                  && new Amount(transactionDetails.gasLimit)
                    .divideByDecimals(transactionsNetwork.decimals)
                    .formatAsAsset(6, transactionsNetwork.symbol)}
              </TransactionTypeText>
            </SectionColumn>
          )}

          {transactionDetails.gasFeeCap && (
            <SectionColumn>
              <TransactionTitle>
                {getLocale('qoraiWalletTransactionGasFeeCap')}
              </TransactionTitle>
              <TransactionTypeText>
                {transactionsNetwork
                  && new Amount(transactionDetails.gasFeeCap)
                    .divideByDecimals(transactionsNetwork.decimals)
                    .formatAsAsset(6, transactionsNetwork.symbol)}
              </TransactionTypeText>
            </SectionColumn>
          )}
        </>
      ) : (
        <SectionRow>
          <TransactionTitle>
            {getLocale(
              isERC20Approve
                ? 'qoraiWalletAllowSpendTransactionFee'
                : feeLocale,
            )}
          </TransactionTitle>

          {onToggleEditGas && (
            <EditButton onClick={onToggleEditGas}>
              {getLocale('qoraiWalletAllowSpendEditButton')}
            </EditButton>
          )}
        </SectionRow>
      )}

      {hasFeeEstimatesError ? (
        <TransactionText hasError={true}>
          {getLocale('qoraiWalletTransactionHasFeeEstimatesError')}
        </TransactionText>
      ) : isLoadingGasFee ? (
        <FeeSkeleton />
      ) : (
        <TransactionTypeText>
          {(transactionsNetwork
            && new Amount(gasFee)
              .divideByDecimals(transactionsNetwork.decimals)
              .formatAsAsset(6, transactionsNetwork.symbol))
            || ''}
        </TransactionTypeText>
      )}

      {hasFeeEstimatesError ? null : isLoadingGasFeeFiat ? (
        <FeeSkeleton />
      ) : (
        <TransactionText>
          {new Amount(transactionDetails.gasFeeFiat).formatAsFiat(
            defaultFiatCurrency,
          )}
        </TransactionText>
      )}

      {/* TODO: ERC allowance checks */}

      {!isERC20Approve && (
        <>
          <Divider />

          <WarningBoxTitleRow>
            <TransactionTitle>
              {getLocale('qoraiWalletConfirmTransactionTotal')}{' '}
              {!isFilecoinTransaction && getLocale(feeLocale)}
            </TransactionTitle>
          </WarningBoxTitleRow>
          <TransactionValue
            isErc721Transfer={isERC721SafeTransferFrom || isERC721TransferFrom}
            symbol={transactionDetails.symbol}
            valueExact={transactionDetails.valueExact}
          />

          {isFilecoinTransaction ? null : hasFeeEstimatesError ? (
            <TransactionText hasError>
              {getLocale('qoraiWalletTransactionHasFeeEstimatesError')}
            </TransactionText>
          ) : isLoadingGasFee ? (
            <FeeSkeleton />
          ) : (
            <TransactionTypeText>
              +{' '}
              {transactionsNetwork
                && new Amount(gasFee)
                  .divideByDecimals(transactionsNetwork.decimals)
                  .formatAsAsset(6, transactionsNetwork.symbol)}
            </TransactionTypeText>
          )}

          {hasFeeEstimatesError ? null : isLoadingGasFeeFiat ? (
            <FeeSkeleton />
          ) : (
            <TransactionText>
              {new Amount(transactionDetails.fiatTotal).formatAsFiat(
                defaultFiatCurrency,
              )}
            </TransactionText>
          )}
        </>
      )}

      {insufficientFundsForGasError && (
        <TransactionText hasError={true}>
          {getLocale('qoraiWalletSwapInsufficientFundsForGas')}
        </TransactionText>
      )}
      {!insufficientFundsForGasError && insufficientFundsError && (
        <TransactionText hasError={true}>
          {getLocale('qoraiWalletSwapInsufficientBalance')}
        </TransactionText>
      )}

      {isERC20Approve && (
        <>
          <Divider />

          <TransactionTitle>
            {getLocale('qoraiWalletAllowSpendCurrentAllowance')}
          </TransactionTitle>
          <TransactionTypeText>
            {isCurrentAllowanceUnlimited
              ? getLocale('qoraiWalletTransactionApproveUnlimited')
              : currentTokenAllowance}{' '}
            {transactionDetails.symbol}
          </TransactionTypeText>

          <Divider />

          <TransactionTitle>
            {getLocale('qoraiWalletAllowSpendProposedAllowance')}
          </TransactionTitle>
          <TransactionTypeText>
            {transactionDetails.isApprovalUnlimited
              ? getLocale('qoraiWalletTransactionApproveUnlimited')
              : new Amount(transactionDetails.valueExact).formatAsAsset(
                  undefined,
                  transactionDetails.symbol,
                )}
          </TransactionTypeText>
        </>
      )}

      {memoText && (
        <SectionColumn>
          <Divider />
          <TransactionTitle>{getLocale('qoraiWalletMemo')}</TransactionTitle>
          <TransactionTypeText>{memoText}</TransactionTypeText>
        </SectionColumn>
      )}
    </>
  )
}

const FeeSkeleton = () => {
  return (
    <Column
      fullHeight
      fullWidth
      alignItems={'flex-start'}
      justifyContent='flex-start'
    >
      <Skeleton
        width={'40px'}
        height={'12px'}
        enableAnimation
      />
    </Column>
  )
}

const TransactionValue = ({
  isErc721Transfer,
  symbol,
  valueExact,
}: {
  isErc721Transfer: boolean
  valueExact: string
  symbol: string
}) => {
  /**
   * This will need updating if we ever switch to using per-locale formatting,
   * since `.` isn't always the decimal separator
   */
  const transactionValueParts = (
    isErc721Transfer
      ? valueExact
      : new Amount(valueExact).format(undefined, true)
  ).split('.')

  /**
   * Inserts a <wbr /> tag between the integer and decimal portions of the value
   * for wrapping
   * This will need updating if we ever switch to using per-locale formatting
   */
  const transactionValueText = (
    <span>
      {transactionValueParts.map((part, i, { length }) => [
        part,
        ...(i < length - 1 ? ['.'] : []),
        <wbr key={part} />,
      ])}
    </span>
  )

  // render
  return (
    <TransactionTypeText>
      {transactionValueText} {symbol}
    </TransactionTypeText>
  )
}
