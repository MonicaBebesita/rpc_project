program CocineroPedidos {
    version CocineroPedidos_version {
        /* Operación para que el cocinero se registre */
        int registrar_cocinero(int id_cocinero) = 1;

        /* Operación para notificar que terminó un pedido */
        bool notificar_pedido_terminado(int id_cocinero) = 2;
    } = 1;
} = 0x20000003; 