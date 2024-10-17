#include <climits>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

/*para este codigo me vase en uno que encontre en internet
 "https://www.mycompiler.io/view/JV06mkzT2k9"
 */

class Grafo {
private:
  int numVertices;
  vector<vector<int>> matrizAdyacencia;

public:
  Grafo(int n) : numVertices(n) {
    matrizAdyacencia = vector<vector<int>>(n, vector<int>(n, 0));
  }

  void ingresarPeso(int i, int j, int peso) {
    matrizAdyacencia[i][j] = peso;
    matrizAdyacencia[j][i] = peso; // Grafo no dirigido, matriz simétrica
  }

  void mostrarMatriz() {
    cout << "\nMatriz de adyacencia actual:\n";
    cout << "   ";
    for (int i = 0; i < numVertices; i++) {
      cout << (char)('a' + i) << "  ";
    }
    cout << "\n";

    for (int i = 0; i < numVertices; i++) {
      cout << (char)('a' + i) << "  ";
      for (int j = 0; j < numVertices; j++) {
        cout << matrizAdyacencia[i][j] << "  ";
      }
      cout << "\n";
    }
  }

  void generarGraphvizOriginal() {
    ofstream file("grafo_original.dot");
    file << "graph G {\n";
    file << "graph [rankdir=LR]\n";
    file << "node [style=filled fillcolor=springgreen];\n";

    for (int i = 0; i < numVertices; i++) {
      for (int j = i + 1; j < numVertices; j++) {
        if (matrizAdyacencia[i][j] != 0) {
          file << (char)('a' + i) << " -- " << (char)('a' + j);
          file << " [label=" << matrizAdyacencia[i][j] << "];\n";
        }
      }
    }
    file << "}\n";
    file.close();
  }

  void prim() {
    vector<bool> visitado(numVertices, false);
    vector<int> padre(numVertices, -1);
    vector<int> clave(numVertices, INT_MAX);

    clave[0] = 0;

    cout << "\nConjunto L durante la ejecución:\n";

    for (int i = 0; i < numVertices - 1; i++) {
      int minimo = INT_MAX;
      int u = 0;
      for (int v = 0; v < numVertices; v++) {
        if (!visitado[v] && clave[v] < minimo) {
          minimo = clave[v];
          u = v;
        }
      }

      visitado[u] = true;

      cout << "L = { ";
      for (int j = 0; j < numVertices; j++) {
        if (visitado[j])
          cout << (char)('a' + j) << " ";
      }
      cout << "}\n";

      for (int v = 0; v < numVertices; v++) {
        if (matrizAdyacencia[u][v] && !visitado[v] &&
            matrizAdyacencia[u][v] < clave[v]) {
          padre[v] = u;
          clave[v] = matrizAdyacencia[u][v];
        }
      }
    }

    generarGraphvizResultado(padre);
  }

  void generarGraphvizResultado(const vector<int> &padre) {
    ofstream file("grafo_resultado.dot");
    file << "graph G {\n";
    file << "graph [rankdir=LR]\n";
    file << "node [style=filled fillcolor=springgreen];\n";

    for (int i = 1; i < numVertices; i++) {
      file << (char)('a' + padre[i]) << " -- " << (char)('a' + i);
      file << " [label=" << matrizAdyacencia[padre[i]][i] << "];\n";
    }

    file << "}\n";
    file.close();
  }

  bool todosNodosConectados() {
    for (int i = 0; i < numVertices; i++) {
      bool tieneConexion = false;
      for (int j = 0; j < numVertices; j++) {
        if (i != j && matrizAdyacencia[i][j] != 0) {
          tieneConexion = true;
          break;
        }
      }
      if (!tieneConexion)
        return false;
    }
    return true;
  }
};

int main() {
  int N;
  cout << "Ingrese el número de nodos (N > 2): ";
  cin >> N;

  if (N <= 2) {
    cout << "El número de nodos debe ser mayor a 2" << endl;
    return 1;
  }

  Grafo g(N);
  int opcion;

  while (true) {
    cout << "\n    ======= MENÚ =========       \n";
    cout << "1. Ingresar peso entre dos nodos\n";
    cout << "2. Mostrar matriz actual\n";
    cout << "3. Ejecutar algoritmo de Prim\n";
    cout << "4. Salir\n";
    cout << "   Ingrese su opción: ";
    cin >> opcion;

    switch (opcion) {
    case 1: {
      char nodo1, nodo2;
      int peso;
      cout << "Ingrese primer nodo (a-" << (char)('a' + N - 1) << "): ";
      cin >> nodo1;
      cout << "Ingrese segundo nodo (a-" << (char)('a' + N - 1) << "): ";
      cin >> nodo2;
      cout << "Ingrese peso de la conexión: ";
      cin >> peso;

      if (nodo1 < 'a' || nodo1 >= 'a' + N || nodo2 < 'a' || nodo2 >= 'a' + N) {
        cout << "Nodos inválidos!\n";
        break;
      }

      g.ingresarPeso(nodo1 - 'a', nodo2 - 'a', peso);
      break;
    }
    case 2:
      g.mostrarMatriz();
      break;
    case 3: {
      if (!g.todosNodosConectados()) {
        cout << "Error: El grafo debe estar conectado para ejecutar Prim\n";
        break;
      }
      g.generarGraphvizOriginal();
      g.prim();

      // comandos de Graphviz
      system("dot -Tpng grafo_original.dot -o grafo_original.png");
      system("dot -Tpng grafo_resultado.dot -o grafo_resultado.png");
      system("eog grafo_original.png &");
      system("eog grafo_resultado.png &");

      cout << "\nSe han generado las imágenes:\n";
      break;
    }
    case 4:
      return 0;
    default:
      cout << "Opción inválida\n";
    }
  }

  return 0;
}
