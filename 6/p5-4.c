#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "shmz.h" /* Fichero que contiene la información de la estructura de datos a
compartir */
/* Función principal */
int main(void)
{
	int shmid,semid;
	memo *zona;
	struct sembuf operacion;
	pid_t pid;
	char *nombre="p5-5";
	char *nombre2="p5-5b";
	char *av[2];
	/* Creación de la zona de memoria compartida */
	if((semid = semget(LLAVE,2,IPC_CREAT|0600)) == -1)
	{
		perror("semget");
		exit(EXIT_FAILURE);
	}
	if((shmid = shmget(CLAVE_SHM, sizeof(memo), IPC_CREAT|0666)) == -1)
	{
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	/* Obtención del puntero a la estructura de datos compartida */
	zona = (memo *)shmat(shmid,0,0);
	/* Escribimos en la zona de memoria común */
	zona->tarea = 0;
	/* Creación de un proceso hijo */
	semctl(semid,SEM_A,SETVAL,0);
	switch(pid=fork())
	{
		case (pid_t) -1:
			(void) perror("fork");
			exit(EXIT_FAILURE);
		case (pid_t) 0:
			/* Ejecutamos el proceso2 */
			av[0]=nombre;
			av[1]=(char *)0; /* Puntero a un null */
			if(execve(nombre,av,0) == -1)
			{
				(void) perror("execlp");
				exit(EXIT_FAILURE);
			}
	}
	switch(pid=fork())
	{
		case (pid_t) -1:
			(void) perror("fork");
			exit(EXIT_FAILURE);
		case (pid_t) 0:
			/* Ejecutamos el proceso2 */
			av[0]=nombre2;
			av[1]=(char *)0; /* Puntero a un null */
			if(execve(nombre2,av,0) == -1)
			{
				(void) perror("execlp");
				exit(EXIT_FAILURE);
			}
	}
	operacion.sem_flg = SEM_UNDO;
	operacion.sem_num = SEM_A; //SEM_A o SEM_B
	operacion.sem_op = 1; // +1 o -1
	semop(semid,&operacion,1);
	printf("Escribe un numero: ");
	fflush(stdin);
	scanf("%d",&zona->tarea);
	operacion.sem_num = SEM_A; //SEM_A o SEM_B
	operacion.sem_op = -1; // +1 o -1
	semop(semid,&operacion,1);
	
	sleep(1);
	printf("El resultado es: %d\n", zona->tarea);
	wait(NULL);
	/* Borrado de la zona de memoria compartida */
	shmctl(shmid, IPC_RMID,0);
	exit(EXIT_SUCCESS);
}
/* Fin función principal */
