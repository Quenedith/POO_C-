#include <iostream>
#include "Persona.cpp"
using namespace std;
// Se ponen dos puntos indicando que la clase Cliente hereda de la clase Persona
class Cliente : Persona{
			// Atributos
			private :
				string nit;
			// Metodos constructor, get set, crud
			public :
				Cliente(){
				}
				Cliente(string nom,string ape,string dir,int tel,string fn, string n) : Persona(nom,ape,dir,tel,fn){
					nit = n;
				}
				// set (modificar)
				void setNit(string n){
					nit = n;
				}
				void setNombres(string nom){
					nombres = nom;
				}
				void setApellidos(string ape){
					apellidos = ape;
				}
				void setDireccion(string dir){
					direccion = dir;
				}
				void setTelefono(int tel){
					telefono = tel;
				}
				void setFechaNacimiento(string fn){
					fecha_nacimiento = fn;
				}
				// get (mostrar)
				string getNit(){
					return nit;
				}
				string getNombres(){
					return nombres;
				}
				string getApellidos(){
					return apellidos;
				}
				string getDireccion(){
					return direccion;
				}
				int getTelefono(){
					return telefono;
				}
				string getFechaNacimiento(){
					return fecha_nacimiento;
				}
				// Creamos el método para mostrar la información
				void leer(){
					cout<<"Nit: "<<nit<<endl;
					cout<<"Nombres: "<<nombres<<endl;
					cout<<"Apellidos : "<<apellidos<<endl;
					cout<<"Direccion: "<<direccion<<endl;
					cout<<"Telefono: "<<telefono<<endl;
					cout<<"Fecha de nacimiento: "<<fecha_nacimiento<<endl;
				}
};

