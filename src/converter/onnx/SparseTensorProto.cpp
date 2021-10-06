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
#include "SparseTensorProto.h"

#include "TensorProto.h"

#if ONNX_VERSION >= ONNX_V1_6_0

flatbuffers::Offset<onnx_flat::SparseTensorProto> SparseTensorProto::convert(
        flatbuffers::FlatBufferBuilder& fbb,
        const onnx::SparseTensorProto& proto)
{
    return onnx_flat::CreateSparseTensorProto(
            fbb
            , PROTO_OPTIONAL(TensorProto,   values)
            , PROTO_OPTIONAL(TensorProto,   indices)
            , PROTO_REPEATED(Long,          dims)
            );
}

onnx::SparseTensorProto SparseTensorProto::convert(
        const onnx_flat::SparseTensorProto* flat)
{
    onnx::SparseTensorProto proto;
    FLAT_CONVERT(TensorProto,           values);
    FLAT_CONVERT(TensorProto,           indices);
    FLAT_CONVERT(Long,                  dims);
    return proto;
}

#endif
