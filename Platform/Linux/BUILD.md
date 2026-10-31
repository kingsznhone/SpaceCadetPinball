# Building

Install devel packages for `SDL2` and `SDL2_mixer`.\

Compile with CMake 3.25+; tested with GCC 13+ and Clang 17+.\
GCC 13+ is required; on Ubuntu 22.04 install `gcc-13`/`g++-13` or use Ubuntu 24.04+.\
To cross-compile for Windows, install a 64-bit version of mingw and its `SDL2` and `SDL2_mixer` distributions, then use the `mingwcc.cmake` toolchain.

```bash
# On Debian and Ubuntu
sudo apt install cmake build-essential ninja-build libsdl2-dev libsdl2-mixer-dev libsdl2-mixer-2.0-0 libsdl2-2.0-0 fluidsynth

# On Fedora
sudo dnf install cmake ninja-build SDL2 SDL2-devel SDL2_mixer SDL2_mixer-devel fluidsynth fluidsynth-libs mscore-fonts g++

# Build
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build

# Or use the preset
cmake --preset linux-x64
cmake --build --preset linux-x64-release
```

**If you can't hear the background music**: You need to export the following variable before launching the game like this:
`export SDL_SOUNDFONT=/path/to/your/soundfont`

Fluidsynth will install a default soundfont in the following path:
On Fedora: `/usr/share/soundfonts/FluidR3_GM.sf2`
On Ubuntu/Debian: `/usr/share/sounds/sf2/FluidR3_GM.sf2`
