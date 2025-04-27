#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOMBRE 50

// Definición de la estructura
typedef struct {
    int id;
    char nombres[MAX_NOMBRE];
    char apellidos[MAX_NOMBRE];
    float notas[4]; // nota1, nota2, nota3, nota4
    float promedio;
    char estado[10];
} Estudiante;

// Función para calcular el promedio de las notas
float calcularPromedio(float *notas) {
    float suma = 0;
    for (int i = 0; i < 4; i++) {
        suma += *(notas + i);
    }
    return suma / 4;
}

// Función para determinar si aprobó o reprobó
void verificarEstado(float promedio, char *estado) {
    if (promedio >= 60) {
        strcpy(estado, "Aprobado");
    } else {
        strcpy(estado, "Reprobado");
    }
}

int main() {
    int n;
    Estudiante *estudiantes;
    
    printf("Ingrese la cantidad de estudiantes a registrar: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("Número inválido de estudiantes.\n");
        return 1;
    }
    
    // Asignar memoria para los estudiantes
    estudiantes = (Estudiante*)malloc(n * sizeof(Estudiante));
    
    if (estudiantes == NULL) {
        printf("Error al asignar memoria.\n");
        return 1;
    }
    
    // Ingreso de datos
    for (int i = 0; i < n; i++) {
        printf("\nDatos del estudiante %d:\n", i+1);
        
        printf("ID: ");
        scanf("%d", &(estudiantes + i)->id);
        
        printf("Nombres: ");
        scanf(" %[^\n]", (estudiantes + i)->nombres);
        
        printf("Apellidos: ");
        scanf(" %[^\n]", (estudiantes + i)->apellidos);
        
        printf("Nota 1: ");
        scanf("%f", &(estudiantes + i)->notas[0]);
        
        printf("Nota 2: ");
        scanf("%f", &(estudiantes + i)->notas[1]);
        
        printf("Nota 3: ");
        scanf("%f", &(estudiantes + i)->notas[2]);
        
        printf("Nota 4: ");
        scanf("%f", &(estudiantes + i)->notas[3]);
        
        // Calcular promedio y estado
        (estudiantes + i)->promedio = calcularPromedio((estudiantes + i)->notas);
        verificarEstado((estudiantes + i)->promedio, (estudiantes + i)->estado);
    }
    
    // Mostrar resultados
    printf("\nResultados:\n");
    printf("%-5s %-15s %-15s %-7s %-7s %-7s %-7s %-10s %-10s\n", 
           "ID", "Nombres", "Apellidos", "Nota 1", "Nota 2", "Nota 3", "Nota 4", "Promedio", "Estado");
    printf("----------------------------------------------------------------------\n");
    
    for (int i = 0; i < n; i++) {
        printf("%-5d %-15s %-15s %-7.2f %-7.2f %-7.2f %-7.2f %-10.2f %-10s\n",
               (estudiantes + i)->id, 
               (estudiantes + i)->nombres, 
               (estudiantes + i)->apellidos, 
               (estudiantes + i)->notas[0], 
               (estudiantes + i)->notas[1], 
               (estudiantes + i)->notas[2], 
               (estudiantes + i)->notas[3],
               (estudiantes + i)->promedio, 
               (estudiantes + i)->estado);
    }
    
    // Liberar memoria
    free(estudiantes);
    
    return 0;
}
