option(BUILD_CUSTOMIZED_LAYER_DEMO "build customized layer demo" OFF)

if (BUILD_CUSTOMIZED_LAYER_DEMO)
  add_subdirectory(customized_layer_plugin)
endif()
