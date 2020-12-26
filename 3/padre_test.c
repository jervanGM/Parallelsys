#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
# include <unistd.h>

int main(void)
{
	int pd[2],pd2[2];
	char fc[10],fc2[10];
	int status;
	int nbyte;
	char s[100];
	if(pipe(pd) ==-1 || pipe(pd2)==-1) perror("pipe");
	switch(fork())
	{
		case -1 : 
			perror("fork");
			exit(EXIT_FAILURE);
		case 0 : 
			if(close(pd[1])==-1 || close(pd2[0])==-1) perror("close");
			sprintf(fc,"%d",pd[0]);
			sprintf(fc2,"%d",pd2[1]);
			if(execlp("./hijop","hijop",fc,fc2,NULL) ==-1)
			{
				perror("execlp");
				exit(EXIT_FAILURE);
			}
		default : 
			if(close(pd[0])==-1 || close(pd2[1])==-1) perror("close");
			
			if(write(pd[1],"Hola, soy padre desde hijo", 27) ==-1)
			{
				perror("write");
			}
			switch(nbyte=read(pd2[0],s,sizeof(s)))
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
			wait(&status);
			if(close(pd[1])==-1 || close(pd2[0])==1) perror("close");
			exit(EXIT_SUCCESS);
	}
}
