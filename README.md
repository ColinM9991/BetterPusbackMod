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

To build BetterPushback, check to see you have the pre-requisites installed. The
Linux and Windows versions are built in one step on an Ubuntu 16.04 (or
compatible) machine and the Mac version is obviously built on macOS (10.9
or later).

>Note: __on macOS only__ , by using the option ```-f```, the script will build also the linux and windows versions. see ```README-docker.md```.  

For the Linux and Mac build pre-requisites, see ```build_xpl.sh```

The global build script is located here and is called '```build_release```'.
Once you have the pre-requisite build packages installed, simply run:
***
```
$ ./build_release [-f]
```
This builds the dependencies and then proceeds to build BetterPushback for the appropriate target platforms. Please note that this builds a
stand-alone version of the plugin that is to be installed into the global
Resources/plugins directory in X-Plane.
***
```
$ ./build_xpl_sh [-f] 
```
This build only the .xpl file. (option described above can be used)
***
```
$ ./install_xplane.sh
```
Copy the .xpl files to the x-plane and change the quarantine attribute of the ```mac.xpl``` file.  
In the script, just set ```XPLANE_PLUGIN_DIR``` accordingly. 
***

For details on how to add tug liveries, see
`objects/tugs/LIVERIES_HOWTO.txt`.

To add a voice set, see `data/msgs/README.txt` for the information.

### libacfutils Library Required

I removed from the project. It need to by downloaded separatly. To make sure you have a matched version, take the fork in my repository.
To connect with the library setup the Library in the "CMakeLists.txt" File in the "src" directory.

file(GLOB LIBACFUTILS "../../../libs/libacfutils")

As I found out in the last view days the relation to this library are very hard and many issues come from here ... it is not possible to splitup the library.

The library can be found here:
https://github.com/olivierbutler/libacfutils

### CREDIT

Original version by skiselkov: https://github.com/skiselkov/BetterPushbackC

### DISCLAIMER

BetterPushback is *NOT* meant for flight training or use in real avionics. Its
performance can seriously deviate from the real world system, so *DO NOT*
rely on it for anything critical. It was created solely for entertainment
use. This project has *no* ties to Honeywell or Laminar Research.
