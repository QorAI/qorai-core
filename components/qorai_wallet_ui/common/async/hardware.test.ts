/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import { QoraiWallet, emptyProviderErrorCodeUnion } from '../../constants/types'
import {
  signTrezorTransaction,
  signLedgerEthereumTransaction,
  signLedgerFilecoinTransaction,
  signLedgerSolanaTransaction,
} from './hardware'
import WalletApiProxy from '../wallet_api_proxy'
import { getLocale } from '../../../common/locale'
import { getMockedTransactionInfo } from '../constants/mocks'
import {
  HardwareOperationError,
  HardwareOperationResult,
  HardwareOperationResultEthereumSignatureVRS,
  HardwareOperationResultFilecoinSignature,
  HardwareOperationResultSolanaSignature,
} from '../hardware/types'
import LedgerBridgeKeyring from '../hardware/ledgerjs/eth_ledger_bridge_keyring'
import TrezorBridgeKeyring from '../hardware/trezor/trezor_bridge_keyring'
import FilecoinLedgerBridgeKeyring from '../hardware/ledgerjs/fil_ledger_bridge_keyring'
import SolanaLedgerBridgeKeyring from '../hardware/ledgerjs/sol_ledger_bridge_keyring'

const mockEthereumSignatureVRS: QoraiWallet.EthereumSignatureVRS = {
  vBytes: [1],
  rBytes: [2, 3],
  sBytes: [4, 5, 6],
}

const getMockedLedgerEthKeyring = (args: {
  expectedPath: string
  expectedData: string | QoraiWallet.TransactionInfo
  mockSignature?: QoraiWallet.EthereumSignatureVRS
}) => {
  return {
    signTransaction: async (
      path: string,
      data: string,
    ): Promise<HardwareOperationResultEthereumSignatureVRS> => {
      expect(path).toStrictEqual(args.expectedPath)
      expect(data).toStrictEqual(args.expectedData)
      if (args.mockSignature) {
        return {
          success: true,
          signature: args.mockSignature,
        }
      } else {
        return {
          success: false,
          error: 'qoraiWalletSignOnDeviceError',
          code: undefined,
        }
      }
    },
  }
}

const getMockedLedgerFilKeyring = (args: {
  expectedMessage: string
  mockSignature?: QoraiWallet.FilecoinSignature
}) => {
  return {
    type: (): QoraiWallet.HardwareVendor => {
      return QoraiWallet.HardwareVendor.kLedger
    },
    signTransaction: async (
      message: string,
    ): Promise<HardwareOperationResultFilecoinSignature> => {
      expect(message).toStrictEqual(args.expectedMessage)
      if (args.mockSignature) {
        return {
          success: true,
          signature: args.mockSignature,
        }
      }
      return {
        success: false,
        error: 'qoraiWalletSignOnDeviceError',
        code: undefined,
      }
    },
  }
}

const getMockedLedgerSolKeyring = (args: {
  expectedMessage: Buffer
  mockSignature?: QoraiWallet.SolanaSignature
}) => {
  return {
    signTransaction: async (
      path: string,
      message: Buffer,
    ): Promise<HardwareOperationResultSolanaSignature> => {
      expect(message).toStrictEqual(args.expectedMessage)
      if (args.mockSignature) {
        return { success: true, signature: args.mockSignature }
      }
      return {
        success: false,
        error: 'qoraiWalletSignOnDeviceError',
        code: undefined,
      }
    },
  }
}

const getMockedTrezorKeyring = (args: {
  expectedDevicePath: string
  expectedEthTxData1559: QoraiWallet.TxData1559
  mockSignature?: QoraiWallet.EthereumSignatureVRS
  mockHardwareOperationError?: HardwareOperationError
}) => {
  return {
    signTransaction: async (
      path: string,
      txid: string,
      ethTxData1559: QoraiWallet.TxData1559,
      chainId: string,
    ): Promise<HardwareOperationResultEthereumSignatureVRS> => {
      expect(path).toStrictEqual(args.expectedDevicePath)
      if (args.mockSignature) {
        return { success: true, signature: args.mockSignature }
      } else if (args.mockHardwareOperationError) {
        return args.mockHardwareOperationError
      } else {
        return {
          success: false,
          error: 'qoraiWalletSignOnDeviceError',
          code: undefined,
        }
      }
    },
  }
}

