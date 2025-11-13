use_relative_paths = True

vars = {
  'download_prebuilt_sparkle': True,
  'checkout_dmg_tool': False,
}

deps = {
  "vendor/python-patch": "https://github.com/blockmandev/python-patch",
  "vendor/omaha": {
    "url": "https://github.com/blockmandev/omaha.git",
    "condition": "checkout_win",
  },
  "vendor/sparkle": {
    "url": "https://github.com/blockmandev/sparkle.git",
    "condition": "checkout_mac",
  },
  "vendor/qor-native-tweetnacl": "https://github.com/blockmandev/qor-native-tweetnacl.git",
  "vendor/gn-project-generators": "https://github.com/blockmandev/gn-project-generators.git",
  "vendor/web-discovery-project": "https://github.com/blockmandev/web-discovery-project",
  "third_party/bip39wally-core-native": "https://github.com/blockmandev/qor-native-bip39wally-core.git",
  "third_party/ethash/src": "https://github.com/chfast/ethash.git@e4a15c3d76dc09392c7efd3e30d84ee3b871e9ce",
  "third_party/bitcoin-core/src": "https://github.com/bitcoin/bitcoin.git@8105bce5b384c72cf08b25b7c5343622754e7337", # v25.0
  "third_party/argon2/src": "https://github.com/P-H-C/phc-winner-argon2.git@62358ba2123abd17fccf2a108a301d4b52c01a7c",
  "third_party/libdmg-hfsplus": {
    "url": "https://github.com/fanquake/libdmg-hfsplus.git@1cc791e4173da9cb0b0cc16c5a1aaa25d5eb5efa",
    "condition": 'checkout_mac and host_os != "mac" and checkout_dmg_tool',
  },
  "third_party/reclient_configs/src": "https://github.com/EngFlow/reclient-configs.git@21c8fe69ff771956c179847b8c1d9fd216181967",
  'third_party/android_deps/libs/com_google_android_play_core': {
      'packages': [
          {
              'package': 'chromium/third_party/android_deps/libs/com_google_android_play_core',
              'version': 'version:2@1.10.3.cr1',
          },
      ],
      'condition': 'checkout_android',
      'dep_type': 'cipd',
  },
  "third_party/playlist_component/src": "https://github.com/blockmandev/playlist-component.git",
  "third_party/rust/futures_retry/v0_5/crate": "https://github.com/blockmandev/futures-retry.git",
  "third_party/macholib": {
    "url": "https://github.com/ronaldoussoren/macholib.git@36a6777ccd0891c5d1b44ba885573d7c90740015",
    "condition": "checkout_mac",
  },
  "components/qorai_wallet/browser/zcash/rust/librustzcash/src": "https://github.com/blockmandev/librustzcash.git", # v2
}

recursedeps = [
  'vendor/omaha'
]

