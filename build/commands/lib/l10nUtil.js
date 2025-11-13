/* Copyright (c) 2018 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

/**
 * This file manages the following:
 * - Lists of files needed to be translated (Which is all top level GRD and JSON files)
 * - All mappings for auto-generated Qorai files from the associated Chromium files.
 * - Top level global string replacements, such as replacing Chromium with Qorai
 */

const path = require('path')
const fs = require('fs')
const chalk = require('chalk')
const { JSDOM } = require('jsdom')
const config = require('./config')

// Change to `true` for verbose console log output of GRD traversal
const verboseLogFindGrd = false
const srcDir = config.srcDir

// chromium_strings.grd and any of its parts files that we track localization
// for in l10n service.
// These map to qorai/app/resources/chromium_strings*.xtb
const chromiumStringsPath = path.resolve(
  path.join(srcDir, 'chrome', 'app', 'chromium_strings.grd'),
)
const qoraiStringsPath = path.resolve(
  path.join(srcDir, 'qorai', 'app', 'qorai_strings.grd'),
)
const chromiumSettingsPartPath = path.resolve(
  path.join(srcDir, 'chrome', 'app', 'settings_chromium_strings.grdp'),
)
const qoraiSettingsPartPath = path.resolve(
  path.join(srcDir, 'qorai', 'app', 'settings_qorai_strings.grdp'),
)

// Replace android strings.
const androidChromeStringsPath = path.resolve(
  path.join(
    srcDir,
    'chrome',
    'browser',
    'ui',
    'android',
    'strings',
    'android_chrome_strings.grd',
  ),
)
const qoraiAndroidChromeStringsPath = path.resolve(
  path.join(
    srcDir,
    'qorai',
    'browser',
    'ui',
    'android',
    'strings',
    'android_chrome_strings.grd',
  ),
)
const androidTabUiStringsPath = path.resolve(
  path.join(
    srcDir,
    'chrome',
    'android',
    'features',
    'tab_ui',
    'java',
    'strings',
    'android_chrome_tab_ui_strings.grd',
  ),
)
const qoraiAndroidTabUiStringsPath = path.resolve(
  path.join(
    srcDir,
    'qorai',
    'android',
    'features',
    'tab_ui',
    'java',
    'strings',
    'android_chrome_tab_ui_strings.grd',
  ),
)
const androidWebappsStringsPath = path.resolve(
  path.join(
    srcDir,
    'components',
    'webapps',
    'browser',
    'android',
    'android_webapps_strings.grd',
  ),
)
const qoraiAndroidWebappsStringsPath = path.resolve(
  path.join(
    srcDir,
    'qorai',
    'components',
    'webapps',
    'browser',
    'android',
    'android_webapps_strings.grd',
  ),
)
const androidBrowserUiStringsPath = path.resolve(
  path.join(
    srcDir,
    'components',
    'browser_ui',
    'strings',
    'android',
    'browser_ui_strings.grd',
  ),
)
const qoraiAndroidBrowserUiStringsPath = path.resolve(
  path.join(
    srcDir,
    'qorai',
    'components',
    'browser_ui',
    'strings',
    'android',
    'browser_ui_strings.grd',
  ),
)

// component_chromium_strings.grd and any of its parts files that we track
// localization for in l10n service.
// These map to qorai/app/strings/components_chromium_strings*.xtb
const chromiumComponentsChromiumStringsPath = path.resolve(
  path.join(srcDir, 'components', 'components_chromium_strings.grd'),
)
const qoraiComponentsQoraiStringsPath = path.resolve(
  path.join(srcDir, 'qorai', 'components', 'components_qorai_strings.grd'),
)

// components/component_strings.grd and any of its parts files that we track
// localization for in l10n service.
// These map to qorai/components/component_strings*.xtb
const chromiumComponentsStringsPath = path.resolve(
  path.join(srcDir, 'components', 'components_strings.grd'),
)
const qoraiComponentsStringsPath = path.resolve(
  path.join(srcDir, 'qorai', 'components', 'components_strings.grd'),
)

