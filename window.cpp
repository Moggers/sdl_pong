#include "window.hpp"
#include <stdio.h>
#include <SDL2/SDL.h>

namespace Graphics
{
	SDL_Window * Window::g_win;
	SDL_Renderer * Window::g_ren;
	int g_winsize[2];
	int Window::initialize( int winwidth, int winheight )
	{
		g_winsize[0] = winwidth;
		g_winsize[1] = winheight; 
		if( SDL_Init( SDL_INIT_VIDEO ) != 0 ) {
			fprintf( stdout, "Faild to init SDL: %s\n", SDL_GetError() );
			return 1;
		}

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

		SDL_SetRenderDrawColor( g_ren, 0, 0, 0, 255 );
		SDL_RenderClear( g_ren );

		return 0;
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
		return 0;
	}
	
	int Window::test( void )
	{

		SDL_Window* window;
		SDL_Renderer* renderer;

		// Initialize SDL.
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
			return 1;

		// Create the window where we will draw.
		window = SDL_CreateWindow("SDL_RenderClear",
				SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				512, 512,
				0);

		// We must call SDL_CreateRenderer in order for draw calls to affect this window.
		renderer = SDL_CreateRenderer(window, -1, 0);

		// Select the color for drawing. It is set to red here.
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

		// Clear the entire screen to our selected color.
		SDL_RenderClear(renderer);

		// Up until now everything was drawn behind the scenes.
		// This will show the new, red contents of the window.
		SDL_RenderPresent(renderer);

		// Give us time to see the window.
		SDL_Delay(5000);

		// Always be sure to clean up
		SDL_Quit();
		return 0;
	}
}
