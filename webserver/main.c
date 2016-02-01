#include <stdio.h>
#include <string.h>
#include "socket.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>

int main(int argc, char **argv) 
{
	argc = argc;
	argv = argv;//TODO temp

	int serveur = creer_serveur(8080);
	if (serveur < 0) 
	{
		return serveur;
	}

	while(1) 
	{  
		/*fixe la file d'attente et demare l'écoute*/
		int file_attente = 10;
		if( listen( serveur , file_attente) == -1)
		{
			perror("listen socket_serveur");
			return -3;
		}

		/*cree socket client*/
		int socket_client ;
		socket_client = accept(serveur, NULL, NULL);
		if ( socket_client == -1)
		{
		   	perror ("accept");
		   	return -4;
		}

		/* On peut maintenant dialoguer avec le client */
		const char * message_bienvenue = "Bonjour, bienvenue sur mon serveur\n0100001001101111011011100110101001101111011101010111001000100000001011000010000001100010011010010110010101101110011101100110010101101110011101010110010100100000011100110111010101110010001000000110110101101111011011100010000001110011011001010111001001110110011001010111010101110010" ;

		write(socket_client, message_bienvenue, strlen(message_bienvenue));


		char buf[100];
		while(strlen(buf) != 0)//tant que la co est valide
		{
		    bzero(buf,100);
		    int n = read(socket_client, buf, 100);//on lit ce que nous dit le client
		    if (n < 0) 
		    {
		    	perror("ERROR reading from socket_client");
		    	return -5;
		    }

		    printf("server received %d bytes: %s", n, buf);
		   
		    
		    n = write(socket_client, buf, strlen(buf));//on repete au client ce qu'il nous a dit
		    if (n < 0)
		    { 
		    	perror("ERROR writing to socket_client");
		    	return -6;
			}
		}//une fois que le client deco
		close(socket_client);
	}
  	return 0;
}
