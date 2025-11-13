#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    printf("Ingrese filas (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Entrada inválida.\n");
        return 1;
    }

    printf("Ingrese columnas (m): ");
    if (scanf("%d", &m) != 1 || m <= 0) {
        printf("Entrada inválida.\n");
        return 1;
    }

    int **A = malloc(n * sizeof(int*));
    int **B = malloc(n * sizeof(int*));
    int **C = malloc(n * sizeof(int*));
    if (!A || !B || !C) {
        printf("Error de memoria.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        A[i] = malloc(m * sizeof(int));
        B[i] = malloc(m * sizeof(int));
        C[i] = malloc(m * sizeof(int));
        if (!A[i] || !B[i] || !C[i]) {
            printf("Error de memoria.\n");
            for (int k = 0; k <= i; k++) {
                free(A[k]);
                free(B[k]);
                free(C[k]);
            }
            free(A); free(B); free(C);
            return 1;
        }
    }

    // Leer matrices
    printf("Matriz A:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &A[i][j]);

    printf("Matriz B:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &B[i][j]);

    // Sumar matrices
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            C[i][j] = A[i][j] + B[i][j];

    // Mostrar resultado en consola
    printf("Matriz suma:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }

    // Guardar en archivo
    FILE *f = fopen("matriz_suma.txt", "w");
    if (!f) {
        printf("Error al abrir archivo.\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            fprintf(f, "%d ", C[i][j]);
        fprintf(f, "\n");
    }
    fclose(f);
    printf("Resultado guardado en matriz_suma.txt\n");

    // Liberar memoria
    for (int i = 0; i < n; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}