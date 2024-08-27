#include <iostream>

using namespace std;

struct Paciente {
  string nombre;
  int edad;
  double altura;
  double peso;
};

int main() {

  Paciente paciente1;

  paciente1.nombre = "Pepe";
  paciente1.edad = 20;
  paciente1.altura = 1.98;
  paciente1.peso = 89.2;
  Paciente paciente2;

  paciente2.nombre = "Rolo";
  paciente2.edad = 2;
  paciente2.altura = 0.30;
  paciente2.peso = 9.2;

  Paciente paciente3;

  paciente3.nombre = "Jack";
  paciente3.edad = 56;
  paciente3.altura = 1.58;
  paciente3.peso = 49.2;

  cout << "el nombre del paciente es: " << paciente1.nombre << "\n";
  cout << "La edad del paciente es: " << paciente1.edad << "\n";
  cout << "La estatura del paciente es: " << paciente1.altura << " cm \n";
  cout << "El peso de la persona es: " << paciente1.peso << " kg \n";

  cout << "el nombre del paciente es: " << paciente2.nombre << "\n";
  cout << "La edad del paciente es: " << paciente2.edad << "\n";
  cout << "La estatura del paciente es: " << paciente2.altura << "cm \n";
  cout << "El peso de la persona es: " << paciente2.peso << " kg \n";

  cout << "el nombre del paciente es: " << paciente3.nombre << "\n";
  cout << "La edad del paciente es: " << paciente3.edad << "\n";
  cout << "La estatura del paciente es: " << paciente3.altura << "cm \n";
  cout << "El peso de la persona es: " << paciente3.peso << " kg \n";
}
