//poner esto en el inicio de la terminal para que funcionen los caracteres especiales: chcp 65001 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tildes.h"

#define CANT_MAX 100
#define MAX_CAMP 10
#define MAX_PILOTOS 30

typedef struct {
    unsigned char nombre[CANT_MAX];
    unsigned char nombre2[CANT_MAX];
    unsigned char apellido[CANT_MAX];
    unsigned char apodo[CANT_MAX];
    unsigned char nomYApellido [CANT_MAX];
    unsigned char nomBackup[CANT_MAX];
    unsigned int campeonatos[MAX_CAMP];
    int numCampeonatos;
} piloto_t;

void leerArchivo (piloto_t pilotos[],  const char *archivoNombre, unsigned int *cantPilotos);
int buscarPorNombre (piloto_t pilotos[], const char *nombre,  unsigned int cantPilotos);
void buscarPorAnio (piloto_t pilotos[], unsigned int cantPilotos, int anio); 
void datoInteresante (const char *archivoNombre, const char *palabra);
void toLowerCase (char *str);
void trim (char *str);

int main (void) {
    piloto_t pilotos[MAX_PILOTOS];
    unsigned int nPilotos = 0;
    int opcion, anio;
    const char nombre[CANT_MAX], elegir[CANT_MAX];
    const char  *si="si", *no= "no";
    leerArchivo(pilotos, "pilotos2.txt", &nPilotos);
    do{
        do{
            printf("\n-------Menú-------\n");
            printf("Ingrese 1 si desea ingresar un nombre o apodo de un piloto.\nIngrese 2");
            printf("si desea ingresar un año (entre 1950 y 2023)\nIngrese 3 si desea salir.");
            printf("\nopción: ");
            scanf("%d", &opcion);  
            if (opcion != 1 && opcion != 2 && opcion != 3){
                printf("La opción que usted eligió no está permitida. Por favor, ingrese 1, 2 o 3\n");
            }
        } while (opcion != 1 && opcion != 2 && opcion != 3);
        if (opcion == 1) {
            int i;
            /* do{ */
                printf("Nombre o apodo: ");
                scanf("\n%[^\n]s", nombre);
                i = buscarPorNombre(pilotos, nombre, nPilotos);
            /* } while (i != 88); */
            if (pilotos[i].numCampeonatos == 1){
                printf("%sgano en el año %d\n", pilotos[i].nomBackup, pilotos[i].campeonatos[0]);
                datoInteresante("datosf1.txt", nombre);
            } else {
                printf("%sgano en los años: ", pilotos[i].nomBackup); 
                for (int j = 0; j < pilotos[i].numCampeonatos; j++){
                    printf("%u ", pilotos[i].campeonatos[j]);
                }
                printf("\n");
                datoInteresante("datosf1.txt", nombre);
            }
        } else if (opcion == 2) {
            do{
                printf("Año: ");
                scanf("%u", &anio);
                if(anio > 2023 || anio < 1950){
                    printf("el año es incorrecto. por favor, ingrese otro.\n");
                }
            } while (anio > 2023 || anio < 1950);
            buscarPorAnio(pilotos, nPilotos, anio);
        }
        printf("\n\n¿continuar?, [si/no]");
        scanf("%s", &elegir);
    } while ((strcmp(elegir, no) == 0)||opcion != 3 && opcion > 0);
    return 0;
} 

void leerArchivo (piloto_t pilotos[], const char *archivoNombre, unsigned int *cantPilotos) {
    FILE *archivo;
    archivo = fopen (archivoNombre, "r");
    if (archivo == NULL) {
        printf("no se encontro el archivo");
        return;
    } 
        *cantPilotos = 0;
        char linea[256];
        while (fgets(linea, sizeof(linea), archivo)) { 
            char *NA = strtok(linea, "\"");            
            strcpy(pilotos[*cantPilotos].nomYApellido, NA);
            pilotos[*cantPilotos].numCampeonatos = 0;

            char nYap[50];
            strcpy(nYap, pilotos[*cantPilotos].nomYApellido);

            strcpy(pilotos[*cantPilotos].nomBackup, pilotos[*cantPilotos].nomYApellido);
            
            NA = strtok(NULL, "\"");
            strcpy(pilotos[*cantPilotos].apodo, NA);
            trim(pilotos[*cantPilotos].apodo);

            while ((NA = strtok(NULL, " \n")) != NULL) {
                if (pilotos[*cantPilotos].numCampeonatos < MAX_CAMP) {
                    pilotos[*cantPilotos].campeonatos[pilotos[*cantPilotos].numCampeonatos++] = atoi(NA);
                }
            }

            if (pilotos[*cantPilotos].numCampeonatos == 5) {
                NA = strtok(nYap, " ");
                strcpy(pilotos[*cantPilotos].nombre, NA);    
                trim(pilotos[*cantPilotos].nombre);

                NA = strtok(NULL, " ");
                strcpy(pilotos[*cantPilotos].nombre2, NA);    
                trim(pilotos[*cantPilotos].nombre2);

                NA = strtok(NULL, "\"");
                strcpy(pilotos[*cantPilotos].apellido, NA);
                trim(pilotos[*cantPilotos].apellido);

                toLowerCase(pilotos[*cantPilotos].nombre2);
            } else {

                NA = strtok(nYap, " ");
                strcpy(pilotos[*cantPilotos].nombre, NA);    
                trim(pilotos[*cantPilotos].nombre);     

                NA = strtok(NULL, "\"");
                strcpy(pilotos[*cantPilotos].apellido, NA);
                trim(pilotos[*cantPilotos].apellido);

                trim(pilotos[*cantPilotos].nomYApellido);

                toLowerCase(pilotos[*cantPilotos].nomYApellido);
                toLowerCase(pilotos[*cantPilotos].nombre);
                toLowerCase(pilotos[*cantPilotos].apellido);
                toLowerCase(pilotos[*cantPilotos].apodo);

                (*cantPilotos)++;
            }
    }
    fclose(archivo);
}
   
