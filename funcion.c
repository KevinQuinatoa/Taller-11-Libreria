#include <string.h>
#include <stdio.h>
#include "funcion.h"

int menu(){
     int opcion;

    printf("-------------- Menu ----------------\n");
    printf("1. Ingresar libros\n");
    printf("2. Agregar stock de libros\n");
    printf("3. Mostrar lista de libros\n");
    printf("4. Mostrar tabla de estados de los libros\n");
    printf("5. Busqueda de libros\n");
    printf("6. Prestar libro\n");
    printf("7. Entrega de libros\n");
    printf("8. Eliminar libros\n");
    printf("9. Salir del programa\n");
    printf("Ingrese una opcion: ");
    opcion = opcionValida(1,9);
    return opcion;
}
int opcionValida(int min, int max){
    int numero;
    while (1)
    {
        if (scanf ("%d", &numero) ==1 && numero >= min && numero<=max)
        {
            while(getchar()!='\n');
            return numero;
        }else{
            printf("Error, ingrese una opcion valida: ");
            while(getchar()!='\n');
        } 
    }
}

void eliminarSalto(char *cadena, int n) {
     fflush(stdin);
    fgets(cadena,n,stdin);
    int len = strlen(cadena) - 1;
    cadena[len]='\0';
}

void agregarStock(){

}

void crearLibro(Libro*libro, int *cont){
    if (*cont>=10)
    {

        printf("Se ingreso la cantidad maxima de libros\n");
        return;

    } else {

        int existeN, existeId;
    printf("Ingrese el ID del libro: ");
    libro[*cont].Id=opcionValida(1,9999999);
    
    existeId=buscarId(libro, *cont, libro[*cont].Id);
    // comprobar si el ID ya esta registrado
    if (existeId!=-2)
    {
        printf("el Id ya esta registrado\n");
        return;
    }

    printf("Ingrese el nombre del libro: ");
    eliminarSalto(libro[*cont].nombreL,50);
    existeN=buscarLibro(libro, *cont, libro[*cont].nombreL);
    // comprobar si el nombre del libro ya esta registrado
    if (existeN!=-1)
    {
        printf("El libro ya esta ingresado\n");
        return;
    }

    printf("Ingrese el nombre del autor del libro: ");
    eliminarSalto(libro[*cont].autor,50);
    printf("Ingrese el dia de publicacion: ");
    libro[*cont].dia=opcionValida(1,32);
    printf("Ingrese el mes de publicion: ");
    libro[*cont].mes=opcionValida(1,12);
    printf("Ingrese el anio de publicacion: ");
    libro[*cont].anio=opcionValida(1,3000);
    printf("Estado del libro:\n");
    printf("1. Disponible\n");
    printf("2. Prestado\n");
    printf("Ingrese una opcion: ");

    int opcionE = opcionValida(1, 2);
    if (opcionE == 1) {
        strcpy(libro[*cont].estado, "Disponible");
    } else {
        strcpy(libro[*cont].estado, "Prestado");
    }
    // para que eno arroje basura al poner la tabla de estados
    strcpy(libro[*cont].prestamo.nombreC, "-");
    strcpy(libro[*cont].prestamo.cedula, "-");

    printf("Ingrese el stock del libro: ");
    libro[*cont].stockI=opcionValida(1,1000); 
    (*cont)++;
    printf("Libro Registrado.........\n");
    }
    
}

void tablaLibros(Libro*libro, int *cont){
    printf("------------------------------ Tabla de libros ------------------------\n");

    printf("#\tID\tNombre\t\tAutor\t\tDia\tMes\tAnio\tEstado\tStock\n");
    for (int i = 0; i < *cont; i++)
    {
        printf("%d\t%d\t%s\t%s\t\t%d\t%d\t%d\t%s\t%d\n", i+1, libro[i].Id, 
                                                            libro[i].nombreL, 
                                                            libro[i].autor, 
                                                            libro[i].dia, 
                                                            libro[i].mes, 
                                                            libro[i].anio, 
                                                            libro[i].estado, 
                                                            libro[i].stockI);
    }
}

int buscarLibro(Libro *libro, int cont, char buscar[]){
    for (int i = 0; i < cont; i++)
    {
        if (strcmp(libro[i].nombreL, buscar)==0)
        return i;
    }
    return -1;
}

int buscarId(Libro*libro, int cont, int id){
    for (int i = 0; i < cont; i++)
    {
        if (libro[i].Id == id){
            return i;
        }
        
    }
    return -2;
}

