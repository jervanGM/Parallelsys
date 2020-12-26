#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
# include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{	
	int pd[2];
	char s[100];
	char buf[100];
	int nbyte;
	int num;
	pd[0]=atoi(argv[1]);
	pd[1]=atoi(argv[2]);
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
			num=atoi(s);
			num*=2;
			sprintf(buf,"%d",num);
			printf("%s",buf);
			
	}
	sleep(4);
	if(write(pd[1],buf, sizeof(buf)) ==-1) perror("write");
	
	exit(EXIT_SUCCESS);
	
}
