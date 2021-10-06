/* Abs-1
 * Absolute takes one input data (Tensor) and produces one output data (Tensor) where the absolute is, y = abs(x), is applied to the tensor elementwise.
 * 
 * Version
 * This version of the operator has been available since version 1 of the default ONNX operator set.
 * 
 * Attributes
 * consumed_inputs : list of ints
 * legacy optimization attribute.
 * Inputs
 * X : T
 * Input tensor
 * Outputs
 * Y : T
 * Output tensor
 * Type Constraints
 * T : tensor(float16), tensor(float), tensor(double)
 * Constrain input and output types to float tensors.
 */

struct Abs1 {
    int8_t 
}
