#include "layer3.h"
#include <adf.h>
#include "adf/io_buffer/io_buffer.h"

/*
Final layer of 2x8x4x1 network
*/

MULT41::MULT41(const std::array<int32, NUM_COEFFS>& coefficients, const int32 biases) : coeffs(coefficients), bias(biases) {
}

void MULT41::multiply41(adf::input_buffer<int32> & in, adf::output_buffer<int32> & out)
{
    auto in_t = in.data();
    auto out_t = out.data();

    int32 acc = bias;
    acc += coeffs[0] * in_t[0];
    acc += coeffs[1] * in_t[1];
    acc += coeffs[2] * in_t[2];
    acc += coeffs[3] * in_t[3];
    
    if (acc >= 2048) {
        out_t[0] = 4096;
        // Saturate to ~1.0
        // Inside the circle
    }
    else if (acc <= -2048) {
        out_t[0] = 0;  
        // Saturate to ~0.0
        // Outside the cicle
    }
    else {
        out_t[0] = 2048 + (acc >> 3);
        // Linear approximation: sigmoid(x) ≈ 0.5 + x/8
        // Boundary region
    }

    // ALTERNATIVE ACTUAL SIGMOID FUNCTION

    // int32 x = out_t[0];
    
    // // Scale x down for better numerical stability
    // x = x >> 2;  // Divide by 4
    
    // int32 abs_x = (x >= 0) ? x : -x;
    
    // if (abs_x > 8192) {
    //     // Saturate for very large values
    //     out_t[0] = (x > 0) ? 4096 : 0;
    // } else {
    //     // Rational approximation: 0.5 + 0.5 * x / (1 + |x|)
    //     // In fixed point: 2048 + 2048 * x / (4096 + abs_x)
        
    //     int32 numerator = x << 11;  // x * 2048
    //     int32 denominator = 4096 + abs_x;
    //     int32 result = numerator / denominator;
        
    //     out_t[0] = 2048 + result;
        
    //     // Clamp to valid range [0, 4096]
    //     if (out_t[0] < 0) out_t[0] = 0;
    //     if (out_t[0] > 4096) out_t[0] = 4096;
    // }
    
}