#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char argv[])
{
	int lec, i, iteraciones;
	char leer[100];
	lec = atoi(argv[0]);
	iteraciones = atoi(argv[1]);
	for(i=0;i<iteraciones;i--)
	{
	 	read(lec,leer,sizeof(char));
	 	printf("Leo del pipe el numero: %s\n", leer);
	}


	if(close(lec) == -1)
		perror("close");

	exit(0);
}