#include <cstdarg>
#include <SDL2/SDL.h>
#include <string>

namespace Graphics
{
	class Menu
	{
		public:
		Menu( int x, int y, int w, int h, int argc, ... );
		int draw( void );
		private:
		std::string * m_fields[32];
		SDL_Rect m_dimensions;
		int m_fieldc;
	};
}
