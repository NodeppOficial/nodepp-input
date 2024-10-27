#ifndef NODEPP_INPUT
#define NODEPP_INPUT

/*────────────────────────────────────────────────────────────────────────────*/

#if   _KERNEL == NODEPP_KERNEL_WINDOWS
    #include "windows/input.cpp"
#elif _KERNEL == NODEPP_KERNEL_POSIX
    #include "posix/input.cpp"
#else
    #error "This OS Does not support input.h"
#endif

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace input {

    input_t add(){ input_t input; input.pipe(); return input; }

}}

/*────────────────────────────────────────────────────────────────────────────*/

#endif