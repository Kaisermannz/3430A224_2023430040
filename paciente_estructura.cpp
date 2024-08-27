#include <iostream>

using namespace std;

struct Paciente {
  string nombre;
  int edad;
  double altura;
};

int main() {

  Paciente paciente1;

  paciente1.nombre = "Pepe";
  paciente1.edad = 20;
  paciente1.altura = 1.98;

  Paciente paciente2;

  paciente2.nombre = "Rolo";
  paciente2.edad = 2;
  paciente2.altura = 0.30;

  Paciente paciente3;

  paciente3.nombre = "Jack";
  paciente3.edad = 56;
  paciente3.altura = 1.58;

  cout << "el nombre del paciente es: " << paciente1.nombre << "\n";
  cout << "La edad del paciente es: " << paciente1.edad << "\n";
  cout << "La estatura del paciente es: " << paciente1.altura << "cm \n";

  cout << "el nombre del paciente es: " << paciente2.nombre << "\n";
  cout << "La edad del paciente es: " << paciente2.edad << "\n";
  cout << "La estatura del paciente es: " << paciente2.altura << "cm \n";

  cout << "el nombre del paciente es: " << paciente3.nombre << "\n";
  cout << "La edad del paciente es: " << paciente3.edad << "\n";
  cout << "La estatura del paciente es: " << paciente3.altura << "cm \n";
}