// generated_resources.grd and any of its parts files that we track localization
// for in l10n service. There is also chromeos_strings.grdp, but we don't need
// to track it here because it is explicitly skipped in l10n service python
// scripts.
// These map to qorai/app/resources/generated_resoruces*.xtb
const chromiumGeneratedResourcesPath = path.resolve(
  path.join(srcDir, 'chrome', 'app', 'generated_resources.grd'),
)
const qoraiGeneratedResourcesPath = path.resolve(
  path.join(srcDir, 'qorai', 'app', 'generated_resources.grd'),
)
const chromiumGeneratedResourcesExcludes = new Set(['chromeos_strings.grdp'])

// locale_settings_*.grd don't have any strings that we currently want to
// override, but they are missing <output .../> and <file .../> tags for some
// languages that we want to support (such as 'si'). Adding them here would let
// us use chromium-rebase-l10n.py script to insert the missing tags and will
// allow to use l10n service to translate for the missing languages.
const chromiumLocaleSettingsLinux = path.resolve(
  path.join(srcDir, 'chrome', 'app', 'resources', 'locale_settings_linux.grd'),
)
const qoraiLocaleSettingsLinux = path.resolve(
  path.join(srcDir, 'qorai', 'app', 'resources', 'locale_settings_linux.grd'),
)
const chromiumLocaleSettingsMac = path.resolve(
  path.join(srcDir, 'chrome', 'app', 'resources', 'locale_settings_mac.grd'),
)
const qoraiLocaleSettingsMac = path.resolve(
  path.join(srcDir, 'qorai', 'app', 'resources', 'locale_settings_mac.grd'),
)
const chromiumLocaleSettingsWin = path.resolve(
  path.join(srcDir, 'chrome', 'app', 'resources', 'locale_settings_win.grd'),
)
const qoraiLocaleSettingsWin = path.resolve(
  path.join(srcDir, 'qorai', 'app', 'resources', 'locale_settings_win.grd'),
)

// The following are not generated files but still need to be tracked so they
// get sent to l10n service. These xtb files don't need to be copied anywhere.
// qorai_generated_resources.grd maps to
//     qorai/app/resources/qorai_generated_resources*.xtb,
// qorai_components_strings.grd maps to
//     qorai/components/resources/strings/qorai_components_resources*.xtb
// messages.json localization is handled inside of qorai extension.
const qoraiSpecificGeneratedResourcesPath = path.resolve(
  path.join(srcDir, 'qorai', 'app', 'qorai_generated_resources.grd'),
)
const qoraiResourcesComponentsStringsPath = path.resolve(
  path.join(
    srcDir,
    'qorai',
    'components',
    'resources',
    'qorai_components_strings.grd',
  ),
)
const qoraiExtensionMessagesPath = path.resolve(
  path.join(
    srcDir,
    'qorai',
    'components',
    'qorai_extension',
    'extension',
    'qorai_extension',
    '_locales',
    'en_US',
    'messages.json',
  ),
)
const qoraiAndroidQoraiStringsPath = path.resolve(
  path.join(
    srcDir,
    'qorai',
    'browser',
    'ui',
    'android',
    'strings',
    'android_qorai_strings.grd',
  ),
)
const qoraiAndroidQuickSearchEnginesStringsPath = path.resolve(
  path.join(
    srcDir,
    'qorai',
    'browser',
    'quick_search_engines',
    'android',
    'java',
    'strings',
    'android_quick_search_engines_strings.grd',
  ),
)

// Helper function to find all grdp parts in a grd.
function getGrdPartsFromGrd(path) {
  const grd = new JSDOM(fs.readFileSync(path, 'utf8'))
  const partTags = grd.window.document.getElementsByTagName('part')
  let parts = []
  for (const partTag of partTags) {
    parts.push(partTag.getAttribute('file'))
  }
  return parts
}

