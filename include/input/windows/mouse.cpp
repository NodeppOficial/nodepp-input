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
        auto size = get_screen_size(); return ptr_t<float>({
            x * ::GetSystemMetrics( SM_CXSCREEN ) / 100, 
            y * ::GetSystemMetrics( SM_CYSCREEN ) / 100
        });
	};

    struct NODE {
        array_t<uint> button;
        MSG           msg;
    };  ptr_t<NODE> obj;

public:

    event_t<uint>      onButtonRelease;
    event_t<uint>      onButtonPress;
    event_t<uint,uint> onMotionMove;
	
    /*─······································································─*/

    int next() const noexcept {
    coStart

        while( GetMessage( obj->msg, NULL, 0, 0 )==0 ){ coGoto(0); }
		TranslateMessage(obj->msg); DispatchMessage(obj->msg);

        if( obj->msg.message == WM_MOUSEMOVE ) {
            int btX = GET_X_LPARAM( obj->msg.lParam );
            int btY = GET_Y_LPARAM( obj->msg.lParam );
            	onMotionMove.emit( btX, btY ); 
        }

        elif( obj->msg.message == WM_LBUTTONDOWN ) { uint bt = 0;
            for( ulong x=obj->button.size(); x--; ){
             if( obj->button[x] == bt ){ return 1; }
               } obj->button.push( bt ); 
                 onButtonPress.emit( bt );
        }

        elif( obj->msg.message == WM_LBUTTONUP ) { uint bt = 0;
            for( ulong x=obj->button.size(); x--; ){
             if( obj->button[x] == bt ) 
               { obj->button.erase(x); }
               } onButtonRelease.emit( bt ); 
        }

        elif( obj->msg.message == WM_RBUTTONDOWN ) { uint bt = 1;
            for( ulong x=obj->button.size(); x--; ){
             if( obj->button[x] == bt ){ return; }
               } obj->button.push( bt ); 
                 onButtonPress.emit( bt );
        }

        elif( obj->msg.message == WM_RBUTTONUP ) { uint bt = 1;
            for( ulong x=obj->button.size(); x--; ){
             if( obj->button[x] == bt ) 
               { obj->button.erase(x); }
               } onButtonRelease.emit( bt ); 
        }

        elif( obj->msg.message == WM_MBUTTONDOWN ) { uint bt = 3;
            for( ulong x=obj->button.size(); x--; ){
             if( obj->button[x] == bt ){ return; }
               } obj->button.push( bt ); 
                 onButtonPress.emit( bt );
        }

        elif( obj->msg.message == WM_MBUTTONUP ) { uint bt = 3;
            for( ulong x=obj->button.size(); x--; ){
             if( obj->button[x] == bt ) 
               { obj->button.erase(x); }
               } onButtonRelease.emit( bt ); 
        }

    coGoto(0);
    coStop
    }

    /*─······································································─*/

	void scroll_mouse_down() const noexcept { mouse_event( MOUSEEVENTF_WHEEL, 0, 0, 120, 0 ); }

	void   scroll_mouse_up() const noexcept { mouse_event( MOUSEEVENTF_WHEEL, 0, 0,-120, 0 ); }

    ptr_t<int> get_mouse_position() const noexcept { 
        POINT mousePos; if (!GetCursorPos(&mousePos) ){ return nullptr; }
        return ptr_t<int>({ mousePos.x, mousePos.y, mousePos.x, mousePos.y });
    }

	void set_mouse_position( float x, float y ) const noexcept {
		auto fg = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
        auto sr = screen_ref( x, y );
        auto sz = get_screen_size( );
		auto dx = sr[0] * ( 65535.0f / sz[0] );
		auto dy = sr[1] * ( 65535.0f / sz[1] );
		mouse_event( fg, dx, dy, 0, 0 );
	}

	void release_mouse_button( int button ) const noexcept { 
        int fg = 0; switch( button ){
			case 3:  fg = MOUSEEVENTF_MIDDLEUP; break;
			case 2:  fg = MOUSEEVENTF_RIGHTUP;  break;
			case 1:  fg = MOUSEEVENTF_LEFTUP;   break;
            default: fg = button;
		} 	mouse_event( fg, 0, 0, 1, 0 ); 
	}

	void press_mouse_button( int button ) const noexcept { 
        int fg = 0; switch( button ){
			case 3:  fg = MOUSEEVENTF_MIDDLEDOWN; break;
			case 2:  fg = MOUSEEVENTF_RIGHTDOWN;  break;
			case 1:  fg = MOUSEEVENTF_LEFTDOWN;   break;
            default: fg = button;                 break;
		} 	mouse_event( fg, 0, 0, 1, 0 ); 
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

    mouse_t () noexcept : obj( new NODE() ) {}

};}

/*────────────────────────────────────────────────────────────────────────────*/