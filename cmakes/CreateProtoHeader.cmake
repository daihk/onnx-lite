cmake_minimum_required(VERSION 3.12)

if(NOT PROTOBUF_FOUND) 
    message(FATAL_ERROR "Not Find ProtoBuf.")
endif()

protobuf_generate_cpp(ONNX_PROTO_SRCS ONNX_PROTO_HDRS ${PROJECT_SOURCE_DIR}/onnx-proto/${ONNX_VERSION}/onnx.proto)

add_library(proto OBJECT)
target_sources(proto
    PRIVATE ${ONNX_PROTO_SRCS}
    )
target_link_libraries(proto PUBLIC libprotobuf)
target_include_directories(proto PUBLIC ${PROJECT_BINARY_DIR})