const getMockedProxyServices = (args: {
  expectedChainId: string
  expectedId: string
  nonce?: string
  ethMessageToSign?: string
  solMessageToSign?: Buffer
  filMessageToSign?: string | undefined
  btcMessageToSign?: Buffer
  processHardwareSignatureResult?: boolean
  expectedEthereumSignatureVRS?: QoraiWallet.EthereumSignatureVRS
  expectedFilSignedTransaction?: QoraiWallet.FilecoinSignature
  expectedBtcSignedTransaction?: QoraiWallet.BitcoinSignature
  expectedSolSignature?: QoraiWallet.SolanaSignature
}) => {
  return {
    jsonRpcService: {
      getChainId: async () => {
        return '0x123'
      },
    },
    ethTxManagerProxy: {
      getEthTransactionMessageToSign: (id: string) => {
        expect(id).toStrictEqual(args.expectedId)
        return Promise.resolve({ hexMessage: args.ethMessageToSign ?? null })
      },
      getNonceForHardwareTransaction: (id: string) => {
        expect(id).toStrictEqual(args.expectedId)
        return Promise.resolve({ nonce: args.nonce ?? null })
      },
      processEthHardwareSignature: (
        id: string,
        hwSignature: QoraiWallet.EthereumSignatureVRS,
      ) => {
        expect(id).toStrictEqual(args.expectedId)
        expect(hwSignature).toStrictEqual(args.expectedEthereumSignatureVRS)
        return Promise.resolve({
          status: !!args.processHardwareSignatureResult,
          error: 0,
          errorMessage: '',
        })
      },
    },
    filTxManagerProxy: {
      getFilTransactionMessageToSign: (id: string) => {
        expect(id).toStrictEqual(args.expectedId)
        return Promise.resolve({ jsonMessage: args.filMessageToSign! })
      },
      processFilHardwareSignature: (
        id: string,
        hwSignature: QoraiWallet.FilecoinSignature,
      ) => {
        expect(id).toStrictEqual(args.expectedId)
        expect(hwSignature).toStrictEqual(args.expectedFilSignedTransaction)
        return Promise.resolve({
          status: !!args.processHardwareSignatureResult,
          errorUnion: emptyProviderErrorCodeUnion,
          errorMessage: '',
        })
      },
    },
    btcTxManagerProxy: {
      getBtcTransactionMessageToSign: (id: string) => {
        expect(id).toStrictEqual(args.expectedId)
        return Promise.resolve({ jsonMessage: args.btcMessageToSign! })
      },
      processBtcHardwareSignature: (
        id: string,
        hwSignature: QoraiWallet.BitcoinSignature,
      ) => {
        expect(id).toStrictEqual(args.expectedId)
        expect(hwSignature).toStrictEqual(args.expectedBtcSignedTransaction)
        return Promise.resolve({
          status: !!args.processHardwareSignatureResult,
          errorUnion: emptyProviderErrorCodeUnion,
          errorMessage: '',
        })
      },
    },
    solanaTxManagerProxy: {
      getSolTransactionMessageToSign: (id: string) => {
        expect(id).toStrictEqual(args.expectedId)
        return Promise.resolve({ message: [...args.solMessageToSign!] })
      },
      processSolanaHardwareSignature: (
        id: string,
        signature: QoraiWallet.SolanaSignature,
      ) => {
        expect(id).toStrictEqual(args.expectedId)
        expect(signature).toStrictEqual(args.expectedSolSignature)
        return Promise.resolve({
          status: !!args.processHardwareSignatureResult,
          errorUnion: emptyProviderErrorCodeUnion,
          errorMessage: '',
        })
      },
    },
  }
}

const signEthTransactionWithLedger = (args?: {
  mockSignature?: QoraiWallet.EthereumSignatureVRS
  processHardwareSignatureResult?: boolean
}): Promise<HardwareOperationResult> => {
  const txInfo = getMockedTransactionInfo()
  const expectedData = 'raw_message_to_sign'
  const messageToSign = expectedData

  const expectedPath = 'path'
  const mockedKeyring = getMockedLedgerEthKeyring({
    expectedPath,
    expectedData,
    mockSignature: args?.mockSignature,
  })
  const apiProxy = getMockedProxyServices({
    expectedChainId: txInfo.chainId,
    expectedId: txInfo.id,
    nonce: '0x1',
    ethMessageToSign: messageToSign,
    expectedEthereumSignatureVRS: args?.mockSignature,
    processHardwareSignatureResult: args?.processHardwareSignatureResult,
  })
  return signLedgerEthereumTransaction(
    apiProxy as unknown as WalletApiProxy,
    expectedPath,
    txInfo.id,
    mockedKeyring as unknown as LedgerBridgeKeyring,
  )
}

