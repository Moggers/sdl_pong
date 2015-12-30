#include "text.hpp"
namespace Graphics
{
	TTF_Font * Text::g_font;
	int Text::initialize( const char * filename )
	{
		g_font = TTF_OpenFont( filename, 24 );
		if( g_font == NULL ) {
			fprintf( stdout, "Failed to load font: %s\n", TTF_GetError() );
			return 1;
		}
		return 0;
	}
}
