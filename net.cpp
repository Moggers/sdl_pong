#include "net.hpp"
#include <stdio.h>
#include <stdlib.h>
namespace Net
{
	Host::Host( int port )
	{
		if( SDLNet_ResolveHost( &ip, NULL, port ) == -1 ) {
			fprintf( stdout, "Failed to resolve host: %s\n", SDLNet_GetError() );
		}
		listen = SDLNet_TCP_Open( &ip );
		if( !listen ) {
			fprintf( stdout, "Failed to create listen server :%s\n", SDLNet_GetError() );
		}
		log = (char*)calloc( 1024, sizeof( char ) );
		strcat( log, "Starting server\n" );
	}
	int Host::start( void )
	{
		listen_thread = SDL_CreateThread( listen_thread_callback, "listen thread", (void*)this );
		return 0;
	}
	int Host::init( void )
	{
		if( SDLNet_Init() != 0 ) {
			fprintf( stdout, "Failed to init net subsystem: %s\n", SDLNet_GetError() );
			return 1;
		}
		return 0;
	}

	int Host::listen_thread_callback( void * param )
	{
		Net::Host * host = (Net::Host*)param;
		while( 1 ) {
			TCPsocket clientcon = SDLNet_TCP_Accept( host->listen );
			if( !clientcon ) {
				SDL_Delay( 100 );
				continue;
			}
			IPaddress * clientip = SDLNet_TCP_GetPeerAddress( clientcon );
			if( !clientip ) {
				fprintf( stdout, "Failed to retrieve IP of connecting peer: %s\n", SDLNet_GetError() );
				continue;
			}
			Uint32 ipaddr = SDL_SwapBE32( clientip->host );
			sprintf( host->log, "Accepted a connection from %d.%d.%d.%d on port %hu\n",
				ipaddr>>24,
				(ipaddr>>16)&0xff,
				(ipaddr>>8)&0xff,
				ipaddr&0xff,
				clientip->port );
		}
		return 0;
	}
}
