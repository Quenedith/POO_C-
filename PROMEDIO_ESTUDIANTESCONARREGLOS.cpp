#include <stdio.h>
#include <string.h>

#define MAX_ESTUDIANTES 100
#define MAX_NOMBRE 50

// Función para calcular el promedio de las notas
float calcularPromedio(float notas[4]) {
    float suma = 0;
    for (int i = 0; i < 4; i++) {
        suma += notas[i];
    }
    return suma / 4;
}

// Función para determinar si aprobó o reprobó - versión corregida
void verificarEstado(float promedio, char* estado) {
    if (promedio >= 60) {
        strcpy(estado, "Aprobado");
    } else {
        strcpy(estado, "Reprobado");
    }
}

int main() {
    int n, ids[MAX_ESTUDIANTES];
    char nombres[MAX_ESTUDIANTES][MAX_NOMBRE];
    char apellidos[MAX_ESTUDIANTES][MAX_NOMBRE];
    float notas[MAX_ESTUDIANTES][4]; // nota1, nota2, nota3, nota4
    float promedios[MAX_ESTUDIANTES];
    char estados[MAX_ESTUDIANTES][10];
    
    printf("Ingrese la cantidad de estudiantes a registrar: ");
    scanf("%d", &n);
    
    if (n > MAX_ESTUDIANTES || n <= 0) {
        printf("Número inválido de estudiantes. Debe estar entre 1 y %d.\n", MAX_ESTUDIANTES);
        return 1;
    }
    
    // Ingreso de datos
    for (int i = 0; i < n; i++) {
        printf("\nDatos del estudiante %d:\n", i+1);
        
        printf("ID: ");
        scanf("%d", &ids[i]);
        
        printf("Nombres: ");
        scanf(" %[^\n]", nombres[i]);
        
        printf("Apellidos: ");
        scanf(" %[^\n]", apellidos[i]);
        
        printf("Nota 1: ");
        scanf("%f", &notas[i][0]);
        
        printf("Nota 2: ");
        scanf("%f", &notas[i][1]);
        
        printf("Nota 3: ");
        scanf("%f", &notas[i][2]);
        
        printf("Nota 4: ");
        scanf("%f", &notas[i][3]);
        
        // Calcular promedio y estado - versión corregida
        promedios[i] = calcularPromedio(notas[i]);
        verificarEstado(promedios[i], estados[i]);
    }
    
    // Mostrar resultados
    printf("\nResultados:\n");
    printf("%-5s %-15s %-15s %-7s %-7s %-7s %-7s %-10s %-10s\n", 
           "ID", "Nombres", "Apellidos", "Nota 1", "Nota 2", "Nota 3", "Nota 4", "Promedio", "Estado");
    printf("----------------------------------------------------------------------\n");
    
    for (int i = 0; i < n; i++) {
        printf("%-5d %-15s %-15s %-7.2f %-7.2f %-7.2f %-7.2f %-10.2f %-10s\n",
               ids[i], nombres[i], apellidos[i], 
               notas[i][0], notas[i][1], notas[i][2], notas[i][3],
               promedios[i], estados[i]);
    }
    
    return 0;
}
