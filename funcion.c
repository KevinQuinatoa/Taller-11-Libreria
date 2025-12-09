#include <string.h>
#include <stdio.h>
#include "funcion.h"

int menu(){
     int opcion;

    printf("-------------- Menu ----------------\n");
    printf("1. Ingresar libros\n");
    printf("2. Mostrar lista de libros\n");
    printf("3. Mostrar tabla de estados de los libros\n");
    printf("4. Busqueda de libros\n");
    printf("5. Prestar libro\n");
    printf("6. Entrega de libros\n");
    printf("7. Eliminar libros\n");
    printf("8. Salir del programa\n");
    printf("Ingrese una opcion: ");
    opcion = opcionValida(1,8);
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


void crearLibro(Libro*libro, int *cont){
    int cantidad;
    printf("Ingrese la cantidad de libros a registrar (maximo 10): \n");
    cantidad=opcionValida(1,10);
    
    if (cantidad>10)
    {
        printf("Se ingreso la cantidad maxima de libros\n");
        return;

    } 
    for (int i = 0; i < cantidad; i++){

        int existeN, existeId;
    printf("Ingrese el ID del libro %d: ", i+1);
    ingresarID(libro[*cont].Id, 20);
    
    existeId=buscarId(libro, *cont, libro[*cont].Id);
    // comprobar si el ID ya esta registrado
    if (existeId!=-2)
    {
        printf("el Id ya esta registrado\n");
        return;
    }

    printf("Ingrese el nombre del libro %d: ", i+1);
    eliminarSalto(libro[*cont].nombreL,50);
    

    printf("Ingrese el nombre del autor del libro %d: ", i+1);
    eliminarSalto(libro[*cont].autor,50);
    printf("Ingrese el dia de publicacion: ");
    libro[*cont].dia=opcionValida(1,32);
    printf("Ingrese el mes de publicion: ");
    libro[*cont].mes=opcionValida(1,12);
    printf("Ingrese el anio de publicacion: ");
    libro[*cont].anio=opcionValida(1,3000);
    printf("Estado del libro %d:\n",i+1);
    printf("1. Disponible\n");
    printf("2. Prestado\n");
    printf("Ingrese una opcion: ");

    int opcionE = opcionValida(1, 2);
    if (opcionE == 1) {
        strcpy(libro[*cont].estado, "Disponible");
        // para que eno arroje basura al poner la tabla de estados
        strcpy(libro[*cont].prestamo.nombreC, "-");
        strcpy(libro[*cont].prestamo.cedula, "-");
    } else {
        strcpy(libro[*cont].estado, "Prestado");
        printf("Ingrese nombre de la persona que pide el libro: ");
        eliminarSalto(libro[*cont].prestamo.nombreC, 50);

        printf("Ingrese la cedula: ");
        ingresarCedula(libro[*cont].prestamo.cedula);
    }
    (*cont)++;
    printf("Libro Registrado.........\n");
    }
    
}

void tablaLibros(Libro*libro, int *cont){
    printf("------------------------------ Tabla de libros ------------------------\n");

    printf("#\tID\tNombre\t\tAutor\t\tDia\tMes\tAnio\tEstado\n");
    for (int i = 0; i < *cont; i++)
    {
        printf("%d\t%s\t%s\t%s\t\t%d\t%d\t%d\t%s\n", i+1, libro[i].Id, 
                                                            libro[i].nombreL, 
                                                            libro[i].autor, 
                                                            libro[i].dia, 
                                                            libro[i].mes, 
                                                            libro[i].anio, 
                                                            libro[i].estado);
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

void ingresarID(char *destino, int max) {
    while (1) {
        eliminarSalto(destino, max);

        // Validación: NO permitir cadena vacía ni solo espacios
        if (strlen(destino) == 0) {
            printf("El ID no puede estar vacío. Ingrese nuevamente: ");
            continue;
        }

        // NO permitir negativo: si comienza con '-'
        if (destino[0] == '-') {
            printf("No se permiten ID negativos. Ingrese nuevamente: ");
            continue;
        }

        return;
    }
}

int buscarId(Libro* libro, int cont, char idBuscado[]){
    for (int i = 0; i < cont; i++)
    {   
        if (strcmp(libro[i].Id, idBuscado) == 0){
            return i;
        }
        
    }
    return -2;
}

void encontrarLibro(Libro*libro, int *cont){

    char nombreBuscar[50];
    char idBuscar[20];
    int encontrado = -1;

    printf("Ingrese el nombre del libro que desea buscar: ");
    eliminarSalto(nombreBuscar, 50);

    printf("Ingrese el ID del libro que desea buscar: ");
    eliminarSalto(idBuscar, 20);

    // Buscar libro que coincida en nombre Y ID
    for (int i = 0; i < *cont; i++) {
        if (strcmp(libro[i].nombreL, nombreBuscar) == 0 &&
            strcmp(libro[i].Id, idBuscar) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("El libro no esta registrado\n");
        return;
    }

    printf("El libro fue encontrado\n");
    printf("ID\tNombre\t\tAutor\t\tDia\tMes\tAnio\tEstado\n");

    printf("%s\t%s\t%s\t\t%d\t%d\t%d\t%s\n",
            libro[encontrado].Id,
            libro[encontrado].nombreL,
            libro[encontrado].autor,
            libro[encontrado].dia,
            libro[encontrado].mes,
            libro[encontrado].anio,
            libro[encontrado].estado);
}


void prestarLibro(Libro*libro, int *cont){
    char busca[50];
    int conta;
    int opc2;
    tablaLibros(libro, cont);
    printf("Ingrese el ID del libro que desea pedir prestado: ");
    eliminarSalto(busca,20);
    conta=buscarId(libro, *cont, busca);
     if (conta==-2)
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
        printf("  Cedula: %s\n", libro[conta].prestamo.cedula);
        return;
    }

    // Si está disponible → prestar
    printf("El libro esta disponible.\n");

    printf("Ingrese nombre de la persona que pide el libro: ");
    eliminarSalto(libro[conta].prestamo.nombreC, 50);

    printf("Ingrese la cedula: ");
    ingresarCedula(libro[conta].prestamo.cedula);

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
        printf("No hay ningun libro prestado a esa cedula.\n");
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
    char buscar[20];
    int pos;
    printf("Ingrese el ID del libro que desea eliminar: ");
    eliminarSalto(buscar,20);
    pos=buscarId(libro, *cont, buscar);
    if (pos ==-2)
    {
        printf("Libro no encontrado\n");
        return;
    }
    if (strcmp(libro[pos].estado,"Prestado")==0)
    {
        printf("No se puede eliminar un libro que esta prestado\n");
        return;
    }
    
    for (int i = pos; i < *cont-1; i++)
    {
        strcpy(libro[i].Id,libro[i+1].Id);
        strcpy(libro[i].nombreL,libro[i+1].nombreL);
        strcpy(libro[i].autor,libro[i+1].autor);
        libro[i].dia=libro[i+1].dia;
        libro[i].mes=libro[i+1].mes;
        libro[i].anio=libro[i+1].anio;
        strcpy(libro[i].estado,libro[i+1].estado);
        strcpy(libro[i].prestamo.nombreC,libro[i+1].prestamo.nombreC);
        strcpy(libro[i].prestamo.cedula,libro[i+1].prestamo.cedula);
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