#include "InterfaceCocineroServidorPedidos.h"
#include <stdbool.h>
#include <string.h>

// Variables globales (compartidas con el servidor principal)
extern int cantidadUsuariosFila;
extern cocinero vectorCocineros[3];
extern nodo_hamburguesa filaVirtual[10];

/*
 * Función: registrar_cocinero_1_svc
 * Descripción: Registra un cocinero en el sistema
 */
bool_t *
registrar_cocinero_1_svc(int *id_cocinero, struct svc_req *rqstp)
{
    static bool_t result;
    result = FALSE;
    
    printf("\nSolicitud de registro para cocinero %d\n", *id_cocinero);

    // Validar ID del cocinero (1-3)
    if(*id_cocinero < 1 || *id_cocinero > 3) {
        printf("Error: ID de cocinero inválido\n");
        return &result;
    }

    // Verificar si el cocinero ya está registrado
    if(vectorCocineros[*id_cocinero-1].ocupado) {
        printf("Error: Cocinero %d ya está registrado\n", *id_cocinero);
        return &result;
    }

    // Registrar el cocinero
    vectorCocineros[*id_cocinero-1].noCocinero = *id_cocinero;
    vectorCocineros[*id_cocinero-1].ocupado = false;
    memset(&vectorCocineros[*id_cocinero-1].objHamburguesaAPreparar, 0, sizeof(nodo_hamburguesa));
    
    printf("Cocinero %d registrado exitosamente\n", *id_cocinero);
    result = TRUE;
    
    // Notificar al display
    notificar_cocineros_1();
    
    return &result;
}

/*
 * Función: notificar_pedido_terminado_1_svc
 * Descripción: Maneja la notificación cuando un cocinero completa un pedido
 */
bool_t *
notificar_pedido_terminado_1_svc(int *id_cocinero, struct svc_req *rqstp)
{
    static bool_t result;
    result = FALSE;
    
    printf("\nCocinero %d notifica pedido terminado\n", *id_cocinero);

    // Validar ID del cocinero
    if(*id_cocinero < 1 || *id_cocinero > 3) {
        printf("Error: ID de cocinero inválido\n");
        return &result;
    }

    // Verificar que el cocinero tenga un pedido asignado
    if(!vectorCocineros[*id_cocinero-1].ocupado) {
        printf("Error: Cocinero %d no tiene pedidos asignados\n", *id_cocinero);
        return &result;
    }

    // Liberar al cocinero
    vectorCocineros[*id_cocinero-1].ocupado = false;
    memset(&vectorCocineros[*id_cocinero-1].objHamburguesaAPreparar, 0, sizeof(nodo_hamburguesa));
    
    // Asignar nuevo pedido si hay en cola
    if(cantidadUsuariosFila > 0) {
        printf("Asignando nuevo pedido de la fila virtual\n");
        vectorCocineros[*id_cocinero-1].objHamburguesaAPreparar = filaVirtual[0];
        vectorCocineros[*id_cocinero-1].ocupado = true;
        
        // Mover la fila
        for(int i = 0; i < cantidadUsuariosFila-1; i++) {
            filaVirtual[i] = filaVirtual[i+1];
        }
        cantidadUsuariosFila--;
    }
    
    printf("Cocinero %d liberado\n", *id_cocinero);
    result = TRUE;
    
    // Notificar al display
    notificar_cocineros_1();
    
    return &result;
}

/*
 * Función: consultar_pedido_1_svc
 * Descripción: Permite a los cocineros consultar si tienen pedidos pendientes
 */
pedido_asignado *
consultar_pedido_1_svc(int *id_cocinero, struct svc_req *rqstp)
{
    static pedido_asignado result;
    memset(&result, 0, sizeof(result));
    
    printf("\nCocinero %d consulta por pedido asignado\n", *id_cocinero);

    // Validar ID del cocinero
    if(*id_cocinero < 1 || *id_cocinero > 3) {
        printf("Error: ID de cocinero inválido\n");
        return &result;
    }

    // Verificar si el cocinero tiene un pedido asignado
    if(vectorCocineros[*id_cocinero-1].ocupado) {
        result.id_cocinero = *id_cocinero;
        result.hamburguesa = vectorCocineros[*id_cocinero-1].objHamburguesaAPreparar;
        printf("Pedido encontrado para cocinero %d\n", *id_cocinero);
    } else {
        printf("No hay pedidos asignados para cocinero %d\n", *id_cocinero);
    }
    
    return &result;
}