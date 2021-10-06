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
#pragma once
#include <onnx.pb.h>
#include <onnx_generated.h>

#define DECLEAR_REPEATED_INNER(type, name)                                        \
    inline static flatbuffers::Offset<flatbuffers::Vector<                        \
            flatbuffers::Offset<onnx_flat::type##_::name>>>                       \
            convert ( flatbuffers::FlatBufferBuilder& fbb,                        \
            const ::google::protobuf::RepeatedPtrField<onnx::type::name>& proto){ \
        std::vector<flatbuffers::Offset<onnx_flat::type##_::name> > f;            \
        for(auto& tensor : proto) {                                               \
            f.push_back(name::convert(fbb, tensor));                              \
        }                                                                         \
        return fbb.CreateVector(f);                                               \
    }                                                                             \
    inline static ::google::protobuf::RepeatedPtrField<onnx::type::name> convert (\
            const flatbuffers::Vector<                                            \
            flatbuffers::Offset<onnx_flat::type##_::name>>*flat){                 \
    ::google::protobuf::RepeatedPtrField<onnx::type::name> proto;                 \
        for(auto f : *flat) {                                                     \
           onnx::type::name* p = proto.Add();                                     \
           *p = name::convert(f);                                                 \
        }                                                                         \
        return proto;                                                             \
    }

#define DECLEAR_REPEATED(name)                                                    \
    inline static flatbuffers::Offset<flatbuffers::Vector<                        \
            flatbuffers::Offset<onnx_flat::name>>>                                \
            convert ( flatbuffers::FlatBufferBuilder& fbb,                        \
            const ::google::protobuf::RepeatedPtrField<onnx::name>& proto) {      \
        std::vector<flatbuffers::Offset<onnx_flat::name> > f;                     \
        for(auto& tensor : proto) {                                               \
            f.push_back(name::convert(fbb, tensor));                              \
        }                                                                         \
        return fbb.CreateVector(f);                                               \
    }                                                                             \
    inline static ::google::protobuf::RepeatedPtrField<onnx::name> convert (      \
            const flatbuffers::Vector<flatbuffers::Offset<onnx_flat::name>>*flat){\
    ::google::protobuf::RepeatedPtrField<onnx::name> proto;                       \
        for(auto f : *flat) {                                                     \
           onnx::name* p = proto.Add();                                           \
           *p = name::convert(f);                                                 \
        }                                                                         \
        return proto;                                                             \
    }

#define PROTO_OPTIONAL(type,name) \
    proto.has_##name()?type::convert(fbb, proto.name()):0
#define PROTO_REPEATED(type,name) \
    type::convert(fbb, proto.name())
#define PROTO_ONEOF(type,name) \
        proto.name##_case()!=0?type::convert(fbb, proto):0
#define PROTO_ENUM(type,name) \
        proto.has_name()?(onnx_flat::type)proto.name():(onnx_flat::type)0

#define FLAT_SETTING(type,name) \
    if(flat->name())proto.set_##name(type::convert(flat->name()))
