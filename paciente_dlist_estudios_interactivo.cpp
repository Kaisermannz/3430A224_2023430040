#include <fstream>
#include <iostream>
#include <sstream>
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

void guardarArchivo(const Paciente *head) {
  ofstream archivo("pacientes.csv");

  if (archivo.is_open()) {
    archivo << "Nombre,Edad,Altura,Peso\n";
    const Paciente *current = head;

    while (current != nullptr) {
      archivo << current->nombre << "," << current->edad << ","
              << current->altura << "," << current->peso << "\n";
      current = current->siguiente;
    }
    archivo.close();
    cout << "Datos guardados exitosamente en pacientes.csv" << endl;
  } else {
    cout << "No se pudo abrir el archivo para escribir." << endl;
  }
}

void leerArchivo(Paciente *&head) {
  ifstream archivo("pacientes.csv");
  string linea;

  // Limpiar la lista existente
  while (head != nullptr) {
    Paciente *temp = head;
    head = head->siguiente;
    delete temp;
  }

  if (archivo.is_open()) {
    getline(archivo, linea); // Saltar la primera línea
    while (getline(archivo, linea)) {
      stringstream ss(linea);
      string nombre;
      int edad;
      double altura, peso;

      getline(ss, nombre, ',');
      ss >> edad;
      ss.ignore(); // ignorar la coma
      ss >> altura;
      ss.ignore();
      ss >> peso;

      agregarPaciente(head, nombre, edad, altura, peso);
    }
    archivo.close();
    cout << "Datos cargados exitosamente desde pacientes.csv" << endl;
  } else {
    cout << "No se pudo abrir el archivo para leer." << endl;
  }
}

int main() {
  Paciente *head = nullptr;
  char respuesta;

  while (true) {
    cout << "------------------------------------------------" << endl;
    cout << "         Opciones.          " << endl;
    cout << "1. Agregar un Paciente." << endl;
    cout << "2. Imprimir Pacientes." << endl;
    cout << "3. Borrar un Paciente." << endl;
    cout << "4. Calcular el promedio de peso." << endl;
    cout << "5. Calcular el promedio de edad." << endl;
    cout << "6. Calcular el IMC de un Paciente." << endl;
    cout << "7. Guardar en un archivo de texto." << endl;
    cout << "8. Cargar Pacientes de un archivo .csv" << endl;
    cout << "9. Salir." << endl;
    cout << "------------------------------------------------" << endl;
    cin >> respuesta;

    switch (respuesta) {
    case '1': {
      string nombre;
      int edad;
      double altura;
      double peso;
      cout << "Ingrese el nombre: ";
      cin >> nombre;
      cout << "Ingrese la edad: ";
      cin >> edad;
      cout << "Ingrese la altura en metros: ";
      cin >> altura;
      cout << "Ingrese el peso en Kg: ";
      cin >> peso;
      agregarPaciente(head, nombre, edad, altura, peso);
      break;
    }
    case '2': {
      imprimirPaciente(head);
      break;
    }
    case '3': {
      string nombre;
      cout << "Ingrese el nombre del paciente que desea borrar: ";
      cin >> nombre;
      borrarPaciente(head, nombre);
      cout << nombre << " A sido borrado con exito." << endl;
      break;
    }
    case '4': {
      calcularPromedioPeso(head);
      break;
    }
    case '5': {
      calcularPromedioEdad(head);
      break;
    }
    case '6': {
      calcularIMC(head);
      break;
    }
    case '7': {
      guardarArchivo(head);
      break;
    }
    case '8': {
      leerArchivo(head);
      break;
    }
    case '9': {
      while (head != nullptr) {
        Paciente *temp = head;
        head = head->siguiente;
        delete temp;
      }
      return 0;
    }
    default:
      cout << "Ingrese una opcion valida" << endl;
    }
  }
}
