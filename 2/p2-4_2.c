
/* Creación, terminación y control de procesos hijo a partir de un proceso padre */
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
/* Prototipos */
int hijo(int sleep_t, int id);
void padre(void);
/* Función principal */
int main (void)
{
	pid_t pid;
	pid_t pid2;
	int status;
	/* Creación de un proceso hijo */
	pid=fork();
	if(pid==-1){
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if(pid==0){
		exit(hijo(1,0));
	}
	else{
		pid2=fork();
		if(pid2==-1){
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if(pid2==0){
			exit(hijo(5,1));
		}
		else{
			/* pid_t waitpid(pid_t pid, int *status, int options): provoca una espera del
			proceso padre hasta que el proceso hijo con identificador pid finalice. Si pid es
			–1 realiza una espera asociada a la finalización de todos los procesos hijos, es
			decir, se comporta como wait(). La información del estado del proceso hijo se
			almacena en status. El tercer argumento es una máscara de bits (deberá valer
			0 “OR”). La función devuelve el identificador pid del proceso cuyo estado está
			proporcionando. */
			padre();
			/* pid_t waitpid(pid_t pid, int *status, int options): provoca una espera del
			proceso padre hasta que el proceso hijo con identificador pid finalice. Si pid es
			–1 realiza una espera asociada a la finalización de todos los procesos hijos, es
			decir, se comporta como wait(). La información del estado del proceso hijo se
			almacena en status. El tercer argumento es una máscara de bits (deberá valer
			0 “OR”). La función devuelve el identificador pid del proceso cuyo estado está
			proporcionando. */
			waitpid(pid , &status, 0);
			waitpid(pid2, &status, 0);
			/* pid_t wait(int *status): provoca una espera del proceso padre hasta que
			cualquier proceso hijo finalice. La información del estado del proceso hijo se
			almacena en status.*/
			//wait(&status);			
			printf("Ya ha terminado los procesos hijos\n");
		}
	
			
	}
	
	exit(EXIT_SUCCESS);
}
/* Fin función principal */
/* Declaración de las dos funciones que permiten identificar ambos procesos */
int hijo(int sleep_t, int id)
{
	sleep(sleep_t);
	printf("Hola soy el proceso hijo %d\n",id);
	return 1;
}

void padre(void)
{
	printf("Hola soy el proceso padre\n");
}
