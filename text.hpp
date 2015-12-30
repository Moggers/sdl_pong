#include <SDL2/SDL_ttf.h>
namespace Graphics
{
	class Text
	{
		public:
		static TTF_Font * g_font;
		static int initialize( const char * filename );
	};
}
