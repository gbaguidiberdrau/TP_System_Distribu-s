
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/shm.h>


int main() {
   
    //Generate a key
    key_t key = ftok("memory",65);
    //Take identifier of memory
    int memoId = shmget(key,1024,0666|IPC_CREAT);
    //Attach the shared memory
    char *str = (char*) shmat(memoId,(void*)0,0);
	int comp,comp1,j,b,tmp =0;
	int ordre = 3;
	int taille = ordre * ordre;
	 pid_t pid1[taille];
        int a=0,i;

	for (comp = 1;comp <= ordre; comp++){
	  for(comp1 = 1;comp1<=ordre;comp1++)
          {
		tmp +=1;
		sprintf(str,"%d",comp);
		sprintf(str+1,"%d",comp1);
		printf("%s \n",str);
	        pid1[tmp] = fork();
		if(pid1[tmp] == 0){printf("Le processus %d créé calcul %d et %d\n",tmp,comp,comp1);
		int pi= comp;
		int pj = comp1;	
	                   } 
         }
	
 	                                  }
	//detach from shared memory
	shmdt(str);	
	// destroy the shared memory
	shmctl(memoId,IPC_RMID,NULL);

return 0;
}


