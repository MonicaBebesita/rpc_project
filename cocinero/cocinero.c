#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tirpc/rpc/rpc.h>
#include "InterfaceCocineroServidorPedidos.h"  // Header generado por rpcgen

#define SERVIDOR_PEDIDOS "localhost"

void mostrar_menu_cocinero();

int main(int argc, char *argv[]) {
    CLIENT *cliente_rpc;
    int *resultado_registro;
    bool_t *resultado_terminado;  // Cambiado a bool_t para compatibilidad con RPC
    int id_cocinero;
    char opcion;

    // Crear cliente RPC usando las constantes generadas
    cliente_rpc = clnt_create(
        SERVIDOR_PEDIDOS, 
        COCINEROPEDIDOS,  // Nombre generado automáticamente 
        COCINEROPEDIDOS_VERS,   // Versión generada automáticamente
        "tcp"
    );

    if (cliente_rpc == NULL) {
        clnt_pcreateerror(SERVIDOR_PEDIDOS);
        exit(1);
    }

    // Paso 1: Registro del cocinero
    printf("\n=== REGISTRO DE COCINERO ===\n");
    while (1) {
        printf("Ingrese su ID (1, 2 o 3): ");
        scanf("%d", &id_cocinero);
        getchar();  // Limpiar el buffer

        resultado_registro = registrar_cocinero_1(&id_cocinero, cliente_rpc);
        
        if (resultado_registro == NULL) {
            printf("\nError: No se pudo contactar al servidor\n");
            clnt_destroy(cliente_rpc);
            exit(1);
        }
        
        if (*resultado_registro == 1) {
            printf("\nRegistrado como Cocinero %d\n", id_cocinero);
            break;
        } else {
            printf("\nError: ID no válido o ya en uso. Intente nuevamente.\n");
        }
    }

    // Paso 2: Menú principal del cocinero
    while (1) {
        mostrar_menu_cocinero();
        opcion = getchar();
        getchar();  // Limpiar el buffer

        switch (opcion) {
            case '1':
                resultado_terminado = notificar_pedido_terminado_1(&id_cocinero, cliente_rpc);
                
                if (resultado_terminado == NULL) {
                    printf("\nError: No se pudo contactar al servidor\n");
                } else if (*resultado_terminado) {
                    printf("\nPedido marcado como terminado. Esperando nuevo pedido...\n");
                } else {
                    printf("\nError: No tiene pedidos asignados actualmente.\n");
                }
                break;
                
            case '2':
                printf("\nSaliendo del sistema...\n");
                clnt_destroy(cliente_rpc);
                exit(0);
                
            default:
                printf("\nOpción no válida. Intente nuevamente.\n");
        }
    }

    return 0;
}

void mostrar_menu_cocinero() {
    printf("\n=== MENÚ COCINERO ===\n");
    printf("1. Notificar pedido terminado\n");
    printf("2. Salir\n");
    printf("======================\n");
    printf("Seleccione una opción: ");
}