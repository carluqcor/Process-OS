#include <sys/types.h> //Para estructura pid_t 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Para fork()
#include <errno.h>
#include <sys/wait.h>

int main()
	{

	pid_t hijo_pid; 
    int status, childpid, n, i;
	printf("Introducir el numero de hijos para el padre: "); 
			scanf("%d",&n);
	
	for(i=0; i<n; i++)
	{

		hijo_pid=fork();
  		switch(hijo_pid){
       	 	case -1: //Error
           		perror("fork error");
           		printf("errno value= %d\n", errno); 
				exit(EXIT_FAILURE); 
          		break;           
       	 
			case 0: //Proceso hijo 
				printf("Soy el hijo %d, mi PID es : %d y mi padre es %d \n", i, getpid(), getppid());
				break;
            default: //Proceso padre
				childpid=wait(&status);
				if(childpid>0)
		    	 {
		           if (WIFEXITED(status)) 
				   {
		               printf("child %d exited, status=%d\n",childpid, WEXITSTATUS(status));
				   }
 
				   else if (WIFSIGNALED(status)) 
				   {
		               printf("child %d killed (signal %d)\n", childpid, WTERMSIG(status));
		           }

				   else if (WIFSTOPPED(status)) 
                   {
		               printf("child %d stopped (signal %d)\n", childpid, WSTOPSIG(status));
			       } 
			}
			exit(0);
		}
	}		
}