#define FLAT_CONVERT(type,name) \
    if(flat->name())*(proto.mutable_##name())=type::convert(flat->name())
#define FLAT_ONEOF(type,name) \
    if(flat->name())proto.MergeFrom(type::convert(flat->name()));
#define FLAT_ENUM(type,name) \
        if(flat->name())proto.set_##name((onnx::type)flat->name());


class Float{
public:
    inline static flatbuffers::Offset<flatbuffers::Vector<float>> convert (
            flatbuffers::FlatBufferBuilder& fbb,
            const google::protobuf::RepeatedField<float>& proto) {

        return fbb.CreateVector(proto.data(), proto.size());
    }
    inline static flatbuffers::Offset<onnx_flat::Float> convert ( 
            flatbuffers::FlatBufferBuilder& fbb,
            const float& proto) {
        return onnx_flat::CreateFloat(fbb, proto);
    }
public:
    inline static float convert (const onnx_flat::Float* flat) {
        return flat->v();
    }
    inline static google::protobuf::RepeatedField<float> convert (
            const flatbuffers::Vector<float>* flat) {
        google::protobuf::RepeatedField<float> proto(flat->begin(), flat->end());
        return proto;
    }
};
class Double{
public:
    inline static flatbuffers::Offset<flatbuffers::Vector<double>> convert (
            flatbuffers::FlatBufferBuilder& fbb,
            const google::protobuf::RepeatedField<double>& proto) {

        return fbb.CreateVector(proto.data(), proto.size());
    }
    inline static flatbuffers::Offset<onnx_flat::Double> convert ( flatbuffers::FlatBufferBuilder& fbb, const double& proto) {
        return onnx_flat::CreateDouble(fbb, proto);
    }
public:
    inline static google::protobuf::RepeatedField<double> convert (
            const flatbuffers::Vector<double>* flat) {
        google::protobuf::RepeatedField<double> proto(flat->begin(), flat->end());
        return proto;
    }
    inline static double convert (const onnx_flat::Double* flat) {
        return flat->v();
    }
};
class Long{
public:
    inline static flatbuffers::Offset<flatbuffers::Vector<long int>> convert (
            flatbuffers::FlatBufferBuilder& fbb,
            const google::protobuf::RepeatedField<long int>& proto) {

        return fbb.CreateVector(proto.data(), proto.size());
    }
    inline static flatbuffers::Offset<onnx_flat::Long> convert ( flatbuffers::FlatBufferBuilder& fbb, const long int& proto) {
        return onnx_flat::CreateLong(fbb, proto);
    }
public:
    inline static google::protobuf::RepeatedField<long int> convert (
            const flatbuffers::Vector<long int>* flat) {
        google::protobuf::RepeatedField<long int> proto(flat->begin(), flat->end());
        return proto;
    }
    inline static long int convert (const onnx_flat::Long* flat) {
        return flat->v();
    }
};
class ULong {
public:
    inline static flatbuffers::Offset<flatbuffers::Vector<unsigned long int>> convert (
            flatbuffers::FlatBufferBuilder& fbb,
            const google::protobuf::RepeatedField<unsigned long int>& proto) {

        return fbb.CreateVector(proto.data(), proto.size());
    }
    inline static flatbuffers::Offset<onnx_flat::ULong> convert ( flatbuffers::FlatBufferBuilder& fbb, const unsigned long int& proto) {
        return onnx_flat::CreateULong(fbb, proto);
    }
public:
    inline static google::protobuf::RepeatedField<unsigned long int> convert (
            const flatbuffers::Vector<unsigned long int>* flat) {
        google::protobuf::RepeatedField<unsigned long int> proto(flat->begin(), flat->end());
        return proto;
    }
    inline static unsigned long int convert (const onnx_flat::ULong* flat) {
        return flat->v();
    }
};
class Int {
public:
    inline static flatbuffers::Offset<flatbuffers::Vector<int>> convert (
            flatbuffers::FlatBufferBuilder& fbb,
            const google::protobuf::RepeatedField<int>& proto) {

        return fbb.CreateVector(proto.data(), proto.size());
    }
    inline static flatbuffers::Offset<onnx_flat::Int> convert ( flatbuffers::FlatBufferBuilder& fbb, const int& proto) {
        return onnx_flat::CreateInt(fbb, proto);
    }
public:
    inline static google::protobuf::RepeatedField<int> convert (
            const flatbuffers::Vector<int>* flat) {
        google::protobuf::RepeatedField<int> proto(flat->begin(), flat->end());
        return proto;
    }
    inline static int convert (const onnx_flat::Int* flat) {
        return flat->v();
    }
};
class UInt {
public:
    inline static flatbuffers::Offset<flatbuffers::Vector<unsigned int>> convert (
            flatbuffers::FlatBufferBuilder& fbb,
            const google::protobuf::RepeatedField<unsigned int>& proto) {

        return fbb.CreateVector(proto.data(), proto.size());
    }
    inline static flatbuffers::Offset<onnx_flat::UInt> convert ( flatbuffers::FlatBufferBuilder& fbb, const unsigned int& proto) {
        return onnx_flat::CreateUInt(fbb, proto);
    }
public:
    inline static google::protobuf::RepeatedField<unsigned int> convert (
            const flatbuffers::Vector<unsigned int>* flat) {
        google::protobuf::RepeatedField<unsigned int> proto(flat->begin(), flat->end());
        return proto;
    }
    inline static unsigned int convert (const onnx_flat::UInt* flat) {
        return flat->v();
    }
};

class UChar{
public:
    inline static flatbuffers::Offset<flatbuffers::Vector<unsigned char>> convert (
            flatbuffers::FlatBufferBuilder& fbb,
            const std::string& proto) {
        return fbb.CreateVector((unsigned char*)proto.data(), proto.size());
    }
public:
    inline static std::string convert (
            const flatbuffers::Vector<unsigned char>* flat) {
        std::string proto;
        proto.assign((char*)flat->data(), flat->size());
        return proto;
    }
};

class String{
public:
    inline static flatbuffers::Offset<flatbuffers::String> convert (
            flatbuffers::FlatBufferBuilder& fbb,
            const std::string& proto) {
        return fbb.CreateString(proto);
    }
    inline static flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> convert (
            flatbuffers::FlatBufferBuilder& fbb,
            const ::google::protobuf::RepeatedPtrField<::std::string>& proto) {
        std::vector<flatbuffers::Offset<flatbuffers::String> > f;
        for(auto& p : proto) {
            auto v = String::convert(fbb, p);
            f.push_back(v);
        }
        return fbb.CreateVector(f);
    }

    inline static std::string convert (
            const flatbuffers::String* flat) {
        if(!flat) return "";
        return std::string(flat->c_str());
    }
    inline static ::google::protobuf::RepeatedPtrField<std::string> convert (
            const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>* flat) {
        ::google::protobuf::RepeatedPtrField<std::string> proto;
        for(auto f : *flat) {
            std::string* p = proto.Add();
            *p = String::convert(f);
        }
        return proto;
    }
};

template<typename P, typename F, typename T> 
static flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<F>>> 
        __PROTO_REPEATED__(flatbuffers::FlatBufferBuilder& fbb,
        const ::google::protobuf::RepeatedPtrField<P>& proto) {
    std::vector<flatbuffers::Offset<F> > f;
    for(auto& tensor : proto) {
        auto v = T::convert(fbb, tensor);
        f.push_back(v);
    }
    return fbb.CreateVector(f);
}
