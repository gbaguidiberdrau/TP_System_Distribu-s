/**Ce programme lit en argument trois fichiers et
 * lance trois fois le même programme avec trois fichiers 
 * d'entrée différens comme argument d'entré
 * 20/08/18
 * Auteur: Assogba Emery Kouassi assogba.emery@gmail.com*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t proc1, proc2, proc3;
    int status;
    
    proc1 = fork();
    if(proc1 < 0){
          perror("Erreur de création du processus\n");
          exit(EXIT_FAILURE);
    }

    if(proc1 == 0){
        printf("Création deu processus 1\n");
    }

    else{
  
        proc2 = fork();
        if(proc2 < 0){
          perror("Erreur de création du second processus\n");
          proc1 = wait(&status);
          exit(EXIT_FAILURE);
        }

        if(proc2== 0){
            printf("Création du processus 2\n");
        }

        else{
            proc3 = fork();
            if(proc3 < 0){
              perror("Erreur de création du troisieme processus\n");
              proc1 = wait(&status);
              proc2 = wait(&status);
              exit(EXIT_FAILURE);
            }

            if(proc3 == 0){
               printf("Création du processus 3\n");
            }

            else{
                proc1 = wait(&status);
                printf("pid du fils 1 %d\n",proc1);
                proc2 = wait(&status);
                printf("pid du fils 2 %d\n", proc2);
                proc3 = wait(&status);
                printf("pid du fils 3 %d\n", proc3);
            }
        }

        
    } 
}
