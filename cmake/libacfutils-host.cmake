# Passed to libacfutils' native CMake dependency builds via the
# CMAKE_TOOLCHAIN_FILE environment variable (see build_libacfutils).
# On distros such as Fedora, GNUInstallDirs installs into lib64, but the
# libacfutils scripts only look in lib.
set(CMAKE_INSTALL_LIBDIR lib CACHE PATH "Object code libraries (lib)")
