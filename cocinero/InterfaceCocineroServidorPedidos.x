/* InterfaceCocineroServidor.x */
const int MAX_IDENTIFICACION = 20;

/* Reutilizando las mismas estructuras definidas en InterfaceClienteServidorPedidos.h */
struct nodo_hamburguesa {
    int cantidadIngredientesExtra;
    int tipoHamburguesa;  /* 1:Pequeña, 2:Mediana, 3:Grande */
    char nombreHamburguesa[MAX_IDENTIFICACION];
};

struct estado_cocinero {
    int noCocinero;       /* 1, 2 o 3 */
    bool ocupado;
    nodo_hamburguesa objHamburguesaAPreparar;
};

program COCINERO_PROG {
    version COCINERO_VERS {
        /* Registra un cocinero en el sistema */
        int REGISTRAR_COCINERO(int) = 1;
        
        /* Obtiene el estado actual del cocinero */
        estado_cocinero CONSULTAR_ESTADO(int) = 2;
        
        /* Notifica que ha terminado un pedido */
        int NOTIFICAR_TERMINADO(int) = 3;
        
        /* Obtiene un pedido asignado (si hay) */
        nodo_hamburguesa OBTENER_PEDIDO(int) = 4;
    } = 1;
} = 0x30000001;