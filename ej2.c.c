#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUMNOS 100
#define MAX_NOMBRE 50

typedef struct {
    char nombre[MAX_NOMBRE];
    float nota1, nota2, nota3;
    float promedio;
} Alumno;

int main() {
    FILE *archivo;
    Alumno alumnos[MAX_ALUMNOS];
    int count = 0;
    float sumaPromedios = 0.0;
    Alumno mejorAlumno;
    float mayorPromedio = 0.0;

    archivo = fopen("alumnos.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo alumnos.txt\n");
        return 1;
    }

    // Leer datos del archivo
    while (fscanf(archivo, "%s %f %f %f", alumnos[count].nombre,
                  &alumnos[count].nota1, &alumnos[count].nota2, &alumnos[count].nota3) == 4) {

        alumnos[count].promedio = (alumnos[count].nota1 +
                                   alumnos[count].nota2 +
                                   alumnos[count].nota3) / 3.0;

        sumaPromedios += alumnos[count].promedio;

        if (alumnos[count].promedio > mayorPromedio) {
            mayorPromedio = alumnos[count].promedio;
            mejorAlumno = alumnos[count];
        }

        count++;
    }

    fclose(archivo);

    // Mostrar resultados
    printf("\n--- Promedios individuales ---\n");
    for (int i = 0; i < count; i++) {
        printf("%s -> %.1f\n", alumnos[i].nombre, alumnos[i].promedio);
    }

    float promedioGeneral = sumaPromedios / count;

    printf("\nPromedio grupo: %.1f\n", promedioGeneral);
    printf("Mejor alumno: %s\n", mejorAlumno.nombre);

    return 0;
}
