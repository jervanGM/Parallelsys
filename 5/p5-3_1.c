/* Crea una zona de memoria común, escribe en ella y la borra */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
# include <sys/wait.h>
#include "shmz.h" /* Fichero que contiene la información de la estructura de datos a
compartir */
/* Función principal */
int main(void)
{	
	pid_t pid;
	pid_t pid2;
	int status;
	int shmid;
	memo *zona;
	/* Creación de la zona de memoria compartida */
	if((shmid = shmget(CLAVE_SHM, sizeof(memo), IPC_CREAT|0666)) == -1)
	{
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	/* Obtención del puntero a la estructura de datos compartida */
	zona = (memo *)shmat(shmid,0,0);
	zona->tarea=0;
	switch(pid=fork())
	{
		case -1: 
			perror("fork");
		case 0:
			if(execlp("./p5-4_1","p5-4_1",NULL)==-1)
			{
				perror("execlp");
				exit(EXIT_FAILURE);
			}
	}
	switch(pid2=fork())
	{
		case -1: 
			perror("fork");
		case 0:
			if(execlp("./p5-4_1_2","p5-4_1_2",NULL)==-1)
			{
				perror("execlp");
				exit(EXIT_FAILURE);
			}
	}
	fflush(stdin);
	do
	{
		printf("Escribe un número: ");
		scanf("%d",&zona->valor);
	}while(zona->valor==0);
	
	zona->tarea=1;
	sleep(1);
	printf("Valor leido por padre: %d\n", zona->valor);
	waitpid(pid,&status,0);
	waitpid(pid2,&status,0);
	/* Borrado de la zona de memoria compartida */
	//shmctl(shmid, IPC_RMID,0);
}
/* Fin función principal */
