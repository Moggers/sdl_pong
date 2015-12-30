#include "textbox.hpp"
#include "text.hpp"
#include "window.hpp"

namespace Graphics
{
	Textbox::Textbox( int x, int y, int w, int h )
	{
		m_text = (char*)calloc( 32, sizeof( char ) );
		m_texture = NULL;
		m_shown = 0;
		m_active = 0;
		m_editable = 0;
		m_updated = 0;
		m_border.x = x;
		m_border.y = y;
		m_border.w = w;
		m_border.h = h;
		m_fill.x = m_border.x + 1;
		m_fill.y = m_border.y + 1;
		m_fill.w = m_border.w - 2;
		m_fill.h = m_border.h - 2;
	}

	int Textbox::think( SDL_Event * event )
	{
		if( !m_shown ) return 1;
		SDL_MouseMotionEvent * mousemotion = &event->motion;
		SDL_TextInputEvent * textevent = &event->text;
		switch( event->type ) {
			case SDL_MOUSEMOTION:
				m_mouseover = 0;
				if( mousemotion->x > m_fill.x && mousemotion->x < m_fill.x + m_fill.w &&
					mousemotion->y > m_fill.y && mousemotion->y < m_fill.y + m_fill.h ) {
					m_mouseover = 1;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				m_active = m_mouseover;
				if( m_active == 1 ) {
					SDL_StartTextInput();
					m_text[0] = '\0';
					fprintf( stdout, "Help!!!\n" );
				}
				break;
			case SDL_MOUSEBUTTONUP:
				break;
			case SDL_TEXTINPUT:
				if( !m_active ) break;
				update_text( textevent->text, 1 );
				break;
		}
		return 0;
	}

	int Textbox::update_text( char * text, int append )
	{
				if( append )
					strcat( m_text, text );
				else
					strcpy( m_text, text );
				SDL_Color red = {150, 0, 0 };
				m_surf = TTF_RenderText_Blended( Graphics::Text::g_font, m_text, red );
				m_texture = SDL_CreateTextureFromSurface( Graphics::Window::g_ren, m_surf );
				int tw, th;
				SDL_QueryTexture( m_texture, NULL, NULL, &tw, &th );
				m_textsize.x = m_fill.x + (m_fill.w / 2 ) - (tw / 2);
				m_textsize.y = m_fill.y + (m_fill.h / 2 ) - (th / 2);
				m_textsize.w = tw;
				m_textsize.h = th;
				m_updated = 1;
		return 0;
	}
	int Textbox::draw( void )
	{
		if( !m_shown ) return 1;
		SDL_SetRenderDrawColor( Graphics::Window::g_ren, 175, 175, 175, 255 );
		SDL_RenderDrawRect( Graphics::Window::g_ren, &m_border );
		SDL_SetRenderDrawColor( Graphics::Window::g_ren, 
			150 - m_active * 50 + m_mouseover * 30, 
			150 + m_mouseover * 30, 
			150 + m_mouseover * 30, 
			255 );
		SDL_RenderFillRect( Graphics::Window::g_ren, &m_fill );
		if( m_texture != NULL )
			SDL_RenderCopy( Graphics::Window::g_ren, m_texture, NULL, &m_textsize );
		m_updated = 0;
		return 0;
	}
	
	void Textbox::hide( void )
	{
		m_shown = 0;
	}

	void Textbox::show( void )
	{
		m_shown = 1;
	}
}
