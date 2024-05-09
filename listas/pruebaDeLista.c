#include <stdio.h>
#include <stdlib.h>
#include "tildes.h"

#define CARGAR 1
#define VER 2
#define SALIR 3

typedef struct alumno {
    char nombre[30];
    int edad;
    struct alumno *next;
} alumno_t;

alumno_t * curso1925 = NULL;
void menu (void);
void pedir_datos(alumno_t *alumno);
void cargar_alumno(void);
void imprimir_alumno(alumno_t alumno);
void ver_lista(void);
void liberar_memoria(void);

int main (void) {
    menu();
    liberar_memoria();
    return 0;
}

void menu (void) {
    int opcion;
    printf("Ingrese el n%cmero correpondiente\n", UT);
    do {
        printf("1_Cargar nuevo alumno\n2_Ver alumnos cargados\n3_Salir\n");
        printf("ingrese el n%cmero : ", UT);
        scanf("%d", &opcion);
        if (opcion == CARGAR) {
            cargar_alumno();
        }
        if (opcion == VER) {
            ver_lista();
        }
    } while (opcion != SALIR);
    printf("Hasta luego!");
}

void cargar_alumno(void) {
    alumno_t *alumno_aux;
    alumno_aux = malloc (sizeof(alumno_t));
    if (alumno_aux == NULL){
        printf("No hay memoria\n");
    } else {
        pedir_datos(alumno_aux);
        alumno_aux -> next = curso1925;
        curso1925 = alumno_aux;
    }
}

void pedir_datos(alumno_t *alumno){
    printf("Nombre : ");
    scanf("%s", alumno->nombre);
    printf("Edad : ");
    scanf("%d", &(alumno->edad));
}

void ver_lista(void){
    if (curso1925 == NULL) {
        printf("No hay alumnos cargados.\n");
        return;
    }
    alumno_t *lista = curso1925;
    while (lista != NULL){
        imprimir_alumno(*lista);
        lista = lista -> next;
    }
}

void imprimir_alumno(alumno_t alumno) {
    printf("nombre : %s\n", alumno.nombre);
    printf("edad : %d\n", alumno.edad);
    printf("++++++++++++++++++++++++++++++++++\n");
}

void liberar_memoria(void){
    alumno_t *aux = NULL;
    while (curso1925 != NULL){
        aux = curso1925;
        curso1925 = curso1925 -> next;
        free(aux);
    }
}

