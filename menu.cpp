#include "menu.hpp"
#include "window.hpp"
#include <stdio.h>

namespace Graphics 
{

	Menu::Menu( int x, int y, int w, int h, int argc, ... )
	{
		va_list arguments;
		va_start( arguments, argc );
		for( int ii = 0; ii < argc; ii++ ) {
			m_fields[ii] = new std::string( va_arg( arguments, char* ) );
		}
		va_end( arguments );
		m_fieldc = argc;
		m_dimensions.x = x;
		m_dimensions.y = y;
		m_dimensions.w = w;
		m_dimensions.h = h;
	}
	int Menu::draw( void )
	{
		for( int ii = 0; ii < m_fieldc; ii++ ) {
			SDL_Rect border = { 
				m_dimensions.x,
				m_dimensions.y + (m_dimensions.h / m_fieldc) * ii,
				m_dimensions.w,
				m_dimensions.h / m_fieldc };
			SDL_SetRenderDrawColor( Graphics::Window::g_ren, 175, 175, 175, 255 );
			SDL_RenderDrawRect( Graphics::Window::g_ren, &border );
		}
		return 0;
	}

}
