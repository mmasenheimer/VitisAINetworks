#pragma once
#include "adf.h"
#define NUM_COEFFS 4
#define NUM_INPUTS 4
#include <array>
#include "layer3.h"

class MULT41 {
private:

    const std::array<int32, NUM_COEFFS> coeffs;
    const int32 bias;

public:
    MULT41(const std::array<int32, NUM_COEFFS>& coefficients, const int32 biases);

    void multiply41(adf::input_buffer<int32> & in, adf::output_buffer<int32> & out);

    static void registerKernelClass() {
        REGISTER_FUNCTION(MULT41::multiply41);
    }
};