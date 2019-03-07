
include(CMakeParseArguments)
include(assert)

function(proto_gen_cpp)
    cmake_parse_arguments(ARG "" "TARGET;PROTO;CPP_OUT;SRCS;HDRS" "DEPENDS" ${ARGN})
    # check argument
    assert_var(ARG_TARGET ARG_PROTO)
    if (NOT ARG_CPP_OUT)
        set(ARG_CPP_OUT ${CMAKE_CURRENT_BINARY_DIR})
    endif()
    # setup varialbe
    get_filename_component(ARG_PROTO ${ARG_PROTO} ABSOLUTE)
    get_filename_component(proto_name_we ${ARG_PROTO} NAME_WE)
    get_filename_component(proto_path ${ARG_PROTO} DIRECTORY)
    set(hdrs ${ARG_CPP_OUT}/${proto_name_we}.pb.h)
    set(srcs ${ARG_CPP_OUT}/${proto_name_we}.pb.cc)
    set(out ${hdrs} ${srcs})
    # add target
    add_custom_target(${ARG_TARGET}_dir
        COMMAND ${CMAKE_COMMAND} -E make_directory ${ARG_CPP_OUT})
    add_custom_command(OUTPUT ${out}
        COMMAND protoc --proto_path=${proto_path} --cpp_out=${ARG_CPP_OUT} ${ARG_PROTO}
        DEPENDS ${ARG_PROTO})
    add_custom_target(${ARG_TARGET}
        DEPENDS ${ARG_TARGET}_dir ${ARG_DEPENDS} ${out})
    set(${ARG_SRCS} ${srcs} PARENT_SCOPE)
    set(${ARG_HDRS} ${hdrs} PARENT_SCOPE)
endfunction()

function(proto_gen_cpp2)
    cmake_parse_arguments(ARG "" "TARGET;PROTO;CPP_OUT;SRCS;HDRS" "DEPENDS;PROTO_PATH" ${ARGN})
    # check argument
    assert_var2(ARG TARGET PROTO)
    if (NOT ARG_CPP_OUT)
        set(ARG_CPP_OUT ${CMAKE_CURRENT_BINARY_DIR})
    endif()
    get_filename_component(ARG_PROTO ${ARG_PROTO} ABSOLUTE)
    if (NOT ARG_PROTO_PATH)
        get_filename_component(ARG_PROTO_PATH ${ARG_PROTO} DIRECTORY)
    endif()
    set(t "")
    foreach(p ${ARG_PROTO_PATH})
        get_filename_component(p ${p} ABSOLUTE)
        list(APPEND t ${p})
    endforeach()
    set(ARG_PROTO_PATH ${t})
    # setup varialbe
    list(GET ARG_PROTO_PATH 0 ARG_PROTO_PATH_0)
    file(RELATIVE_PATH relative_path ${ARG_PROTO_PATH_0} ${ARG_PROTO})
    get_filename_component(relative_path ${relative_path} DIRECTORY)
    get_filename_component(proto_name_we ${ARG_PROTO} NAME_WE)
    set(hdrs ${ARG_CPP_OUT}/${relative_path}/${proto_name_we}.pb.h)
    set(srcs ${ARG_CPP_OUT}/${relative_path}/${proto_name_we}.pb.cc)
    set(out ${hdrs} ${srcs})
    # add target
    add_custom_target(${ARG_TARGET}_dir
        COMMAND ${CMAKE_COMMAND} -E make_directory ${ARG_CPP_OUT})
    set(arg "")
    foreach(p ${ARG_PROTO_PATH})
        list(APPEND arg --proto_path=${p})
    endforeach()
    add_custom_command(OUTPUT ${out}
        COMMAND protoc ${arg}  --cpp_out=${ARG_CPP_OUT} ${ARG_PROTO}
        DEPENDS ${ARG_PROTO})
    add_custom_target(${ARG_TARGET}
        DEPENDS ${ARG_TARGET}_dir ${ARG_DEPENDS} ${out})
    set(${ARG_SRCS} ${srcs} PARENT_SCOPE)
    set(${ARG_HDRS} ${hdrs} PARENT_SCOPE)
endfunction()

