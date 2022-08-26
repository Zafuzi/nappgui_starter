clear

rmdir /s /q build
mkdir build
cd build

cmake -G "Visual Studio 17 2022" ../src
msbuild NAppGUI.sln
cd ../
.\build\hello\Debug\Hello.exe