#include <stdio.h>
#include <stdlib.h>//es una cabecera, no archivo.c
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int pid, estado, i=0;
	int tuberia[2]; //habia 1 campo en vez de 2
	char lectura[100], numero[100];
	char *arg[4];
	if(pipe(tuberia)==-1) perror("pipe");//falta manejar el error

	fflush(stdout);
	printf("Cuantas iteraciones?\n");
	char iteraciones[100];
	scanf("%s", iteraciones);//debe ser leido por un entero referenciado con &
	i=atoi(iteraciones);//debe haber un sprintf puesto que interacciones es una cadena de char

	pid = fork();

	if(pid < 0)//>0 es incorrecto, devuelve un -1
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	else if(pid == 0) //hay un if y debe ser un else if, además de ser condición por lo que pid=0 es incorrecto
	{
		if(close(tuberia[1]) == -1)// es de lectura, por lo que no se puede cerrar el campo 0 correspondiente a lectura
			perror("close");
		sprintf(lectura, "%d", tuberia[0]);
		arg[0] = "hijo";
		arg[1] = lectura;
		arg[2] = iteraciones;
		arg[3] = NULL;
		if(execv("./hijo",arg)==-1)
		{
			perror("exceve");
			exit(EXIT_FAILURE);
		}
			
		//null es el último argumento de arg, por lo que ya se incluye. Manejo de error
	}
	else
	{

		if(close(tuberia[0]) == -1)//escritura es 0, por lo que no debe cerrarse el campo 1(escritura)
			perror("close");

		do{
				sprintf(numero, "%d", i);
				printf("Escribo en el pipe el numero %d\n",i);
				write(tuberia[1], numero,2);//el campo de escritura es 1
				i--;
				sleep(1);
		}while(i>0);//la condición empieza en 10 y termina en 1, por lo que no debe ser <0

		
	}
	wait(&estado);//en el caso del wait, debe hacer referencia a la variable con &
	if(close(tuberia[1]) == -1)//en este caso se cierra el campo del escritura 1 en vez de lectura 0, debido a que ya ha sido usado.
		perror("close");

	exit(0);
}
