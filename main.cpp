#include "menu.hpp"
#include "net.hpp"
#include "textbox.hpp"
#include "window.hpp"
#include <stdio.h>

int main( int argc, char ** argv )
{
	Graphics::Window::initialize( 640, 480 );
	Net::Host::init();
	fprintf( stdout, "Starting\n" );
	Graphics::Menu startmenu = Graphics::Menu( 100, 50, 440, 160, 4, "Join Game", "Host Game", "Options", "Exit" );
	Graphics::Menu hostmenu  = Graphics::Menu( 100, 90, 440, 80, 2, "Host", "Back"  );
	Graphics::Textbox portinput = Graphics::Textbox( 100, 50, 440, 35  );
	Graphics::Textbox serverlog = Graphics::Textbox( 10, 10, 630, 470 );
	portinput.m_editable = 1;
	startmenu.show();
	startmenu.setaction( 3, Graphics::Window::shutdown );
	startmenu.setaction( 1, [&]() mutable { startmenu.hide(); hostmenu.show(); portinput.show(); } );
	hostmenu.setaction( 1, [&]() mutable { startmenu.show(); hostmenu.hide(); portinput.hide(); } );
	hostmenu.setaction( 0, [&]() mutable { 
		startmenu.hide(); 
		hostmenu.hide(); 
		portinput.hide(); 
		serverlog.show();
		Net::Host * instance = new Net::Host( atoi( portinput.m_text ) );
		instance->start();
	} );
	while( 1 ) {
		SDL_Event event;
		while( SDL_PollEvent( &event ) ) {
			switch( event.type ) {
				case SDL_QUIT:
					fprintf( stdout, "Shutting down\n" );
					Graphics::Window::destroy();
					return 0;
				case SDL_MOUSEMOTION:
					startmenu.think( &event );
					hostmenu.think( &event );
					portinput.think( &event );
					break;
				case SDL_MOUSEBUTTONDOWN:
					startmenu.think( &event);
					hostmenu.think( &event );
					portinput.think( &event );
					break;
				case SDL_MOUSEBUTTONUP:
					startmenu.think( &event );
					hostmenu.think( &event );
					portinput.think( &event );
					break;
				case SDL_TEXTINPUT:
					portinput.think( &event );
					break;
			}

		}

		Graphics::Window::clear( 100, 100, 110, 255 );
		startmenu.draw();
		hostmenu.draw();
		portinput.draw();
		Graphics::Window::flush();
		SDL_Delay( 50 );
	}
	Graphics::Window::destroy();
	fprintf( stdout, "Shutting down safely\n" );
	return 0;
}
