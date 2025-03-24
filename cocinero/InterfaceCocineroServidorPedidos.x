/* Interface para gestión de cocineros */
const MAX_NOMBRE = 50;

struct info_cocinero {
    int id;
    int estado; /* 0=libre, 1=ocupado */
};

struct pedido_asignado {
    nodo_hamburguesa hamburguesa;
    int id_pedido;
};

program PROG_COCINEROS {
    version VER_COCINEROS_1 {
        /* Registro/autenticación */
        bool registrar_cocinero(info_cocinero) = 1;
        
        /* Notificaciones */
        bool notificar_completado(int id_pedido) = 2;
        pedido_asignado obtener_proximo_pedido(int id_cocinero) = 3;
    } = 1;
} = 0x20000002;