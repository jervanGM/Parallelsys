#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
# include <unistd.h>


int main(int argc, char *argv[])
{	
	int pd[2];
	char s[100];
	int nbyte;
	pd[0]=atoi(argv[1]);
	pd[1]=atoi(argv[2]);
	printf("\n%d\n",pd[0]);
	printf("%d",pd[1]);
	sleep(1);
	switch(nbyte=read(pd[0],s,sizeof(s)))
	{
		case -1: 
			perror("read");
			break;
		case 0:
			perror("EOF");
			break;
		default:
			printf("Leídos : %d bytes : %s \n",nbyte,s);
			
	}
	sleep(4);
	if(write(pd[1],"Hola, soy hijo respondiendo", 28) ==-1) perror("write");
	
	exit(EXIT_SUCCESS);
	
}
