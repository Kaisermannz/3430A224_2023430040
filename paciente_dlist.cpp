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
  // La función borrarPaciente recorre la lista enlazada buscando un nodo con un
  // nombre específico. Si lo encuentra, ajusta los punteros correspondientes
  // para eliminar ese nodo de la lista y libera la memoria asociada a él. Si el
  // nodo a eliminar es la cabeza de la lista, actualiza head para apuntar al
  // siguiente nodo.
}

void agregarPaciente(Paciente *&head, const string &nombre, int edad,
                     double altura, double peso) {
  Paciente *nuevoPaciente = new Paciente();
  nuevoPaciente->nombre = nombre;
  nuevoPaciente->edad = edad;
  nuevoPaciente->altura = altura;
  nuevoPaciente->peso = peso;
  nuevoPaciente->siguiente = head;
  head = nuevoPaciente;
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

int main() {
  Paciente *head = nullptr;

  agregarPaciente(head, "Naruto", 20, 1.74, 75.6);
  agregarPaciente(head, "Sasuke", 21, 1.94, 95.3);
  agregarPaciente(head, "Sakura", 19, 1.64, 40.3);

  imprimirPaciente(head);

  borrarPaciente(head, "Naruto");
  borrarPaciente(head, "Sakura");
  cout << "\n";
  imprimirPaciente(head);

  // recorre la lista enlazada desde la cabeza hasta el final limpiandola
  while (head != nullptr) {
    Paciente *temp = head;
    head = head->siguiente;
    delete temp;
  }
  return 0;
}
