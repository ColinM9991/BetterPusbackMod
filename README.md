# About BetterPushback Mod X-Plane 11/12

This is a pushback plugin for the X-Plane 11/12 flight simulator.
It provides an overhead view to plan a pushback route and
accomplishes a fully automated "hands-off" pushback, letting the user
focus on aircraft startup and other pilot duties during pushback. It can
of course also tow you forward, or perform any arbitrarily complicated
pushback operation. To increase immersion, it speaks to you in a variety
of languages and accents, simulating ground staff at various places
around the world.

### About this Fork and Copyright

This is a fork of of OButler's BetterPushback fork.

To put it bluntly, this fork exists because I am fed up with non-developers vibe-coding functionality and believe the X-Plane ecosystem is going through a shift from well-designed plugins to vibe-coded systems. This isn't to gatekeep who can/can't use AI, or who can/can't contribute to plugins. Rather, it makes clear that using AI doesn't automatically make somebody a developer and the output still needs to be
1. Well designed
2. Peer reviewed by a human
3. The code assessed and following best practice

The purpose of this is to freeze the functionality in place, remove the recent AI contributions and allow for a version of BpB which sticks to the core principals of having a small, simple to use pushback system.

It's fine if anybody wishes to create pull requests against this particular version to fix issues. It's also fine if you wish to use AI to assist in the development of those features/bugfixes but you absolutely **must** have enough development experience to be able to independently review the code. Using an LLM to validate the output is not an acceptable means of validation - it needs to be human validation.

Any changes that cannot be explained in the authors own words (I.E; an explanation that is **not** produced by an LLM) will be rejected. Questions may range from
1. Explain this feature
2. Why did you opt for this block of code, over another approach?

## Downloading BetterPushback

_Coming Soon_

## Building BetterPushback

The Linux and Windows versions are built in one step on a Linux machine
(Windows is cross-compiled with MinGW-w64). The Mac version must be built on
macOS (10.9 or later).

BetterPushback depends on [libacfutils](https://codeberg.org/skiselkov/libacfutils),
which is included as a git submodule in `src/libacfutils`. Clone with
submodules, or initialize them after cloning:

```
$ git submodule update --init --recursive
```

### Linux / Windows Pre-requisites

The following packages are required to build libacfutils' bundled dependencies
(cairo, freetype, openal-soft, OpenSSL, curl, etc.), libacfutils itself (via
`qmake`) and BetterPushback (via `cmake`).

**Fedora:**

```
$ sudo dnf install gcc gcc-c++ make cmake git pkgconf-pkg-config \
    autoconf automake libtool patch tar bzip2 xz unzip \
    perl perl-core python3 \
    qt5-qtbase-devel \
    libstdc++-static glibc-static \
    mesa-libGL-devel mesa-libGLU-devel libX11-devel libXcursor-devel \
    alsa-lib-devel pulseaudio-libs-devel \
    mingw64-gcc mingw64-gcc-c++
```

Fedora installs qmake as `qmake-qt5`, but the libacfutils build scripts call
`qmake`, so add a symlink:

```
$ sudo ln -s "$(command -v qmake-qt5)" /usr/local/bin/qmake
```

**Ubuntu / Debian:** run `src/libacfutils/install-ubuntu-packages`, which
installs the equivalent packages via `apt`.

### Building libacfutils

libacfutils must be built before BetterPushback. First build its bundled
third-party dependencies:

```
$ cd src/libacfutils
$ CFLAGS='\ -std=gnu17' CXXFLAGS='\ -std=gnu++17' ./build_deps
```

>Note: the `CFLAGS`/`CXXFLAGS` override is required with recent compilers
>because some of the older bundled dependencies, such as cairo, do not
>compile under the newer default language standard. The leading `\ ` is intentional: `build_dep.common` passes the
>flags through `eval`, so the space must be escaped.

Then build the libacfutils static library for Linux and Windows:

```
$ cd qmake
$ ./build-win-lin
```

This produces `qmake/lin64/libacfutils.a` and `qmake/win64/libacfutils.a`,
which `src/CMakeLists.txt` links against. On macOS use `./build-mac` instead.

### Building the Plugin

The global build script is located here and is called '```build_release```'.
Once libacfutils is built, simply run:
***
```
$ ./build_release
```
This builds BetterPushback for the appropriate target platforms (Linux and
Windows on a Linux host, macOS on a Mac host). Please note that this builds a
stand-alone version of the plugin that is to be installed into the global
Resources/plugins directory in X-Plane.
***

For details on how to add tug liveries, see
`objects/tugs/LIVERIES_HOWTO.txt`.

To add a voice set, see `data/msgs/README.txt` for the information.

### CREDIT

Original version by skiselkov: https://github.com/skiselkov/BetterPushbackC
Forked version by obutler: https://github.com/olivierbutler/BetterPusbackMod

### DISCLAIMER

BetterPushback is *NOT* meant for flight training or use in real avionics. Its
performance can seriously deviate from the real world system, so *DO NOT*
rely on it for anything critical. It was created solely for entertainment
use. This project has *no* ties to Honeywell or Laminar Research.
