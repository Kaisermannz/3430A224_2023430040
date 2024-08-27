#include <iostream>

using namespace std;

struct Paciente {
  string nombre;
  int edad;
  double altura;
};

int main() {
  cout << "Hola mundo\n";

  Paciente paciente1;
  // Paciente paciente2;
  // Paciente paciente3;

  paciente1.nombre = "pepe";
  paciente1.edad = 20;
  paciente1.altura = 1.98;

  cout << "el nombre del paciente es: " << paciente1.nombre << "\n";
  cout << "La edad del paciente es: " << paciente1.edad << "\n";
  cout << "La estatura del paciente es: " << paciente1.altura << "\n";
}
