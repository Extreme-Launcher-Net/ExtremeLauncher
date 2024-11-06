<p>
  Extreme Launcher is a custom launcher for Minecraft that allows you to easily manage multiple installations of Minecraft at once.<br />
  <br />This is a <b>fork</b> of the Prims/MultiMC Launcher and is <b>not</b> endorsed by it.
</p>

## Installation

- All downloads and instructions for Extreme Launcher can be found on our [Website](https://extremelauncher.net/download/).
- Last build status can be found in the [GitHub Actions](https://github.com/Extreme-Launcher-Net/ExtremeLauncher/actions) tab (this also includes the pull requests status).

### Development Builds

Please understand that these builds are not intended for most users. There may be bugs, and other instabilities. You have been warned.

There are development builds available through:

- [GitHub Actions](https://github.com/Extreme-Launcher-Net/ExtremeLauncher/actions) (includes builds from pull requests opened by contribuitors)
- [nightly.link](https://nightly.link/Extreme-Launcher-Net/ExtremeLauncher/workflows/trigger_builds/develop) (this will always point only to the latest version of develop)

These have debug information in the binaries, so their file sizes are relatively larger.

Prebuilt Development builds are provided for **Linux**, **Windows** and **macOS**.

## Community & Support

Feel free to create a GitHub issue if you find a bug or want to suggest a new feature. We have multiple community spaces where other community members can help you:

## Translations

The translation effort for Extreme Launcher is hosted on [Weblate](https://hosted.weblate.org/projects/extremelauncher/launcher/) and information about translating Extreme Launcher is available at <https://github.com/ExtremeLauncher/Translations>.

## Forking/Redistributing/Custom builds policy

You are free to fork, redistribute and provide custom builds as long as you follow the terms of the [license](LICENSE) (this is a legal responsibility), and if you made code changes rather than just packaging a custom build, please do the following as a basic courtesy:

- Make it clear that your fork is not Extreme Launcher and is not endorsed by or affiliated with the Extreme Launcher project (<https://extremelauncher.net>).
- Go through [CMakeLists.txt](CMakeLists.txt) and change Extreme Launcher's API keys to your own or set them to empty strings (`""`) to disable them (this way the program will still compile but the functionality requiring those keys will be disabled).

If you have any questions or want any clarification on the above conditions please make an issue and ask us.

If you are just building Extreme Launcher for your distribution, please make sure to set the `Launcher_BUILD_PLATFORM` to a slug representing your distribution. Examples are `archlinux`, `fedora` and `nixpkgs`.

Note that if you build this software without removing the provided API keys in [CMakeLists.txt](CMakeLists.txt) you are accepting the following terms and conditions:

- [Microsoft Identity Platform Terms of Use](https://docs.microsoft.com/en-us/legal/microsoft-identity-platform/terms-of-use)
- [CurseForge 3rd Party API Terms and Conditions](https://support.curseforge.com/en/support/solutions/articles/9000207405-curse-forge-3rd-party-api-terms-and-conditions)

If you do not agree with these terms and conditions, then remove the associated API keys from the [CMakeLists.txt](CMakeLists.txt) file by setting them to an empty string (`""`).

## License [![https://github.com/Extreme-Launcher-Net/ExtremeLauncher/blob/develop/LICENSE](https://img.shields.io/github/license/Extreme-Launcher-Net/ExtremeLauncher?label=License&logo=gnu&color=C4282D)](LICENSE)

All launcher code is available under the GPL-3.0-only license.

The logo and related assets are under the CC BY-SA 4.0 license.
