cmake_minimum_required(VERSION 3.12)

if(NOT FLATBUFFERS_FOUND) 
    message(FATAL_ERROR "Not Find Flatbuffers.")
endif()

FLATBUFFERS_GENERATE_C_HEADERS(ONNX_FLAT 
    "${PROJECT_SOURCE_DIR}/onnx-flat/base.fbs"
    "${PROJECT_SOURCE_DIR}/onnx-flat/${ONNX_VERSION}/onnx.fbs"
    )

string(REGEX REPLACE "v([0-9]+).([0-9]+).([0-9]+)" "\\1" ONNX_MAJOR ${ONNX_VERSION})
string(REGEX REPLACE "v([0-9]+).([0-9]+).([0-9]+)" "\\2" ONNX_MINOR ${ONNX_VERSION})
string(REGEX REPLACE "v([0-9]+).([0-9]+).([0-9]+)" "\\3" ONNX_PATCH ${ONNX_VERSION})
math(EXPR ONNX_INT_VERSION "${ONNX_MAJOR}*100000000+${ONNX_MINOR}*10000+${ONNX_PATCH}")
add_definitions(-DONNX_VERSION=${ONNX_INT_VERSION})

SUBDIRLIST(ONNX_VERSION_LIST ${PROJECT_SOURCE_DIR}/onnx-proto)
foreach(ONNX_BASE_VERSION ${ONNX_VERSION_LIST})
    string(REGEX REPLACE "v([0-9]+).([0-9]+).?([0-9]?)" "\\1" ONNX_BASE_MAJOR ${ONNX_BASE_VERSION})
    string(REGEX REPLACE "v([0-9]+).([0-9]+).?([0-9]?)" "\\2" ONNX_BASE_MINOR ${ONNX_BASE_VERSION})
    string(REGEX REPLACE "v([0-9]+).([0-9]+).?([0-9]?)" "\\3" ONNX_BASE_PATCH ${ONNX_BASE_VERSION})
    math(EXPR ONNX_BASE_INT_VERSION "${ONNX_BASE_MAJOR}*100000000+${ONNX_BASE_MINOR}*10000+${ONNX_BASE_PATCH}")
    add_definitions(-DONNX_V${ONNX_BASE_MAJOR}_${ONNX_BASE_MINOR}_${ONNX_BASE_PATCH}=${ONNX_BASE_INT_VERSION})
endforeach()

add_library(flat OBJECT ${ONNX_FLAT_OUTPUTS})
target_link_libraries(flat PRIVATE fbs)
target_sources(flat INTERFACE ${FLATBUFFERS_INCLUDE_DIR})
target_include_directories(flat PUBLIC ${CMAKE_BINARY_DIR})
