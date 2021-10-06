cmake_minimum_required(VERSION 3.12)

if(NOT FLATBUFFERS_FOUND) 
    message(FATAL_ERROR "Not Find Flatbuffers.")
endif()

set(ONNX_FLATC_PATH   onnx-flat/${ONNX_VERSION})
set(ONNX_FLATC_OUTPUT ${ONNX_FLATC_PATH}/onnx.fbs)
set(ONNX_FLATC_INPUT  onnx-proto/${ONNX_VERSION}/onnx.proto)
file(MAKE_DIRECTORY ${ONNX_FLATC_PATH})

add_custom_command(OUTPUT ${ONNX_FLATC_OUTPUT}
    COMMAND ${FLATBUFFERS_FLATC_EXECUTABLE} 
    ARGS --proto -o ${ONNX_FLATC_PATH} ${ONNX_FLATC_INPUT}
    COMMAND sed 
    ARGS -i \"2i\/\/ Modify base type by onnx-flat\\n\" ${ONNX_FLATC_OUTPUT}
    COMMAND sed 
    ARGS -i \"4iinclude \\\"\\.\\.\\/base\.fbs\\\"\\;\\n\" ${ONNX_FLATC_OUTPUT}
    COMMAND sed 
    ARGS -i \"s/onnx/onnx_flat/g\" ${ONNX_FLATC_OUTPUT}
    COMMAND sed 
    ARGS -i \"s/\\:float\\;/\\:Float\\;/g\" ${ONNX_FLATC_OUTPUT}
    COMMAND sed 
    ARGS -i \"s/\\:double\\;/\\:Double\\;/g\" ${ONNX_FLATC_OUTPUT}
    COMMAND sed 
    ARGS -i \"s/\\:int\\;/\\:Int\\;/g\" ${ONNX_FLATC_OUTPUT}
    COMMAND sed 
    ARGS -i \"s/\\:uint\\;/\\:UInt\\;/g\" ${ONNX_FLATC_OUTPUT}
    COMMAND sed 
    ARGS -i \"s/\\:long\\;/\\:Long\\;/g\" ${ONNX_FLATC_OUTPUT}
    COMMAND sed 
    ARGS -i \"s/\\:ulong\\;/\\:ULong\\;/g\" ${ONNX_FLATC_OUTPUT}
    DEPENDS ${ONNX_FLATC_INPUT}
    COMMENT "Create onnx.fbs from onnx.proto"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_library(fbs OBJECT ${ONNX_FLATC_OUTPUT})
