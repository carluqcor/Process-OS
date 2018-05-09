#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <errno.h>

int main(int argc, char *argv[])
{
	pid_t pid; 
    int status, childpid;
	char *ficheroP;
	FILE *fp; 
	pid= fork();
	if(argc!=2)
	{
		printf("Error se ejecuta asi: <%s> <Nombre del fichero>\n", argv[0]);
	}
	else
	{
		switch(pid)	
		{
			case -1:
				perror("fork error");
    		    printf("errno value= %d\n", errno); exit(EXIT_FAILURE); 
	
			case 0:
				fp=fopen(argv[1], "a");
				if(fp==NULL)
				{
					printf("Error en adición del fichero de texto <%s>\n", ficheroP);	//Se ve si hay error en la adición del fichero creado
					exit(-1);
				}
			{ 		
				fprintf(fp,"-----\n");	//El hijo escribe
				sleep(1);
				exit(0);
			}
	
			default:
				sleep(1);	
				childpid=wait(&status);	//El padre espera al hijo para escribir
				fp=fopen(argv[1], "a");
				if(fp==NULL)
				{
	//Se ve si hay error en la adición del fichero que ha creado el proceso hijo, ya que el que escribe primero es el
					printf("Error en lectura del fichero de texto <%s>\n", ficheroP);	
					exit(-1);
				}
			{ 		
			fprintf(fp,"+++++\n");
			}	
		}
	fclose(fp);
	}
}
