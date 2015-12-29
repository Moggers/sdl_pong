#include <SDL2/SDL.h>

namespace Graphics
{
	class Window
	{
		public:
		static int initialize( int winwidth, int winheight );
		static int destroy( void );
		static int flush( void );
		static int test( void );
		static SDL_Window *g_win;
		static SDL_Renderer *g_ren;
		static int g_winsize[2];
	};
}
