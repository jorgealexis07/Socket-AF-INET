#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>

#define DIRSIZE 8192

main()
{
	char dir[DIRSIZE];
	INT sd, sd_actual;
	struct sockaddr_un sin;
	
	/*OBTENCION DE UN SOCKET tipo AF_UNIX*/
	((sd=socket(AF_UNIX,SOCK_STREAM,0))==-1){
		perror("socket");
		exit(1);
	}
	/* llenando los campos de la estructura de direccion unix */
	strcpy(sin.sun_path,"./socket");
	sin.sun_family=AF_UNIX;	

	/*asociando el socket al archivo ./socket*/
	if(bind(sd,(struc sockaddr*)&sin,sizeof(sin))==-1){
		perror("bind");
		exit(1);
	}
	/*ponerse a ecuchar a traves del socket*/
	if(listen(sd,5)==-1){
		perror("listen");
		exit(1);
	}
	/*ESPERANDO QUE UN CLIENTE solicite un servicio*/
	if(read(sd_actual=accept(sd,0,0))==-1{
		perror("accept");
		exit(1);
	}
	/*tomar un mensaje del cliente*/
	if(read(sd_actual,dir,sizeof(dir))==-1){
		perror("read");
		exit(1);
	}
	/*realizando servicio solicitado: leyendo el directorio*/
	lee_dir(dir);
	/*enviando la respuesta del servicio*/
	if(write(sd_actual,dir,sizeof(dir))==-1){
		perror("write");
		exit(1);
	}
	/*cerrar los dos socket*/
	close(sd_actual);
	/*no olvidar realizar un poco de limpieza*/
		unlink("./socket");
}		


}