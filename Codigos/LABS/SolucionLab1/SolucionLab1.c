#include <stdio.h>
#include <stdlib.h>
// Se llaman los encabezados de las funciones para poder escribirlas despues del main.
// Asi puedo usarlas cuando quiera en vez de tenerlas arribas
void mostrarPares(int **matriz, int filas, int columnas);
void escribirPares(int **matriz, int filas, int columnas, char *nombreSalida);
void mostrarTraspuesta(int **matriz, int filas, int columnas);
void ordenarMatriz(int **matriz, int filas, int columnas);
void swap(int *a, int *b);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s archivo_entrada archivo_salida\n", argv[0]);
        return 1;
    }
    // Se guardan directamente los nombres ya que se usaran para las invocaciones despues.
    char *nombreEntrada = argv[1];
    char *nombreSalida = argv[2];
    
    // Problema 1
    printf("Problema 1---------------\n");
    printf("%s %s\n", nombreEntrada, nombreSalida);
    
    FILE *archivo = fopen(nombreEntrada, "r");
    // Como se explico en las ayudantias, es dificil que pase algo asi, pero los "sanity checks" son necesarios.
    if (archivo == NULL) {
        printf("No se puede abrir el archivo.\n");
        return 1;
    }
    
    int filas, columnas;
    fscanf(archivo, "%d %d", &filas, &columnas);
    // Si bien el fscanf es doble, se puede perfectamente hacer 2 llamadas separadas.
    
    // Problema 2
    printf("Problema 2---------------\n");
    printf("%d %d\n", filas, columnas);

    
    // Problema 3
    printf("Problema 3---------------\n");
    // Reserva de memoria dinamica para una matriz.
    int **matriz = (int **)malloc(filas * sizeof(int *));
    for (int i = 0; i < filas; i++) {
		// A cada fila se le asocia su propio espacio extra para las columnas, por eso queda doble puntero.
        matriz[i] = (int *)malloc(columnas * sizeof(int));
    }
     printf("Matriz Creada\n");
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            fscanf(archivo, "%d", &matriz[i][j]);
            printf("%d ", matriz[i][j]);
            // Lectura a la posicion de la matriz e impresion dentro del mismo for loop
            // Se lee de la misma matriz que genere.
        }
        printf("\n");
    }
    // Como ya guarde los valores, no necesito seguir usando el archivo, se cierra.
    fclose(archivo); 
  
    printf("Se agregaron los datos del archivo a la matriz\n");
    
    // Problema 4
    printf("Problema 4---------------\n");
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    
    // Problema 5
    printf("Problema 5---------------\n");
    printf("Pares Negativos: ");
    mostrarPares(matriz, filas, columnas);
    printf("\n");
    
    // Problema 6
    printf("Problema 6:\n");
    escribirPares(matriz, filas, columnas, nombreSalida);
    printf("Archivo %s con contenido\n", nombreSalida);
    
    // Problema 7
    printf("Problema 7---------------\n");
    printf("Traspuesta\n");
    mostrarTraspuesta(matriz, filas, columnas);
    
    // Problema Bonus
    printf("Problema Bonus---------------\n");
    printf("Matriz ordenada:\n");
    ordenarMatriz(matriz, filas, columnas);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    // Ya se uso la matriz, hay que liberar el espacio declarado.
    for (int i = 0; i < filas; i++) {
        free(matriz[i]);
    }
    free(matriz);
    
    return 0;
}

void mostrarPares(int **matriz, int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (matriz[i][j] < 0 && matriz[i][j] % 2 == 0) {
				// Dentro de la parte del string del printf, se agrega espacio para separar los elementos.
                printf("%d ", matriz[i][j]);
            }
        }
    }
}

void escribirPares(int **matriz, int filas, int columnas, char *nombreSalida) {
	// Error muy comun, el fopen debe ser llamado con un "w" en vez de "r".
	// Si el archivo de salida no existe, "w" lo crea.
    FILE *archivo = fopen(nombreSalida, "w");
    if (archivo == NULL) {
        printf("No se pudo crear el archivo de salida.\n");
        return;
    }

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (matriz[i][j] < 0 && matriz[i][j] % 2 == 0) {
				// Se guarda directamente en el archivo con un espacio.
				// No hay necesidad de guardar memoria para los numeros.
				// Mientras los encuentro los agrego.
                fprintf(archivo, "%d ", matriz[i][j]);
            }
        }
    }
    // se cierra el archivo
    fclose(archivo);
}

void mostrarTraspuesta(int **matriz, int filas, int columnas) {
    for (int j = 0; j < columnas; j++) {
        for (int i = 0; i < filas; i++) {
			// La transpuesta de una matriz es dar vuelta los indices.
			// En vez de dar vuelta la representacion de columnas y filas, se dan vuelta los iteradores.
			// Ahora es j y luego i, asi se da vuelta la matriz.
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void ordenarMatriz(int **matriz, int filas, int columnas) {
	// Se hace un arreglo del size total de la matriz.
    int *array = (int *)malloc(filas * columnas * sizeof(int));
    int indice = 0;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            array[indice++] = matriz[i][j];
        }
    }
    
    // Bubble Sort
    for (int i = 0; i < filas * columnas - 1; i++) {
        for (int j = 0; j < filas * columnas - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                swap(&array[j], &array[j + 1]);
            }
        }
    }
    
    // Se copian los elementos ordenados a la matriz.
    indice = 0;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
			// Aqui cada vez que se llama indice aumentara su valor directamente.
            matriz[i][j] = array[indice++];
        }
    }
    // Ya se uso el array, se libera la memoria.
    free(array);
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
