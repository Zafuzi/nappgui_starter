# NAppGUI
Cross-Platform C SDK. Build portable desktop applications for Windows, macOS and Linux.

![NAppGUI Stack](https://nappgui.com/img/quick/nappgui_stack.png)

## Prerequisites
- [Visual Studio 2019](https://visualstudio.microsoft.com/vs/) - Windows
- [Xcode 10 or 11](https://developer.apple.com/xcode/) - macOS Mojave or Catalina
- GCC 7 - Ubuntu 18.04 LTS
- [CMake](https://cmake.org/download/) - Cross platform

## Running on Windows
### Open a terminal
```
C:\>git clone https://github.com/frang75/nappgui.git C:\nappgui
```

It will create a working copy on `C:\nappgui`

### Open CMake
- **Where is the source code:** `C:\nappgui\src` (Or `src` folder in your working copy)
- **Where to build the binaries:** `C:\nappgui_build` (Or other folder)
- [Configure]
- [Generate]
- [Open Project]

![NAppGUI CMake](https://nappgui.com/img/start/nappgui_cmake.png)

You must select the **Visual Studio 16 2019** generator with **x64** platform the first time.

![NAppGUI Generator](https://nappgui.com/img/start/cmake_generator.png)

### In Visual Studio 2019 (after click in [Open Project])
- Build->Build Solution
- Run the examples under `demo` or `howto`

![NAppGUI Build](https://nappgui.com/img/start/rundemo_visualstudio.png)

## Running on macOS

Get the working copy and run CMake in the same way as Windows, using `Xcode` generator.

```
git clone https://github.com/frang75/nappgui.git ~/nappgui
```
![Xcode_Debugging](https://nappgui.com/img/start/xcode_debug.png)

**Important:** `CMAKE_DEPLOYMENT_TARGET` must be `10.15` or `10.14`

## More info
- [NAppGUI Quick Start](https://nappgui.com/en/start/quick.html)
- [NAppGUI Hello World](https://nappgui.com/en/start/hello.html)
- [Create a new project](https://nappgui.com/en/start/newprj.html)
- [About Portability](https://nappgui.com/en/start/win_mac_linux.html)

