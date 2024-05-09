
#include <stdio.h>
#include <stdlib.h>
#define MAX_AL 30
#define SALIR 3
typedef struct alumno{
    char Nombre[30];
    int Edad;
    struct alumno *next;
}alumno_t; 

alumno_t * curso1925=NULL;
void menu(void);
void imprimir_alumno(alumno_t);
void pedir_datos(alumno_t * alumno);
void ver_lista(void);
void cargar_alumno(void);
void liberar_memoria(void);

int main(){
    menu();
    liberar_memoria(void);
    return 0;
}

void imprimir_alumno(alumno_t alumno){
    printf("Nombre: %s\n",alumno.Nombre);
    printf("Edad: %d\n",alumno.Edad);
    printf("+++++++++++++++++++++++\n");

}
void pedir_datos(alumno_t * alumno){
    printf("ingrese el nombre del alumno:\n");
    scanf("%s",alumno->Nombre);
    printf("ingrese la edad del alumno:\n");
    scanf("%d",&(alumno->Edad));

}

void menu(void){
    int opcion;
    do{
        printf("1_Cargar un nuevo alumno\n");
        printf("2_Ver todos los alumnos cargados\n");
        printf("3_Salir\n");
        scanf("%d",&opcion);
        if(opcion==1)cargar_alumno();
        if(opcion==2)ver_lista();
    }while(opcion!=SALIR);
    
}

void cargar_alumno(){
    alumno_t *alumno_aux;
    alumno_aux=malloc(sizeof(alumno_t));
    if(alumno_aux==NULL){
        printf("Out of memory\n");
    }else{
        pedir_datos(alumno_aux);
        alumno_aux->next=curso1925;
        curso1925=alumno_aux;
    }
     
        
}

void ver_lista(void){
    alumno_t *lista=curso1925;
    while(lista!=NULL){
        imprimir_alumno(*lista);
        lista=lista->next;
    }
}
void liberar_memoria(void){
    alumno_t *aux=NULL;
    while(curso1925!=NULL){
        aux=curso1925;
        curso1925=curso1925->next;
        free(aux);
    }
}