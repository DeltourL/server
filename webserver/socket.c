#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <signal.h>

int creer_serveur(int port) {
	/*crÃ©e socket_serveur*/
	int socket_serveur ;
	socket_serveur = socket ( AF_INET , SOCK_STREAM , 0);
	if(socket_serveur == -1) {
		perror ("socket_serveur");
		return -1;
    }
	
	/*aloue @ip et port a socket_serveur*/
	struct sockaddr_in saddr ;
	saddr.sin_family = AF_INET ; /* Socket ipv4 */
	saddr.sin_port = htons(port); /* Port d'Ã©coute */
	saddr.sin_addr.s_addr = INADDR_ANY ; /* Ã©coute sur toutes les interfaces */

	//permet au processus de faire le bind sur le même port (sauf si un processus est déjà en listen dessus)
	int optval = 1;
	if (setsockopt(socket_serveur, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)) == -1)
		perror("Can not set SO_REUSEADDR option");
  
	if(bind(socket_serveur, (struct sockaddr *)& saddr , sizeof( saddr )) == -1) {
		perror ("bind socket_serveur");
		return -2;
    }

  
	return socket_serveur;
}

void traitement_signal(int sig) {
	printf("Signal %d reçu\n",sig);
	if (sig == SIGCHLD) {
		int retour;
		waitpid(-1,&retour,0);
	}
}

void initialiser_signaux(void) {
	//si je recoit un sigpipe je previen mais je crash pas
	if(signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
		perror("sigpipe");
	}

	struct sigaction sa ;
	sa.sa_handler = traitement_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	//si un des fils est zombi j'execute traitement_signal(int sig)
	if(sigaction(SIGCHLD,&sa,NULL) == -1) {
		perror("sigaction(SIGCHLD)");
	}
}
