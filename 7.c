#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char  *argv[])	// 1 Argc el programa, 2 el numero de procesos que queremos
{
	key_t Clave;
	int Id_Memoria;
	int *Memoria = NULL;
	int i,j, valor=0;
	int status, childpid;
	pid_t pid;
    
	//obtenemos la clave de memoria
	Clave = ftok ("/bin/ls", 33);

    if (Clave == -1)
	{

    	printf("No consigo clave para Memoria compartida\n");
    	exit(0);
	}

     //obtenemos el codigo de la memoria.
	Id_Memoria = shmget (Clave, sizeof(int)*1, 0777 | IPC_CREAT);

	if (Id_Memoria == -1)
	{
		printf("No consigo Id para Memoria compartida\n");
		exit(0);
	}

	//obtenemos un puntero a la memoria compartida
	Memoria = (int *)shmat (Id_Memoria, (char *)0, 0);

	if (Memoria == NULL)	//Si la memoria es Null no se consigue la memoria compartida
	{
		printf("No consigo Memoria compartida");
		exit (0);
	}
	*Memoria=0;
	//Cada vez que se hace el for los hijos incrementan la variable 100 veces cada uno
	for (i=0; i<atoi(argv[1]); i++)	
	  {
		pid = fork(); 
		if (pid==0)
		  {
			printf("Soy hijo %d; mi PID: %d y mi padre = %d. \n", i, getpid(), getppid());
			for(j=0; j<100; j++)
			{
				Memoria[0]=Memoria[0]+1;

			}
			shmdt ((char*)Memoria);
			exit(i);
		
   		  }
   	  }
//While de espera para los hijos
	while (childpid=wait(&status)>0){
 
   		 if (WIFEXITED(status)) 
		{
           printf("child %d exited, status=%d\n",childpid, WEXITSTATUS(status));
           } else if (WIFSIGNALED(status)) {
           printf("child %d killed (signal %d)\n", childpid, WTERMSIG(status));
           } else if (WIFSTOPPED(status)) {
           printf("child %d stopped (signal %d)\n", childpid, WSTOPSIG(status));
        } 

	}


	printf("El valor total del contador es: %d\n", Memoria[0]);
	//Se libera la memoria 
	shmdt ((char *)Memoria);
	shmctl (Id_Memoria, IPC_RMID, (struct shmid_ds *)NULL);
	return 0;	//Retornamos el valor 0 para acabar el programa satifactoriamente
}

