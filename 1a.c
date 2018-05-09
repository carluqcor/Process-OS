#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <errno.h>

int main(void)
{
	pid_t hijo_pid; 
    int status, childpid,n;
	printf("Introducir el numero de hijos para el padre: "); 
			scanf("%d",&n);
	
	for(int i=0;i<n;i++)
	{
		hijo_pid= fork();

		if (hijo_pid == 0){
			printf("Soy el hijo[%d] con pid: %ld y mi padre es: %d\n",i , getpid(), getppid());
		    exit(i); //Necesaria la librería <stdlib.h> 
	 	}
	}
		for (int i=0;i<n;i++){
		childpid=wait(&status);
	
		if(childpid>0){
			if (WIFEXITED(status)) {
				printf("child %d exited, status=%d\n\n",childpid, WEXITSTATUS(status));
			} else if (WIFSIGNALED(status)) {
		               printf("child %d killed (signal %d)\n\n", childpid, WTERMSIG(status));
			} else if (WIFSTOPPED(status)) {
				printf("child %d stopped (signal %d)\n\n", childpid, WSTOPSIG(status));
			} 
		}

	}
}