const signSolTransactionWithLedger = (args: {
  mockSignature: QoraiWallet.SolanaSignature
  processHardwareSignatureResult?: boolean
}): Promise<HardwareOperationResult> => {
  const txInfo = getMockedTransactionInfo()
  const expectedData = Buffer.from('raw_message_to_sign')
  const expectedPath = 'path'
  const messageToSign = [...expectedData]
  const mockedKeyring = getMockedLedgerSolKeyring({
    expectedMessage: expectedData,
    mockSignature: args.mockSignature,
  })
  const apiProxy = getMockedProxyServices({
    expectedChainId: txInfo.chainId,
    expectedId: txInfo.id,
    solMessageToSign: Buffer.from(messageToSign),
    processHardwareSignatureResult: args.processHardwareSignatureResult,
    expectedSolSignature: args.mockSignature,
  })
  return signLedgerSolanaTransaction(
    apiProxy as unknown as WalletApiProxy,
    expectedPath,
    txInfo.id,
    mockedKeyring as unknown as SolanaLedgerBridgeKeyring,
  )
}

const signFilTransactionWithLedger = (args: {
  mockSignature: QoraiWallet.FilecoinSignature
  processHardwareSignatureResult?: boolean
}): Promise<HardwareOperationResult> => {
  const txInfo = getMockedTransactionInfo()
  const expectedData = 'raw_message_to_sign'
  const messageToSign = expectedData
  const mockedKeyring = getMockedLedgerFilKeyring({
    expectedMessage: expectedData,
    mockSignature: args.mockSignature,
  })
  const apiProxy = getMockedProxyServices({
    expectedChainId: txInfo.chainId,
    expectedId: txInfo.id,
    filMessageToSign: messageToSign,
    processHardwareSignatureResult: args.processHardwareSignatureResult,
    expectedFilSignedTransaction: args.mockSignature,
  })
  return signLedgerFilecoinTransaction(
    apiProxy as unknown as WalletApiProxy,
    txInfo.id,
    mockedKeyring as unknown as FilecoinLedgerBridgeKeyring,
  )
}

const hardwareTransactionErrorResponse = (
  errorId: string,
  code: string | undefined = undefined,
): HardwareOperationError => {
  return { success: false, error: getLocale(errorId), code }
}
const hardwareTransactionErrorResponseWithCode = (
  errorId: string,
  code: string = '',
): HardwareOperationError => {
  return { success: false, error: getLocale(errorId), code: code }
}
const signTransactionWithTrezor = (args: {
  mockSignature?: QoraiWallet.EthereumSignatureVRS
  mockHardwareOperationError?: HardwareOperationError
  processHardwareSignatureResult?: boolean
}) => {
  const txInfo = getMockedTransactionInfo()
  const expectedPath = 'path'
  const mockedKeyring = getMockedTrezorKeyring({
    expectedDevicePath: expectedPath,
    expectedEthTxData1559: txInfo.txDataUnion.ethTxData1559,
    mockSignature: args.mockSignature,
    mockHardwareOperationError: args.mockHardwareOperationError,
  })
  const apiProxy = getMockedProxyServices({
    expectedChainId: txInfo.chainId,
    expectedId: txInfo.id,
    nonce: '0x03',
    expectedEthereumSignatureVRS: args.mockSignature,
    processHardwareSignatureResult: args.processHardwareSignatureResult,
  })
  return signTrezorTransaction(
    apiProxy as unknown as WalletApiProxy,
    expectedPath,
    txInfo,
    mockedKeyring as unknown as TrezorBridgeKeyring,
  )
}

