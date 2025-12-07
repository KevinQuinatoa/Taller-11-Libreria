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
        tablaLibros(libro, &cont);
        break;
    case 3:
        tablaEstado(libro, cont);
        break;
    case 4:
        encontrarLibro(libro, &cont);
        break;
    case 5:
        prestarLibro(libro, &cont);
        break;
    case 6:
        devolverLibros(libro, cont);
        break;
    case 7:
        eliminarLibro(libro, &cont);
        break;
    case 8:
        printf("Saliendo del programa.....\n");
        break;


    default:
    printf("Opcion no valida.\n");
        break;
    }
   } while (opc1!=8);       
    return 0;
}
