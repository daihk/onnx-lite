cmake_minimum_required(VERSION 3.13)

project(onnx-lite)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/onnxlite CACHE PATH "Default install prefix" FORCE)
endif()


set(VERSION 0.0.1)
set(ONNX_VERSION v1.10.1)

message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "ONNX-LITE Version: v${VERSION}")
message(STATUS "ONNX      Version: ${ONNX_VERSION}")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
include(${PROJECT_SOURCE_DIR}/cmakes/Base.cmake)
include(${PROJECT_SOURCE_DIR}/3rdparty/flatbuffers/CMake/FindFlatBuffers.cmake)
include(${PROJECT_SOURCE_DIR}/cmakes/FindProtobuf.cmake)
include(${PROJECT_SOURCE_DIR}/cmakes/CreateProtoHeader.cmake)
include(${PROJECT_SOURCE_DIR}/cmakes/CreateFlatHeader.cmake)
include(${PROJECT_SOURCE_DIR}/cmakes/CreateOnnxFlat.cmake)

add_subdirectory(src)
