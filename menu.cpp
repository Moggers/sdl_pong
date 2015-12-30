#include "menu.hpp"
#include "window.hpp"
#include <stdio.h>
#include "text.hpp"

namespace Graphics 
{

	Menu::Menu( int x, int y, int w, int h, int argc, ... )
	{
		m_shown = 0;
		m_mouseover = -1;
		m_fieldc = argc;
		m_dimensions.x = x;
		m_dimensions.y = y;
		m_dimensions.w = w;
		m_dimensions.h = h;

		m_border = (SDL_Rect**)calloc( argc, sizeof( SDL_Rect * ) );
		m_fill = (SDL_Rect**)calloc( argc, sizeof( SDL_Rect * ) );
		m_textpos = (SDL_Rect**)calloc( argc, sizeof( SDL_Texture * ) );
		m_texts = (SDL_Texture**)calloc( argc, sizeof( SDL_Texture * ) );
		m_functions = (std::function<void()>*)calloc( argc, sizeof(std::function<void()>) );

		va_list arguments;
		va_start( arguments, argc );
		for( int ii = 0; ii < argc; ii++ ) {
			m_fields[ii] = new std::string( va_arg( arguments, char* ) );

			m_border[ii] = (SDL_Rect*)malloc( sizeof( SDL_Rect ) );
			m_border[ii]->x = x;
			m_border[ii]->y = y + (h / m_fieldc) * ii + (5 / m_fieldc) * ii;
			m_border[ii]->w = w;
			m_border[ii]->h = h / m_fieldc - 5;

			m_fill[ii] = (SDL_Rect*)malloc( sizeof( SDL_Rect ) );
			m_fill[ii]->x = m_border[ii]->x + 1;
			m_fill[ii]->y = m_border[ii]->y + 1;
			m_fill[ii]->w = m_border[ii]->w - 2;
			m_fill[ii]->h = m_border[ii]->h - 2;

			m_texts[ii] = (SDL_Texture*)malloc( sizeof( SDL_Texture* ) );
			SDL_Color red = {150, 0, 0 };
			SDL_Surface * text = TTF_RenderText_Blended( Graphics::Text::g_font, m_fields[ii]->c_str(), red );
			m_texts[ii] = SDL_CreateTextureFromSurface( Graphics::Window::g_ren, text );

			int tw, th;
			SDL_QueryTexture( m_texts[ii], NULL, NULL, &tw, &th );
			m_textpos[ii] = (SDL_Rect*)malloc( sizeof( SDL_Rect ) );
			m_textpos[ii]->x = m_fill[ii]->x + (m_fill[ii]->w / 2 ) - (tw / 2);
			m_textpos[ii]->y = m_fill[ii]->y + (m_fill[ii]->h / 2 ) - (th / 2);
			m_textpos[ii]->w = tw;
			m_textpos[ii]->h = th;

		}
		va_end( arguments );
	}
	int Menu::draw( void )
	{
		if( !m_shown ) return 1;
		for( int ii = 0; ii < m_fieldc; ii++ ) {
			SDL_SetRenderDrawColor( Graphics::Window::g_ren, 175, 175, 175, 255 );
			SDL_RenderDrawRect( Graphics::Window::g_ren, m_border[ii] );
			if( ii == m_mouseover ) SDL_SetRenderDrawColor( Graphics::Window::g_ren, 180 - m_click * 50, 180, 180, 255 );
			else 					SDL_SetRenderDrawColor( Graphics::Window::g_ren, 150, 150, 150, 255 );
			SDL_RenderFillRect( Graphics::Window::g_ren, m_fill[ii] );

			SDL_RenderCopy( Graphics::Window::g_ren, m_texts[ii], NULL, m_textpos[ii] );
		}
		return 0;
	}
	int Menu::initialize( void )
	{
		return 0;
	}

	int Menu::setaction( int id, std::function<void()> function )
	{
		m_functions[id] = function;
		return 0;
	}

	int Menu::think( SDL_Event * event )
	{
		if( !m_shown ) return 1;
		SDL_MouseMotionEvent * mousemotion = &event->motion;
		switch( event->type ) {
			case SDL_MOUSEMOTION:
				m_mouseover = -1;
				for( int ii = 0; ii < m_fieldc; ii++ ) {
					if( mousemotion->x > m_fill[ii]->x && mousemotion->x < m_fill[ii]->x + m_fill[ii]->w &&
						mousemotion->y > m_fill[ii]->y && mousemotion->y < m_fill[ii]->y + m_fill[ii]->h ) {
						m_mouseover = ii;
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				m_click = 1;
				break;
			case SDL_MOUSEBUTTONUP:
				if( m_click == 1 && m_mouseover != -1 ) {
					if( m_functions[m_mouseover] != NULL ) {
						m_functions[m_mouseover]();
					} else {
						fprintf( stdout, "Not implemented\n" );
					}
				}
				m_click = 0;
				break;
		}
		return 0;
	}
	
	void Menu::hide( void )
	{
		m_shown = 0;
	}
	void Menu::show( void )
	{
		m_shown = 1;
	}
}
