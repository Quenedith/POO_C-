#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <limits>

using namespace std;

const string ARCHIVO_DATOS = "notas.dat";

// Definición de la estructura
struct Estudiante {
    int id;
    char nombres[50];
    char apellidos[50];
    float notas[4];
    float promedio;
    char resultado[10];
};

// Prototipos de funciones
void crearEstudiante();
void mostrarEstudiantes();
void buscarEstudiantePorId();
void actualizarEstudiante();
void eliminarEstudiante();

// Funciones auxiliares
float calcularPromedio(const float notas[4]);
void verificarResultado(float promedio, char* resultado);
bool existeId(int id);
void mostrarMenuPrincipal();
void limpiarPantalla();
void pausar();

int main() {
    int opcion;
    do {
        mostrarMenuPrincipal();
        cout << "Ingrese su opción: ";
        cin >> opcion;
        
        switch (opcion) {
            case 1: crearEstudiante(); break;
            case 2: mostrarEstudiantes(); break;
            case 3: buscarEstudiantePorId(); break;
            case 4: actualizarEstudiante(); break;
            case 5: eliminarEstudiante(); break;
            case 0: cout << "Saliendo del programa..." << endl; break;
            default: cout << "Opción inválida. Intente de nuevo." << endl;
        }

        if (opcion != 0) {
            pausar();
        }

    } while (opcion != 0);
    return 0;
}

void mostrarMenuPrincipal() {
    limpiarPantalla();
    cout << "=== SISTEMA DE GESTIÓN DE ESTUDIANTES ===" << endl;
    cout << "1. Registrar nuevo estudiante" << endl;
    cout << "2. Mostrar todos los estudiantes" << endl;
    cout << "3. Buscar estudiante por ID" << endl;
    cout << "4. Actualizar datos de estudiante" << endl;
    cout << "5. Eliminar estudiante" << endl;
    cout << "0. Salir" << endl;
}

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausar() {
    cout << "\nPresione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

float calcularPromedio(const float notas[4]) {
    float suma = 0;
    for (int i = 0; i < 4; i++) {
        suma += notas[i];
    }
    return suma / 4;
}

void verificarResultado(float promedio, char* resultado) {
    if (promedio >= 60) {
        strcpy(resultado, "Aprobado");
    } else {
        strcpy(resultado, "Reprobado");
    }
}

bool existeId(int id) {
    ifstream archivo(ARCHIVO_DATOS, ios::binary);
    if (!archivo) {
        return false;
    }

    Estudiante estudiante;
    while (archivo.read(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante))) {
        if (estudiante.id == id) {
            archivo.close();
            return true;
        }
    }

    archivo.close();
    return false;
}

void crearEstudiante() {
    int n;
    cout << "Ingrese la cantidad de estudiantes a registrar: ";
    cin >> n;

    if (n <= 0) {
        cout << "Número inválido de estudiantes." << endl;
        return;
    }

    Estudiante* estudiantes = new Estudiante[n];

    for (int i = 0; i < n; i++) {
        cout << "\nDatos del estudiante " << i + 1 << ":" << endl;

        do {
            cout << "ID: ";
            cin >> estudiantes[i].id;
            if (existeId(estudiantes[i].id)) {
                cout << "Error: El ID ya existe. Ingrese otro ID." << endl;
            }
        } while (existeId(estudiantes[i].id));

        cin.ignore();

        cout << "Nombres: ";
        cin.getline(estudiantes[i].nombres, 50);

        cout << "Apellidos: ";
        cin.getline(estudiantes[i].apellidos, 50);

        cout << "Nota 1: "; cin >> estudiantes[i].notas[0];
        cout << "Nota 2: "; cin >> estudiantes[i].notas[1];
        cout << "Nota 3: "; cin >> estudiantes[i].notas[2];
        cout << "Nota 4: "; cin >> estudiantes[i].notas[3];

        estudiantes[i].promedio = calcularPromedio(estudiantes[i].notas);
        verificarResultado(estudiantes[i].promedio, estudiantes[i].resultado);
    }

    // Guardar en el archivo binario
    ofstream archivo(ARCHIVO_DATOS, ios::binary | ios::app);
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        delete[] estudiantes;
        return;
    }

    archivo.write(reinterpret_cast<char*>(estudiantes), sizeof(Estudiante) * n);
    archivo.close();

    cout << "\nEstudiantes registrados exitosamente!" << endl;

    delete[] estudiantes;
}

