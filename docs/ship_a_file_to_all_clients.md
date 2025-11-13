### How to Ship a File to All Clients

1. In `qorai/qorai-core`
([Example](https://github.com/qorai/qorai-core/pull/27620)):
    1. Create the component class that will consume the downloaded file as
    needed.
        - The component should be a singleton. See
        [qorai-browser#40545](https://github.com/qorai/qorai-browser/issues/40545)
        for more info.
    2. Create the component installer policy for the component.
    3. Create the `Register*Component` method and register it in
    `RegisterComponentsForUpdate`.
2. Follow the `qorai-core-crx-packager`
[README](https://github.com/qorai/qorai-core-crx-packager/blob/master/README.md)
to generate:
    - `key.pem`
    - public key for `key.pem`
    - component id for `key.pem`
3. Create a 1Password item to hold the `key.pem`, the public key and the
component id.
4. In `qorai/qorai-core-crx-packager`
([Example](https://github.com/qorai/qorai-core-crx-packager/pull/1048)):
    1. Add a script to download the file to `pacakge.json`.
    2. Create a script to build the package and manifest and add it to the
    `package.json`.
5. In `qorai/devops`
([Example](https://github.com/qorai/devops/issues/13229)):
    1. Open an issue to create a Jenkins job to publish the crx-package.
6. Once the package is published, test it in your local development of Qorai to
be sure it's downloaded and consumed as expected.