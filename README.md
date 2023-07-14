# About project
skgl is the OpenGL boilerplate for avoid of writing routine code and focus on solving tasks related to the 3d-graphics in c++ fashion. The main conception behind skgl is that sharing is caring. So it uses shared objects whenever and wherever it's possible and impossible. So when you use shaders, textures, buffers and others skgl's objects - you can relax and do not think about manual memory management.

# How to download
This project uses git submodules so to download you should use:

`git clone --recurse-submodules https://github.com/serkosal/skgl.git`

If you've just already downloaded it without --recurse-submodules, you should go inside downloaded skgl folder and then execute:

`git submodule init`

`git submodule update`

# How to build

## Windows using Microsoft Visual Studio
1. Open skgl folder in Visual Studio.
2. Wait before visual studio completely generate cmake configuration for your platform. By default it's will be writed in the console panel below.
3. In the Solution Explorer find and right click on the CMakeLists.txt.
4. Select build.
5. Wait untill build process ends.
6. Your executable by default will be located in skgl/out/build/YOURS_BUILD_CONFIGURATION/skgl.exe

## Linux using g++
Open skgl folder in the terminal and execute the following commands:

`mkdir build`

`cd build`

`cmake -S . -B build/`

`make`

And finally you can launch it using the following command:

`./build/skgl`
