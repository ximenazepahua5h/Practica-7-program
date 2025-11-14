#include <stdio.h>
#include <stdlib.h>

struct Alumno {
    char nombre[40];
    float calificaciones[3];
    float promedio;
};

int main() {
    struct Alumno *alumnos = NULL;
    int cantidad = 0;
    char opcion;
    FILE *archivo = fopen("alumnos.txt", "a");
    if(!archivo) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    do {
        alumnos = (struct Alumno*) realloc(alumnos, (cantidad + 1) * sizeof(struct Alumno));
        printf("Nombre: ");
        scanf(" %[^\n]", alumnos[cantidad].nombre);
        printf("Ingrese 3 calificaciones: ");
        float suma = 0;
        for(int i=0;i<3;i++){
            scanf("%f", &alumnos[cantidad].calificaciones[i]);
            suma += alumnos[cantidad].calificaciones[i];
        }
        alumnos[cantidad].promedio = suma / 3;

        fprintf(archivo, "Nombre: %s\n", alumnos[cantidad].nombre);
        fprintf(archivo, "Calificaciones: %.2f %.2f %.2f\n", 
                alumnos[cantidad].calificaciones[0], 
                alumnos[cantidad].calificaciones[1], 
                alumnos[cantidad].calificaciones[2]);
        fprintf(archivo, "Promedio: %.2f\n\n", alumnos[cantidad].promedio);

        cantidad++;
        printf("Agregar otro alumno? (s/n): ");
        scanf(" %c", &opcion);
    } while(opcion == 's' || opcion == 'S');

    fclose(archivo);

    printf("\n--- Alumnos registrados ---\n");
    for(int i=0;i<cantidad;i++){
        printf("Nombre: %s\n", alumnos[i].nombre);
        printf("Calificaciones: %.2f %.2f %.2f\n", 
               alumnos[i].calificaciones[0],
               alumnos[i].calificaciones[1],
               alumnos[i].calificaciones[2]);
        printf("Promedio: %.2f\n\n", alumnos[i].promedio);
    }

    free(alumnos);
    return 0;
}
