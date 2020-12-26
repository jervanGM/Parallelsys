#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])//no hay puntero dinamico
{
	int lec, i, iteraciones;
	char leer[100];
	lec = atoi(argv[1]);//0 es el nombre del archivo
	iteraciones = atoi(argv[2]);//1 es el valor de la pipe
	
	for(i=0;i<iteraciones;i++)
	{
	 	read(lec,leer,sizeof(leer)); //el sizeof no debe ser char, debe ser el tamaño de leer
	 	printf("Leo del pipe el numero: %s\n", leer);
	}

	//en hijo no hace falta cerrar la pipe, se hace dsde padre
	/*if(close(lec) == -1)
		perror("close");*/

	exit(0);
}
