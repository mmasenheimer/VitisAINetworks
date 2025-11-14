#pragma once
#include "adf.h"
#define NUM_COEFFS 16
#define NUM_OUTPUTS 8
#define NUM_INPUTS 2
#include <array>
#include "layer1.h"

class MULT28 {
private:
    const std::array<int32, NUM_COEFFS> coeffs;
    const std::array<int32, NUM_OUTPUTS> biases;

public:
    MULT28(const std::array<int32, NUM_COEFFS>& coefficients, const std::array<int32, NUM_OUTPUTS> biases);

    void multiply28(adf::input_buffer<int32> & in, adf::output_buffer<int32> & out);

    static void registerKernelClass() {
        REGISTER_FUNCTION(MULT28::multiply28);
    }
};

