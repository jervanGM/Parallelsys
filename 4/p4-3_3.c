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
	int msg1, i;
	struct msgbuf
	{
		long mtype;
		char mtext [1];
		char ntext[50];
	} time_msg;
	/* Llamada a la función de creación de colas */
	msg1=crearcola(M_1);
	/* Bucle para la lectura de la cola de mensajes */
	for(i=0;i<10;i++)
	{
		/* int msgrcv(int msg, struct msgbuf * buf, int size, long type, int flag): recupera el primer
		mensaje con identificador type, de tamaño size almacenado en la cola con identificador msg,
		en el segundo campo de buf. El último parámetro sirve para controlar el nivel de ocupación de
		la cola */
		/* Lectura de datos de la cola */
		
		if(msgrcv(msg1,&time_msg,sizeof(time_msg.mtext[0]),3,0) == -1 || msgrcv(msg1,&time_msg,sizeof(time_msg.ntext),3,0) == -1)
		{
			perror("msgrcv");
			exit(EXIT_FAILURE);
		}
		printf("El tiempo en segundos es : %d, y el mensaje es %s\n",time_msg.mtext[0],time_msg.ntext);
	}

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
