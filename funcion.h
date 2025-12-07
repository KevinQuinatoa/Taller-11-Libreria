#include <string.h>
#include <stdio.h>

typedef struct 
{
    char nombreC[50];
    char cedula[11];
}Cliente;

typedef struct 
{
    int Id;
    char nombreL[50];
    char autor[50];
    int dia, mes, anio;
    char estado[20];
    Cliente prestamo;
}Libro;



int menu();
int opcionValida(int min, int max);
void crearLibro(Libro*libro, int *cont);
void eliminarSalto(char *cadena, int n);
void tablaLibros(Libro*libro, int *cont);
int buscarLibro(Libro*libro, int cont, char buscar[]);
void encontrarLibro(Libro*libro, int *cont);
int buscarId(Libro*libro, int cont, int id);
void prestarLibro(Libro*libro, int *cont);
void eliminarLibro(Libro*libro, int *cont);
void devolverLibros(Libro*libro, int cont);
void ingresarCedula(char *cedula);
void tablaEstado(Libro*libro, int cont);