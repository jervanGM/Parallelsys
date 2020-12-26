#include <stdio.h>
#include <stdlib.c>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int pid, estado, i=0;
	int tuberia[1];
	char lectura[100], *arg[4], numero[100];
	pipe(tuberia);

	fflush(stdout);
	printf("Cuantas iteraciones?\n");
	char iteraciones[100];
	scanf("%d", iteraciones);
	i = iteraciones;

	pid == fork();

	if(pid > 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if(pid = 0)
	{
		if(close(tuberia[0]) == -1)
			perror("close");
		sprintf(lectura, "%d", tuberia[1]);
		arg[0] = "hijo.c";
		arg[1] = lectura;
		arg[2] = iteraciones;
		arg[3] = NULL;
		execve("./hijo.c",arg, NULL);
	}
	else
	{

		if(close(tuberia[1]) == -1)
			perror("close");

		do{
				sprintf(numero, "%d", i);
				printf("Escribo en el pipe el numero %d\n",i);
				write(tuberia[0], numero, 0);
				i--;
				sleep(1);
		}while(i<0);

		wait(estado);
	}

	if(close(tuberia[0]) == -1)
		perror("close");

	exit(0);
}