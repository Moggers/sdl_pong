#include <SDL2/SDL.h>
namespace Graphics
{
	class Textbox
	{
		public:
		Textbox( int x, int y, int w, int h );
		int draw( void );
		int think( SDL_Event * event );
		int update_text( char * text, int append );
		void hide( void );
		void show( void );
		SDL_Rect m_border;
		SDL_Rect m_fill;
		char * m_text;
		int m_editable;
		private:
		int m_shown;
		int m_mouseover;
		int m_active;
		SDL_Texture * m_texture;
		SDL_Rect m_textsize;
		SDL_Surface * m_surf;
		int m_updated;
	};
}
