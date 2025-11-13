// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

// constants
import { QoraiWallet } from '../../constants/types'

export const dappRadarChainNamesToChainIdMapping: Record<string, string> = {
  'aleph-zero': '', // NOT SUPPORTED
  'algorand': '', // NOT SUPPORTED
  'aptos': '', // NOT SUPPORTED
  'arbitrum': QoraiWallet.ARBITRUM_MAINNET_CHAIN_ID,
  'astar': QoraiWallet.ASTAR_CHAIN_ID,
  'astar-zkevm': QoraiWallet.ASTAR_ZK_EVM_CHAIN_ID,
  'aurora': QoraiWallet.AURORA_MAINNET_CHAIN_ID,
  'avalanche': QoraiWallet.AVALANCHE_MAINNET_CHAIN_ID,
  'bahamut': QoraiWallet.BAHAMUT_CHAIN_ID,
  'base': QoraiWallet.BASE_MAINNET_CHAIN_ID,
  'blast': QoraiWallet.BLAST_MAINNET_CHAIN_ID,
  'bnb-chain': QoraiWallet.BNB_SMART_CHAIN_MAINNET_CHAIN_ID,
  'bttc': QoraiWallet.BIT_TORRENT_CHAIN_MAINNET_CHAIN_ID,
  'cardano': '', // NOT SUPPORTED
  'celo': QoraiWallet.CELO_MAINNET_CHAIN_ID,
  'chromia': '', // NOT SUPPORTED
  'core': QoraiWallet.CORE_CHAIN_ID,
  'cronos': QoraiWallet.CRONOS_MAINNET_CHAIN_ID,
  'cyber': QoraiWallet.CYBER_MAINNET_CHAIN_ID,
  'defikingdoms': '', // NOT SUPPORTED
  'elysium': QoraiWallet.ELYSIUM_MAINNET_CHAIN_ID,
  'eos': '', // NOT SUPPORTED
  'eosevm': QoraiWallet.EOSEVM_NETWORK_CHAIN_ID,
  'ethereum': QoraiWallet.MAINNET_CHAIN_ID,
  'fantom': QoraiWallet.FANTOM_MAINNET_CHAIN_ID,
  'fio': '', // NOT SUPPORTED
  'flow': '', // NOT SUPPORTED
  'hedera': QoraiWallet.HEDERA_MAINNET_CHAIN_ID,
  'hive': '', // NOT SUPPORTED
  'icp': '', // NOT SUPPORTED
  'immutablex': '', // NOT SUPPORTED
  'immutablezkevm': QoraiWallet.IMMUTABLE_ZK_EVM_CHAIN_ID,
  'klaytn': QoraiWallet.KLAYTN_MAINNET_CYPRESS_CHAIN_ID,
  'kroma': QoraiWallet.KROMA_CHAIN_ID,
  'lightlink': QoraiWallet.LIGHTLINK_PHOENIX_MAINNET_CHAIN_ID,
  'linea': QoraiWallet.LINEA_CHAIN_ID,
  'mooi': '', // NOT SUPPORTED
  'moonbeam': QoraiWallet.MOONBEAM_CHAIN_ID,
  'moonriver': QoraiWallet.MOONRIVER_CHAIN_ID,
  'near': QoraiWallet.NEAR_MAINNET_CHAIN_ID,
  'oasis': QoraiWallet.OASIS_EMERALD_CHAIN_ID,
  'oasis-sapphire': QoraiWallet.OASIS_SAPPHIRE_CHAIN_ID,
  'oasys-chain-verse': '', // NOT SUPPORTED
  'oasys-defi-verse': '', // NOT SUPPORTED
  'oasys-gesoten-verse': '', // NOT SUPPORTED
  'oasys-home-verse': '', // NOT SUPPORTED
  'oasys-mainnet': QoraiWallet.OASYS_MAINNET_CHAIN_ID,
  'oasys-mch-verse': '', // NOT SUPPORTED
  'oasys-saakuru-verse': '', // NOT SUPPORTED
  'oasys-tcg-verse': '', // NOT SUPPORTED
  'oasys-yooldo-verse': '', // NOT SUPPORTED
  'ontology': QoraiWallet.ONTOLOGY_MAINNET_CHAIN_ID,
  'opbnb': QoraiWallet.OP_BNB_MAINNET_CHAIN_ID,
  'optimism': QoraiWallet.OPTIMISM_MAINNET_CHAIN_ID,
  'other': '', // NOT SUPPORTED
  'polygon': QoraiWallet.POLYGON_MAINNET_CHAIN_ID,
  'rangers': QoraiWallet.RANGERS_PROTOCOL_MAINNET_CHAIN_ID,
  'ronin': QoraiWallet.RONIN_CHAIN_ID,
  'shiden': QoraiWallet.SHIDEN_CHAIN_ID,
  'skale-calypso': QoraiWallet.SKALE_CALYPSO_HUB_CHAIN_ID,
  'skale-europa': QoraiWallet.SKALE_EUROPA_HUB_CHAIN_ID,
  'skale-exorde': '', // NOT SUPPORTED
  'skale-nebula': QoraiWallet.SKALE_NEBULA_HUB_CHAIN_ID,
  'skale-omnus': '', // NOT SUPPORTED
  'skale-razor': '', // NOT SUPPORTED
  'skale-strayshot': '', // NOT SUPPORTED
  'skale-titan': QoraiWallet.SKALE_TITAN_HUB_CHAIN_ID,
  'solana': QoraiWallet.SOLANA_MAINNET,
  'stacks': '', // NOT SUPPORTED
  'stargaze': '', // NOT SUPPORTED
  'steem': '', // NOT SUPPORTED
  'telos': '', // NOT SUPPORTED
  'telosevm': QoraiWallet.TELOS_EVM_MAINNET_CHAIN_ID,
  'tezos': '', // NOT SUPPORTED
  'theta': QoraiWallet.THETA_MAINNET_CHAIN_ID,
  'thundercore': QoraiWallet.THUNDER_CORE_MAINNET_CHAIN_ID,
  'ton': '', // NOT SUPPORTED
  'tron': '', // NOT SUPPORTED
  'wax': '', // NOT SUPPORTED
  'wemix': QoraiWallet.WEMIX_MAINNET_CHAIN_ID,
  'xai': QoraiWallet.XAI_MAINNET_CHAIN_ID,
  'xrpl': '', // NOT SUPPORTED
  'zetachain': QoraiWallet.ZETA_CHAIN_MAINNET_CHAIN_ID,
  'zilliqa': QoraiWallet.ZILLIQA_EVM_CHAIN_ID,
  'zksync-era': QoraiWallet.ZK_SYNC_ERA_CHAIN_ID,
}
