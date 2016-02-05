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

  initialiser_signaux();
  
  printf("%s\n", "server started listening on 8080 ...");
	
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
      const char * message_bienvenue = "0100001001101111011011100110101001101111011101010111001000100000001011000010000001100010011010010110010101101110011101100110010101101110011101010110010100100000011100110111010101110010001000000110110101101111011011100010000001110011011001010111001001110110011001010111010101110010\n102 157 156 152 157 165 162 054 040 142 151 145 156 166 145 156 165 145 040 163 165 162 040 155 157 156 040 163 145 162 166 145 165 162\n66 111 110 106 111 117 114 44 32 98 105 101 110 118 101 110 117 101 32 115 117 114 32 109 111 110 32 115 101 114 118 101 117 114\n42 6f 6e 6a 6f 75 72 2c 20 62 69 65 6e 76 65 6e 75 65 20 73 75 72 20 6d 6f 6e 20 73 65 72 76 65 75 72\nLXVI CXI CX CVI CXI CXVII CXIV XLIV XXXII XCVIII CV CI CX CXVIII CI CX CXVII CI XXXII CXV CXVII CXIV XXXII CIX CXI CX XXXII CXV CI CXIV CXVIII CI CXVII CXIV\n-... --- -. .--- --- ..- .-. --..-- / -... .. . -. ...- . -. ..- . / ... ..- .-. / -- --- -. / ... . .-. ...- . ..- .-.\nßo|\\|joµ12, b][env3nue su.- mo/V $&12\\/eur\n7752e0fad02e1ac9dbda87af611e6602\n79039ee375d4ec5cd4b8d29bdba19e279ee8c03e\nBonjour, bienvenue sur mon serveur\n";
      sleep(1);
      write(socket_client, message_bienvenue, strlen(message_bienvenue));


      char buf[100] = "a";
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
	  
	  if (n!=0) {
	    n = write(socket_client, buf, strlen(buf));//on repete au client ce qu'il nous a dit
	    if (n < 0)
	      { 
		perror("ERROR writing to socket_client");
		return -6;
	      }
	  }
	}//une fois que le client deco
      close(socket_client);
    }
  close(serveur);
  return 0;
}
