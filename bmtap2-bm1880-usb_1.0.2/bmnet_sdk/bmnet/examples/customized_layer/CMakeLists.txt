cmake_minimum_required(VERSION 2.8.0)

include_directories("${bmnet_BINARY_DIR}/src")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories("${bmnet_BINARY_DIR}/")
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include) # override original bmnet_caffe.pb.h
include_directories("${bmnet_SOURCE_DIR}/../include")

set(LIBS ${LIBS} bmnet)
set(LIBS ${LIBS} bmkernel)
set(LIBS ${LIBS} glog)
set(LIBS ${LIBS} pthread)
set(LIBS ${LIBS} protobuf)
set(LIBS ${LIBS} boost_system)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR})

include(proto)
set(proto_path ${CMAKE_CURRENT_SOURCE_DIR}/proto)
proto_gen_cpp2(
    TARGET gen_bmnet_caffe_proto_cpp
    PROTO_PATH ${proto_path}
    PROTO ${proto_path}/bmnet/bmnet_caffe.proto
    CPP_OUT ${CMAKE_CURRENT_BINARY_DIR}/include
    SRCS bmnet_caffe_pb_src
    HDRS bmnet_caffe_pb_hdr)


add_executable(bm_builder_demo.bin
  bm_builder_demo.cpp
  layer_LeakyRelu.cpp tg_leakyrelu.cpp
  layer_Elu.cpp tg_elu.cpp
  ${bmnet_caffe_pb_src})
add_dependencies(bm_builder_demo.bin gen_bmnet_caffe_proto_cpp)
set_target_properties(bm_builder_demo.bin PROPERTIES PUBLIC_HEADER "${bmnet_caffe_pb_hdr}")
target_link_libraries(bm_builder_demo.bin ${LIBS})

install(TARGETS
        bm_builder_demo.bin
        DESTINATION bin
        PUBLIC_HEADER DESTINATION include)

set(LIBS ${LIBS} onnx)
set(LIBS ${LIBS} onnx_proto)
add_definitions(-DONNX_NAMESPACE=bmnet_onnx)
add_executable(bm_builder_onnx_demo.bin
  bm_builder_onnx_demo.cpp
  op_LeakyRelu.cpp tg_leakyrelu.cpp
  op_Elu.cpp tg_elu.cpp)
target_link_libraries(bm_builder_onnx_demo.bin ${LIBS})

install(TARGETS bm_builder_onnx_demo.bin
          DESTINATION bin)
