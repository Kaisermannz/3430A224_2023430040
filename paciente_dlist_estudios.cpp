#include <iostream>
#include <string>

using namespace std;

struct Paciente {
  string nombre;
  int edad;
  double altura;
  double peso;
  Paciente *siguiente; // Puntero hacia la siguiente persona
};

void borrarPaciente(Paciente *&head, const string &nombre) {
  Paciente *current = head;
  Paciente *previous = nullptr;

  while (current != nullptr && current->nombre != nombre) {
    previous = current;
    current = current->siguiente;
  }

  if (current != nullptr) {
    if (previous == nullptr) {
      head = current->siguiente;
    } else {
      previous->siguiente = current->siguiente;
    }
    delete current;
  }
}

void agregarPaciente(Paciente *&head, const string &nombre, int edad,
                     double altura, double peso) {
  Paciente *nuevoPaciente = new Paciente();
  nuevoPaciente->nombre = nombre;
  nuevoPaciente->edad = edad;
  nuevoPaciente->altura = altura;
  nuevoPaciente->peso = peso;
  nuevoPaciente->siguiente = head;
  head = nuevoPaciente; // Al agregar el nuevo paciente al head esta lista se
                        // comporta como pila
}

void imprimirPaciente(const Paciente *head) {
  const Paciente *current = head;
  while (current != nullptr) {
    cout << current->nombre << " Tiene " << current->edad << " años, mide "
         << current->altura << " metros y pesa " << current->peso << " Kg."
         << endl;
    current = current->siguiente;
  }
}

double calcularPromedioPeso(const Paciente *head) {
  const Paciente *current = head;
  double sumaPeso = 0, nPacientes = 0;

  while (current != nullptr) {
    sumaPeso = sumaPeso + current->peso;
    nPacientes += 1;
    current = current->siguiente;
  }

  if (nPacientes == 0) {
    return 0; // Evita la división por cero
  }

  double promedioPeso = sumaPeso / nPacientes;

  cout << "Promedio de peso de los pacientes: " << promedioPeso << endl;

  return promedioPeso;
}

double calcularPromedioEdad(const Paciente *head) {
  const Paciente *current = head;
  int sumaEdad = 0, nPacientes = 0;

  while (current != nullptr) {
    sumaEdad = sumaEdad + current->edad;
    nPacientes += 1;
    current = current->siguiente;
  }

  if (nPacientes == 0) {
    return 0; // Evita la división por cero
  }

  int promedioEdad = sumaEdad / nPacientes;

  cout << "Promedio de edad de los pacientes: " << promedioEdad << endl;

  return promedioEdad;
}

void calcularIMC(const Paciente *head) {
  const Paciente *current = head;
  double peso = 0, altura = 0, imc = 0;

  while (current != nullptr) {
    peso = current->peso;
    altura = current->altura;

    imc = peso / (altura * altura);

    cout << "El IMC de " << current->nombre << " es de: " << imc;

    if (imc <= 18.5) {
      cout << ", Lo cual indica Bajo peso" << endl;
    } else if (imc > 18.5 && imc < 24.9) {
      cout << ", Lo cual indica Peso normal" << endl;
    } else if (imc >= 25.0 && imc < 29.9) {
      cout << ", Lo cual indica Sobre peso" << endl;
    } else {
      cout << ", Lo cual indica Obesidad" << endl;
    }

    current = current->siguiente;
  }
}

int main() {
  Paciente *head = nullptr;

  agregarPaciente(head, "Kakashi", 27, 1.83, 102.5);
  agregarPaciente(head, "Shikamaru", 20, 1.75, 50.0);
  agregarPaciente(head, "Ino", 19, 1.62, 48.7);
  agregarPaciente(head, "Neji", 20, 1.77, 67.4);
  agregarPaciente(head, "Gaara", 19, 1.66, 50.3);
  agregarPaciente(head, "Rock Lee", 20, 1.72, 94.8);
  agregarPaciente(head, "Temari", 22, 1.70, 53.9);

  imprimirPaciente(head);
  cout << "\n";
  calcularPromedioPeso(head);
  cout << "\n";
  calcularPromedioEdad(head);
  cout << "\n";
  calcularIMC(head);

  // recorre la lista enlazada desde la cabeza hasta el final limpiandola
  while (head != nullptr) {
    Paciente *temp = head;
    head = head->siguiente;
    delete temp;
  }
  return 0;
}
