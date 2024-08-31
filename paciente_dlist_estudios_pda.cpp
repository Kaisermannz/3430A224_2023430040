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
  double imc;
  double a1c;
  int prioridad;
  Paciente *siguiente;
};

void calcularIMC(Paciente *paciente) {
  paciente->imc = paciente->peso / (paciente->altura * paciente->altura);
}

void calcularPrioridad(Paciente *paciente) {
  // Se calcula la prioridad del paciente usando una combinación ponderada de
  // IMC, A1C y Edad.

  // paciente->imc * 2: se multiplica el IMC por 2, lo que indica que se le da
  // un peso significativo a este factor, ya que es un buen indicador de
  // posibles problemas de salud relacionados con el peso.

  // paciente->a1c * 1.2: se multiplica el valor de A1C (un indicador importante
  // del control de la glucosa en sangre) por 1.2, lo que le da menos prioridad
  // que el IMC, pero sigue siendo relevante para pacientes con problemas de
  // azúcar en sangre como la diabetes.

  // paciente->edad * 0.8: la edad se multiplica por 0.8, asignándole la menor
  // prioridad en comparación con el IMC y el A1C. la razon de esto es que,
  // aunque la edad es un factor de riesgo, no es tan determinante como el
  // estado actual del IMC o el A1C para la atención inmediata.

  paciente->prioridad =
      (int)(paciente->imc * 2 + paciente->a1c * 1.2 + paciente->edad * 0.8);
}

void agregarPaciente(Paciente *&head, const string &nombre, int edad,
                     double altura, double peso, double a1c) {
  Paciente *nuevoPaciente = new Paciente();
  nuevoPaciente->nombre = nombre;
  nuevoPaciente->edad = edad;
  nuevoPaciente->altura = altura;
  nuevoPaciente->peso = peso;
  nuevoPaciente->a1c = a1c;
  calcularIMC(nuevoPaciente);
  calcularPrioridad(nuevoPaciente);
  nuevoPaciente->siguiente = head;
  head = nuevoPaciente;
}

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
    cout << nombre << " ha sido borrado con éxito." << endl;
  } else {
    cout << "Paciente no encontrado." << endl;
  }
}

void imprimirPacientes(const Paciente *head) {
  const Paciente *current = head;
  while (current != nullptr) {
    cout << current->nombre << " - Edad: " << current->edad
         << ", Altura: " << current->altura << "m, Peso: " << current->peso
         << "Kg, IMC: " << current->imc << ", A1C: " << current->a1c
         << ", Prioridad: " << current->prioridad << endl;
    current = current->siguiente;
  }
}

double calcularPromedioPeso(const Paciente *head) {
  const Paciente *current = head;
  double sumaPeso = 0;
  int nPacientes = 0;

  while (current != nullptr) {
    sumaPeso += current->peso;
    nPacientes++;
    current = current->siguiente;
  }

  if (nPacientes == 0)
    return 0;
  return sumaPeso / nPacientes;
}

double calcularPromedioEdad(const Paciente *head) {
  const Paciente *current = head;
  int sumaEdad = 0;
  int nPacientes = 0;

  while (current != nullptr) {
    sumaEdad += current->edad;
    nPacientes++;
    current = current->siguiente;
  }

  if (nPacientes == 0)
    return 0;
  return (double)sumaEdad / nPacientes;
}

void buscarPorIMC(const Paciente *head, double imcMin, double imcMax) {
  const Paciente *current = head;
  while (current != nullptr) {
    if (current->imc >= imcMin && current->imc <= imcMax) {
      cout << current->nombre << " - IMC: " << current->imc << endl;
    }
    current = current->siguiente;
  }
}

void buscarPorA1C(const Paciente *head, double a1cMin, double a1cMax) {
  const Paciente *current = head;
  while (current != nullptr) {
    if (current->a1c >= a1cMin && current->a1c <= a1cMax) {
      cout << current->nombre << " - A1C: " << current->a1c << endl;
    }
    current = current->siguiente;
  }
}

void guardarArchivo(const Paciente *head) {
  ofstream archivo("pacientes.csv");
  if (archivo.is_open()) {
    archivo << "Nombre,Edad,Altura,Peso,IMC,A1C,Prioridad\n";
    const Paciente *current = head;
    while (current != nullptr) {
      archivo << current->nombre << "," << current->edad << ","
              << current->altura << "," << current->peso << "," << current->imc
              << "," << current->a1c << "," << current->prioridad << "\n";
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
      double altura, peso, imc, a1c;
      int prioridad;

      getline(ss, nombre, ',');
      ss >> edad;
      ss.ignore();
      ss >> altura;
      ss.ignore();
      ss >> peso;
      ss.ignore();
      ss >> imc;
      ss.ignore();
      ss >> a1c;
      ss.ignore();
      ss >> prioridad;

      agregarPaciente(head, nombre, edad, altura, peso, a1c);
    }
    archivo.close();
    cout << "Datos cargados exitosamente desde pacientes.csv" << endl;
  } else {
    cout << "No se pudo abrir el archivo para leer." << endl;
  }
}

