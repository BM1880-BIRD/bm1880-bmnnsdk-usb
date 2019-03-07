cmake_minimum_required(VERSION 2.8.0)
set(CMAKE_INSTALL_PREFIX_DEFAULT OFF CACHE BOOL "use default install path")
if (CMAKE_INSTALL_PREFIX_DEFAULT)
    unset(CMAKE_INSTALL_PREFIX CACHE)
else()
    set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install CACHE PATH "install path")
endif()

project(bmnet CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BMNET_EXPORT_PATH ${CMAKE_INSTALL_PREFIX})
include_directories("${BMNET_EXPORT_PATH}/include")
link_directories("${BMNET_EXPORT_PATH}/lib")

add_subdirectory(examples)
