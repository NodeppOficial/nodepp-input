# NODEPP-INPUT
Emulate Keyboard | Mouse | Gamepad | Touch Inputs in Windows, Linux, FreeBSD and Mac, using [Nodepp](https://github.com/NodeppOficial/nodepp).

## Dependencies
```bash
- 🐧libx11-dev : sudo apt install libx11-dev
- 🐧libxi-dev  : sudo apt install libxi-dev
```

## Build & Run
```bash
- 🐧: g++ -o main main.cpp -I ./include lX11 -lXtst -lXi ; ./main
- 🪟: g++ -o main main.cpp -I ./include -lws2_32 ; ./main
```