void mostrarEstudiantes() {
    ifstream archivo(ARCHIVO_DATOS, ios::binary);
    if (!archivo) {
        cout << "No hay estudiantes registrados o error al abrir el archivo." << endl;
        return;
    }

    Estudiante estudiante;
    cout << "\n=== LISTA DE ESTUDIANTES ===" << endl;
    cout << left << setw(5) << "ID"
         << setw(15) << "Nombres"
         << setw(15) << "Apellidos"
         << setw(7) << "Nota1"
         << setw(7) << "Nota2"
         << setw(7) << "Nota3"
         << setw(7) << "Nota4"
         << setw(10) << "Promedio"
         << setw(10) << "Resultado" << endl;
    cout << "-------------------------------------------------------------------------------------------" << endl;

    while (archivo.read(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante))) {
        cout << left << setw(5) << estudiante.id
             << setw(15) << estudiante.nombres
             << setw(15) << estudiante.apellidos
             << fixed << setprecision(2)
             << setw(7) << estudiante.notas[0]
             << setw(7) << estudiante.notas[1]
             << setw(7) << estudiante.notas[2]
             << setw(7) << estudiante.notas[3]
             << setw(10) << estudiante.promedio
             << setw(10) << estudiante.resultado << endl;
    }

    archivo.close();
}

void buscarEstudiantePorId() {
    int id;
    cout << "Ingrese el ID del estudiante a buscar: ";
    cin >> id;

    ifstream archivo(ARCHIVO_DATOS, ios::binary);
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    Estudiante estudiante;
    bool encontrado = false;

    while (archivo.read(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante))) {
        if (estudiante.id == id) {
            cout << "\n=== DATOS DEL ESTUDIANTE ===" << endl;
            cout << "ID: " << estudiante.id << endl;
            cout << "Nombres: " << estudiante.nombres << endl;
            cout << "Apellidos: " << estudiante.apellidos << endl;
            cout << fixed << setprecision(2);
            cout << "Notas: " << estudiante.notas[0] << ", " << estudiante.notas[1]
                 << ", " << estudiante.notas[2] << ", " << estudiante.notas[3] << endl;
            cout << "Promedio: " << estudiante.promedio << endl;
            cout << "Resultado: " << estudiante.resultado << endl;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "No se encontró un estudiante con el ID ingresado." << endl;
    }

    archivo.close();
}

void actualizarEstudiante() {
    int id;
    cout << "Ingrese el ID del estudiante a actualizar: ";
    cin >> id;

    fstream archivo(ARCHIVO_DATOS, ios::binary | ios::in | ios::out);
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    Estudiante estudiante;
    bool encontrado = false;

    while (archivo.read(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante))) {
        if (estudiante.id == id) {
            cout << "Ingrese los nuevos datos:" << endl;

            cin.ignore();
            cout << "Nombres: ";
            cin.getline(estudiante.nombres, 50);
            cout << "Apellidos: ";
            cin.getline(estudiante.apellidos, 50);
            cout << "Nota 1: "; cin >> estudiante.notas[0];
            cout << "Nota 2: "; cin >> estudiante.notas[1];
            cout << "Nota 3: "; cin >> estudiante.notas[2];
            cout << "Nota 4: "; cin >> estudiante.notas[3];

            estudiante.promedio = calcularPromedio(estudiante.notas);
            verificarResultado(estudiante.promedio, estudiante.resultado);

            archivo.seekp(-static_cast<int>(sizeof(Estudiante)), ios::cur);
            archivo.write(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante));
            encontrado = true;
            cout << "Estudiante actualizado exitosamente!" << endl;
            break;
        }
    }

    if (!encontrado) {
        cout << "No se encontró un estudiante con el ID ingresado." << endl;
    }

    archivo.close();
}

void eliminarEstudiante() {
    int id;
    cout << "Ingrese el ID del estudiante a eliminar: ";
    cin >> id;

    ifstream archivoEntrada(ARCHIVO_DATOS, ios::binary);
    if (!archivoEntrada) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    ofstream archivoTemp("temp.dat", ios::binary);
    if (!archivoTemp) {
        cout << "Error al crear archivo temporal." << endl;
        archivoEntrada.close();
        return;
    }

    Estudiante estudiante;
    bool encontrado = false;

    while (archivoEntrada.read(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante))) {
        if (estudiante.id != id) {
            archivoTemp.write(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante));
        } else {
            encontrado = true;
        }
    }

    archivoEntrada.close();
    archivoTemp.close();

    remove(ARCHIVO_DATOS.c_str());
    rename("temp.dat", ARCHIVO_DATOS.c_str());

    if (encontrado) {
        cout << "Estudiante eliminado exitosamente!" << endl;
    } else {
        cout << "No se encontró un estudiante con el ID ingresado." << endl;
    }
}