// Helper function to create a mapping for grd and all of its grdp parts.
function addGrd(chromiumPath, qoraiPath, exclude = new Set()) {
  if (verboseLogFindGrd) {
    console.log('Adding mappings for GRD: ' + chromiumPath)
  }
  if (!fs.existsSync(chromiumPath)) {
    const err = new Error(
      `addGrd: Error. File not found at path "${chromiumPath}"`,
    )
    console.error(err)
    throw err
  }
  let mapping = {}
  // Add grd parts before grd because chromium-rebase-l10n.py expects them to be
  // processed first.
  const grdps = getGrdPartsFromGrd(chromiumPath)
  if (grdps.length) {
    const chromiumDir = path.dirname(chromiumPath)
    const qoraiDir = path.dirname(qoraiPath)
    for (const grdp of grdps) {
      if (exclude.has(grdp)) {
        continue
      }
      const chromiumGrdpPath = path.resolve(path.join(chromiumDir, grdp))
      const qoraiGrdpPath = path.resolve(path.join(qoraiDir, grdp))
      // grdp files can have their own grdp parts too
      mapping = {
        ...mapping,
        ...addGrd(chromiumGrdpPath, qoraiGrdpPath, exclude),
      }
    }
    if (verboseLogFindGrd) {
      console.log('  - Added ' + (Object.keys(mapping).length - 1) + ' GRDP.')
    }
  }
  mapping[chromiumPath] = qoraiPath
  return mapping
}

// Helper functions that's, for a given pair of chromium to qorai GRD mapping
// from the supplied map, determines which GRDP parts are no longer present in
// the chromium GRD file.
function getRemovedGRDParts(mapping) {
  let removedMap = new Map()
  for (const [sourcePath, destPath] of Object.entries(mapping)) {
    if (path.extname(destPath) === '.grd') {
      const qoraiGRDPs = getGrdPartsFromGrd(destPath)
      const chromiumGRDPs = getGrdPartsFromGrd(sourcePath)
      let removed = new Set()
      for (let i = 0; i < qoraiGRDPs.length; i++) {
        if (!chromiumGRDPs.includes(qoraiGRDPs[i])) {
          removed.add(qoraiGRDPs[i])
        }
      }
      if (removed.size) {
        removedMap.set(destPath, removed)
      }
    }
  }
  return removedMap
}

// Add all GRD mappings here.
function getAutoGeneratedGrdMappings() {
  if (typeof getAutoGeneratedGrdMappings.mappings === 'undefined') {
    console.log(chalk.italic('Recursing through GRD to find GRDP files...'))
    // Qorai specific only grd and grdp files should NOT be added.
    // Using AddGrd will add GRD and all of its GRDPs.
    getAutoGeneratedGrdMappings.mappings = {
      ...addGrd(chromiumComponentsStringsPath, qoraiComponentsStringsPath),
      ...addGrd(
        chromiumGeneratedResourcesPath,
        qoraiGeneratedResourcesPath,
        chromiumGeneratedResourcesExcludes,
      ),
      ...addGrd(chromiumLocaleSettingsLinux, qoraiLocaleSettingsLinux),
      ...addGrd(chromiumLocaleSettingsMac, qoraiLocaleSettingsMac),
      ...addGrd(chromiumLocaleSettingsWin, qoraiLocaleSettingsWin),
      ...addGrd(androidChromeStringsPath, qoraiAndroidChromeStringsPath),
      ...addGrd(androidTabUiStringsPath, qoraiAndroidTabUiStringsPath),
      ...addGrd(androidWebappsStringsPath, qoraiAndroidWebappsStringsPath),
      ...addGrd(androidBrowserUiStringsPath, qoraiAndroidBrowserUiStringsPath),
    }
    console.log(chalk.italic('Done recursing through GRD to find GRDP files.'))
  }
  return getAutoGeneratedGrdMappings.mappings
}

function getChromiumToAutoGeneratedQoraiMapping() {
  if (typeof getChromiumToAutoGeneratedQoraiMapping.mapping === 'undefined') {
    // When adding new grd or grdp files, never add a grdp part path without a
    // parent grd path, but add the grd parts to the mapping before the parent
    // grd, becase chromium-rebase-l10n.py expects them to be processed first.
    // Group them with a leading and trailing newline to keep this file
    // organized. The first 3 are added explicitly because we change the file
    // names.
    getChromiumToAutoGeneratedQoraiMapping.mapping = {
      [chromiumSettingsPartPath]: qoraiSettingsPartPath,
      [chromiumStringsPath]: qoraiStringsPath,

      [chromiumComponentsChromiumStringsPath]: qoraiComponentsQoraiStringsPath,

      ...getAutoGeneratedGrdMappings(),
    }
  }
  return getChromiumToAutoGeneratedQoraiMapping.mapping
}