void encontrarLibro(Libro*libro, int *cont){

    int encontrado;
    printf("Ingrese el nombre del libro que desea buscar: ");
    eliminarSalto(libro[*cont].nombreL,50);
    encontrado=buscarLibro(libro, *cont, libro[*cont].nombreL);
    if (encontrado==-1)
    {
        printf("El libro no esta registrado/n");
        return;
    } else{
        printf("El libro fue encontrado\n");
        printf("#\tID\tNombre\t\tAutor\t\tDia\tMes\tAnio\tEstado\tStock\n");
        
        printf("%d\t%s\t%s\t\t%d\t%d\t%d\t%s\t%d\n", libro[encontrado].Id, 
                                                    libro[encontrado].nombreL, 
                                                    libro[encontrado].autor, 
                                                    libro[encontrado].dia, 
                                                    libro[encontrado].mes, 
                                                    libro[encontrado].anio, 
                                                    libro[encontrado].estado, 
                                                    libro[encontrado].stockI);
    }
    
}

void prestarLibro(Libro*libro, int *cont){
    char busca[50];
    int conta;
    int opc2;
    tablaLibros(libro, cont);
    printf("Ingrese el nombre del libro que desea pedir prestado: ");
    eliminarSalto(busca,50);
    conta=buscarLibro(libro, *cont, busca);
     if (conta==-1)
    {
        printf("El libro no esta registrado\n");
        return;
    } 

     printf("Libro encontrado: %s - Estado actual: %s\n",
           libro[conta].nombreL, libro[conta].estado);

     if (strcmp(libro[conta].estado, "Prestado") == 0) {
        printf("El libro ya esta prestado.\n");
        printf("Actualmente lo tiene:\n");
        printf("  Nombre: %s\n", libro[conta].prestamo.nombreC);
        printf("  Cédula: %s\n", libro[conta].prestamo.cedula);
        return;
    }

    // Si está disponible → prestar
    printf("El libro está disponible.\n");

    printf("Ingrese nombre de la persona que pide el libro: ");
    eliminarSalto(libro[conta].prestamo.nombreC, 50);

    printf("Ingrese la cedula: ");
    eliminarSalto(libro[conta].prestamo.cedula, 20);

    // Cambiar estado
    strcpy(libro[conta].estado, "Prestado");

    printf("El libro se ha prestado correctamente.\n");
}

void ingresarCedula(char *cedula) {
    int valido = 0;

    while (!valido) {
        printf("Ingrese la cedula (10 digitos): ");
        eliminarSalto(cedula, 20);

        int len = strlen(cedula);

        if (len != 10) {
            printf("Error: la cedula debe tener exactamente 10 digitos.\n");
            continue;
        }

        // Verificar que sean solo números
        int esNumero = 1;
        for (int i = 0; i < 10; i++) {
            if (cedula[i] < '0' || cedula[i] > '9') {
                esNumero = 0;
                break;
            }
        }

        if (!esNumero) {
            printf("Error: solo se permiten numeros.\n");
            continue;
        }

        // Si pasa todas las validaciones
        valido = 1;
    }
}

void devolverLibros(Libro*libro, int cont){
    char cedulaBuscar[20];
    int encontrado = -1;

    printf("Ingrese la cedula de quien devuelve el libro: ");
    ingresarCedula(cedulaBuscar);

    for (int i = 0; i < cont; i++) {
        if (strcmp(libro[i].estado, "Prestado") == 0 &&
            strcmp(libro[i].prestamo.cedula, cedulaBuscar) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("No hay ningún libro prestado a esa cedula.\n");
        return;
    }

    printf("Libro encontrado:\n");
    printf("  Nombre libro: %s\n", libro[encontrado].nombreL);
    printf("  Prestado a: %s\n", libro[encontrado].prestamo.nombreC);

    strcpy(libro[encontrado].estado, "Disponible");

    libro[encontrado].prestamo.nombreC[0] = '\0';
    libro[encontrado].prestamo.cedula[0] = '\0';

    printf("El libro ha sido devuelto correctamente.\n");
}


void eliminarLibro(Libro*libro, int *cont){

    tablaLibros(libro, cont);
    char buscar[50];
    int pos;
    printf("Ingrese el nombre del libro que desea ingresar: ");
    eliminarSalto(buscar,50);
    pos=buscarLibro(libro, *cont, buscar);
    if (pos ==-1)
    {
        printf("Libro no encontrado\n");
        return;
    }
    for (int i = pos; i < *cont-1; i++)
    {
        libro[i].Id=libro[i+1].Id;
        strcpy(libro[i].nombreL,libro[i+1].nombreL);
        strcpy(libro[i].autor,libro[i+1].autor);
        libro[i].dia=libro[i+1].dia;
        libro[i].mes=libro[i+1].mes;
        libro[i].anio=libro[i+1].anio;
        strcpy(libro[i].estado,libro[i+1].estado);
        libro[i].stockI=libro[i+1].stockI;
    }
    (*cont)--;
    printf("Producto Eliminado........\n");
}

void tablaEstado(Libro*libro, int cont){
    printf("------------------ Tabla de estados ----------------\n");
    printf("#\tNombre del libro\testado\tNombre del cliente\tCedula\n");
    for (int i = 0; i < cont; i++)
    {
        printf("%d\t%s\t%s\t%s\t%s\n", i+1, libro[i].nombreL,libro[i].estado,libro[i].prestamo.nombreC,libro[i].prestamo.cedula);
    }
    
}