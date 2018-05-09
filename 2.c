#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <errno.h>

int main()
{
	pid_t hijo_pid; 
    int status, childpid;
	hijo_pid= fork();
	if (hijo_pid == 0)
	{
		printf("Soy el hijo con pid: %ld\n", getpid());
		exit(0); //Necesaria la librería <stdlib.h> 
	}
	system("ps -a");   //DEJAR AL HIJO ZOMBIE 
	sleep(5);  
}
