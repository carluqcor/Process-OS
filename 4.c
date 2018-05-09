#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <errno.h>

int main(int argc, char *argv[])
{
	if(argc<3)
	{
		printf("Error en los argumentos, se inicia así: <%s> <gnome-calculator> <gedit> y el nombre de todos de cuantos ficheros queramos crear separados con espacio\n", argv[0]); 
	}	
	pid_t pid; 
    int status, childpid;
	pid= fork();
	if (pid==0)
		execlp("gnome-calculator","", NULL);	//SE abre la calculadora
	pid=fork();
	if(pid==0)
	{
		execvp(argv[2], &argv[2]);	//Abre tantos ficheros en gedit como valor pongamos en argv2
	}
	while(childpid=wait(&status)>0)
	{
		if(WIFEXITED(status)) 
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