test('Test sign Ledger transaction, approved, no message to sign', () => {
  const txInfo = getMockedTransactionInfo()
  const apiProxy = getMockedProxyServices({
    expectedChainId: txInfo.chainId,
    expectedId: txInfo.id,
    nonce: '0x1',
  })
  return expect(
    signLedgerEthereumTransaction(
      apiProxy as unknown as WalletApiProxy,
      'path',
      txInfo.id,
    ),
  ).resolves.toStrictEqual(
    hardwareTransactionErrorResponse('qoraiWalletNoMessageToSignError'),
  )
})

test('Test sign Ledger transaction, approved, device error', () => {
  return expect(signEthTransactionWithLedger()).resolves.toStrictEqual(
    hardwareTransactionErrorResponseWithCode('qoraiWalletSignOnDeviceError'),
  )
})

test('Test sign Ledger transaction, approved, processing error', () => {
  return expect(
    signEthTransactionWithLedger({
      mockSignature: mockEthereumSignatureVRS,
    }),
  ).resolves.toStrictEqual(
    hardwareTransactionErrorResponse('qoraiWalletProcessTransactionError'),
  )
})

test('Test sign Ledger transaction, approved, processed', () => {
  return expect(
    signEthTransactionWithLedger({
      mockSignature: mockEthereumSignatureVRS,
      processHardwareSignatureResult: true,
    }),
  ).resolves.toStrictEqual({ success: true })
})

test('Test sign Trezor transaction, approve failed', () => {
  const txInfo = getMockedTransactionInfo()
  const apiProxy = getMockedProxyServices({
    expectedChainId: txInfo.chainId,
    expectedId: txInfo.id,
    nonce: '',
  })
  return expect(
    signTrezorTransaction(
      apiProxy as unknown as WalletApiProxy,
      'path',
      txInfo,
    ),
  ).resolves.toStrictEqual(
    hardwareTransactionErrorResponse('qoraiWalletApproveTransactionError'),
  )
})

test('Test sign Trezor transaction, approved, device error', () => {
  return expect(
    signTransactionWithTrezor({
      mockHardwareOperationError: {
        success: false,
        error: 'error',
        code: '111',
      },
    }),
  ).resolves.toStrictEqual({
    success: false,
    error: 'error',
    code: '111',
  })
})

test('Test sign Trezor transaction, approved, generic device error', () => {
  return expect(
    signTransactionWithTrezor({
      mockHardwareOperationError: {
        success: false,
        error: 'qoraiWalletSignOnDeviceError',
        code: undefined,
      },
    }),
  ).resolves.toStrictEqual(
    hardwareTransactionErrorResponse('qoraiWalletSignOnDeviceError'),
  )
})

test('Test sign Trezor transaction, approved, processing error', () => {
  return expect(
    signTransactionWithTrezor({
      mockSignature: mockEthereumSignatureVRS,
      processHardwareSignatureResult: false,
    }),
  ).resolves.toStrictEqual(
    hardwareTransactionErrorResponse('qoraiWalletProcessTransactionError'),
  )
})

test('Test sign Trezor transaction, approved, processed', () => {
  return expect(
    signTransactionWithTrezor({
      mockSignature: mockEthereumSignatureVRS,
      processHardwareSignatureResult: true,
    }),
  ).resolves.toStrictEqual({ success: true })
})

test('Test sign Ledger FIL transaction, signed', () => {
  const message = {
    'From': 't1h4n7rphclbmwyjcp6jrdiwlfcuwbroxy3jvg33q',
    'GasFeeCap': '3',
    'GasLimit': 4,
    'GasPremium': '2',
    'Method': 0,
    'Nonce': 1,
    'Params': '',
    'To': 't1lqarsh4nkg545ilaoqdsbtj4uofplt6sto26ziy',
    'Value': '11',
  }
  const expectedSignature = {
    Message: message,
    Signature: {
      Type: 1,
      Data: 'signed',
    },
  }

  return expect(
    signFilTransactionWithLedger({
      mockSignature: {
        signedMessageJson: JSON.stringify(expectedSignature),
      },
      processHardwareSignatureResult: true,
    }),
  ).resolves.toStrictEqual({ success: true })
})

test('Test sign Ledger SOL transaction, signed', () => {
  const expectedSignature = Buffer.from('signature')
  return expect(
    signSolTransactionWithLedger({
      mockSignature: {
        bytes: [...expectedSignature],
      },
      processHardwareSignatureResult: true,
    }),
  ).resolves.toStrictEqual({ success: true })
})
