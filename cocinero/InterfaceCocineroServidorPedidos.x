/* InterfaceCocineroServidorPedidos.x */
const MAX_ID = 20;

program COCINEROPEDIDOS {
    version COCINEROPEDIDOS_VERS {
        int registrar_cocinero(int) = 1;
        bool notificar_pedido_terminado(int) = 2;
    } = 1;
} = 0x20000003;