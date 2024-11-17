# CMake SFML Project Setup

Requirements:

- [MingW 13.1](https://github.com/brechtsanders/winlibs_mingw/releases/download/13.1.0-16.0.5-11.0.0-msvcrt-r5/winlibs-x86_64-posix-seh-gcc-13.1.0-mingw-w64msvcrt-11.0.0-r5.7z)

- [Git](https://git-scm.com/downloads)

- [CMake](https://cmake.org/download)

## Build Commands

- build only `cmake --build build`

- build and run `cmake --build build -t run`

- run only `cmake --build build -t run-only`

## How to Use

If you want to add or remove any .cpp files, change the source files listed in the `add_executable` call in CMakeLists.txt to match the source files your project requires. If you plan on keeping the default main.cpp file then no changes are required.

If your code uses the Audio or Network modules then add `sfml-audio` or `sfml-network` to the `target_link_libraries` call alongside the existing `sfml-graphics` library that is being linked.

If you use Linux, install SFML's dependencies using your system package manager. On Ubuntu and other Debian-based distributions you can use the following commands:

```
sudo apt update
sudo apt install \
    libxrandr-dev \
    libxcursor-dev \
    libudev-dev \
    libfreetype-dev \
    libopenal-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev
```

Configure and build your project. Most popular IDEs support CMake projects with very little effort on your part.

- [VS Code](https://code.visualstudio.com) via the [CMake extension](https://code.visualstudio.com/docs/cpp/cmake-linux)
- [Visual Studio](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170)
- [CLion](https://www.jetbrains.com/clion/features/cmake-support.html)
- [Qt Creator](https://doc.qt.io/qtcreator/creator-project-cmake.html)

## Upgrading SFML

SFML is found via CMake's [FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html) module.
FetchContent automatically downloads SFML from GitHub and builds it alongside your own code.
Beyond the convenience of not having to install SFML yourself, this ensures ABI compatibility and simplifies things like specifying static versus shared libraries.

Modifying what version of SFML you want is as easy as changing the [`GIT_TAG`](CMakeLists.txt#L7) argument.
Currently it uses the latest in-development version of SFML 2 via the `2.6.x` tag.
If you're feeling adventurous and want to give SFML 3 a try, use the `master` tag.
Beware, this requires changing your code to suit the modified API!
The nice folks in the [SFML community](https://github.com/SFML/SFML#community) can help you with that transition and the bugs you may encounter along the way.

## Here are some useful resources if you want to learn more about CMake:

- [Official CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/)
- [How to Use CMake Without the Agonizing Pain - Part 1](https://alexreinking.com/blog/how-to-use-cmake-without-the-agonizing-pain-part-1.html)
- [How to Use CMake Without the Agonizing Pain - Part 2](https://alexreinking.com/blog/how-to-use-cmake-without-the-agonizing-pain-part-2.html)
- [Better CMake YouTube series by Jefferon Amstutz](https://www.youtube.com/playlist?list=PL8i3OhJb4FNV10aIZ8oF0AA46HgA2ed8g)
