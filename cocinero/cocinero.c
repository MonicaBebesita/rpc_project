#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "InterfaceCocineroServidor.h"

void mostrar_menu() {
    printf("\n=== MENÚ COCINERO ===\n");
    printf("1. Registrar cocinero\n");
    printf("2. Ver pedido asignado\n");
    printf("3. Marcar pedido como terminado\n");
    printf("4. Salir\n");
    printf("Seleccione: ");
}

void mostrar_pedido(nodo_hamburguesa *pedido) {
    if (pedido == NULL) {
        printf("No hay pedido asignado\n");
        return;
    }
    
    const char* tipos[] = {"", "Pequeña", "Mediana", "Grande"};
    printf("\n--- Pedido Actual ---\n");
    printf("Nombre: %s\n", pedido->nombreHamburguesa);
    printf("Tipo: %s\n", tipos[pedido->tipoHamburguesa]);
    printf("Ingredientes extra: %d\n", pedido->cantidadIngredientesExtra);
    printf("---------------------\n");
}

int main(int argc, char *argv[]) {
    CLIENT *clnt;
    int *result;
    int id_cocinero = 0;
    char *host;

    if (argc != 2) {
        fprintf(stderr, "Uso: %s servidor_pedidos\n", argv[0]);
        exit(1);
    }

    host = argv[1];
    clnt = clnt_create(host, COCINERO_PROG, COCINERO_VERS, "udp");
    if (clnt == NULL) {
        clnt_pcreateerror(host);
        exit(1);
    }

    /* Registro inicial del cocinero */
    while (id_cocinero < 1 || id_cocinero > 3) {
        printf("\nIngrese su número de cocinero (1-3): ");
        scanf("%d", &id_cocinero);
        
        result = registrar_cocinero_1(&id_cocinero, clnt);
        if (result == NULL || *result != 0) {
            fprintf(stderr, "Error: Número de cocinero no disponible\n");
            id_cocinero = 0;
        } else {
            printf("Registrado como cocinero %d\n", id_cocinero);
        }
    }

    /* Bucle principal */
    int opcion;
    do {
        mostrar_menu();
        scanf("%d", &opcion);
        
        switch(opcion) {
            case 1: {
                /* Ya registrado */
                printf("Ya estás registrado como cocinero %d\n", id_cocinero);
                break;
            }
            
            case 2: {
                nodo_hamburguesa *pedido = obtener_pedido_1(&id_cocinero, clnt);
                mostrar_pedido(pedido);
                break;
            }
            
            case 3: {
                result = notificar_terminado_1(&id_cocinero, clnt);
                if (result == NULL || *result != 0) {
                    fprintf(stderr, "Error: No hay pedido para marcar como terminado\n");
                } else {
                    printf("Pedido marcado como terminado correctamente\n");
                }
                break;
            }
        }
    } while(opcion != 4);

    clnt_destroy(clnt);
    return 0;
}