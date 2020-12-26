/* Comunicación de procesos mediante pipes */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
# include <unistd.h>
/* Función principal */
int main(void)
{
	int pfd[2];
	char fdstr[10];
	int status;
	/* Creación del pipe */
	if(pipe(pfd) == -1)
		perror("pipe");
	/* Creación de un proceso hijo */
	switch(fork()){
		case -1:
			perror("fork");
			exit(EXIT_FAILURE);
		case 0:
			/* Cierre del descriptor de escritura del pipe en el proceso hijo */
			if(close(pfd[1]) == -1)
				perror("close");
			/* int sprintf(char *buffer, const char *formato,...): su funcionamiento es
			idéntico a la función printf, salvo que la salida generada se pone en el array
			apuntado por buffer. El valor devuelto es igual al número de caracteres puesto
			en el array */

			sprintf(fdstr,"%d",pfd[0]);

			/* int execlp(const char *filename, const char *argv[0],..): permite la ejecución
			del programa filename como un nuevo proceso imagen. La lista de argumentos
			es:
			const char *filename: contiene el nombre del programa
			ejecutable.
			const char argv[]: el primer elemento de array es el
			nombre de programa, y el último un puntero NULL. */
			if (execlp("./p3-3","p3-3", fdstr, NULL) == -1) 
			{
				perror("execlp");
				exit(EXIT_FAILURE);
			}
	}
	/* Cierre del descriptor de lectura en el proceso padre */
	if(close(pfd[0]) ==- 1)
		perror("close");
	/* El proceso padre escribe en el pipe */
	if(write(pfd[1],"hola proceso 3",15) == -1)
		perror("write");
	/* El proceso padre espera la finalización del proceso hijo */
	wait(&status);
	exit(EXIT_SUCCESS);
}
/* Fin función principal */