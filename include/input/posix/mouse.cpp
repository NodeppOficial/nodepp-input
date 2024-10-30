/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#pragma once

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { class mouse_t {
protected: 

    ptr_t<float> screen_ref( const float& x, const float& y ) const noexcept{
        Screen* scr = DefaultScreenOfDisplay( obj->dpy ); if( scr == nullptr )
        { return nullptr; } return ptr_t<float>({ 
            x * scr->width  / 100, 
            y * scr->height / 100 
        });
	};

    struct NODE {
        Display* dpy = nullptr;
        array_t<uint> button;
    };  ptr_t<NODE> obj;

public:

    event_t<uint>      onButtonRelease;
    event_t<uint>      onButtonPress;
    event_t<uint,uint> onMotionMove;

    /*─······································································─*/

    int next() const noexcept {
    coStart

        do {
            auto events = ButtonPressMask | ButtonReleaseMask | ButtonMotionMask;
            uint   idx  = DefaultScreen( obj->dpy );
            Window win  = XRootWindow( obj->dpy, idx );
            XSelectInput( obj->dpy, win, events );
        } while(0); coYield(1);

        while( XPending( obj->dpy ) > 0 ){
        
            XEvent ev;
            memset( &ev, 0, sizeof(ev) );
            XNextEvent( obj->dpy, &ev );

            if( ev.type == MotionNotify ) { 
                auto bt =  ev.xmotion;
                onMotionMove.emit( bt.x, bt.y ); 
            }

            elif( ev.type == ButtonRelease ) { 
                  auto bt =  ev.xbutton.button;
             for( ulong x=obj->button.size(); x--; ){
              if( obj->button[x] == bt ) 
                { obj->button.erase(x); }
                } onButtonRelease.emit( bt ); 
            }

            elif( ev.type == ButtonPress ) { 
                  auto bt =  ev.xbutton.button;
             for( ulong x=obj->button.size(); x--; ){
              if( obj->button[x] == bt ){ coGoto(1); }
                } obj->button.push( bt ); 
                  onButtonPress.emit( bt );
            }
        
          coNext; 
        } coGoto(1);

    coStop
    }

    /*─······································································─*/

    ptr_t<int> get_position() const noexcept { 
        uint mask; int rootX, rootY, winX, winY;
        uint   idx = DefaultScreen( obj->dpy );
        Window win = XRootWindow( obj->dpy, idx );

        XQueryPointer( 
            obj->dpy, win, &win, &win, 
            &rootX, &rootY, &winX, &winY, 
            &mask 
        );
        
        return ptr_t<int>({ winX, winY, rootX, rootY });
    }

    /*─······································································─*/

    bool is_button_released( uint btn ) const noexcept {
        if( obj->button.empty() ) return 1; 
        else { for( auto x : obj->button ){
           if( x == btn ) return 0;
        }}                return 1;
    }

    bool is_button_pressed( uint btn ) const noexcept {
        if( obj->button.empty() ) return 0; 
        else { for( auto x : obj->button ){
           if( x == btn ) return 1;
        }}                return 0;
    }

    /*─······································································─*/

	void move( int x, int y ) const noexcept {
        XEvent event; memset( &event, 0, sizeof(event) );
        uint   idx = DefaultScreen( obj->dpy );
        Window win = XRootWindow(obj->dpy,idx);

        event.type              = ButtonPress;
        event.xmotion.time      = CurrentTime;
        event.xmotion.display   = obj->dpy;
        event.xmotion.window    = win;
        event.xmotion.root      = win;
        event.xmotion.subwindow = win;
        event.xmotion.x         = x;
        event.xmotion.y         = y;
        
        XSendEvent( obj->dpy, win, 1, 0, &event );
		XFlush( obj->dpy );
	}

	void release( int button ) const noexcept { 
        XEvent event; memset( &event, 0, sizeof(event) );
        uint   idx = DefaultScreen( obj->dpy );
        Window win = XRootWindow(obj->dpy,idx);

        event.type              = ButtonRelease;
        event.xbutton.time      = CurrentTime;
        event.xbutton.display   = obj->dpy;
        event.xbutton.button    = button;
        event.xbutton.window    = win;
        event.xbutton.root      = win;
        event.xbutton.subwindow = win;
        
        XSendEvent( obj->dpy, win, 1, 0, &event );
		XFlush( obj->dpy );
	}

	void press( int button ) const noexcept { 
        XEvent event; memset( &event, 0, sizeof(event) );
        uint   idx = DefaultScreen( obj->dpy );
        Window win = XRootWindow(obj->dpy,idx);

        event.type              = ButtonPress;
        event.xbutton.time      = CurrentTime;
        event.xbutton.display   = obj->dpy;
        event.xbutton.button    = button;
        event.xbutton.window    = win;
        event.xbutton.root      = win;
        event.xbutton.subwindow = win;
        
        XSendEvent( obj->dpy, win, 1, 0, &event );
		XFlush( obj->dpy );
	}

	void scroll_up  () const noexcept { press( 4 ); release( 4 ); }

	void scroll_down() const noexcept { press( 5 ); release( 5 ); }

    /*─······································································─*/

    mouse_t () noexcept : obj( new NODE() ) {
        obj->dpy = XOpenDisplay( nullptr ); if ( !obj->dpy ) { 
            process::error("Unable to open X display"); 
            return;
        }
    }

   ~mouse_t () noexcept {
        if( obj.count() > 1 ){ return; }
        if( obj->dpy != nullptr ){ XCloseDisplay(obj->dpy); }
    }

};}

/*────────────────────────────────────────────────────────────────────────────*/