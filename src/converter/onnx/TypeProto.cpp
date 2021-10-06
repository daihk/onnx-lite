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
#include "TypeProto.h"

#include "TensorShapeProto.h"

class Tensor{
public:
    inline static flatbuffers::Offset<onnx_flat::TypeProto_::Tensor> convert(
            flatbuffers::FlatBufferBuilder& fbb,
            const onnx::TypeProto_Tensor& proto)
    {
        return onnx_flat::TypeProto_::CreateTensor(
                fbb
#if ONNX_VERSION >= ONNX_V1_4_0
                , PROTO_OPTIONAL(Int,   elem_type)
#else
                , PROTO_ENUM(TensorProto_::DataType,  elem_type)
#endif
                , PROTO_OPTIONAL(TensorShapeProto,   shape)
                );

   }
    inline static onnx::TypeProto_Tensor convert(
            const onnx_flat::TypeProto_::Tensor* flat)
    {
        onnx::TypeProto_Tensor proto;
#if ONNX_VERSION >= ONNX_V1_4_0
        FLAT_SETTING(Int,               elem_type);
#else
        FLAT_ENUM(TensorProto_DataType, elem_type)
#endif
        FLAT_CONVERT(TensorShapeProto,  shape);
        return proto;
    }
};

#if ONNX_VERSION >= ONNX_V1_6_0
class Sequence{
public:
    inline static flatbuffers::Offset<onnx_flat::TypeProto_::Sequence> convert(
            flatbuffers::FlatBufferBuilder& fbb,
            const onnx::TypeProto_Sequence& proto)
    {
        return onnx_flat::TypeProto_::CreateSequence(
                fbb
                , PROTO_OPTIONAL(TypeProto,  elem_type)
                );

   }
    inline static onnx::TypeProto_Sequence convert(
            const onnx_flat::TypeProto_::Sequence* flat)
    {
        onnx::TypeProto_Sequence proto;
        FLAT_CONVERT(TypeProto,  elem_type);
        return proto;
    }
};
class Map{
public:
    inline static flatbuffers::Offset<onnx_flat::TypeProto_::Map> convert(
            flatbuffers::FlatBufferBuilder& fbb,
            const onnx::TypeProto_Map& proto)
    {
        return onnx_flat::TypeProto_::CreateMap(
                fbb
                , PROTO_OPTIONAL(Int,        key_type)
                , PROTO_OPTIONAL(TypeProto,  value_type)
                );

   }
    inline static onnx::TypeProto_Map convert(
            const onnx_flat::TypeProto_::Map* flat)
    {
        onnx::TypeProto_Map proto;
        FLAT_SETTING(Int,        key_type);
        FLAT_CONVERT(TypeProto,  value_type);
        return proto;
    }
};
#endif


#if ONNX_VERSION >= ONNX_V1_10_0
class Optional{
public:
    inline static flatbuffers::Offset<onnx_flat::TypeProto_::Optional> convert(
            flatbuffers::FlatBufferBuilder& fbb,
            const onnx::TypeProto_Optional& proto)
    {
        return onnx_flat::TypeProto_::CreateOptional(
                fbb
                , PROTO_OPTIONAL(TypeProto,  elem_type)
                );

   }
    inline static onnx::TypeProto_Optional convert(
            const onnx_flat::TypeProto_::Optional* flat)
    {
        onnx::TypeProto_Optional proto;
        FLAT_CONVERT(TypeProto,  elem_type);
        return proto;
    }
};
class SparseTensor{
public:
    inline static flatbuffers::Offset<onnx_flat::TypeProto_::SparseTensor> convert(
            flatbuffers::FlatBufferBuilder& fbb,
            const onnx::TypeProto_SparseTensor& proto)
    {
        return onnx_flat::TypeProto_::CreateSparseTensor(
                fbb
                , PROTO_OPTIONAL(Int,               elem_type)
                , PROTO_OPTIONAL(TensorShapeProto,  shape)
                );

   }
    inline static onnx::TypeProto_SparseTensor convert(
            const onnx_flat::TypeProto_::SparseTensor* flat)
    {
        onnx::TypeProto_SparseTensor proto;
        FLAT_SETTING(Int,               elem_type);
        FLAT_CONVERT(TensorShapeProto,  shape);
        return proto;
    }
};
#endif

class Anonymous1{
public:
    inline static flatbuffers::Offset<onnx_flat::TypeProto_::Anonymous1> convert(
            flatbuffers::FlatBufferBuilder& fbb,
            const onnx::TypeProto& proto)
    {
        return onnx_flat::TypeProto_::CreateAnonymous1(
                fbb
                , PROTO_OPTIONAL(Tensor,    tensor_type)
#if ONNX_VERSION >= ONNX_V1_6_0
                , PROTO_OPTIONAL(Sequence,  sequence_type)
                , PROTO_OPTIONAL(Map,       map_type)
#endif
#if ONNX_VERSION >= ONNX_V1_10_0
                , PROTO_OPTIONAL(Optional,  optional_type)
                , PROTO_OPTIONAL(SparseTensor,sparse_tensor_type)
#endif
                );
    }
    inline static onnx::TypeProto convert(
            const onnx_flat::TypeProto_::Anonymous1* flat)
    {
        onnx::TypeProto proto;
        FLAT_CONVERT(Tensor,        tensor_type);
#if ONNX_VERSION >= ONNX_V1_6_0
        FLAT_CONVERT(Sequence,      sequence_type);
        FLAT_CONVERT(Map,           map_type);
#endif
#if ONNX_VERSION >= ONNX_V1_10_0
        FLAT_CONVERT(Optional,      optional_type);
        FLAT_CONVERT(SparseTensor,  sparse_tensor_type);
#endif
        return proto;
    }
};


flatbuffers::Offset<onnx_flat::TypeProto> TypeProto::convert(
        flatbuffers::FlatBufferBuilder& fbb,
        const onnx::TypeProto& proto)
{
    return onnx_flat::CreateTypeProto(
            fbb
            , PROTO_ONEOF(Anonymous1,       value)
#if ONNX_VERSION > ONNX_V1_1_2
            , PROTO_OPTIONAL(String,      denotation)
#endif
            );
}

onnx::TypeProto TypeProto::convert(
        const onnx_flat::TypeProto* flat)
{
    onnx::TypeProto proto;
    FLAT_ONEOF(Anonymous1,  value);
#if ONNX_VERSION > ONNX_V1_1_2
    FLAT_CONVERT(String,    denotation);
#endif
    return proto;
}

