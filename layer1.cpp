#include "layer1.h"
#include <adf.h>
#include "adf/io_buffer/io_buffer.h"
/*
First layer of 2x8x4x1 network
*/
MULT28::MULT28(const std::array<int32, NUM_COEFFS>& coefficients, std::array<int32, NUM_OUTPUTS> bias) : coeffs(coefficients), biases(bias) {
}

void MULT28::multiply28(adf::input_buffer<int32> & in, adf::output_buffer<int32> & out)
{
    auto in_t = in.data();
    auto out_t = out.data();
    
    // Output 0
    out_t[0] = biases[0];
    out_t[0] += coeffs[0] * in_t[0];
    out_t[0] += coeffs[8] * in_t[1];
    if (out_t[0] < 0) out_t[0] = 0;
    
    // Output 1
    out_t[1] = biases[1];
    out_t[1] += coeffs[1] * in_t[0];
    out_t[1] += coeffs[9] * in_t[1];
    if (out_t[1] < 0) out_t[1] = 0;
    
    // Output 2
    out_t[2] = biases[2];
    out_t[2] += coeffs[2] * in_t[0];
    out_t[2] += coeffs[10] * in_t[1];
    if (out_t[2] < 0) out_t[2] = 0;
    
    // Output 3
    out_t[3] = biases[3];
    out_t[3] += coeffs[3] * in_t[0];
    out_t[3] += coeffs[11] * in_t[1];
    if (out_t[3] < 0) out_t[3] = 0;
    
    // Output 4
    out_t[4] = biases[4];
    out_t[4] += coeffs[4] * in_t[0];
    out_t[4] += coeffs[12] * in_t[1];
    if (out_t[4] < 0) out_t[4] = 0;
    
    // Output 5
    out_t[5] = biases[5];
    out_t[5] += coeffs[5] * in_t[0];
    out_t[5] += coeffs[13] * in_t[1];
    if (out_t[5] < 0) out_t[5] = 0;
    
    // Output 6
    out_t[6] = biases[6];
    out_t[6] += coeffs[6] * in_t[0];
    out_t[6] += coeffs[14] * in_t[1];
    if (out_t[6] < 0) out_t[6] = 0;
    
    // Output 7
    out_t[7] = biases[7];
    out_t[7] += coeffs[7] * in_t[0];
    out_t[7] += coeffs[15] * in_t[1];

    // Relu
    if (out_t[7] < 0) out_t[7] = 0;
}