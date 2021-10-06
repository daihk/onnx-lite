onnx-lite
----

onnx-lite目的是使用flatbuffer表示ONNX模型, 如此移动端推理框架就可以使用flatbuffer解析ONNX模型而不是protobuf。onnx和onnx-lite模型是相互等价的，可以将onnx模型转换成onnx-lite后再转换成onnx模型而不丢失细节。

### How to Build

```sh
mkdir build && cd build
cmake ..
make install -j2
```
