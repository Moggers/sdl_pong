#include "window.hpp"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "menu.hpp"
#include "text.hpp"

namespace Graphics
{
	SDL_Window * Window::g_win;
	SDL_Renderer * Window::g_ren;
	int Window::g_winsize[2];
	int Window::initialize( int winwidth, int winheight )
	{
		if( SDL_Init( SDL_INIT_VIDEO ) != 0 ) {
			fprintf( stdout, "Faild to init SDL: %s\n", SDL_GetError() );
			return 1;
		}
		if( TTF_Init() != 0 ) {
			fprintf( stdout, "Failed to init TTF library: %s\n", TTF_GetError() );
			return 1;
		}

		g_winsize[0] = winwidth;
		g_winsize[1] = winheight; 
		g_win = SDL_CreateWindow( "Pong Test", 100, 100, winwidth, winheight, SDL_WINDOW_SHOWN );
		if( g_win == NULL ) {
			fprintf( stdout, "Failed to create SDL2 window: %s\n", SDL_GetError() );
			SDL_Quit();
			return 1;
		}

		g_ren = SDL_CreateRenderer( g_win, -1, SDL_RENDERER_ACCELERATED );
		if( g_ren == NULL ) {
			SDL_DestroyWindow( g_win );
			fprintf( stdout, "Failed to create SDL2 renderer %s\n", SDL_GetError() );
			SDL_Quit();
			return 1;
		}

		if( Graphics::Menu::initialize() != 0 ) {
			fprintf( stdout, "Failed to init menu system\n" );
			destroy();
			return 1;
		}
		const char * fn = "gothic_urw.ttf";
		if( Graphics::Text::initialize( fn ) != 0 ) {
			fprintf( stdout, "Failed to init text system\n" );
			destroy();
			return 1;
		}

		return 0;
	}

	void Window::clear( int r, int g, int b, int a )
	{
		SDL_SetRenderDrawColor( g_ren, r, g, b, a );
		SDL_RenderClear( g_ren );
	}
	int Window::destroy( void )
	{
		SDL_DestroyRenderer( g_ren );
		SDL_DestroyWindow( g_win );
		SDL_Quit();
		return 0;
	}

	int Window::flush( void )
	{
		SDL_RenderPresent( g_ren );
		clear( 100, 100, 110, 255 );
		return 0;
	}
	
	void Window::shutdown( void ) {
		destroy();
		exit(0);
	}
}
