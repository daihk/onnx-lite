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
#include "TrainingInfoProto.h"

#include "GraphProto.h"
#include "StringStringEntryProto.h"

#if ONNX_VERSION >= ONNX_V1_7_0

flatbuffers::Offset<onnx_flat::TrainingInfoProto> TrainingInfoProto::convert(
        flatbuffers::FlatBufferBuilder& fbb,
        const onnx::TrainingInfoProto& proto) 
{
    return onnx_flat::CreateTrainingInfoProto(

            fbb
            , PROTO_OPTIONAL(GraphProto,                initialization)
            , PROTO_OPTIONAL(GraphProto,                algorithm)
            , PROTO_REPEATED(StringStringEntryProto,    initialization_binding)
            , PROTO_REPEATED(StringStringEntryProto,    update_binding)
            );
}

onnx::TrainingInfoProto TrainingInfoProto::convert(
        const onnx_flat::TrainingInfoProto* flat) 
{
    onnx::TrainingInfoProto proto;
    FLAT_CONVERT(GraphProto,                initialization);
    FLAT_CONVERT(GraphProto,                algorithm);
    FLAT_CONVERT(StringStringEntryProto,    initialization_binding);
    FLAT_CONVERT(StringStringEntryProto,    update_binding);
    return proto;
}

#endif
