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
#include "TensorProto.h"
#include "StringStringEntryProto.h"

class Segment{
    public:
        inline static flatbuffers::Offset<onnx_flat::TensorProto_::Segment> convert(
                flatbuffers::FlatBufferBuilder& fbb,
                const onnx::TensorProto_Segment& proto)
        {
            return onnx_flat::TensorProto_::CreateSegment(
                    fbb,
                    PROTO_OPTIONAL(Long,    begin),
                    PROTO_OPTIONAL(Long,    end)
                    );
        }

        inline static onnx::TensorProto_Segment convert(
                const onnx_flat::TensorProto_::Segment* flat)
        {
            onnx::TensorProto_Segment proto;
            FLAT_SETTING(Long,      begin);
            FLAT_SETTING(Long,      end);
            return proto;
        }
};

flatbuffers::Offset<onnx_flat::TensorProto> TensorProto::convert(
        flatbuffers::FlatBufferBuilder& fbb,
        const onnx::TensorProto& proto)
{
    return onnx_flat::CreateTensorProto(
            fbb
            , PROTO_REPEATED(Long,                        dims)
#if ONNX_VERSION >= ONNX_V1_4_0
            , PROTO_OPTIONAL(Int,                         data_type)
#else
            , PROTO_ENUM(TensorProto_::DataType,          data_type)
#endif
            , PROTO_OPTIONAL(Segment,                     segment)
            , PROTO_REPEATED(Float,                       float_data)
            , PROTO_REPEATED(Int,                         int32_data)
            , PROTO_REPEATED(String,                      string_data)
            , PROTO_REPEATED(Long,                        int64_data)
            , PROTO_OPTIONAL(String,                      name)
            , PROTO_OPTIONAL(String,                      doc_string)
            , PROTO_OPTIONAL(UChar,                       raw_data)
#if ONNX_VERSION >= ONNX_V1_4_0
            , PROTO_REPEATED(StringStringEntryProto,      external_data)
            , PROTO_ENUM(TensorProto_::DataLocation,      data_location)
#endif
            , PROTO_REPEATED(Double,                      double_data)
            , PROTO_REPEATED(ULong,                       uint64_data)
            );
}

onnx::TensorProto TensorProto::convert(
        const onnx_flat::TensorProto* flat)
{
    onnx::TensorProto proto;
    FLAT_CONVERT(Long,                  dims);
#if ONNX_VERSION >= ONNX_V1_4_0
    FLAT_SETTING(Int,                   data_type);
#else
    FLAT_ENUM(TensorProto_DataType,     data_type);
#endif
    FLAT_CONVERT(Segment,               segment);
    FLAT_CONVERT(Float,                 float_data);
    FLAT_CONVERT(Int,                   int32_data);
    FLAT_CONVERT(String,                string_data);
    FLAT_CONVERT(Long,                  int64_data);
    FLAT_CONVERT(String,                name);
    FLAT_CONVERT(String,                doc_string);
    FLAT_CONVERT(UChar,                 raw_data);
#if ONNX_VERSION >= ONNX_V1_4_0
    FLAT_CONVERT(StringStringEntryProto,external_data);
    FLAT_ENUM(TensorProto_DataLocation, data_location);
#endif
    FLAT_CONVERT(Double,                double_data);
    FLAT_CONVERT(ULong,                 uint64_data);
    return proto;
}
