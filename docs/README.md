# Qorai docs

This directory contains documentation for the Qorai Browser. For additional resources outside this repository, go to:

 * [qorai-browser/wiki](https://github.com/qorai/qorai-browser/wiki)

> [!IMPORTANT]
> If you add new documents, please also add a link to them in the Document
> Index below.

## Creating Documentation

### Guidelines

*   Markdown documents must follow the
    [Markdown Style
    Guide](https://chromium.googlesource.com/chromium/src/+/HEAD/styleguide/markdown/markdown.md).

### Previewing changes

#### Locally using [md_browser](https://chromium.googlesource.com/chromium/src/+/refs/heads/main/tools/md_browser/)

```bash
# in src/qorai/
npm run docs
```

This is only an estimate. The **github** view may differ.

## Document Index

### Checking Out and Patching
*   [Upgrading Chromium](chromium_version_upgrade.md) Upgrading `qorai-core` to
    a newer Chromium version.
*   [Patching with `plaster`](plaster.md) A patching engine for semantical
    patching of upstream Chromium.
*   [WebUI Overriding](webui_overriding.md)
*   [DevTools Frontend Patching](devtools_frontend_patching.md) Managing
    changes to the upstream project.

### General Development
*   [`gni` notes](gni_sources.md) - Brief notes on the use of `source.gni`
    files in our code base.
*   [Rust notes](rust.md) - General recommendations on integrating rust code
    into `qorai-core`
*   [Adapting Chromium tests to the Qorai Codebase](adapting_chromium_tests.md) -
    Suggestions on how to make chromium test work on our test targets.
*   [Ship a File to All Clients](ship_a_file_to_all_clients.md) - How to ship a
    file to all clients via component updater.
*   [Git Configuration](git_configuration.md) - General recommendations for
    setting up and optimizing your Git environment.
