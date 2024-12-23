#include <iostream>

using namespace std;

struct Paciente {
  string nombre;
  int edad;
  double altura;
  double peso;
};

int main() {

  Paciente pacientes[5];

  pacientes[0].nombre = "Lorena";
  pacientes[0].edad = 30;
  pacientes[0].altura = 1.41;
  pacientes[0].peso = 50.4;

  pacientes[1].nombre = "Tony";
  pacientes[1].edad = 32;
  pacientes[1].altura = 2.1;
  pacientes[1].peso = 76.4;

  pacientes[2].nombre = "Panita";
  pacientes[2].edad = 89;
  pacientes[2].altura = 1.91;
  pacientes[2].peso = 53.4;

  pacientes[3].nombre = "Pablo";
  pacientes[3].edad = 29;
  pacientes[3].altura = 1.67;
  pacientes[3].peso = 75.4;

  pacientes[4].nombre = "Emme Kid";
  pacientes[4].edad = 20;
  pacientes[4].altura = 1.65;
  pacientes[4].peso = 65.4;

  for (int i = 0; i < 5; ++i) {
    cout << "Nombre: " << pacientes[i].nombre << "\n";
    cout << "Edad: " << pacientes[i].edad << "\n";
    cout << "Altura: " << pacientes[i].altura << "cm \n";
    cout << "Peso: " << pacientes[i].peso << "kg \n";
    cout << "\n";
  }
}
