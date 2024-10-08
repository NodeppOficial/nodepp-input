# NODEPP-INPUT
Emulate Keyboard/Mouse Inputs in Windows, Linux and Mac, using [Nodepp](https://github.com/NodeppOficial/nodepp).

## Dependencies
```bash
- 🐧libxtst-dev: sudo apt install libxtst-dev
- 🐧libx11-dev : sudo apt install libx11-dev
```

## Build & Run
```bash
- 🐧: g++ -o main main.cpp -I ./include lX11 -lXtst ; ./main
- 🪟: g++ -o main main.cpp -I ./include -lws2_32 ; ./main
```
