#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

struct Contenedor {
  int numero;
  string empresa;

  Contenedor(int num, string emp) : numero(num), empresa(emp) {}
};

void mostrarPilas(const vector<stack<Contenedor>> &pilas) {
  for (int i = 0; i < pilas.size(); i++) {
    cout << "Pila " << i + 1 << ": ";
    stack<Contenedor> temp = pilas[i];
    while (!temp.empty()) {
      Contenedor c = temp.top();
      cout << "[" << c.numero << "/" << c.empresa << "] ";
      temp.pop();
    }
    cout << endl;
  }
}

// función para retirar un contenedor específico
void retirarContenedor(int numero, const string &empresa,
                       vector<stack<Contenedor>> &pilas) {
  bool encontrado = false;
  for (int i = 0; i < pilas.size(); i++) {
    stack<Contenedor> temp;
    while (!pilas[i].empty()) {
      Contenedor c = pilas[i].top();
      if (c.numero == numero && c.empresa == empresa) {
        cout << "Retirando contenedor [" << c.numero << "/" << c.empresa
             << "] de la pila " << i + 1 << endl;
        pilas[i].pop();
        encontrado = true;
        break;
      } else {
        cout << "Moviendo contenedor [" << c.numero << "/" << c.empresa
             << "] de la pila " << i + 1 << " a una pila temporal." << endl;
        temp.push(c);
        pilas[i].pop();
      }
    }

    // Regresar los contenedores movidos a la pila original
    while (!temp.empty()) {
      pilas[i].push(temp.top());
      temp.pop();
    }

    if (encontrado)
      break;
  }

  if (!encontrado) {
    cout << "Contenedor [" << numero << "/" << empresa << "] no encontrado."
         << endl;
  }
}

int main() {
  int n, m;
  cout << "Ingrese el número de contenedores (n) y el número de pilas (m): ";
  cin >> n >> m;

  vector<stack<Contenedor>> pilas(m);

  for (int i = 0; i < n; i++) {
    int numero;
    string empresa;
    int pilaIndex;
    cout << "Ingrese el número del contenedor y la empresa: ";
    cin >> numero >> empresa;
    cout << "Ingrese el número de la pila (1 a " << m << ") donde colocarlo: ";
    cin >> pilaIndex;
    pilaIndex--; // Ajuste para índice 0
    pilas[pilaIndex].push(Contenedor(numero, empresa));
  }

  cout << "\nEstado inicial de las pilas:\n";
  mostrarPilas(pilas);

  int numero;
  string empresa;
  cout << "\nIngrese el número y la empresa del contenedor a retirar: ";
  cin >> numero >> empresa;

  retirarContenedor(numero, empresa, pilas);

  cout << "\nEstado final de las pilas:\n";
  mostrarPilas(pilas);

  return 0;
}

