/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_TEST_UTILS_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_TEST_UTILS_H_

#include <memory>
#include <string>
#include <vector>

#include "base/files/file_path.h"
#include "base/files/scoped_temp_dir.h"
#include "base/memory/scoped_refptr.h"
#include "base/test/test_future.h"
#include "qorai/components/qorai_wallet/browser/account_resolver_delegate.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_service.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_service_delegate.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "components/value_store/test_value_store_factory.h"
#include "components/value_store/value_store_frontend.h"

class PrefService;

namespace base {
class ScopedTempDir;
}  // namespace base

namespace qorai_wallet {

inline constexpr char kMnemonicDivideCruise[] =
    "divide cruise upon flag harsh carbon filter merit once advice bright "
    "drive";
inline constexpr char kMnemonicDripCaution[] =
    "drip caution abandon festival order clown oven regular absorb evidence "
    "crew where";
inline constexpr char kMnemonicScarePiece[] =
    "scare piece awesome elite long drift control cabbage glass dash coral "
    "angry";
// Mnemonic referenced in various bips.
// https://github.com/bitcoin/bips/blob/master/bip-0084.mediawiki#test-vectors
// https://github.com/bitcoin/bips/blob/master/bip-0049.mediawiki#test-vectors
inline constexpr char kMnemonicAbandonAbandon[] =
    "abandon abandon abandon abandon abandon abandon abandon abandon abandon "
    "abandon abandon about";
inline constexpr char kMnemonicGalleryEqual[] =
    "gallery equal segment repair outdoor bronze limb dawn daring main burst "
    "design palm demise develop exit cycle harbor motor runway turtle quote "
    "blast tail";
inline constexpr char kTestWalletPassword[] = "qorai";

class KeyringService;
class TxStorageDelegate;
class TxStorageDelegateImpl;

base::FilePath QoraiWalletComponentsTestDataFolder();
base::FilePath QoraiWalletTestDataFolder();

class AccountResolverDelegateForTest : public AccountResolverDelegate {
 public:
  AccountResolverDelegateForTest();
  ~AccountResolverDelegateForTest() override;

  mojom::AccountIdPtr RegisterAccount(mojom::AccountIdPtr account_id);

 protected:
  mojom::AccountIdPtr ResolveAccountId(
      const std::string* from_account_id,
      const std::string* from_address) override;
  bool ValidateAccountId(const mojom::AccountIdPtr& account_id) override;
  std::optional<std::string> ResolveAddress(
      const mojom::AccountIdPtr& account_id) override;

 private:
  std::vector<mojom::AccountIdPtr> accounts_;
};

class AccountUtils {
 public:
  explicit AccountUtils(KeyringService* keyring_service);

  void CreateWallet(const std::string& mnemonic, const std::string& password);

  mojom::AccountInfoPtr GetDerivedAccount(mojom::KeyringId keyring_id,
                                          uint32_t index);
  mojom::AccountInfoPtr CreateDerivedAccount(mojom::KeyringId keyring_id,
                                             const std::string& name);
  mojom::AccountInfoPtr GetImportedAccount(mojom::KeyringId keyring_id,
                                           uint32_t index);
  mojom::AccountInfoPtr GetHardwareAccount(mojom::KeyringId keyring_id,
                                           uint32_t index);
  mojom::AccountInfoPtr CreateImportedAccount(mojom::KeyringId keyring_id,
                                              const std::string& name);
  mojom::AccountInfoPtr CreateHardwareAccount(mojom::KeyringId keyring_id,
                                              const std::string& name);
  mojom::AccountInfoPtr EnsureAccount(mojom::KeyringId keyring_id,
                                      uint32_t index);

  mojom::AccountInfoPtr EthAccount(uint32_t index);
  mojom::AccountIdPtr EthAccountId(uint32_t index);
  mojom::AccountInfoPtr EthUnkownAccount();
  mojom::AccountIdPtr EthUnkownAccountId();

  mojom::AccountInfoPtr EnsureEthAccount(uint32_t index);
  mojom::AccountInfoPtr EnsureSolAccount(uint32_t index);
  mojom::AccountInfoPtr EnsureFilAccount(uint32_t index);
  mojom::AccountInfoPtr EnsureFilTestAccount(uint32_t index);
  mojom::AccountInfoPtr EnsureBtcAccount(uint32_t index);
  mojom::AccountInfoPtr EnsureBtcTestAccount(uint32_t index);
  mojom::AccountInfoPtr EnsureZecAccount(uint32_t index);
  mojom::AccountInfoPtr EnsureZecTestAccount(uint32_t index);
  mojom::AccountInfoPtr EnsureAdaAccount(uint32_t index);
  mojom::AccountInfoPtr EnsureAdaTestAccount(uint32_t index);

