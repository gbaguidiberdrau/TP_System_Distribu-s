
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/shm.h>


int main() {
    pid_t pid1, pid2, pid3;
    int a=0,i,status;

    //Generate a key
    key_t key = ftok("memory",65);
    //Take identifier of memory
    int memoId = shmget(key,1024,0666|IPC_CREAT);
    //Attach the shared memory
    char *str = (char*) shmat(memoId,(void*)0,0);
    sprintf(str,"%d",a);
    printf("%s\n",str);
    pid1 = fork();

    if(pid1<0){
        printf("Erreur le premier processus n'est pas cree\n");
    } else{
        if(pid1==0){

            //Generate a key
            key_t key = ftok("memory",65);
            //Take identifier of memory
            int memoId = shmget(key,1024,0666|IPC_CREAT);
            //Attach the shared memory
            char *str = (char*) shmat(memoId,(void*)0,0);
            for(i=0;i<100;++i){
                a = atoi(str);
                a++;
		
                sprintf(str,"%d",a);
                printf("valeur 1 : %s\n",str);

            }
            exit(0);
        } else{
            sleep(5);
            pid2 = fork();
            if(pid2<0){
                printf("Erreur le second processus n'est pas cree\n");
            } else{
                if(pid2==0){

                    //Generate a key
                    key_t key = ftok("memory",65);
                    //Take identifier of memory
                    int memoId = shmget(key,1024,0666|IPC_CREAT);
                    //Attach the shared memory
                    char *str = (char*) shmat(memoId,(void*)0,0);
                    for(i=0;i<100;++i){
                        a = atoi(str);
                        a++;
			
                        sprintf(str,"%d",a);
                        printf("valeur 2 : %s\n",str);
                    }
                    exit(0);
                } else{
                    sleep(5);
                    pid3 = fork();
                    if(pid3<0){
                        printf("Erreur le troisieme processus n'est pas cree \n");
                    } else{
                        if(pid3==0){

                            //Generate a key
                            key_t key = ftok("memory",65);
                            //Take identifier of memory
                            int memoId = shmget(key,1024,0666|IPC_CREAT);
                            //Attach the shared memory
                            char *str = (char*) shmat(memoId,(void*)0,0);
                            for(i=0;i<100;++i){
                                a = atoi(str);
                                a++;
				
                                sprintf(str,"%d",a);
                                printf("valeur 3 : %s\n",str);
                            }
                            exit(0);

                        }
                        else{
                            pid1 = wait(&status);
                            pid2 = wait(&status);
                            pid3 = wait(&status);
                            //Reponse finale
                            printf("La reponse finale : %s\n",str);
                            //detach from shared memory
                            shmdt(str);
                            // destroy the shared memory
                            shmctl(memoId,IPC_RMID,NULL);
                        }
                    }
                }
            }
        }
    }


    return 0;
}
