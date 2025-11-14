#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nombre[40];
    float precio;
    int stock;
} Producto;

void guardarInventario(Producto *productos, int count) {
    FILE *archivo = fopen("inventario.txt", "w");
    if (archivo == NULL) {
        printf("Error al guardar el archivo.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(archivo, "%d %s %.2f %d\n",
                productos[i].id,
                productos[i].nombre,
                productos[i].precio,
                productos[i].stock);
    }
    fclose(archivo);
}

int cargarInventario(Producto **productos) {
    FILE *archivo = fopen("inventario.txt", "r");
    if (archivo == NULL) {
        return 0; // No existe aún
    }

    int count = 0;
    Producto temp;
    while (fscanf(archivo, "%d %s %f %d",
                  &temp.id, temp.nombre, &temp.precio, &temp.stock) == 4) {
        *productos = realloc(*productos, (count + 1) * sizeof(Producto));
        (*productos)[count] = temp;
        count++;
    }

    fclose(archivo);
    return count;
}

void agregarProducto(Producto **productos, int *count) {
    Producto nuevo;
    printf("Ingrese ID del producto: ");
    scanf("%d", &nuevo.id);
    printf("Ingrese nombre del producto: ");
    scanf("%s", nuevo.nombre);
    printf("Ingrese precio: ");
    scanf("%f", &nuevo.precio);
    printf("Ingrese cantidad en stock: ");
    scanf("%d", &nuevo.stock);

    *productos = realloc(*productos, (*count + 1) * sizeof(Producto));
    (*productos)[*count] = nuevo;
    (*count)++;

    printf("\nProducto guardado: ID=%d, %s, $%.2f, Stock=%d\n",
           nuevo.id, nuevo.nombre, nuevo.precio, nuevo.stock);
}

void buscarProducto(Producto *productos, int count) {
    int opcion;
    printf("Buscar por:\n1) ID\n2) Nombre\nOpción: ");
    scanf("%d", &opcion);

    if (opcion == 1) {
        int idBuscado;
        printf("Ingrese ID: ");
        scanf("%d", &idBuscado);
        for (int i = 0; i < count; i++) {
            if (productos[i].id == idBuscado) {
                printf("Encontrado: %d, %s, $%.2f, Stock=%d\n",
                       productos[i].id, productos[i].nombre,
                       productos[i].precio, productos[i].stock);
                return;
            }
        }
    } else if (opcion == 2) {
        char nombreBuscado[40];
        printf("Ingrese nombre: ");
        scanf("%s", nombreBuscado);
        for (int i = 0; i < count; i++) {
            if (strcmp(productos[i].nombre, nombreBuscado) == 0) {
                printf("Encontrado: %d, %s, $%.2f, Stock=%d\n",
                       productos[i].id, productos[i].nombre,
                       productos[i].precio, productos[i].stock);
                return;
            }
        }
    }
    printf("Producto no encontrado.\n");
}

void mostrarInventario(Producto *productos, int count) {
    printf("\n--- Inventario ---\n");
    for (int i = 0; i < count; i++) {
        printf("ID=%d | %s | $%.2f | Stock=%d\n",
               productos[i].id, productos[i].nombre,
               productos[i].precio, productos[i].stock);
    }
}

int main() {
    Producto *productos = NULL;
    int count = 0;
    int opcion;

    count = cargarInventario(&productos);

    do {
        printf("\n1) Agregar producto\n2) Buscar producto\n3) Mostrar inventario\n4) Salir\nOpción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregarProducto(&productos, &count);
                guardarInventario(productos, count);
                break;
            case 2:
                buscarProducto(productos, count);
                break;
            case 3:
                mostrarInventario(productos, count);
                break;
            case 4:
                guardarInventario(productos, count);
                printf("Inventario guardado. Saliendo...\n");
                break;
            default:
                printf("Opción no válida.\n");
        }

    } while (opcion != 4);

    free(productos);
    return 0;
}
