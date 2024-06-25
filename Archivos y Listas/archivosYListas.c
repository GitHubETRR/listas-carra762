#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CANT_MAX 50

typedef struct pilotos{
    unsigned char nombre[CANT_MAX];
    unsigned int campeonato;
} piloto_t;

void leerArchivo (piloto_t pilotos[],  const char *archivoNombre, unsigned int *cantPilotos);
int buscarPorNombre (piloto_t pilotos[], const char *nombre,  unsigned int *cantPilotos);
/* void *buscarPorAnio (piloto_t pilotos[], int cantPilotos, int anio); */

int main (void) {
    piloto_t pilotos[30];
    char *nombre[CANT_MAX];
    int anioGanado;
    unsigned int nPilotos;
    printf("Nombre: ");
    scanf("%s", &nombre);
    printf("se almaceno %s\n", nombre);
    leerArchivo(pilotos, "pilotos.txt", &nPilotos);
/*     printf("piloto ej %s\n", pilotos[0].nombre); */
    printf("cant pilotos : %d\n", nPilotos);
/*     anioGanado = buscarPorNombre(pilotos, nombre, nPilotos);
    printf("%s gano en el anio %d", nombre, anioGanado); */
    return 0;
}


void leerArchivo (piloto_t pilotos[], const char *archivoNombre, unsigned int *cantPilotos ){
    FILE *archivo;
    archivo = fopen (archivoNombre, "r");
    if (archivo == NULL) {
        printf("no se encontro el archivo");
    } else {

    int i = 0, j = 0, k = 0; 
    char* ch;
    char buffer[100];

    while ((ch = (int) fgets(buffer, sizeof(buffer), archivo)) != NULL && i < 30) {
    //ver  como almaceno los nombres y los campeonatos
        i++;
        (*cantPilotos)++;
    }

    for (int j = 0; j < *cantPilotos; j++) {
        printf("nombre piloto : %s\n", pilotos[j].nombre);
    }
    printf("campeonato: %d\n", pilotos[0].campeonato);
    fclose(archivo);
    }
}

 int buscarPorNombre (piloto_t pilotos[], const char *nombre, unsigned int *cantPilotos){
    int anioGanado = -1;  
    printf("cant pilotos : %d\n", *cantPilotos); 
    for (int i = 0; i < (int) cantPilotos; i++) {
        if (strcmp(nombre, pilotos[i].nombre) == 0) {
            pilotos[i].campeonato = anioGanado;
            break;  
        }
    } 

    return anioGanado; */
    }
/
/* char *buscarPorAnio (piloto_t pilotos[], int cantPilotos, int anio){
    char ganador;

    return ganador;
}
  */