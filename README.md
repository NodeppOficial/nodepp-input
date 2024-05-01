# NODEPP-INPUT
Emulate Keyboard/Mouse Inputs in Windows, Linux and Mac, using [Nodepp](https://github.com/NodeppOficial/nodepp).

## Dependencies
- libx11-dev  **( posix only )**
- libxtst-dev **( posix only )**

## compilation
- Windows: `g++ -o main main.cpp -I ./include ; ./main`
- Linux: `g++ -o main main.cpp -I ./include -lX11 -lXtst ; ./main`
