# Vitis AI Engine Neural Networks

Implementation of neural networks for Xilinx AI Engines using Vitis HLS.

## Files
- `graph.h/cpp` - ADF graph definition
- `layer1.h/cpp` - First layer (2→8 fully connected + ReLU)
- `layer2.h/cpp` - Second layer (8→4 fully connected + ReLU)
- `layer3.h/cpp` - Output layer (4→1 fully connected + Sigmoid)

## Requirements
- Xilinx Vitis 2023.x or later
- AI Engine development tools

## License
MIT License - see LICENSE file
