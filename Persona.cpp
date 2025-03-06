#include <iostream>
using namespace std;
class Persona{
	// definimos atributos
	protected :
		string nombres,apellidos,direccion,fecha_nacimiento;
		int telefono;
		
	// Creamos los métodos 1.) Constructor
	protected:
		Persona(){
		}
		Persona(string nom,string ape, string dir, int tel, string fn){
			nombres = nom;
			apellidos = ape;
			direccion = dir;
			telefono = tel;
			fecha_nacimiento = fn;
		}
	// Creamos los métodos  2.) CRUD
	void crear();
	void leer();
	void actualizar();
	void borrar();
};

