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
  int socket = creer_serveur(8080);
  if (socket < 0) {
    return socket;
  }
  while (1) {
    
    /*fixe la file d'attente et demare l'écoute*/
    int file_attente = 10;
    if( listen( socket , file_attente) == -1)
      {
	perror ("listen socket_serveur");
	return -3;
      } else
      {
	int socket_client ;
	socket_client = accept ( socket , NULL , NULL );
	if ( socket_client == -1)
	  {
	    perror ( " accept " );
	    /* traitement d ’ erreur */
	    return -4;
	  }
	/* On peut maintenant dialoguer avec le client */
	const char * message_bienvenue = "Bonjour, bienvenue sur mon serveur\nLorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur sit amet posuere turpis. Proin pellentesque, dui sed semper vulputate, tortor tellus fringilla quam, quis molestie ipsum tellus at ex. Vivamus arcu justo, rutrum vel leo at, suscipit tincidunt justo. Fusce odio lacus, malesuada non dui at, tempus dictum augue. Mauris in enim ligula. Donec vel porta magna. Fusce condimentum ex metus, eget consequat arcu facilisis vel. Vivamus eget ipsum consectetur, congue lorem in, mattis velit. Cras porttitor hendrerit purus, id vehicula tortor vulputate in. Integer lacus arcu, vehicula a venenatis in, vulputate sit amet lectus. Nullam ullamcorper malesuada dui non congue. Maecenas efficitur feugiat orci, nec vulputate nisl consequat ut. Nulla quis lectus laoreet enim rutrum euismod." ;
	write ( socket_client , message_bienvenue , strlen ( message_bienvenue ));
	char buf[100];
	while(strlen(buf) != 0)
	  {
	    bzero(buf, 100);
	    n = read(childfd, buf, 100);
	    if (n < 0) 
	      error("ERROR reading from socket");
	    printf("server received %d bytes: %s", n, buf);
    
	    /* 
	     * write: echo the input string back to the client 
	     */
	    n = write(childfd, buf, strlen(buf));
	    if (n < 0) 
	      error("ERROR writing to socket");
	  }
	
      }
  }
  return 0;
}
