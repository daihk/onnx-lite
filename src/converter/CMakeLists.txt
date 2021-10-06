cmake_minimum_required(VERSION 3.12)

add_executable(converter)
target_sources(converter
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/main.cpp
            ${CMAKE_CURRENT_LIST_DIR}/onnx/AttributeProto.cpp
            ${CMAKE_CURRENT_LIST_DIR}/onnx/GraphProto.cpp
            ${CMAKE_CURRENT_LIST_DIR}/onnx/ModelProto.cpp
            ${CMAKE_CURRENT_LIST_DIR}/onnx/NodeProto.cpp
            ${CMAKE_CURRENT_LIST_DIR}/onnx/OperatorSetIdProto.cpp
            ${CMAKE_CURRENT_LIST_DIR}/onnx/StringStringEntryProto.cpp
            ${CMAKE_CURRENT_LIST_DIR}/onnx/TensorProto.cpp
            ${CMAKE_CURRENT_LIST_DIR}/onnx/TensorShapeProto.cpp
            ${CMAKE_CURRENT_LIST_DIR}/onnx/TypeProto.cpp
            ${CMAKE_CURRENT_LIST_DIR}/onnx/ValueInfoProto.cpp
            ${CMAKE_CURRENT_LIST_DIR}/onnx/SparseTensorProto.cpp
            ${CMAKE_CURRENT_LIST_DIR}/onnx/TensorAnnotation.cpp
            ${CMAKE_CURRENT_LIST_DIR}/onnx/TrainingInfoProto.cpp
            ${CMAKE_CURRENT_LIST_DIR}/onnx/FunctionProto.cpp
    )

target_link_libraries(converter PUBLIC proto)
target_link_libraries(converter PUBLIC flat)
target_include_directories(converter PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/onnx
    )

install(TARGETS converter RUNTIME DESTINATION bin)
