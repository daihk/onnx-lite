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
#include <iostream>
#include <fstream>

#include <onnx_generated.h>
inline long onnx_get_long(const onnx_flat::Long* key) {
    return key?key->v():0;
}
inline const char* onnx_get_string(const flatbuffers::String* key) {
    return key?key->c_str():"UNKNOW";
}
#define PRINT_LONG(model, name) \
    printf("[%s] %s: %ld\n", #model, #name, onnx_get_long(model->name()));

#define PRINT_STR(model, name) \
    printf("[%s] %s: %s\n", #model, #name, onnx_get_string(model->name()));

#define PRINT_STRS(model, name) \
    printf("[%s] %s:", #model, #name); \
    for(auto m: *model->name()) { \
      printf("%s,", onnx_get_string(m)); \
    } \
    printf("\n");

void print_help() {
    printf(
           "Usage: convert -i model.onnxf    [Option]\n"
           );
}

const onnx_flat::ModelProto* load_model(const std::string input) {
    std::ifstream fs(input, std::ifstream::in | std::ifstream::binary);
    if (!fs.is_open()) {
        printf("open failed %s\n\n", input.c_str());
        return nullptr;
    }
    fs.seekg(0,std::ios::end);
    size_t size = fs.tellg();
    fs.seekg(0,std::ios::beg);
    char* buffer = new char[size];
    fs.read(buffer, size);
    flatbuffers::Verifier verify((uint8_t*)buffer, size);
    fs.close();
    return flatbuffers::GetRoot<onnx_flat::ModelProto>(buffer);
}

void printf_model(const onnx_flat::ModelProto* model) {
    for(auto opset : *model->opset_import()) {
        PRINT_STR(opset, domain);
        PRINT_LONG(opset, version);
    }
    PRINT_LONG(model, ir_version);
    PRINT_STR(model, producer_name);
    PRINT_STR(model, producer_version);
    PRINT_STR(model, domain);
    PRINT_LONG(model, ir_version);
    PRINT_STR(model, doc_string);
    PRINT_STR(model, doc_string);

    const onnx_flat::GraphProto* graph = model->graph();

    for(auto node: *graph->node()) {
        printf("%5s\t",     onnx_get_string(node->name()));
        printf("%10s\t",    onnx_get_string(node->op_type()));
        for(auto input : *node->input()) {
            printf("%s,", onnx_get_string(input));
        }
        printf("=>");
        for(auto output : *node->output()) {
            printf("%s,", onnx_get_string(output));
        }

        printf("%5s\t",     onnx_get_string(node->domain()));
        printf("%5s\t",     onnx_get_string(node->doc_string()));

        printf("\n");
    }


}

int main(int argc, char** argv) {
    const char *optstring = "i:h";
    int opt;
    std::string input;
    while ((opt = getopt(argc, argv, optstring)) != -1) {
        switch(opt) {
            case 'i': 
                input = optarg;
                break;
            case 'h': 
            default:
                print_help();
                return 0;
        }
    }
    if(input.empty()){
        print_help();
        return -1;
    }

    const onnx_flat::ModelProto* model = load_model(input);
    if(!model) {
        return -1;
    }
    printf_model(model);
}
