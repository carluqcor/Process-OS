#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <errno.h>

int main(void)
{
	pid_t hijo_pid; 
    int status, childpid, n, s=0;
	printf("Introducir el numero de hijos para el padre: "); 
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		hijo_pid= fork();
		switch(hijo_pid)	
		{
			case 0: 
				printf("Soy el hijo[%d] con pid: %ld\n",i , getpid());
				s++;
				exit(i); //Necesaria la librería <stdlib.h> 	
			default:
				childpid=wait(&status);
				printf("padre con pid: %ld\n\n", getpid());  
		}
	}
	printf("Contador: %d\n\n", s);	//Nos dice cuanto valdrá contador después de pasar por los hijos
	exit(0);
}
