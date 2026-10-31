<!-- markdownlint-disable-file MD033 -->

# SpaceCadetPinball

## Summary

Reverse engineering of `3D Pinball for Windows - Space Cadet`, a game bundled with Windows.

## Source layout

| Path | Contents |
| --- | --- |
| `src/app` | Entry point, main loop, window/fullscreen handling, options |
| `src/core` | Game state, rules, table, physics and timing |
| `src/core/components` | Table components (`TBall`, `TFlipper`, `TLight`, ...) |
| `src/render` | Software renderer, bitmaps, z-buffer and projection |
| `src/audio` | MIDI and sound playback |
| `src/data` | DAT parsing, resource groups and loaders |
| `src/ui` | ImGui UI, score/high-score, text boxes and translations |
| `src/platform` | Platform-specific resources (Windows `.rc`/icon) |
| `third_party/imgui` | Vendored ImGui sources |
| `assets` | Icons and source assets embedded into the build |
| `debug` | Visual Studio natvis file |

## How to play

Place compiled executable into a folder containing original game resources (not included).\
Supports data files from Windows and Full Tilt versions of the game.

For local development, put the original game data in `Resources/` at the repository root; the build copies it next to the executable automatically.

## Known source ports

| Platform           | Author          | URL                                                                                                        |
| ------------------ | --------------- | ---------------------------------------------------------------------------------------------------------- |
| PS Vita            | Axiom           | <https://github.com/suicvne/SpaceCadetPinball_Vita>                                                        |
| Emscripten         | alula           | <https://github.com/alula/SpaceCadetPinball> <br> Play online: <https://alula.github.io/SpaceCadetPinball> |
| Nintendo Switch    | averne          | <https://github.com/averne/SpaceCadetPinball-NX>                                                           |
| webOS TV           | mariotaku       | <https://github.com/webosbrew/SpaceCadetPinball>                                                           |
| Android (WIP)      | Iscle           | https://github.com/Iscle/SpaceCadetPinball                                                                 |
| Nintendo Wii       | MaikelChan      | https://github.com/MaikelChan/SpaceCadetPinball                                                            |
| Nintendo 3DS       | MaikelChan      | https://github.com/MaikelChan/SpaceCadetPinball/tree/3ds                                                   |
| Nintendo DS        | Headshotnoby    | https://github.com/headshot2017/3dpinball-nds                                                              |
| Nintendo Wii U     | IntriguingTiles | https://github.com/IntriguingTiles/SpaceCadetPinball-WiiU                                                  |
| PlayStation 2      | Headshotnoby    | https://github.com/headshot2017/3dpinball-ps2                                                              |
| Sega Dreamcast     | Headshotnoby    | https://github.com/headshot2017/3dpinball-dc                                                               |
| MorphOS            | BeWorld         | https://www.morphos-storage.net/?id=1688897                                                                |
| AmigaOS 4          | rjd324          | http://aminet.net/package/game/actio/spacecadetpinball-aos4                                                |
| Android (WIP)      | fexed           | https://github.com/fexed/Pinball-on-Android                                                                |

Platforms covered by this project: desktop Windows, Linux and macOS.

<br>
<br>
<br>
<br>
<br>
<br>

## Source

* `pinball.exe` from `Windows XP` (SHA-1 `2A5B525E0F631BB6107639E2A69DF15986FB0D05`) and its public PDB
* `CADET.EXE` 32bit version from `Full Tilt! Pinball` (SHA-1 `3F7B5699074B83FD713657CD94671F2156DBEDC4`)

## Tools used

`Ghidra`, `Ida`, `Visual Studio`

## What was done

* All structures were populated, globals and locals named.
* All subs were decompiled, C pseudo code was converted to compilable C++. Loose (namespace?) subs were assigned to classes.

## Compiling

Project uses `C++20` and depends on `SDL2` / `SDL2_mixer`. The supported baseline is Windows 11 with Visual Studio 2022+, macOS 12+ with Xcode 16+, and Linux with GCC 13+ or Clang 17+. CMake 3.25 or newer is required.

The repository includes a `vcpkg.json` manifest and `CMakePresets.json`. With `VCPKG_ROOT` pointing at a vcpkg checkout:

```sh
cmake --preset windows-x64        # or windows-x64-vs2022 on VS 2022
cmake --build --preset windows-x64-release
```

On Linux and macOS the `linux-x64` / `macos-universal` presets use system SDL2 packages.

### On Windows

Download and unpack devel packages for `SDL2` and `SDL2_mixer` into `/Libs`, or use the vcpkg presets above.\
Compile with Visual Studio 2022 or newer; tested with Visual Studio 2026 on Windows 11.

### On Linux

Install devel packages for `SDL2` and `SDL2_mixer`.\
Compile with CMake 3.25+; tested with GCC 13+ and Clang 17+.\
To cross-compile for Windows, install a 64-bit version of mingw and its `SDL2` and `SDL2_mixer` distributions, then use the `mingwcc.cmake` toolchain.

[![Packaging status](https://repology.org/badge/tiny-repos/spacecadetpinball.svg)](https://repology.org/project/spacecadetpinball/versions) 

Some distributions provide a package in their repository. You can use those for easier dependency management and updates.

This project is available as Flatpak on [Flathub](https://flathub.org/apps/details/com.github.k4zmu2a.spacecadetpinball).

### On macOS

Install Xcode 16 or newer (or at least the Xcode 16 Command Line Tools with `xcode-select --install`) and CMake.

**HomeBrew**

You can easily install the build artifact by using `brew`.

```sh
brew tap draftbrew/tap
brew install --no-quarantine space-cadet-pinball
```

Be aware that the flag `--no-quarantime` will disable macOS's Gatekeeper during installation.

**Manual compilation:**

* **Homebrew**: Install the `SDL2`, `SDL2_mixer` homebrew packages.
* **MacPorts**: Install the `libSDL2`, `libSDL2_mixer` macports packages.

Compile with CMake 3.25+. `CMakeLists.txt` defaults to a universal `arm64;x86_64` build with a macOS 12.0 deployment target; override `CMAKE_OSX_ARCHITECTURES` if you need a single architecture.

Build with Xcode 16+ (AppleClang 16); the deployment target is macOS 12.0.

**Automated compilation:**

Run the `build-mac-app.sh` script from the root of the repository. The app will be available in a DMG file named `SpaceCadetPinball-<version>-mac.dmg`.

Tested with: macOS 14/15 and Xcode 16.

## Plans

* ~~Decompile original game~~
* ~~Resizable window, scaled graphics~~
* ~~Loader for high-res sprites from CADET.DAT~~
* ~~Cross-platform port using SDL2, SDL2_mixer, ImGui~~
* Full Tilt Cadet features
* Localization support
* Maybe: Support for the other two tables - Dragon and Pirate
* Maybe: Game data editor

## On 64-bit bug that killed the game

I did not find it, decompiled game worked in x64 mode on the first try.\
It was either lost in decompilation or introduced in x64 port/not present in x86 build.\
Based on public description of the bug (no ball collision), I guess that the bug was in `TEdgeManager::TestGridBox`
