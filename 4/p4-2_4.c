/* Creación de colas de mensajes, envío de datos */
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
# include <sys/wait.h>
/* Definición de la clave de la cola */
#define M_1 1
/* Prototipos */
int crearcola(int key);
/* Función principal */
int main(void)
{
	int msg1, i,status;
	char* args[]={"p4-3_4",NULL};
	/*struct msgbuf time_msg;
	struct msgbuf presenta dos campos:
	long mtype, permite definir al usuario una etiqueta asociada al mensaje.
	char mtext[], texto del mensaje que se envía. */
	struct msgbuf
	{
		long mtype;
		int num;
	} time_msg;
	/* Llamada a la función de creación de colas */
	msg1=crearcola(M_1);
	/* Inicialización de los campos de la estructura */
	time_msg.mtype=3;
	switch(fork())
	{
		case -1: 
			perror("fork");
			exit(EXIT_FAILURE);
		case 0 :
			execv("./p4-3_4",args);
		default:
			do
			{
				/* unsigned int sleep(unsigned int seconds): provoca una espera en segundos, en función del
				valor del parámetro */
				sleep(1);
				printf("Numero a multiplicar:");
			
				scanf("%d",&time_msg.num);
				if(msgsnd(msg1,&time_msg,sizeof(time_msg.num),0) == -1)
				{
					perror("msgsnd");
					exit(EXIT_FAILURE);
				}
				if(msgrcv(msg1,&time_msg,sizeof(time_msg.num),3,0) == -1)
				{
					perror("msgrcv");
					exit(EXIT_FAILURE);
				}
				printf("Resutado : %d \n",time_msg.num);
				
			}while(time_msg.num!=0);
			
	}
	wait(&status);
}
/* Fin función principal */
/* Función que proporciona el identificador de la cola de mensaje */
int crearcola(int key)
{
	int msgqid;
	/* int msgget(int ident, int flag): proporciona un identificador para la cola de clave ident, con
	permisos flag (máscara de bits) */
	switch(msgqid = msgget(key, IPC_CREAT|0666))
	{
		/* IPC_CREAT, instrucción al sistema para crear la cola si todavía no existe */
		case -1:
			perror("msgget");
			exit(EXIT_FAILURE);
		default:
			return msgqid;
	}
} /* Fin función auxiliar */
