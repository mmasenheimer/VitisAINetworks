#include "adf.h"
#include "adf/window/types.h"
#include "layer1.h"
#include "layer2.h"
#include "layer3.h"

class simpleGraph : public adf::graph {
private:
    adf::kernel first;
    adf::kernel second;
    adf::kernel third;
public:
    adf::input_plio in;
    adf::output_plio out;
    
    simpleGraph(){
        // Set the constants for each layer
        const std::array<int32, 16> mycoeffslayer1 = {3, -4, 4, 4, -4, 5, 5, -3, 1, -2, -4, 1, -2, -3, 1, 5};
        const std::array<int32, 8> mybiaslayer1 = {0,0,0,0,0,0,0,0};
        const std::array<int32, 32> mycoeffslayer2 = {5, 5, 5, 5, -4, 2, 5, 5, 5, -4, 0, 3, 3, -2, -4, -5, -1, -4, 5, 2, 3, 4, 5, 0, 2, 3, -5, -2, 4, -3, 5, 2};
        const std::array<int32, 4> mybiaslayer2 = {0,0,0,0};
        const std::array<int32, 4> mycoeffslayer3 = {2, -1, 3, 3};
        const int32 mybiaslayer3 = 0;
        
        first = adf::kernel::create_object<MULT28>(mycoeffslayer1, mybiaslayer1);
        second = adf::kernel::create_object<MULT84>(mycoeffslayer2, mybiaslayer2);
        third = adf::kernel::create_object<MULT41>(mycoeffslayer3, mybiaslayer3);
        
        in = adf::input_plio::create(adf::plio_32_bits, "data/input.txt");
        out = adf::output_plio::create(adf::plio_32_bits, "data/output.txt");
        
        // Connect the kernels
        adf::connect(in.out[0], first.in[0]);
        adf::connect(first.out[0], second.in[0]);
        adf::connect(second.out[0], third.in[0]);
        adf::connect(third.out[0], out.in[0]);
        
        // Set dimensions
        adf::dimensions(first.in[0]) = {2};
        adf::dimensions(first.out[0]) = {8};
        adf::dimensions(second.in[0]) = {8};
        adf::dimensions(second.out[0]) = {4};
        adf::dimensions(third.in[0]) = {4};
        adf::dimensions(third.out[0]) = {1};
        
        // Set source files
        adf::source(first) = "layer1.cpp";
        adf::source(second) = "layer2.cpp";
        adf::source(third) = "layer3.cpp";
        
        // Set kernel locations
        adf::location<adf::kernel>(first)  = adf::tile(10, 0);
        adf::location<adf::kernel>(second) = adf::tile(11, 0);
        adf::location<adf::kernel>(third)  = adf::tile(12, 0);
        
        // Set runtime ratios (percentage of time kernel is active)
        adf::runtime<ratio>(first) = 0.6;   // Adjust based on actual computation time
        adf::runtime<ratio>(second) = 0.6;
        adf::runtime<ratio>(third) = 0.6;

        // Enable single buffer mode for pipelining
        adf::single_buffer(first.in[0]);
        adf::single_buffer(first.out[0]);
        adf::single_buffer(second.in[0]);
        adf::single_buffer(second.out[0]);
        adf::single_buffer(third.in[0]);
        adf::single_buffer(third.out[0]);
    }
};