hooks = [
  {
    'name': 'bootstrap',
    'pattern': '.',
    'action': ['vpython3', 'script/bootstrap.py'],
  },
  {
    'name': 'bootstrap_ios',
    'pattern': '.',
    'condition': 'checkout_ios and host_os == "mac"',
    'action': ['vpython3', 'script/ios_bootstrap.py']
  },
  {
    # Download hermetic xcode for goma
    'name': 'download_hermetic_xcode',
    'pattern': '.',
    'condition': 'checkout_mac or checkout_ios',
    'action': ['vpython3', 'build/mac/download_hermetic_xcode.py'],
  },
  {
    'name': 'configure_reclient',
    'pattern': '.',
    'action': ['python3', 'third_party/reclient_configs/src/configure_reclient.py',
               '--src_dir=..',
               '--custom_py=third_party/reclient_configs/qorai_custom/qorai_custom.py'],
  },
  {
    'name': 'hardlink_qorai_siso_config',
    'pattern': '.',
    'action': [
      'python3', 'build/hardlink_file.py',
      'build/config/siso/qorai_siso_config.star',
      '../build/config/siso/qorai_siso_config.star'
    ],
  },
  {
    'name': 'download_sparkle',
    'pattern': '.',
    'condition': 'checkout_mac and download_prebuilt_sparkle',
    'action': ['vpython3', 'build/download_dep.py',
               'sparkle/sparkle-1.24.3.tar.gz',
               '//build/mac_files/sparkle_binaries'],
  },
  {
    'name': 'download_omaha4',
    'pattern': '.',
    'condition': 'checkout_mac',
    'action': ['vpython3', 'build/download_dep.py',
               'omaha4/QoraiUpdater-141.1.85.63.zip',
               '//qorai/third_party/updater/mac',
               'QoraiUpdater.app/'],
  },
  {
    'name': 'update_pip',
    'pattern': '.',
    # Required for download_cryptography below. Specifically, newer versions of
    # pip are required for obtaining binary wheels on Arm64 macOS.
    'action': ['python3', '-m', 'pip', '-q', '--disable-pip-version-check', 'install', '-U', '--no-warn-script-location', 'pip'],
  },
  {
    'name': 'download_cryptography',
    'pattern': '.',
    # We don't include cryptography as a DEP because building it from source is
    # difficult. We pin to a version >=37.0.2 and <38.0.0 to avoid an
    # incompatibility with our pyOpenSSL version on Android. See:
    # https://github.com/pyca/cryptography/issues/7126.
    # We use python3 instead of vpython3 for two reasons: First, our GN actions
    # are run with python3, so this environment mirrors the one in which
    # cryptography will be used. Second, we cannot update pip in vpython3 on at
    # least macOS due to permission issues.
    'action': ['python3', '-m', 'pip', '-q', '--disable-pip-version-check', 'install', '-U', '-t', 'third_party/cryptography', '--only-binary', 'cryptography', 'cryptography==37.0.4'],
  },
  {
    'name': 'wireguard_nt',
    'pattern': '.',
    'condition': 'checkout_win',
    'action': ['vpython3', 'build/download_dep.py',
               'qorai-vpn-wireguard-dlls/qorai-vpn-wireguard-nt-dlls-0.10.1.zip',
               '//qorai/third_party/qorai-vpn-wireguard-nt-dlls'],
  },
  {
    'name': 'wireguard_tunnel',
    'pattern': '.',
    'condition': 'checkout_win',
    'action': ['vpython3', 'build/download_dep.py',
               'qorai-vpn-wireguard-dlls/qorai-vpn-wireguard-tunnel-dlls-v0.5.3.zip',
               '//qorai/third_party/qorai-vpn-wireguard-tunnel-dlls'],
  },
  {
    # Install Web Discovery Project dependencies for Windows, Linux, and macOS
    'name': 'web_discovery_project_npm_deps',
    'pattern': '.',
    'condition': 'checkout_linux or checkout_mac or checkout_win',
    'action': ['vpython3', 'script/web_discovery_project.py', '--install'],
  },
  {
    'name': 'generate_licenses',
    'pattern': '.',
    'action': ['vpython3', 'script/generate_licenses.py'],
  },
  {
    # Overwrite Chromium's LASTCHANGE using the latest Qorai version commit.
    'name': 'qorai_lastchange',
    'pattern': '.',
    'action': ['python3', '../build/util/lastchange.py',
               '--output', '../build/util/LASTCHANGE',
               '--source-dir', '.',
               '--filter', '^[0-9]\{{1,\}}\.[0-9]\{{1,\}}\.[0-9]\{{1,\}}$'],
  },
  {
    # Downloads & overwrites Chromium's swift-format dep on macOS only
    'name': 'download_swift_format',
    'pattern': '.',
    'condition': 'host_os == "mac"',
    'action': ['python3', 'build/apple/download_swift_format.py', '510.1.0', '0ddbb486640cde862fa311dc0f7387e6c5171bdcc0ee0c89bc9a1f8a75e8bfaf']
  },
  {
    # Chromium_src files require custom formatting to correctly sort includes
    # that reference original files.
    'name': 'generate_chromium_src_clang_format',
    'pattern': '.',
    'action': ['vpython3', 'tools/chromium_src/generate_clang_format.py',
               '../.clang-format', 'chromium_src/.clang-format'],
  },
  {
    # We only need a custom .clang-format in chromium_src. It was previously
    # generated in the root of qorai/, so we remove it now. This hook can be
    # removed after 08/2025.
    'name': 'remove_stale_clang_format',
    'pattern': '.',
    'action': ['python3', '../tools/remove_stale_files.py', '.clang-format']
  },
  {
    'name': 'update_midl_files',
    'pattern': '.',
    'condition': 'checkout_win',
    'action': ['python3', 'build/util/update_midl_files.py']
  },
  {
    'name': 'build_libdmg_hfsplus',
    'pattern': '.',
    "condition": 'checkout_mac and host_os != "mac" and checkout_dmg_tool',
    'action': ['build/mac/cross-compile/build-libdmg-hfsplus.py', 'third_party/libdmg-hfsplus']
  },
  {
    'name': 'download_rust_toolchain_aux',
    'pattern': '.',
    'action': ['python3', 'build/rust/download_rust_toolchain_aux.py']
  },
]

include_rules = [
  "-chrome",
  "-qorai",
  "-third_party/rust",

  # Everybody can use some things.
  "+qorai/base",
  "+qorai/qorai_domains",
]
