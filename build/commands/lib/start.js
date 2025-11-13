// Copyright (c) 2017 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

const path = require('path')
const fs = require('fs-extra')
const config = require('../lib/config')
const util = require('../lib/util')

const start = (
  passthroughArgs,
  buildConfig = config.defaultBuildConfig,
  options,
) => {
  config.buildConfig = buildConfig
  config.update(options)

  let qoraiArgs = ['--enable-logging', '--v=' + options.v]
  if (options.vmodule) {
    qoraiArgs.push('--vmodule=' + options.vmodule)
  }
  if (options.no_sandbox) {
    qoraiArgs.push('--no-sandbox')
  }
  if (options.disable_qorai_extension) {
    qoraiArgs.push('--disable-qorai-extension')
  }
  if (options.disable_qorai_rewards_extension) {
    qoraiArgs.push('--disable-qorai-rewards-extension')
  }
  if (options.disable_pdfjs_extension) {
    qoraiArgs.push('--disable-pdfjs-extension')
  }
  if (options.ui_mode) {
    qoraiArgs.push(`--ui-mode=${options.ui_mode}`)
  }
  if (!options.enable_qorai_update) {
    // This only has meaning with MacOS and official build.
    qoraiArgs.push('--disable-qorai-update')
  }
  if (options.disable_doh) {
    qoraiArgs.push('--disable-doh')
  }
  if (options.single_process) {
    qoraiArgs.push('--single-process')
  }
  if (options.show_component_extensions) {
    qoraiArgs.push('--show-component-extension-options')
  }
  if (options.rewards) {
    qoraiArgs.push(`--rewards=${options.rewards}`)
  }
  if (options.qorai_ads_testing) {
    qoraiArgs.push('--qorai-ads-testing')
  }
  if (options.qorai_ads_debug) {
    qoraiArgs.push('--qorai-ads-debug')
  }
  if (options.qorai_ads_production) {
    qoraiArgs.push('--qorai-ads-production')
  }
  if (options.qorai_ads_staging) {
    qoraiArgs.push('--qorai-ads-staging')
  }

  if (process.platform === 'darwin') {
    // Disable 'accept incoming network connections' and 'keychain access'
    // dialogs in MacOS. See //docs/mac_build_instructions.md for details.
    if (!options.use_real_keychain) {
      qoraiArgs.push('--use-mock-keychain')
    }
    if (!passthroughArgs.some((s) => s.startsWith('--disable-features'))) {
      qoraiArgs.push('--disable-features=DialMediaRouteProvider')
    }
  }

  // Remove -C and path if present because it is just specifying the location
  // of the Qorai executable and is not a Qorai command line option
  const index = passthroughArgs.indexOf('-C')
  if (index > -1) {
    passthroughArgs.splice(index, 2)
  }

  qoraiArgs = qoraiArgs.concat(passthroughArgs)

  let userDataDir
  if (options.user_data_dir_name) {
    if (process.platform === 'darwin') {
      userDataDir = path.join(
        process.env.HOME,
        'Library',
        'Application\\ Support',
        'QoraiSoftware',
        options.user_data_dir_name,
      )
    } else if (process.platform === 'win32') {
      userDataDir = path.join(
        process.env.LocalAppData,
        'QoraiSoftware',
        options.user_data_dir_name,
      )
    } else {
      userDataDir = path.join(
        process.env.HOME,
        '.config',
        'QoraiSoftware',
        options.user_data_dir_name,
      )
    }
    qoraiArgs.push('--user-data-dir=' + userDataDir)
  }

  let cmdOptions = {
    stdio: 'inherit',
    timeout: undefined,
    continueOnFail: false,
    shell: process.platform === 'darwin',
    killSignal: 'SIGTERM',
  }

  let outputPath = options.output_path
  if (!outputPath) {
    outputPath = path.join(config.outputDir, 'qorai')
    if (process.platform === 'win32') {
      outputPath = outputPath + '.exe'
    } else if (process.platform === 'darwin') {
      outputPath = fs
        .readFileSync(outputPath + '_helper')
        .toString()
        .trim()
    }
  }
  util.run(outputPath, qoraiArgs, cmdOptions)
}

module.exports = start
