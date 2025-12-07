#include <string.h>
#include <stdio.h>
#include "funcion.h"

int main(int argc, char const *argv[])
{
    Libro libro[10];
    int opc1=0;
    int cont=0;
   do
   {
    opc1=menu();
        
    switch (opc1)
    {
    case 1:
        crearLibro(libro, &cont);
        break;
    case 2:
        // nose si toca poner stock
        break;
    case 3:
        tablaLibros(libro, &cont);
        break;
    case 4:
        tablaEstado(libro, cont);
        break;
    case 5:
        encontrarLibro(libro, &cont);
        break;
    case 6:
        prestarLibro(libro, &cont);
        break;
    case 7:
        devolverLibros(libro, cont);
        break;
    case 8:
        eliminarLibro(libro, &cont);
        break;
    case 9:
        printf("Saliendo del programa.....\n");
        break;


    default:
    printf("Opcion no valida.\n");
        break;
    }
   } while (opc1!=9);       
    return 0;
}
