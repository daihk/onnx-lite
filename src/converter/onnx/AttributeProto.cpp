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
#include "AttributeProto.h"

#include "TensorProto.h"
#include "GraphProto.h"
#include "SparseTensorProto.h"
#include "TypeProto.h"

flatbuffers::Offset<onnx_flat::AttributeProto> AttributeProto::convert(
        flatbuffers::FlatBufferBuilder& fbb,
        const onnx::AttributeProto& proto) 
{
    return onnx_flat::CreateAttributeProto(

            fbb
            , PROTO_OPTIONAL(String,              name)
#if ONNX_VERSION > ONNX_V1_1_2
            , PROTO_OPTIONAL(String,              ref_attr_name)
#endif
            , PROTO_OPTIONAL(String,              doc_string)
            , PROTO_ENUM(AttributeProto_::AttributeType, type)
            , PROTO_OPTIONAL(Float,               f)
            , PROTO_OPTIONAL(Long,                i)
            , PROTO_OPTIONAL(UChar,               s)
            , PROTO_OPTIONAL(TensorProto,         t)
            , PROTO_OPTIONAL(GraphProto,          g)
#if ONNX_VERSION >= ONNX_V1_6_0
            , PROTO_OPTIONAL(SparseTensorProto,   sparse_tensor)
#endif
#if ONNX_VERSION >= ONNX_V1_10_0
            , PROTO_OPTIONAL(TypeProto,           tp)
#endif
            , PROTO_REPEATED(Float,               floats)
            , PROTO_REPEATED(Long,                ints)
            , PROTO_REPEATED(String,              strings)
            , PROTO_REPEATED(TensorProto,         tensors)
            , PROTO_REPEATED(GraphProto,          graphs)
#if ONNX_VERSION >= ONNX_V1_6_0
            , PROTO_REPEATED(SparseTensorProto,   sparse_tensors)
#endif
#if ONNX_VERSION >= ONNX_V1_10_0
            , PROTO_REPEATED(TypeProto,           type_protos)
#endif
            );
}

onnx::AttributeProto AttributeProto::convert(
        const onnx_flat::AttributeProto* flat) 
{
    onnx::AttributeProto proto;
    FLAT_CONVERT(String,                name);
#if ONNX_VERSION > ONNX_V1_1_2
    FLAT_CONVERT(String,                ref_attr_name);
#endif
    FLAT_CONVERT(String,                doc_string);
    FLAT_ENUM(AttributeProto_AttributeType, type);
    FLAT_SETTING(Float,                 f);
    FLAT_SETTING(Long,                  i);
    FLAT_CONVERT(UChar,                 s);
    FLAT_CONVERT(TensorProto,           t);
    FLAT_CONVERT(GraphProto,            g);
#if ONNX_VERSION >= ONNX_V1_6_0
    FLAT_CONVERT(SparseTensorProto,     sparse_tensor);
#endif
#if ONNX_VERSION >= ONNX_V1_10_0
    FLAT_CONVERT(TypeProto,             tp);
#endif
    FLAT_CONVERT(Float,                 floats);
    FLAT_CONVERT(Long,                  ints);
    FLAT_CONVERT(TensorProto,           tensors);
    FLAT_CONVERT(GraphProto,            graphs);
#if ONNX_VERSION >= ONNX_V1_6_0
    FLAT_CONVERT(SparseTensorProto,     sparse_tensors);
#endif
#if ONNX_VERSION >= ONNX_V1_10_0
    FLAT_CONVERT(TypeProto,             type_protos);
#endif
    return proto;
}
