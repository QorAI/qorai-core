// Copyright 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import Foundation
import PackagePlugin

/// Creates an asset catalog filled with Qorai's Qora SF Symbols
@main
struct QoraAssetsPlugin: BuildToolPlugin {

  func createBuildCommands(context: PluginContext, target: Target) async throws -> [Command] {
    // Check to make sure we have pulled down the icons correctly
    let fileManager = FileManager.default
    let qoraiCoreRootDirectory = context.package.directory.removingLastComponent()
      .removingLastComponent()
    let leoColorsDirectory = qoraiCoreRootDirectory.appending("node_modules/@qorai/qora")

    if !fileManager.fileExists(atPath: leoColorsDirectory.string) {
      Diagnostics.error(
        "Required Qora assets not found: \(FileManager.default.currentDirectoryPath)"
      )
      return []
    }

    // Check to make sure the plugin is being used correctly in SPM
    guard target is SourceModuleTarget else {
      Diagnostics.error("Attempted to use `QoraAssetsPlugin` on an unsupported module target")
      return []
    }

    let copyColorsCommand: Command = {
      let tokensPath = leoColorsDirectory.appending("tokens/ios-swift")
      let outputDirectory = context.pluginWorkDirectory.appending("QoraColors")
      return .buildCommand(
        displayName: "Copy Qora Colors",
        executable: Path("/bin/zsh"),
        arguments: [
          "-c", "find \"\(tokensPath)\" -name \\*.swift -exec cp {} \"\(outputDirectory)\" \\;",
        ],
        inputFiles: [
          tokensPath.appending("Gradients.swift"),
          tokensPath.appending("ColorSetAccessors.swift"),
        ],
        outputFiles: [
          outputDirectory.appending("Gradients.swift"),
          outputDirectory.appending("ColorSetAccessors.swift"),
        ]
      )
    }()

    return [copyColorsCommand]
  }
}
