#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define GREETING "BONJOUR SERVEUR"
int main(int argc, char *argv[]){
   int cfd; // socket du client
   int cfd1;
   int success; // etat de la connection
   int success1;
   int port;
   struct sockaddr_in srv_addr; // socket addr du serveur 

   if (argc != 4) {
     printf("USAGE: ./client <serveur_ip_addr> <serveur_port>  	<fichier_a_envoyer>\n");
     exit(EXIT_FAILURE);
    }
	short int buffer[1000];
	short int value = 1000;
   cfd = socket(AF_INET, SOCK_STREAM, 0); // création de la socket
   cfd1 = socket(AF_INET, SOCK_STREAM, 0);
   if (cfd < 0){ // Une erreur s'est produite la socket n'a pas pu être créer
      printf("Le SE n'a pas pu créer la socket %d\n", cfd);
      exit(-1);
   }
   
   port = atoi(argv[2]);

   srv_addr.sin_family = AF_INET;
   srv_addr.sin_port = htons (port);
   inet_aton(argv[1], (struct in_addr *)&srv_addr.sin_addr.s_addr);

 
   success = connect(cfd, (struct sockaddr *) &srv_addr,
                 sizeof(struct sockaddr_in));
success1 = connect(cfd1, (struct sockaddr *) &srv_addr,
                 sizeof(struct sockaddr_in));
   if(success < 0){ // la connexion a echouée
      printf("Impossible de se connecter au serveur %s:%d error %d\n", 
               argv[1], port, success);
      exit(-1);
   }
	 if(success1 < 0){ // la connexion a echouée
      printf("Impossible de se connecter au serveur %s:%d error %d\n", 
               argv[1], port, success1);
      exit(-1);
   }
   
        send(cfd, argv[3], sizeof(argv[3]), 0);
	FILE* f = fopen(argv[3],"r");
	char line[1];
	sleep(5);
    if (f != NULL) {
        while (fread (line, sizeof(line), 1, f), !        		feof(f)) {
            send(cfd, line, sizeof(line), 0); 
            printf("Paquets envoyés...\n");
        }      
    }
	fclose(f);
   close(cfd);
   	//close(cfd1);
   return(0);
}

