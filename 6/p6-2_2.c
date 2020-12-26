/* Creación y empleo de semáforos en la sincronización de procesos,
este programa es el proceso2 lanzado desde el programa1 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include "shmz.h"

/* Función principal */
int main(void)
{
	memo *zona;
	int semid,shmid;
	struct sembuf operacion;
	/* Variable empleada en el bucle while */
	/* Obtención del identificador que agrupa los semáforos */
	if((shmid = shmget(CLAVE_SHM, sizeof(memo), IPC_CREAT|0666)) == -1)
	{
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	/* Obtención del puntero a la estructura de datos compartida */
	zona = (memo *)shmat(shmid,0,0);
	if((semid = semget(LLAVE,2,IPC_CREAT|0600)) == -1)
	{
		perror("semget");
		exit(EXIT_FAILURE);
	}
	/* Operaciones sobre los semáforos */
	operacion.sem_flg = SEM_UNDO;
	while(zona->tarea)
	{
		operacion.sem_num = SEM_B; //SEM_A o SEM_B
		operacion.sem_op = 1; // +1 o -1
		semop(semid,&operacion,1);
		sleep(1);
		printf("Leo el proceso ------ %d\n",zona->tarea);
		operacion.sem_num = SEM_B; //SEM_A o SEM_B
		operacion.sem_op = -1; // +1 o -1
		semop(semid,&operacion,1);
	}
}
/* Fin función principal */
