#include "menu.hpp"
#include "window.hpp"
#include <stdio.h>

int main( int argc, char ** argv )
{
	Graphics::Window::initialize( 640, 480 );
	fprintf( stdout, "Starting\n" );
	Graphics::Menu startmenu = Graphics::Menu( 50, 50, 540, 260, 4, "Join Game", "Host Game", "Options", "Exit" );
	while( 1 ) {
		startmenu.draw();
		Graphics::Window::flush();
	}
	Graphics::Window::destroy();
	fprintf( stdout, "Shutting down safely\n" );
	return 0;
}
