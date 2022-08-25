#------------------------------------------
# NAppGUI CMake build script
#------------------------------------------
cmake_minimum_required(VERSION 2.8.12)
project(NAppGUI)

# NAppGUI Build Scripts
get_filename_component(ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR} PATH)
include(${ROOT_PATH}/prj/CMakeNAppGUI.txt)

# Libraries
staticLib("sewer" "" NRC_NONE)
staticLib("osbs" "sewer" NRC_NONE)
staticLib("core" "osbs" NRC_NONE)
staticLib("geom2d" "core" NRC_NONE)
staticLib("draw2d" "geom2d" NRC_NONE)
staticLib("osgui" "draw2d" NRC_NONE)
staticLib("gui" "draw2d" NRC_EMBEDDED)
staticLib("osapp" "osgui;gui" NRC_NONE)
staticLib("inet" "core" NRC_NONE)

# Exes
desktopApp("Hello" "hello" "" NRC_EMBEDDED)