function(proto_gen_cpp_and_install2)
    cmake_parse_arguments(ARG "" "TARGET;SRCS;HDRS;PROTO_PATH;PROTO;SOURCE_BASE" "DEPENDS" ${ARGN})
    # setup varialbe
    get_filename_component(ARG_PROTO ${ARG_PROTO} ABSOLUTE)
    #add target
    proto_gen_cpp2(
        TARGET ${ARG_TARGET}
        PROTO_PATH ${ARG_PROTO_PATH}
        PROTO ${ARG_PROTO}
        CPP_OUT ${PROJECT_BINARY_DIR}/include
        SRCS srcs
        HDRS hdrs
        DEPENDS ${ARG_DEPENDS})
    #set return variable
    set(${ARG_SRCS} ${srcs} PARENT_SCOPE)
    set(${ARG_HDRS} ${hdrs} PARENT_SCOPE)
    #install
    file(RELATIVE_PATH relative_path ${ARG_PROTO_PATH} ${ARG_PROTO})
    get_filename_component(relative_path ${relative_path} DIRECTORY)
    INSTALL(FILES ${hdrs}
        DESTINATION include/${relative_path})
endfunction()


function(proto_gen_cpp_and_install)
    cmake_parse_arguments(OPT "" "TARGET;SRCS;HDRS;PROTO;SOURCE_BASE;PREFIX" "" ${ARGN})
    assert_var(OPT_SOURCE_BASE OPT_PREFIX)
    #prepare proto name
    get_filename_component(OPT_PROTO ${OPT_PROTO} ABSOLUTE)
    get_filename_component(proto_name_we ${OPT_PROTO} NAME_WE)
    #prepare target name and path
    file(RELATIVE_PATH relative_path ${OPT_SOURCE_BASE} ${CMAKE_CURRENT_SOURCE_DIR})
    set(include_relative_path include/${OPT_PREFIX}/${relative_path})
    set(out_path ${PROJECT_BINARY_DIR}/${include_relative_path})
    #set return variable
    proto_gen_cpp(
        TARGET ${OPT_TARGET}
        PROTO ${OPT_PROTO}
        CPP_OUT ${out_path}
        SRCS srcs
        HDRS hdrs)
    set(${OPT_SRCS} ${srcs} PARENT_SCOPE)
    set(${OPT_HDRS} ${hdrs} PARENT_SCOPE)
    #install
    INSTALL(FILES ${hdrs}
        DESTINATION ${include_relative_path})
endfunction()


function(proto_gen_py)
    cmake_parse_arguments(ARG "" "TARGET;PROTO;PYTHON_OUT;PYS" "DEPENDS;PROTO_PATH" ${ARGN})
    # check argument
    get_filename_component(ARG_PROTO ${ARG_PROTO} ABSOLUTE)
    if (NOT ARG_PROTO_PATH)
        get_filename_component(ARG_PROTO_PATH ${ARG_PROTO} DIRECTORY)
    endif()
    set(t "")
    foreach(p ${ARG_PROTO_PATH})
        get_filename_component(p ${p} ABSOLUTE)
        list(APPEND t ${p})
    endforeach()
    set(ARG_PROTO_PATH ${t})
    if (NOT ARG_PYTHON_OUT)
        set(ARG_PYTHON_OUT ${CMAKE_CURRENT_BINARY_DIR})
    endif()
    # setup varialbe
    list(GET ARG_PROTO_PATH 0 ARG_PROTO_PATH_0)
    file(RELATIVE_PATH relative_path ${ARG_PROTO_PATH_0} ${ARG_PROTO})
    get_filename_component(relative_path ${relative_path} DIRECTORY)
    get_filename_component(proto_name_we ${ARG_PROTO} NAME_WE)
    set(out ${ARG_PYTHON_OUT}/${relative_path}/${proto_name_we}_pb2.py)
    set(arg "")
    foreach(p ${ARG_PROTO_PATH})
        list(APPEND arg --proto_path=${p})
    endforeach()
    add_custom_command(OUTPUT ${out}
        COMMAND protoc ${arg} --python_out=${ARG_PYTHON_OUT} ${ARG_PROTO}
        DEPENDS ${ARG_PROTO})
    add_custom_target(${ARG_TARGET}
        DEPENDS ${ARG_DEPENDS} ${out})
    set(${ARG_PYS} ${out} PARENT_SCOPE)
endfunction()
