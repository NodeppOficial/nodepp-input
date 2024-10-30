#include <nodepp/nodepp.h>
#include <input/input.h>

using namespace nodepp;

void onMain(){

    mouse_t mouse; 

    mouse.onMotionMove([]( uint x, uint y ){
        console::log( x, y );
    });

    while(1){ mouse.next(); }

}