void atenderPacientesPrioritarios(Paciente *&head, int numPacientes) {
  for (int i = 0; i < numPacientes; i++) {
    if (head == nullptr) {
      cout << "No hay más pacientes en la lista de espera." << endl;
      return;
    }

    Paciente *maxPrioridad = head;
    Paciente *current = head->siguiente;
    Paciente *prevMax = nullptr;
    Paciente *prev = head;

    while (current != nullptr) {
      if (current->prioridad > maxPrioridad->prioridad) {
        maxPrioridad = current;
        prevMax = prev;
      }
      prev = current;
      current = current->siguiente;
    }

    if (prevMax == nullptr) {
      head = head->siguiente;
    } else {
      prevMax->siguiente = maxPrioridad->siguiente;
    }

    cout << "Atendiendo a " << maxPrioridad->nombre
         << " (Prioridad: " << maxPrioridad->prioridad << ")" << endl;
    delete maxPrioridad;
  }
}

int main() {
  Paciente *head = nullptr;
  int respuesta;

  while (true) {
    cout << "------------------------------------------------" << endl;
    cout << "         Opciones.          " << endl;
    cout << "1. Agregar un Paciente." << endl;
    cout << "2. Imprimir Pacientes." << endl;
    cout << "3. Borrar un Paciente." << endl;
    cout << "4. Calcular el promedio de peso." << endl;
    cout << "5. Calcular el promedio de edad." << endl;
    cout << "6. Guardar en un archivo CSV." << endl;
    cout << "7. Cargar Pacientes de un archivo CSV." << endl;
    cout << "8. Buscar por IMC." << endl;
    cout << "9. Buscar por A1C." << endl;
    cout << "10. Atender pacientes prioritarios." << endl;
    cout << "11. Salir." << endl;
    cout << "------------------------------------------------" << endl;
    cin >> respuesta;

    switch (respuesta) {
    case 1: {
      string nombre;
      int edad;
      double altura, peso, a1c;
      cout << "Ingrese el nombre: ";
      cin >> nombre;
      cout << "Ingrese la edad: ";
      cin >> edad;
      cout << "Ingrese la altura en metros: ";
      cin >> altura;
      cout << "Ingrese el peso en Kg: ";
      cin >> peso;
      cout << "Ingrese el A1C: ";
      cin >> a1c;
      agregarPaciente(head, nombre, edad, altura, peso, a1c);
      break;
    }
    case 2: {
      imprimirPacientes(head);
      break;
    }
    case 3: {
      string nombre;
      cout << "Ingrese el nombre del paciente que desea borrar: ";
      cin >> nombre;
      borrarPaciente(head, nombre);
      break;
    }
    case 4: {
      double promedioPeso = calcularPromedioPeso(head);
      cout << "El promedio de peso de los pacientes es: " << promedioPeso
           << " Kg" << endl;
      break;
    }
    case 5: {
      double promedioEdad = calcularPromedioEdad(head);
      cout << "El promedio de edad de los pacientes es: " << promedioEdad
           << " años" << endl;
      break;
    }
    case 6: {
      guardarArchivo(head);
      break;
    }
    case 7: {
      leerArchivo(head);
      break;
    }
    case 8: {
      double imcMin, imcMax;
      cout << "Ingrese el IMC mínimo: ";
      cin >> imcMin;
      cout << "Ingrese el IMC máximo: ";
      cin >> imcMax;
      buscarPorIMC(head, imcMin, imcMax);
      break;
    }
    case 9: {
      double a1cMin, a1cMax;
      cout << "Ingrese el A1C mínimo: ";
      cin >> a1cMin;
      cout << "Ingrese el A1C máximo: ";
      cin >> a1cMax;
      buscarPorA1C(head, a1cMin, a1cMax);
      break;
    }
    case 10: {
      int numPacientes;
      cout << "Ingrese el número de pacientes a atender: ";
      cin >> numPacientes;
      atenderPacientesPrioritarios(head, numPacientes);
      break;
    }
    case 11: {
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
