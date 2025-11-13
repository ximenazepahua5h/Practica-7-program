#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOMBRE 40
#define MAX_CORREO 40
#define ARCHIVO "clientes.txt"

typedef struct {
    int id;
    char nombre[MAX_NOMBRE];
    char correo[MAX_CORREO];
} Cliente;

// Función para agregar cliente al archivo
void agregarCliente(Cliente c) {
    FILE *archivo = fopen(ARCHIVO, "a");
    if (!archivo) {
        printf("No se pudo abrir el archivo para agregar.\n");
        return;
    }
    fprintf(archivo, "%d,%s,%s\n", c.id, c.nombre, c.correo);
    fclose(archivo);
    printf("Cliente agregado: ID=%d, %s, %s\n", c.id, c.nombre, c.correo);
}

// Función para consultar cliente por ID
void consultarCliente(int id) {
    FILE *archivo = fopen(ARCHIVO, "r");
    if (!archivo) {
        printf("No se pudo abrir el archivo para consulta.\n");
        return;
    }

    Cliente c;
    int encontrado = 0;
    char linea[150];

    while (fgets(linea, sizeof(linea), archivo)) {
        sscanf(linea, "%d,%39[^,],%39[^\n]", &c.id, c.nombre, c.correo);
        if (c.id == id) {
            printf("Cliente encontrado: ID=%d, %s, %s\n", c.id, c.nombre, c.correo);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Cliente con ID=%d no encontrado.\n", id);
    }

    fclose(archivo);
}

// Función para eliminar cliente por ID (reescribe archivo sin ese cliente)
void eliminarCliente(int id) {
    FILE *archivo = fopen(ARCHIVO, "r");
    if (!archivo) {
        printf("No se pudo abrir el archivo para eliminar.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Error al crear archivo temporal.\n");
        fclose(archivo);
        return;
    }

    Cliente c;
    char linea[150];
    int eliminado = 0;

    while (fgets(linea, sizeof(linea), archivo)) {
        sscanf(linea, "%d,%39[^,],%39[^\n]", &c.id, c.nombre, c.correo);
        if (c.id == id) {
            eliminado = 1;
            continue;  // Saltar cliente a eliminar
        }
        fprintf(temp, "%d,%s,%s\n", c.id, c.nombre, c.correo);
    }

    fclose(archivo);
    fclose(temp);

    // Reemplazar archivo original por el temporal
    remove(ARCHIVO);
    rename("temp.txt", ARCHIVO);

    if (eliminado) {
        printf("Cliente eliminado: ID=%d\n", id);
    } else {
        printf("Cliente con ID=%d no encontrado para eliminar.\n", id);
    }
}

int main() {
    int opcion;
    Cliente nuevoCliente;
    int idConsulta, idEliminar;

    do {
        printf("\nBase de Datos de Clientes\n");
        printf("1. Agregar cliente\n");
        printf("2. Consultar cliente por ID\n");
        printf("3. Eliminar cliente por ID\n");
        printf("4. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar(); // Limpiar buffer

        switch (opcion) {
            case 1:
                printf("Ingrese ID: ");
                scanf("%d", &nuevoCliente.id);
                getchar();

                printf("Ingrese nombre: ");
                fgets(nuevoCliente.nombre, MAX_NOMBRE, stdin);
                nuevoCliente.nombre[strcspn(nuevoCliente.nombre, "\n")] = 0; // Quitar salto línea

                printf("Ingrese correo: ");
                fgets(nuevoCliente.correo, MAX_CORREO, stdin);
                nuevoCliente.correo[strcspn(nuevoCliente.correo, "\n")] = 0;

                agregarCliente(nuevoCliente);
                break;

            case 2:
                printf("Ingrese ID a consultar: ");
                scanf("%d", &idConsulta);
                consultarCliente(idConsulta);
                break;

            case 3:
                printf("Ingrese ID a eliminar: ");
                scanf("%d", &idEliminar);
                eliminarCliente(idEliminar);
                break;

            case 4:
                printf("Saliendo...\n");
                break;

            default:
                printf("Opción inválida.\n");
        }
    } while (opcion != 4);

    return 0;
}