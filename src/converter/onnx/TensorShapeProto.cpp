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
#include "TensorShapeProto.h"

class Anonymous0{
public:
    inline static flatbuffers::Offset<onnx_flat::TensorShapeProto_::Dimension_::Anonymous0> convert(
            flatbuffers::FlatBufferBuilder& fbb,
            const onnx::TensorShapeProto_Dimension& proto)
    {
        return onnx_flat::TensorShapeProto_::Dimension_::CreateAnonymous0(
                fbb
                , PROTO_OPTIONAL(Long,      dim_value)
                , PROTO_OPTIONAL(String,    dim_param)
                );
    }
    inline static onnx::TensorShapeProto_Dimension convert(
            const onnx_flat::TensorShapeProto_::Dimension_::Anonymous0* flat)
    {
        onnx::TensorShapeProto_Dimension proto;
        FLAT_SETTING(Long,      dim_value);
        FLAT_SETTING(String,    dim_param);
        return proto;
    }
};

class Dimension{
public:
    DECLEAR_REPEATED_INNER(TensorShapeProto, Dimension)
public:
    inline static flatbuffers::Offset<onnx_flat::TensorShapeProto_::Dimension> convert(
            flatbuffers::FlatBufferBuilder& fbb,
            const onnx::TensorShapeProto::Dimension& proto) {
        return onnx_flat::TensorShapeProto_::CreateDimension(
                fbb
                , PROTO_ONEOF(Anonymous0,       value)
#if ONNX_VERSION > ONNX_V1_1_2
                , PROTO_OPTIONAL(String,        denotation)
#endif
                );
    }

public:
    inline static onnx::TensorShapeProto::Dimension convert(
            const onnx_flat::TensorShapeProto_::Dimension* flat) {
        onnx::TensorShapeProto::Dimension proto;
        FLAT_ONEOF(Anonymous0,      value);
#if ONNX_VERSION > ONNX_V1_1_2
        FLAT_CONVERT(String,        denotation);
#endif
        return proto;
    }
};


flatbuffers::Offset<onnx_flat::TensorShapeProto> TensorShapeProto::convert(
        flatbuffers::FlatBufferBuilder& fbb,
        const onnx::TensorShapeProto& proto)
{
    return onnx_flat::CreateTensorShapeProto(
            fbb
            , PROTO_REPEATED(Dimension,   dim)
            );
}

onnx::TensorShapeProto TensorShapeProto::convert(
        const onnx_flat::TensorShapeProto* flat)
{
    onnx::TensorShapeProto proto;
    FLAT_CONVERT(Dimension, dim);
    return proto;
}