const l10nUtil = {
  // Same as with chromiumToAutoGeneratedQoraiMapping but maps in the opposite direction
  getAutoGeneratedQoraiToChromiumMapping: () => {
    if (
      typeof l10nUtil.getAutoGeneratedQoraiToChromiumMapping.mapping
      === 'undefined'
    ) {
      const chromiumToAutoGeneratedQoraiMapping =
        getChromiumToAutoGeneratedQoraiMapping()
      l10nUtil.getAutoGeneratedQoraiToChromiumMapping.mapping = Object.keys(
        chromiumToAutoGeneratedQoraiMapping,
      ).reduce(
        (obj, key) => ({
          ...obj,
          [chromiumToAutoGeneratedQoraiMapping[key]]: key,
        }),
        {},
      )
    }
    return l10nUtil.getAutoGeneratedQoraiToChromiumMapping.mapping
  },

  // All paths which are generated
  getQoraiAutoGeneratedPaths: () => {
    return Object.values(getChromiumToAutoGeneratedQoraiMapping())
  },

  // All paths which are not generated
  getQoraiNonGeneratedPaths: () => {
    if (typeof l10nUtil.getQoraiNonGeneratedPaths.paths === 'undefined') {
      l10nUtil.getQoraiNonGeneratedPaths.paths = [
        qoraiSpecificGeneratedResourcesPath,
        qoraiResourcesComponentsStringsPath,
        qoraiExtensionMessagesPath,
        qoraiAndroidQoraiStringsPath,
        qoraiAndroidQuickSearchEnginesStringsPath,
      ]
    }
    return l10nUtil.getQoraiNonGeneratedPaths.paths
  },

  // Qorai specific strings and Chromium mapped Qorai strings will be here.
  // But you only need to add the Qorai specific strings manually here.
  getAllQoraiPaths: () => {
    return l10nUtil
      .getQoraiNonGeneratedPaths()
      .concat(l10nUtil.getQoraiAutoGeneratedPaths())
  },

  // Get all GRD and JSON paths whether they are generated or not
  // Push and pull scripts for l10n use this.
  // Crowdin manages files per grd and not per grd or grdp.
  // This is because only 1 xtb is created per grd per locale even if it has multiple grdp files.
  getQoraiTopLevelPaths: () => {
    return l10nUtil
      .getAllQoraiPaths()
      .filter((x) => ['grd', 'json'].includes(x.split('.').pop()))
  },

  // Helper function to pretty print removed GRDP file names.
  logRemovedGRDParts: (mapping) => {
    if (mapping.size) {
      console.log(
        '\n**************************************************************************',
      )
      console.log(
        'The following GRDP files are no longer in the corresponding Chromium GRDs:\n',
      )
      for (const [grd, grdps] of mapping.entries()) {
        console.log('  From ' + grd + ':')
        for (const grdp of grdps) {
          console.log('    - ' + grdp)
        }
      }
    }
  },

  // This simply copies the content of Chromium files to their mapped Qorai
  // equivalents. Additionally, it removes GRDP files that are no longer in the
  // Chromium GRD files.
  rebaseQoraiStringFilesOnChromiumL10nFiles: async () => {
    const removedMap = getRemovedGRDParts(getAutoGeneratedGrdMappings())
    const ops = Object.entries(getChromiumToAutoGeneratedQoraiMapping()).map(
      async ([sourcePath, destPath]) => {
        console.log(
          'Resetting '
            + path.relative(srcDir, destPath)
            + ' <- '
            + path.relative(srcDir, sourcePath),
        )
        return await fs.copyFile(sourcePath, destPath, (err) => {
          if (err) {
            console.log('Error: ' + err)
          }
        })
      },
    )
    await Promise.all(ops)
    return removedMap
  },
} // const l10nUtil

module.exports = l10nUtil
