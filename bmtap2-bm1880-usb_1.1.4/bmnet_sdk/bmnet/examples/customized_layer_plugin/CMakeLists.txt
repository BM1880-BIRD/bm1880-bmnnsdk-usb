cmake_minimum_required(VERSION 2.8.0)

include_directories("${bmnet_BINARY_DIR}/src")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories("${bmnet_BINARY_DIR}/")
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include) # override original bmnet_caffe.pb.h
include_directories("${bmnet_SOURCE_DIR}/../include")
include_directories("${bmnet_SOURCE_DIR}/../install/include")
include_directories("${bmnet_SOURCE_DIR}/../install/include/caffe/proto")

set(LIBS ${LIBS} onnx)
set(LIBS ${LIBS} onnx_proto)
add_definitions(-DONNX_NAMESPACE=bmnet_onnx)
set(LIBS ${LIBS} bmnet)
set(LIBS ${LIBS} bmkernel)
set(LIBS ${LIBS} glog)
set(LIBS ${LIBS} pthread)
set(LIBS ${LIBS} protobuf)
set(LIBS ${LIBS} boost_system)
set(LIBS ${LIBS} yaml-cpp)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR})

find_package(LLVM 5 CONFIG)
add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})

add_library(Elu SHARED
    relu/Elu.cpp
    relu/op_Elu.cpp
    relu/tg_elu.cpp
    relu/layer_Elu.cpp)
add_dependencies(Elu bmnet onnx yaml-cpp)
target_link_libraries(Elu "libyaml-cpp.so")
install(TARGETS Elu DESTINATION lib/plugin)

add_library(LeakyRelu SHARED
    leakyrelu/LeakyRelu.cpp
    leakyrelu/layer_LeakyRelu.cpp
    leakyrelu/op_LeakyRelu.cpp
    leakyrelu/tg_leakyrelu.cpp)
add_dependencies(LeakyRelu bmnet onnx yaml-cpp)
target_link_libraries(LeakyRelu "libyaml-cpp.so")
install(TARGETS LeakyRelu DESTINATION lib/plugin)

