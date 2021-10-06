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
#include "GraphProto.h"

#include "NodeProto.h"
#include "TensorProto.h"
#include "ValueInfoProto.h"
#include "SparseTensorProto.h"
#include "TensorAnnotation.h"

flatbuffers::Offset<onnx_flat::GraphProto> GraphProto::convert(
        flatbuffers::FlatBufferBuilder& fbb,
        const onnx::GraphProto& proto) 
{
    return onnx_flat::CreateGraphProto(
            fbb
            , PROTO_REPEATED(NodeProto,       node)
            , PROTO_OPTIONAL(String,          name)
            , PROTO_REPEATED(TensorProto,     initializer)
#if ONNX_VERSION >= ONNX_V1_6_0
            , PROTO_REPEATED(SparseTensorProto,   sparse_initializer)
#endif
            , PROTO_OPTIONAL(String,          doc_string)
            , PROTO_REPEATED(ValueInfoProto,  input)
            , PROTO_REPEATED(ValueInfoProto,  output)
            , PROTO_REPEATED(ValueInfoProto,  value_info)
#if ONNX_VERSION >= ONNX_V1_5_0
            , PROTO_REPEATED(TensorAnnotation,quantization_annotation)
#endif
            );
}

onnx::GraphProto GraphProto::convert(
        const onnx_flat::GraphProto* flat) 
{
    onnx::GraphProto proto;
    FLAT_CONVERT(NodeProto,         node);
    FLAT_CONVERT(String,            name);
    FLAT_CONVERT(TensorProto,       initializer);
#if ONNX_VERSION >= ONNX_V1_6_0
    FLAT_CONVERT(SparseTensorProto, sparse_initializer);
#endif
    FLAT_CONVERT(String,            doc_string);
    FLAT_CONVERT(ValueInfoProto,    input);
    FLAT_CONVERT(ValueInfoProto,    output);
    FLAT_CONVERT(ValueInfoProto,    value_info);
#if ONNX_VERSION >= ONNX_V1_5_0
    FLAT_CONVERT(TensorAnnotation,  quantization_annotation);
#endif
    return proto;
}
