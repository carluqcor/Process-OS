#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <errno.h>
   
void Sum(int s, char *parentesco)	//Funcion que suma el ultimo digito del pid del hijo
{
	int sum, childpid, status;
	sleep(s);
	sum=getpid()%10;	//Coge el decimal con el resto del pid del hijo entre 10
	while(childpid=wait(&status)>0)
	{
		if(WIFEXITED(status))
		sum+=WEXITSTATUS(status);
	}
	if(parentesco!="Padre")
	{
		printf("\nSoy %s, mi pid es %d y el pid de mi padre es: %d y mi suma es %d\n\n", parentesco, getpid(),getppid(),sum);
		exit(sum);
	}
	else	//Separo el if con un else, si no me suma un pid del padre que no es
	{
		printf("\nSoy %s, mi pid es %d y mi suma es %d\n\n", parentesco, getpid(),sum);
			sum=sum+getppid()%10;
		exit(sum);
	}
}

int main(void)
{	
	pid_t pid;
	int childpid, status;
	pid=fork();
	if(pid==0)
	{
		Sum(0, "Primer_Hijo");
	}
	pid=fork();
	if(pid==0)
	{
		pid=fork();
		if(pid==0)
		{
			Sum(0, "Primer_Nieto");
		}
		pid=fork();
		if(pid==0)
		{
			pid=fork();
			if(pid==0)
			{
				Sum(0, "Bisnieto");
			}
		Sum(5, "Segundo_Nieto");
	}
	Sum(5,"Segundo_Hijo");
}	
	if((pid!=0) && (pid!=-1))	
	{
		Sum(5, "Padre");
	}
}


