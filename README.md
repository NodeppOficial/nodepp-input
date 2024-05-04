# NODEPP-INPUT
Emulate Keyboard/Mouse Inputs in Windows, Linux and Mac, using [Nodepp](https://github.com/NodeppOficial/nodepp).

## Dependencies
- 🐧 libxtst-dev **( posix only )** `sudo apt install libxtst-dev`
- 🐧 libx11-dev  **( posix only )** `sudo apt install libx11-dev`

## compilation
- Windows: `g++ -o main main.cpp -I ./include ; ./main`
- Linux: `g++ -o main main.cpp -I ./include -lX11 -lXtst ; ./main`
