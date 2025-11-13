#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINEA 100

typedef struct {
    char letra;
    int sumaCalif;
    int cantidad;
} Grupo;

int main() {
    FILE *archivo = fopen("grupos.txt", "r");
    if (!archivo) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    Grupo *grupos = NULL;
    int numGrupos = 0;

    char linea[MAX_LINEA];
    while (fgets(linea, sizeof(linea), archivo)) {
        // Eliminar salto de línea
        linea[strcspn(linea, "\n")] = 0;

        // Saltar líneas vacías
        if (strlen(linea) == 0) continue;

        char *grupoStr = strtok(linea, ",");
        char *nombre = strtok(NULL, ",");
        char *califStr = strtok(NULL, ",");

        if (!grupoStr || !nombre || !califStr) continue;

        while (*grupoStr == ' ') grupoStr++;
        while (*nombre == ' ') nombre++;
        while (*califStr == ' ') califStr++;

        char letra = grupoStr[0];
        int calificacion = atoi(califStr);

        // Buscar si el grupo ya existe
        int encontrado = 0;
        for (int i = 0; i < numGrupos; i++) {
            if (grupos[i].letra == letra) {
                grupos[i].sumaCalif += calificacion;
                grupos[i].cantidad++;
                encontrado = 1;
                break;
            }
        }

        // Si no existe, agregar nuevo grupo
        if (!encontrado) {
            numGrupos++;
            grupos = realloc(grupos, numGrupos * sizeof(Grupo));
            grupos[numGrupos - 1].letra = letra;
            grupos[numGrupos - 1].sumaCalif = calificacion;
            grupos[numGrupos - 1].cantidad = 1;
        }
    }

    fclose(archivo);

    // Imprimir promedio por grupo
    for (int i = 0; i < numGrupos; i++) {
        double promedio = (double) grupos[i].sumaCalif / grupos[i].cantidad;
        printf("Grupo %c -> Promedio %.1f\n", grupos[i].letra, promedio);
    }

    free(grupos);
    return 0;
}