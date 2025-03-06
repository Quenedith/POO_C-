#include "Cliente.cpp"
#include <iostream>
using namespace std;
main(){
	string nit,nombres,apellidos,direccion,fecha_nacimiento;
	int telefono;
	cout<<"Ingrese Nit: ";
	cin>>nit;
	cout<<"Ingrese nombres: ";
	cin>>nombres;
	cout<<"Ingrese apellidos: ";
	cin>>apellidos;
	cout<<"Ingrese direccion: ";
	cin>>direccion;
	cout<<"Ingrese Fecha de nacimiento: ";
	cin>>fecha_nacimiento;
	cout<<"Ingrese Telefono: ";
	cin>>telefono;
	// Instanciamos la clase (se puede poner el mismo nombre de la clase pero con minúscula)
	Cliente obj = Cliente (nombres,apellidos,direccion,telefono,fecha_nacimiento,nit);
	obj.leer();
}

