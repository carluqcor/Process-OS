#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	key_t Clave;
	int cod_Memoria;
	int *Memoria = NULL;
	int i,j, valor=0;
	int status, childpid;
	pid_t pid;

	//Obtenemos la clave de memoria    
	Clave = ftok ("/bin/ls", 33);

     if (Clave == -1)
	 {

    		printf("No consigo clave para Memoria compartida\n");
     	exit(0);
     }

     //Obtenemos el id de la memoria.
	cod_Memoria = shmget (Clave, sizeof(int)*2, 0777 | IPC_CREAT);

	
	if (cod_Memoria == -1)
	{
		printf("No consigo Id para Memoria compartida\n");
		exit(0);
	}

	//obtenemos un puntero a la memoria compartida
	Memoria = (int *)shmat (cod_Memoria, (char *)0, 0);
	if (Memoria == NULL)
	{
		printf("No consigo Memoria compartida");
		exit (0);
	}
	Memoria[0]=0;
	//los hijos incrementan la variable 100 veces cada uno
	//Memoria[0] lo usaremos como contador, Memoria[1] será el Token Ring
	for (i=0;i<atoi(argv[1]);i++)
	{
		pid = fork(); 
		if (pid==0)
		{	//Si el proceso hijo es 0
			printf("Soy hijo %d; mi PID: %d y mi padre = %d. \n", i, getpid(), getppid());	//Nos da los valores requeridos
				sleep(1);
		 		while(Memoria[1]!=i) //Mientras que sea diferente de i hace la funcion usleep por 100
				{	
					usleep(100);
				}

				for(j=0; j<100; j++)
				{
					Memoria[0]=Memoria[0]+1;
				}

			Memoria[1]=Memoria[1]+1;
			shmdt ((char *)Memoria);
			exit(i);
		}
   	 }
	while (childpid=wait(&status)>0)
	{
		if (WIFEXITED(status)) {
			printf("child %d exited, status=%d\n",childpid, WEXITSTATUS(status));
		} else if (WIFSIGNALED(status)) {
			printf("child %d killed (signal %d)\n", childpid, WTERMSIG(status));
		} else if (WIFSTOPPED(status)) {
			printf("child %d stopped (signal %d)\n", childpid, WSTOPSIG(status));
		} 

	}


	printf("El valor del contador es: %d\n", Memoria[0]);

	//liberamos la memoria
	shmdt ((char *)Memoria);
	shmctl (cod_Memoria, IPC_RMID, (struct shmid_ds *)NULL);
	return 0;
}
