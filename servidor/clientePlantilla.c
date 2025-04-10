/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "InterfaceServidorPedidosServidorDisplay.h"
#include "InterfaceClienteServidorPedidos.h"

void notificar_cocineros_1(char *host)
{
     CLIENT *datosConexion;
    void  *result_1;
    char ipServidor[10];
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
        clnt_perror (clnt, "call failed");
    }
#ifndef DEBUG
    clnt_destroy (clnt);
#endif   /* DEBUG */
}


int
main (int argc, char *argv[])
{
    char *host;

    if (argc < 2) {
        printf ("usage: %s server_host\n", argv[0]);
        exit (1);
    }
    host = argv[1];
    notificar_cocineros_1 (host);
exit (0);
}