/* MIT License
 * 
 * Copyright (c) 2021 daihk
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "ModelProto.h"

#include "OperatorSetIdProto.h"
#include "GraphProto.h"
#include "StringStringEntryProto.h"
#include "TrainingInfoProto.h"
#include "FunctionProto.h"

flatbuffers::Offset<onnx_flat::ModelProto> ModelProto::convert(
        flatbuffers::FlatBufferBuilder& fbb,
        const onnx::ModelProto& proto)
{

    return onnx_flat::CreateModelProto(
            fbb
            , PROTO_OPTIONAL(Long,                ir_version)
            , PROTO_REPEATED(OperatorSetIdProto,  opset_import)
            , PROTO_OPTIONAL(String,              producer_name)
            , PROTO_OPTIONAL(String,              producer_version)
            , PROTO_OPTIONAL(String,              domain)
            , PROTO_OPTIONAL(Long,                model_version)
            , PROTO_OPTIONAL(String,              doc_string)
            , PROTO_OPTIONAL(GraphProto,          graph)
            , PROTO_REPEATED(StringStringEntryProto, metadata_props)
#if ONNX_VERSION >= ONNX_V1_7_0
            , PROTO_REPEATED(TrainingInfoProto,   training_info)
#endif
#if ONNX_VERSION >= ONNX_V1_10_0
            , PROTO_REPEATED(FunctionProto,       functions)
#endif
            );
}

onnx::ModelProto ModelProto::convert(
        const onnx_flat::ModelProto* flat)
{
    onnx::ModelProto proto;
    FLAT_SETTING(Long,                  ir_version);
    FLAT_CONVERT(OperatorSetIdProto,    opset_import);
    FLAT_CONVERT(String,                producer_name);
    FLAT_CONVERT(String,                producer_version);
    FLAT_CONVERT(String,                domain);
    FLAT_SETTING(Long,                  model_version);
    FLAT_CONVERT(String,                doc_string);
    FLAT_CONVERT(GraphProto,            graph);
    FLAT_CONVERT(StringStringEntryProto,metadata_props);
#if ONNX_VERSION >= ONNX_V1_7_0
    FLAT_CONVERT(TrainingInfoProto,     training_info);
#endif
#if ONNX_VERSION >= ONNX_V1_10_0
    FLAT_CONVERT(FunctionProto,         functions);
#endif
    return proto;
}
