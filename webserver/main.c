#include <stdio.h>
#include <string.h>
#include "socket.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <stdlib.h>

int compter_char(char * bufcpy,char c)
{
	int areturn=0;
	int i;
	for (i = 0; i < (int)strlen(bufcpy); ++i)
	{
		areturn+=bufcpy[i]==c? 1:0;
		if (bufcpy[i] == '\n')
			return areturn;
	}
	return areturn;
}

int str_match(char * bufcpy)
{
	char* mot3="";
	int nbsp=0;
	int i=0;
	while(bufcpy[i] != '\n')
	{
		if (nbsp == 2)
		{
			char *tmp = malloc(strlen(mot3)+2);
			strcpy(tmp,mot3);
			tmp[strlen(mot3)]=bufcpy[i];
			tmp[strlen(mot3)+1]='\0';
			mot3=tmp;
		}

		if (bufcpy[i] == ' ')
		{
			nbsp++;
		}
		i++;
	}
	if (strcmp(mot3,"HTTP/1.1")==0 || strcmp(mot3,"HTTP/1.0")==0)
		return 1;
	return 0;
}

int main(int argc, char **argv) {
	argc = argc;
	argv = argv;//TODO temporaire

	int serveur = creer_serveur(8080);
	if (serveur < 0) {
    	return serveur;
    }

  	initialiser_signaux();
  
  	printf("%s\n", "server started listening on 8080 ...");
	
	while(1) {  
    	/*fixe la file d'attente et demare l'écoute*/
    	int file_attente = 10;
    	if( listen( serveur , file_attente) == -1) {
			perror("listen socket_serveur");
			return -3;
		}

		/*cree socket client*/
		int socket_client ;
		socket_client = accept(serveur, NULL, NULL);
		if ( socket_client == -1) {
			perror ("accept");
			return -4;
		}
		if (fork()==0) {
			/* On peut maintenant dialoguer avec le client */
			//const char * message_bienvenue = "0100001001101111011011100110101001101111011101010111001000100000001011000010000001100010011010010110010101101110011101100110010101101110011101010110010100100000011100110111010101110010001000000110110101101111011011100010000001110011011001010111001001110110011001010111010101110010\n102 157 156 152 157 165 162 054 040 142 151 145 156 166 145 156 165 145 040 163 165 162 040 155 157 156 040 163 145 162 166 145 165 162\n66 111 110 106 111 117 114 44 32 98 105 101 110 118 101 110 117 101 32 115 117 114 32 109 111 110 32 115 101 114 118 101 117 114\n42 6f 6e 6a 6f 75 72 2c 20 62 69 65 6e 76 65 6e 75 65 20 73 75 72 20 6d 6f 6e 20 73 65 72 76 65 75 72\nLXVI CXI CX CVI CXI CXVII CXIV XLIV XXXII XCVIII CV CI CX CXVIII CI CX CXVII CI XXXII CXV CXVII CXIV XXXII CIX CXI CX XXXII CXV CI CXIV CXVIII CI CXVII CXIV\n-... --- -. .--- --- ..- .-. --..-- / -... .. . -. ...- . -. ..- . / ... ..- .-. / -- --- -. / ... . .-. ...- . ..- .-.\nßo|\\|joµ12, b][env3nue su.- mo/V $&12\\/eur\n7752e0fad02e1ac9dbda87af611e6602\n79039ee375d4ec5cd4b8d29bdba19e279ee8c03e\nBonjour, bienvenue sur mon serveur\n";
			
			

			char buf[255] = "a";
			//char bufServer[110] = "<server>";
			
			FILE* file = fdopen(socket_client, "w+");
			if (file == NULL) {
					fprintf(stderr, "%s\n", "ERROR opening socket_client");
					return -7;
			} else {
				int entete_ok=0;
				int ligne_vide_detecter=0;
				//tant que la co est valide
				while(strlen(buf) != 0) {
					bzero(buf,255);
					if (fgets(buf, 255, file) == NULL) {
						fprintf(stderr, "%s\n", "ERROR reading from socket_client");
						return -5;
					}
					
					//printf("server received %zu bytes: %s", strlen(buf), buf);
					printf("%s\n", buf);

					char bufcpy[255];
					strcpy(bufcpy, buf);
					int i = compter_char(bufcpy,' ');
					if (strncmp(buf,"GET",3) == 0 && i==2 && str_match(bufcpy))
					{
						entete_ok=1;
					}
					
					if(entete_ok == 1)
					{
						if(strncmp(buf,"\n",1) == 0||strncmp(buf,"\r\n",2) == 0)
						{
							ligne_vide_detecter=1;
						}

						if (ligne_vide_detecter==1)
						{
							char * msg_bjr="HTTP/1.1 200 OK\r\nContent-Length: 1079\r\n\r\n0100001001101111011011100110101001101111011101010111001000100000001011000010000001100010011010010110010101101110011101100110010101101110011101010110010100100000011100110111010101110010001000000110110101101111011011100010000001110011011001010111001001110110011001010111010101110010\n102 157 156 152 157 165 162 054 040 142 151 145 156 166 145 156 165 145 040 163 165 162 040 155 157 156 040 163 145 162 166 145 165 162\n66 111 110 106 111 117 114 44 32 98 105 101 110 118 101 110 117 101 32 115 117 114 32 109 111 110 32 115 101 114 118 101 117 114\n42 6f 6e 6a 6f 75 72 2c 20 62 69 65 6e 76 65 6e 75 65 20 73 75 72 20 6d 6f 6e 20 73 65 72 76 65 75 72\nLXVI CXI CX CVI CXI CXVII CXIV XLIV XXXII XCVIII CV CI CX CXVIII CI CX CXVII CI XXXII CXV CXVII CXIV XXXII CIX CXI CX XXXII CXV CI CXIV CXVIII CI CXVII CXIV\n-... --- -. .--- --- ..- .-. --..-- / -... .. . -. ...- . -. ..- . / ... ..- .-. / -- --- -. / ... . .-. ...- . ..- .-.\nßo|\\|joµ12, b][env3nue su.- mo/V $&12\\/eur\n7752e0fad02e1ac9dbda87af611e6602\n79039ee375d4ec5cd4b8d29bdba19e279ee8c03e\nBonjour, bienvenue sur mon serveur\n";

							write(socket_client, msg_bjr, strlen(msg_bjr));
						}
					}
					else
					{
						char * msg_400="HTTP/1.1 400 Bad Request\r\nConnection: close\r\nContent-Length: 17\r\n\r\n400 Bad request\r\n";

						write(socket_client, msg_400, strlen(msg_400));
						break;
					}

					/*strcpy(bufServer, "<server>");
					strcat(bufServer, buf);
					if (fprintf(file, bufServer) < 0) { 
						fprintf(stderr, "%s\n", "ERROR writing to socket_client");
						return -6;
					}*/
				}//une fois que le client deco
			}
			fclose(file);
			close(socket_client);
			exit(0);
		}
		close(socket_client);
	}
	close(serveur);
	return 0;
}