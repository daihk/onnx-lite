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
#include "FunctionProto.h"

#include "NodeProto.h"
#include "OperatorSetIdProto.h"

#if ONNX_VERSION >= ONNX_V1_10_0

flatbuffers::Offset<onnx_flat::FunctionProto> FunctionProto::convert(
        flatbuffers::FlatBufferBuilder& fbb,
        const onnx::FunctionProto& proto) 
{
    return onnx_flat::CreateFunctionProto(

            fbb
            , PROTO_OPTIONAL(String,              name)
            , PROTO_REPEATED(String,              input)
            , PROTO_REPEATED(String,              output)
            , PROTO_REPEATED(String,              attribute)
            , PROTO_REPEATED(NodeProto,           node)
            , PROTO_OPTIONAL(String,              doc_string)
            , PROTO_REPEATED(OperatorSetIdProto,  opset_import)
            , PROTO_OPTIONAL(String,              domain)
            );
}

onnx::FunctionProto FunctionProto::convert(
        const onnx_flat::FunctionProto* flat) 
{
    onnx::FunctionProto proto;
    FLAT_CONVERT(String,              name);
    FLAT_CONVERT(String,              input);
    FLAT_CONVERT(String,              output);
    FLAT_CONVERT(String,              attribute);
    FLAT_CONVERT(NodeProto,           node);
    FLAT_CONVERT(String,              doc_string);
    FLAT_CONVERT(OperatorSetIdProto,  opset_import);
    FLAT_CONVERT(String,              domain);
    return proto;
}

#endif
