const MAXIDENTIFICACION2 = 20;
struct nodo_hamburguesaActualizado{
int cantidadIngredientesExtra;
int tipoHamburguesa;
char nombreHamburguesa[MAXIDENTIFICACION2];
};
struct cocineroActualizado {
int noCocinero;
bool ocupado;
nodo_hamburguesaActualizado objHamburguesaAPreparar;
};
struct notificacion{
cocineroActualizado cocineros[3];
int cantidadUsuariosFilaVirtual;
};
/*Definicion de las operaciones que se pueden realizar*/
program notificar_cocineros{
version notificar_cocineros_version{
void enviarNotificacion(notificacion objNotificacion)=1;
}=1;
}=0x20000002;