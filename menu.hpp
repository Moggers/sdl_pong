#include <cstdarg>
#include <functional>
#include <SDL2/SDL.h>
#include <string>
#include <SDL2/SDL_ttf.h>

namespace Graphics
{
	class Menu
	{
		public:
		Menu( int x, int y, int w, int h, int argc, ... );
		int draw( void );
		void hide();
		void show();
		int think( SDL_Event * event );
		static int initialize( void );
		int setaction( int id, std::function<void()> function );
		private:
		std::string * m_fields[32];
		SDL_Rect m_dimensions;
		int m_fieldc;
		SDL_Texture ** m_texts;
		SDL_Rect ** m_border;
		SDL_Rect ** m_fill;
		SDL_Rect ** m_textpos;
		int m_mouseover;
		int m_click;
		int m_shown;
		std::function<void()> * m_functions;
	};
}
