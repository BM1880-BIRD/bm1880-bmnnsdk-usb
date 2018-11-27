cmake_minimum_required(VERSION 2.8.0)
project(cpu_op CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${PROJECT_SOURCE_DIR}/../../../../install/include/)
include_directories(${PROJECT_SOURCE_DIR}/../../../../include)
include_directories(${CMAKE_INSTALL_PREFIX}/include/)
include_directories(${BMTAP_INSTALL_PATH}/include/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s -std=gnu++11")

if (CMAKE_CROSSCOMPILING)
  set(target_platform "armv8")
  include_directories(${PROJECT_SOURCE_DIR}/../../../prebuilt/armv8/include)
  link_directories(${PROJECT_SOURCE_DIR}/../../../prebuilt/armv8/lib)
  link_directories(${CMAKE_INSTALL_PREFIX}/lib/armv8/)
else()
  set(target_platform "x86_64")
  link_directories(${CMAKE_INSTALL_PREFIX}/lib/x86_64/)
endif()

function(add_cpu_plugin)
  message(STATUS "To build cpu op for ${target_platform} platform")
  foreach(arg IN LISTS ARGN)
    get_filename_component(target ${arg} NAME_WE)
    message(STATUS "To build ${arg} for cpu plugin: ${target}")
    add_library(${target} SHARED
      ${CMAKE_CURRENT_SOURCE_DIR}/${arg})
    target_link_libraries(${target} cpu-plugin protobuf glog)
    set_target_properties(${target} PROPERTIES LINKER_LANGUAGE CXX)
    set_target_properties(${target} PROPERTIES PREFIX "")

    install(TARGETS ${target} DESTINATION lib/${target_platform})
  endforeach()
endfunction()

add_cpu_plugin(ELU.cpp LeakyRelu.cpp)
