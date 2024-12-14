#include <nodepp/nodepp.h>
#include <input/mouse.h>

using namespace nodepp;

void onMain(){

    mouse_t mouse; 

    mouse.onMotionMove([]( uint x, uint y ){
        console::log( "->", x, y );
    });

    mouse.onButtonPress([]( uint button ){
        console::log( "->", button );
    });

    console::log( 
        mouse.get_position()[0],
        mouse.get_position()[1]
    );
    mouse.move( 100, 100 );
    console::log( 
        mouse.get_position()[0],
        mouse.get_position()[1]
    );

    while(1){ mouse.next(); }

}