/*Declaracion de datos a transferir entre el cliente y el servidor*/

/*Declaracion de constantes*/
const MAXIDENTIFICACION = 20;

/*Declaracion de la estructura que permite almacenar los datos de un usuario*/
struct nodo_hamburguesa{
    int cantidadIngredientesExtra;
    int tipoHamburguesa;
    char nombreHamburguesa[MAXIDENTIFICACION];
};

/*Definicion de las operaciones que se pueden realizar*/
program autorizar_usuarios{
    version autorizar_usuarios_version{
        int generarTurno(nodo_hamburguesa objHamburguesa)=1;
    }=1;
}=0x20000001;