  mojom::AccountInfoPtr CreateEthAccount(const std::string& name);
  mojom::AccountInfoPtr CreateSolAccount(const std::string& name);
  mojom::AccountInfoPtr CreateFilAccount(const std::string& name);
  mojom::AccountInfoPtr CreateFilTestAccount(const std::string& name);
  mojom::AccountInfoPtr CreateBtcAccount(const std::string& name);
  mojom::AccountInfoPtr CreateBtcTestAccount(const std::string& name);
  mojom::AccountInfoPtr CreateZecAccount(const std::string& name);
  mojom::AccountInfoPtr CreateZecTestAccount(const std::string& name);
  mojom::AccountInfoPtr CreateAdaAccount(const std::string& name);
  mojom::AccountInfoPtr CreateAdaTestAccount(const std::string& name);

  mojom::AccountInfoPtr CreateEthHWAccount();
  mojom::AccountInfoPtr CreateBtcHWAccount();

  mojom::AccountIdPtr FindAccountIdByAddress(const std::string& address);

  std::vector<mojom::AccountInfoPtr> AllAccounts(mojom::KeyringId keyring_id);
  std::vector<mojom::AccountInfoPtr> AllAccounts(
      const std::vector<mojom::KeyringId>& keyring_ids);
  std::vector<mojom::AccountInfoPtr> AllEthAccounts();
  std::vector<mojom::AccountInfoPtr> AllSolAccounts();
  std::vector<mojom::AccountInfoPtr> AllFilAccounts();
  std::vector<mojom::AccountInfoPtr> AllFilTestAccounts();
  std::vector<mojom::AccountInfoPtr> AllBtcAccounts();
  std::vector<mojom::AccountInfoPtr> AllBtcTestAccounts();
  std::vector<mojom::AccountInfoPtr> AllZecAccounts();
  std::vector<mojom::AccountInfoPtr> AllZecTestAccounts();
  std::vector<mojom::AccountInfoPtr> AllAdaAccounts();
  std::vector<mojom::AccountInfoPtr> AllAdaTestAccounts();

 private:
  raw_ptr<KeyringService> keyring_service_;
};

class TestQoraiWalletServiceDelegate : public QoraiWalletServiceDelegate {
 public:
  TestQoraiWalletServiceDelegate();

  base::FilePath GetWalletBaseDirectory() override;
  bool IsPrivateWindow() override;

  static std::unique_ptr<QoraiWalletServiceDelegate> Create();

 private:
  base::ScopedTempDir temp_dir_;
};

void WaitForTxStorageDelegateInitialized(TxStorageDelegate* delegate);

scoped_refptr<value_store::TestValueStoreFactory> GetTestValueStoreFactory(
    base::ScopedTempDir& temp_dir);

std::unique_ptr<TxStorageDelegateImpl> GetTxStorageDelegateForTest(
    PrefService* prefs,
    scoped_refptr<value_store::ValueStoreFactory> store_factory);

// Helper class to mock QoraiWalletService::AddSignMessageRequest and
// QoraiWalletService::NotifySignMessageRequestProcessed methods.
class SignMessageRequestWaiter {
 public:
  explicit SignMessageRequestWaiter(QoraiWalletService* qorai_wallet_service);
  ~SignMessageRequestWaiter();

  void WaitAndProcess(bool approved);

 private:
  void OnSignMessageRequestAdded();

  raw_ptr<QoraiWalletService> qorai_wallet_service_;
  base::CallbackListSubscription subscription_;
  base::test::TestFuture<int> future_;
};

// Helper class to mock QoraiWalletService::AddSignTransactionRequest and
// QoraiWalletService::NotifySignMessageRequestProcessed methods.
class SignCardanoTransactionRequestWaiter {
 public:
  explicit SignCardanoTransactionRequestWaiter(
      QoraiWalletService* qorai_wallet_service);
  ~SignCardanoTransactionRequestWaiter();

  mojom::SignCardanoTransactionRequestPtr WaitAndProcess(bool approved);

 private:
  void OnSignTransactionRequestAdded();

  raw_ptr<QoraiWalletService> qorai_wallet_service_;
  base::CallbackListSubscription subscription_;
  base::test::TestFuture<mojom::SignCardanoTransactionRequestPtr> future_;
};

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_TEST_UTILS_H_
