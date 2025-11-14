#include "layer2.h"
#include <adf.h>
#include "adf/io_buffer/io_buffer.h"

/*
Second layer of 2x8x4x1 network
*/

MULT84::MULT84(const std::array<int32, NUM_COEFFS>& coefficients, const std::array<int32, NUM_OUTPUTS> biases) : coeffs(coefficients), bias(biases) {
}

void MULT84::multiply84(adf::input_buffer<int32> &in, adf::output_buffer<int32> &out)
{
    auto in_t = in.data();
    auto out_t = out.data();

    const int32 in0 = in_t[0];
    const int32 in1 = in_t[1];
    const int32 in2 = in_t[2];
    const int32 in3 = in_t[3];
    const int32 in4 = in_t[4];
    const int32 in5 = in_t[5];
    const int32 in6 = in_t[6];
    const int32 in7 = in_t[7];

    // --- Output 0 ---
    {
        int32 acc = bias[0];
        acc += coeffs[0]  * in0;
        acc += coeffs[4]  * in1;
        acc += coeffs[8]  * in2;
        acc += coeffs[12] * in3;
        acc += coeffs[16] * in4;
        acc += coeffs[20] * in5;
        acc += coeffs[24] * in6;
        acc += coeffs[28] * in7;
        out_t[0] = (acc < 0) ? 0 : acc; // ReLU
    }

    // --- Output 1 ---
    {
        int32 acc = bias[1];
        acc += coeffs[1]  * in0;
        acc += coeffs[5]  * in1;
        acc += coeffs[9]  * in2;
        acc += coeffs[13] * in3;
        acc += coeffs[17] * in4;
        acc += coeffs[21] * in5;
        acc += coeffs[25] * in6;
        acc += coeffs[29] * in7;
        out_t[1] = (acc < 0) ? 0 : acc; // ReLU
    }

    // --- Output 2 ---
    {
        int32 acc = bias[2];
        acc += coeffs[2]  * in0;
        acc += coeffs[6]  * in1;
        acc += coeffs[10] * in2;
        acc += coeffs[14] * in3;
        acc += coeffs[18] * in4;
        acc += coeffs[22] * in5;
        acc += coeffs[26] * in6;
        acc += coeffs[30] * in7;
        out_t[2] = (acc < 0) ? 0 : acc; // ReLU
    }

    // --- Output 3 ---
    {
        int32 acc = bias[3];
        acc += coeffs[3]  * in0;
        acc += coeffs[7]  * in1;
        acc += coeffs[11] * in2;
        acc += coeffs[15] * in3;
        acc += coeffs[19] * in4;
        acc += coeffs[23] * in5;
        acc += coeffs[27] * in6;
        acc += coeffs[31] * in7;
        out_t[3] = (acc < 0) ? 0 : acc; // ReLU
    }
}
