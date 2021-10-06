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
#include "ValueInfoProto.h"

#include "TypeProto.h"

flatbuffers::Offset<onnx_flat::ValueInfoProto> ValueInfoProto::convert(
        flatbuffers::FlatBufferBuilder& fbb,
        const onnx::ValueInfoProto& proto)
{
    return onnx_flat::CreateValueInfoProto(
            fbb,
            PROTO_OPTIONAL(String,          name),
            PROTO_OPTIONAL(TypeProto,       type),
            PROTO_OPTIONAL(String,          doc_string)
            );
}

onnx::ValueInfoProto ValueInfoProto::convert(
        const onnx_flat::ValueInfoProto* flat)
{
    onnx::ValueInfoProto proto;
    FLAT_CONVERT(String,        name);
    FLAT_CONVERT(TypeProto,     type);
    FLAT_CONVERT(String,        doc_string);
    return proto;
}