int buscarPorNombre (piloto_t pilotos[], const char *nombre, unsigned int cantPilotos){
    char nombreLow[CANT_MAX];
    strcpy(nombreLow, nombre);
    toLowerCase(nombreLow);
    int repetidas = 0; //ver como identificar a los que tienen mismo apellido o nombre.
    for (int i = 0; i < cantPilotos; i++) {
        if (strcmp(pilotos[i].nombre, nombreLow) == 0 || strcmp(pilotos[i].apellido, nombreLow) == 0 ||
            strcmp(pilotos[i].apodo, nombreLow) == 0 || strcmp(pilotos[i].nomYApellido, nombreLow) == 0 ||
            strcmp(pilotos[i].nombre2, nombreLow) == 0) {
            return i;
        } else {
            //ver como puedo hacer para volver a pedir el nombre si no coincide con ninguno en el archivo.
        }
    }
}

void buscarPorAnio (piloto_t pilotos[], unsigned int cantPilotos, int anio){
    int resta;
    for (int i = 0; i < cantPilotos; i++) {
        for (int j = 0; j < pilotos[i].numCampeonatos; j++) {
            resta = pilotos[i].campeonatos[j] - anio;
            if (resta == 0) {
                printf("%sganó en %d\n", pilotos[i].nomBackup, pilotos[i].campeonatos[j]);
                char nombre[60];
                strcpy(nombre, pilotos[i].nomYApellido);
                datoInteresante("datosf1.txt", nombre);
            }
        }
    }
}

//mejorar.
void datoInteresante (const char *archivoNombre, const char *palabra) {
    FILE *archivo;
    archivo = fopen (archivoNombre, "r");
    char nombreyap[60], nombre[30], nombre2[30], apellido[30];
    int contador = 0;
    toLowerCase((char*) palabra);
    if (archivo == NULL) {
        printf("no se encontró el archivo");
        return;
    } else {
        char linea [2560];
        char *l;
        while (l = fgets(linea, sizeof(linea), archivo)){
            char pa[2500];
            strcpy(pa, l);
            char *pal = strtok(linea, ":"); 
            strcpy(nombreyap, pal);
            toLowerCase(nombreyap);

            char *linea = strtok(NULL, "\n");

            char p[60];
            strcpy(p, nombreyap);

            if (contador == 1) {
                pal = strtok(p, " ");
                strcpy(nombre, pal);

                pal = strtok(NULL, " ");
                strcpy(nombre2, pal);
                trim(nombre2);

                pal= strtok(NULL, ":");
                strcpy(apellido, pal);

            } else {

                pal = strtok(p, " ");
                strcpy(nombre, pal);

                pal= strtok(NULL, ":");
                strcpy(apellido, pal);

            } 

            trim(nombre);
            trim(apellido);
            trim(nombreyap);

            if (strcmp(nombre, palabra) == 0 || strcmp(nombre2, palabra) == 0 || 
                strcmp(apellido, palabra) == 0 || strcmp(nombreyap, palabra) == 0) {
                printf("%s", linea);
            }
            contador++;
        }
    }
    fclose(archivo);
}

void toLowerCase (char *str) {
    for(; *str; ++str) *str = tolower (*str);
}

void trim (char *str) {
    int largo = strlen(str);
    while (largo > 0 && isspace((unsigned char)str[largo - 1])) {
        str[largo - 1] = '\0';
        largo--;
    }
}