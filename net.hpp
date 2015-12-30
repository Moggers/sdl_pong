#include <SDL2/SDL_net.h>
namespace Net
{
	 class Host
	 {
		 public:
		 Host( int port );
		 static int init( void );
		 int start( void );
		 private:
		 static int listen_thread_callback( void * param );
		 int m_port;
		 IPaddress ip;
		 TCPsocket listen;
		 SDL_Thread * listen_thread;
		 char * log;
	 };
}
