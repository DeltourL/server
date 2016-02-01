#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

int creer_serveur(int port)
{
	/*crée socket_serveur*/
	int socket_serveur ;
	socket_serveur = socket ( AF_INET , SOCK_STREAM , 0);
	if(socket_serveur == -1)
	{
		perror ("socket_serveur");
		return 1;
	}
	
	/*aloue @ip et port a socket_serveur*/
	struct sockaddr_in saddr ;
	saddr.sin_family = AF_INET ; /* Socket ipv4 */
	saddr.sin_port = htons(port); /* Port d'écoute */
	saddr.sin_addr.s_addr = INADDR_ANY ; /* écoute sur toutes les interfaces */
	if(bind(socket_serveur, (struct sockaddr *)& saddr , sizeof( saddr )) == -1)
	{
		perror ("bind socker_serveur");
		return 2;
	}

	/*fixe la file d'attente et demare l'écoute*/
	int file_attente = 10;
	if( listen( socket_serveur , file_attente) == -1)
	{
		perror ("listen socket_serveur");
		return 3;
	}

	return 0;
}