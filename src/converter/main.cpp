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
#include <unistd.h>
#include <fstream>
#include <iostream>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/text_format.h>
#include <google/protobuf/message.h>

#include "ModelProto.h"

void print_help() {
    printf(
           "Usage: convert -i model.onnx     [Option]\n"
           "       convert -i model.onnxflat [Option]\n"
           );
}

struct HEAD {
    unsigned char label[8] = {0xFF, 0xFA, 'O', 'N', 'N', 'X', 0xFA, 0xFF};
    int64_t version = 1;
};

struct TAIL{
    unsigned char label[8] = {0xFF, 0xFA, 'L', 'I', 'T', 'E', 0xFA, 0xFF};
};

int proto2flat(std::string ifile, std::string ofile) {
    std::ifstream fs(ifile, std::ifstream::in | std::ifstream::binary);
    onnx::ModelProto pmodel;
    google::protobuf::io::IstreamInputStream input(&fs);
    google::protobuf::io::CodedInputStream codedstr(&input);
    codedstr.SetTotalBytesLimit(INT_MAX, INT_MAX / 2);
    bool success = pmodel.ParseFromCodedStream(&codedstr);
    fs.close();

    flatbuffers::FlatBufferBuilder fbb;
    auto fmodel = ModelProto::convert(fbb, pmodel);
    fbb.Finish(fmodel);
    const uint8_t* buf = fbb.GetBufferPointer();
    std::ofstream of;
    HEAD head;
    TAIL tail;
    of.open(ofile, std::ios::out | std::ios::binary);
    of.write((const char *)&head, sizeof(HEAD));
    of.write((const char *)buf, fbb.GetSize());
    of.write((const char *)&tail, sizeof(TAIL));
    of.close();
    return 0;
}

int flat2proto(std::string ifile, std::string ofile) {
    std::ifstream fs(ifile, std::ifstream::in | std::ifstream::binary);
    fs.seekg(0,std::ios::end);
    size_t size = fs.tellg();
    fs.seekg(0,std::ios::beg);
    char* buffer = new char[size];
    fs.read(buffer, size);
    HEAD* head = (HEAD*)buffer; 
    char* model = buffer + sizeof(HEAD);
    int model_size = size - sizeof(HEAD) - sizeof(TAIL);
    TAIL* tail = (TAIL*)(buffer + size - sizeof(TAIL)); 
    flatbuffers::Verifier verify((uint8_t*)model, model_size);
    fs.close();
    printf("version: %ld\n", head->version);

    auto fmodel = flatbuffers::GetRoot<onnx_flat::ModelProto>(model);
    auto pmodel = ModelProto::convert(fmodel);
    std::ofstream of(ofile, std::ifstream::out | std::ifstream::binary);
    std::string data;
    pmodel.SerializeToString(&data);
    of<<data;
    of.close();
    delete buffer;

    return 0;
}

int main(int argc, char** argv) {
    const char *optstring = "i:o:h";
    int opt;
    std::string input, output;
    while ((opt = getopt(argc, argv, optstring)) != -1) {
        switch(opt) {
            case 'i': 
                input = optarg;
                break;
            case 'o': 
                output = optarg;
                break;
            case 'h': 
            default:
                print_help();
                return 0;
        }
    }
    if(input.empty()||output.empty()){
        print_help();
        return -1;
    }

    // check onnx lite
    bool is_onnx_lite = false;
    {
        std::ifstream fs(input, std::ifstream::in | std::ifstream::binary);
        if (!fs.is_open()) {
            printf("open failed %s\n\n", input.c_str());
            return -1;
        }
        fs.seekg(0,std::ios::end);
        size_t size = fs.tellg();
        fs.seekg(0,std::ios::beg);
        char* buffer = new char[size];
        fs.read(buffer, size);
        HEAD* head = (HEAD*)buffer; 
        if(head->label[0] == 0XFF &&
             head->label[1] == 0XFA &&
             head->label[2] == 'O' &&
             head->label[3] == 'N' &&
             head->label[4] == 'N' &&
             head->label[5] == 'X' &&
             head->label[6] == 0XFA &&
             head->label[7] == 0XFF) {
            is_onnx_lite = true;
        }
        fs.close();
        delete buffer;
    }

    if(is_onnx_lite) {
        flat2proto(input, output);
        printf("Conveter onnx-lite to onnx: %s\n", output.c_str());
    }
    else {
        proto2flat(input, output);
        printf("Conveter onnx to onnx-lite: %s\n", output.c_str());
    }
}
