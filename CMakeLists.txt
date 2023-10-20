cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(FiveOClock_Caves VERSION 0.1)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake-module")
set(THIRDPARTY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /bigobj")
# add thirdparties
include(thirdparty/thirdparty.cmake)

# subdirectories
add_subdirectory(src)