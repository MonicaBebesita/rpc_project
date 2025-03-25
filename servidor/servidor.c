/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "InterfaceClienteServidorPedidos.h"
#include "InterfaceServidorPedidosServidorDisplay.h"
#include <stdbool.h>



int cantidadUsuariosFila = 0;
cocinero vectorCocineros[3];
nodo_hamburguesa filaVirtual[10];
int cocinerosEnLinea[3] = {0,0,0};


void notificar_cocineros_1();

int consultarNumeroCocineroDisponible();

 int * generarturno_1_svc(nodo_hamburguesa *argp, struct svc_req *rqstp);

int * seleccionaridcocinero_1_svc(int *argp, struct svc_req *rqstp);

int * terminarpedido_1_svc(int *argp, struct svc_req *rqstp);

int consultarNumeroCocineroDisponible()
{
	int posicion = -1;
	for (int i = 0; i < 3; i++)
	{
		if (vectorCocineros[i].ocupado == false)
		{
			posicion = i;
			break;
		}
	}
	return posicion;
}

void notificar_cocineros_1()
{
	CLIENT *datosConexion;
	void  *result_1;
	char ipServidor[10];
	strcpy(ipServidor,"localhost");
	notificacion  objNotificacion;

#ifndef DEBUG
//Obtener la ubicacion dle servidor display
	datosConexion = clnt_create (ipServidor, notificar_cocineros, notificar_cocineros_version, "udp");
	if (datosConexion == NULL) {
		clnt_pcreateerror (ipServidor);
		exit (1);
	}
#endif  /* DEBUG */
	for(int i =0; i<3; i++){
		objNotificacion.cocineros[i].noCocinero=vectorCocineros[i].noCocinero;
		objNotificacion.cocineros[i].ocupado=vectorCocineros[i].ocupado;
		objNotificacion.cocineros[i].objHamburguesaAPreparar.cantidadIngredientesExtra=vectorCocineros[i].objHamburguesaAPreparar.cantidadIngredientesExtra;
		strcpy(objNotificacion.cocineros[i].objHamburguesaAPreparar.nombreHamburguesa,
		vectorCocineros[i].objHamburguesaAPreparar.nombreHamburguesa);
		objNotificacion.cocineros[i].objHamburguesaAPreparar.tipoHamburguesa=vectorCocineros[i].objHamburguesaAPreparar.tipoHamburguesa;
	}
	objNotificacion.cantidadUsuariosFilaVirtual=cantidadUsuariosFila;
	//enviar la notificacion
	result_1 = enviarnotificacion_1(&objNotificacion, datosConexion);
	if (result_1 == (void *) NULL) {
		clnt_perror (datosConexion, "call failed");
	}
#ifndef DEBUG
//eliminar recursos utilizados en la conexion
	clnt_destroy (datosConexion);
#endif   /* DEBUG */
}

int *generarturno_1_svc(nodo_hamburguesa *argp, struct svc_req *rqstp)
{
	static int result;
	int posicion = consultarNumeroCocineroDisponible();
	printf("\n");
	printf("\n Hamburguesa a preparar");
	printf("\n Nombre hamburguesa: %s", (*argp).nombreHamburguesa);
	printf("\n Tipo hamburguesa: %d", (*argp).tipoHamburguesa);
	printf("\n Cantidad de ingredientes extra: %d", (*argp).cantidadIngredientesExtra);
	if (posicion == -1)
	{
		printf("\n Los cocineros se encuentran ocupados");
		filaVirtual[cantidadUsuariosFila] = *argp;
		cantidadUsuariosFila++;
		printf("\n La hamburguesa se agrego a la fila virtual");
	}
	else
	{
		printf("\n El cocinero en la posicion %d esta libre y se asignara a la  hamburguesa con nombre %s",(posicion+1),(*argp).nombreHamburguesa);
		vectorCocineros[posicion].ocupado=true;
		vectorCocineros[posicion].objHamburguesaAPreparar=*argp;
	}
	result = cantidadUsuariosFila;
	notificar_cocineros_1();
	printf("\n");
	return &result;
}
// Cocinero cosas

int * seleccionaridcocinero_1_svc(int *argp, struct svc_req *rqstp) {
	static int  result;
	int indexCoc= (*argp)-1;
	printf("> Validando cocinero %d\n", indexCoc+1);

	//  Validar codigo de cocinero
	if(indexCoc<0 || indexCoc>3){
		result = 0;
		return &result;
	}

	// Validar que ya no este conectado

	if( cocinerosEnLinea[indexCoc] != 0){
		result = 0;
		return &result;
	}
	
	//Guardar su conexion

	cocinerosEnLinea[indexCoc] = 1;

	//Notificar la conexion con 1
	result = 1;

	return &result;
}

int * terminarpedido_1_svc(int *argp, struct svc_req *rqstp) {
	static int  result;
	int indexCoc = (*argp)-1;
	printf("> Terminando pedido del cocinero %d\n", indexCoc+1);


	//Validar si el cocinero tiene un pedido
	if(!vectorCocineros[indexCoc].ocupado){
		result = 0;
		return &result;
	}
	
	//Se le asigna otro pedido al cocinero 

	//validar si no hay fila
	if(cantidadUsuariosFila==0){
		vectorCocineros[indexCoc].ocupado=false;
		notificar_cocineros_1();
		result = 0;
		return &result;
	}
	//pre. Hay usuarios en la fila
	
	//Asignamos al cocinero el siguiente pedido
	vectorCocineros[indexCoc].objHamburguesaAPreparar=filaVirtual[0];
	//Movemos la fila
	for(int i=0;i<cantidadUsuariosFila-1;i++){
		filaVirtual[i]=filaVirtual[i+1];
	}
	cantidadUsuariosFila--;

	//Notificacion a los cocineros
	notificar_cocineros_1();
	result = 1;
	return &result;
}