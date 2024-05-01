# NODEPP-INPUT
emulate keyboard / mouse inputs in windows, linux and Mac, using [Nodepp](https://github.com/NodeppOficial/nodepp).

## Dependencies
- libx11-dev  ( posix only )
- libxtst-dev ( posix only )

## compilation
- windows: `g++ -o main main.cpp -I ./include ; ./main`
- linux: `g++ -o main main.cpp -I ./include -lX11 -lXtst ; ./main`