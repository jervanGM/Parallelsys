/* Creación de colas de mensajes, lectura de datos */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
/* Definición de la clave de la cola */
#define M_1 1
/* Prototipos */
int crearcola(int key);
/* Función principal */
int main(void)
{
	int msg1, i,res;
	struct msgbuf
	{
		long mtype;
		int num;
	} time_msg;
	/* Llamada a la función de creación de colas */
	msg1=crearcola(M_1);
	time_msg.mtype=3;
	/* Bucle para la lectura de la cola de mensajes */
	do
	{	
		/* int msgrcv(int msg, struct msgbuf * buf, int size, long type, int flag): recupera el primer
		mensaje con identificador type, de tamaño size almacenado en la cola con identificador msg,
		en el segundo campo de buf. El último parámetro sirve para controlar el nivel de ocupación de
		la cola */
		/* Lectura de datos de la cola */
		//puts("hola");
		if(msgrcv(msg1,&time_msg,sizeof(time_msg.num),3,0) == -1 )
		{
			perror("msgrcv");
			exit(EXIT_FAILURE);
		}
		
		time_msg.num*=2;
		printf("Calculando: %d\n", time_msg.num);
		time_msg.mtype=3;
		if(msgsnd(msg1,&time_msg,sizeof(time_msg.num),0) == -1)
		{
			perror("msgsnd");
			exit(EXIT_FAILURE);
		}
	}while(time_msg.num!=0);

	if (msgctl(msg1,IPC_RMID,(struct msqid_ds *)0) == -1) 
	{
		perror("msgctl");
	}
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
