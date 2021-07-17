#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>

#define DIRSIZE 8192

main(argc, argv)
int argc;
char *argv[];
{
	char dir[DIRSIZE];
	int sd;
	struct sockaddr_un sin;

	/*verificando un numero parametros de entrada*/
	if(argc != 2){
		fprintf(stderr,"Error,uso:%s<directorio>\n",argv[0]);
		exit(1);
	}
	/*obtencion de un socket tipo AF_LINUX (IGUAL QUE EL SERVIDOR)*/
	if((sd=socket(AF_UNIX,SOCK_STREAM,0))==-1){
		perror("socket");
		exit(1);
	}
	/*llenando los campos de la estructura de la direccion unix, mismos datos servidor*/
	strcpy(sin.sun_path,"./socket");
	sin.sun_family=AF_UNIX;
	/*CONECTANDOSE AL ARCHIVO ./socket*/
	if(connect(sd,(struct sockaddr*)&sin,sizeof(sin))==-1){
		perror("connect");
		exit(1);
	}
	/*enviar mensaje al servidor*/
	strcpy(dir,argv[1]);
	if(write(sd,dir,sizeof(dir))==-1){
		perror("write");
		exit(1);
	}
	/*esperar por la respuesta*/	
	if(read(sd,dir,sizeof(dir))==-1){
		perror("read");
		exit(1);
	}
	/*imprimir los resultados y cerrando la conexion del socket*/
	printf("%s\n",dir);
	close(sd);	
}
