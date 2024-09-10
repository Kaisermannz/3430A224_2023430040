#include <iostream>
#include <stack>

using namespace std;

int main() {
  stack<int> stack;
  int n, opcion, respuesta;

  cout << "Ingrese el numero de elementos que puede tener la pila: ";
  cin >> n;

  while (true) {
    cout << "----------------------------" << endl;
    cout << "         opciones       " << endl;
    cout << "1. Push (agregar)." << endl;
    cout << "2. Pop (eliminar elemento)." << endl;
    cout << "3. Imprimir Pila." << endl;
    cout << "4. Salir." << endl;
    cout << "----------------------------" << endl;
    cin >> opcion;

    switch (opcion) {
    case 1: {
      if (stack.size() < n) {
        cout << "Ingresa un valor para agregar a la pila: ";
        cin >> respuesta;
        stack.push(respuesta);
        cout << "Elemento " << respuesta << " agregado a la pila.\n";
      } else {
        cout << "La pila está llena. No se puede agregar más elementos.\n";
      }
      break;
    }
    case 2: {
      if (!stack.empty()) {
        cout << "Elemento " << stack.top() << " eliminado de la pila.\n";
        stack.pop();
      } else {
        cout << "La pila está vacía. No se puede eliminar ningún elemento.\n";
      }
      break;
    }
    case 3: {
      if (!stack.empty()) {
        cout << "Elementos en la pila: ";
        std::stack<int> temp = stack; // copia de la pila para imprimir
        while (!temp.empty()) {
          cout << temp.top() << " ";
          temp.pop();
        }
        cout << endl;
      } else {
        cout << "La pila está vacía.\n";
      }
      break;
    }
    case 4: {
      cout << "Saliendo del programa.\n";
      return 0;
    }
    default:
      cout << "Opción no válida. Inténtalo de nuevo.\n";
    }
  }

  return 0;
}
