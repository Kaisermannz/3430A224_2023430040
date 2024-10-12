#include <fstream>
#include <iostream>
#include <ostream>

#define TRUE 0
#define FALSE 0
#define N 5

using namespace std;

void inicializarVectorD(int D[N], int M[N][N]);
void inicializarVectorCaracter(char vector[N]);
int buscarIndiceCaracter(char V[N], char caracter);
int calcularMinimo(int dw, int dv, int mvw);
void actualizarPesos(int D[N], char VS[N], int M[N][N], char V[N], char v);
void agregarVerticeHaciaS(char S[N], char vertice);
int elegirVertice(char VS[N], int D[N], char V[N]);
int buscaCaracter(char c, char vector[N]);
void actualizarVS(char V[N], char S[N], char VS[N]);
void leerNodos(char vector[N]);
void imprimirVectorCaracter(char vector[N], char *nomVector);
void imprimirVectorEntero(int vector[N]);
void imprimirMatriz(int matriz[N][N]);
void imprimirGrafo(int matriz[N][N], char vector[N]);

// Recorre todas las columnas de la primera fila de la matriz M y copia estos
// valores al arreglo D.
void inicializarVectorD(int D[N], int M[N][N]) {
  int col;
  for (col = 0; col < N; ++col) {
    D[col] = M[0][col];
  }
}

// Recorre todos los elementos del arreglo vector y asigna el carácter espacio
// " " a cada posición del arreglo.
void inicializarVectorCaracter(char vector[N]) {
  int col;

  for (col = 0; col < N; col++) {
    vector[col] = ' ';
  }
}

// retorna el índice del caracter consultado.
int buscarIndiceCaracter(char V[N], char caracter) {
  int i;

  for (i = 0; i < N; i++) {
    if (V[i] == caracter)
      return i;
  }
  return i;
}

int calcularMinimo(int dw, int dv, int mvw) {
  int min = 0;

  // Usa -1 como un valor especial para representar "infinito" o "no conectado".
  if (dw == -1) {
    if (dv != -1 && mvw != -1)
      min = dv + mvw;
    else
      min = -1;

  } else {
    if (dv != -1 && mvw != -1) {
      if (dw <= (dv + mvw))
        min = dw;
      else
        min = (dv + mvw);
    } else
      min = dw;
  }

  cout << "dw: " << dw << " dv: " << dv << " mvw: " << mvw << " min: " << min
       << endl;

  return min;
}

void actualizarPesos(int D[N], char VS[N], int M[N][N], char V[N], char v) {
  int i = 0;
  int indice_w, indice_v;

  cout << " actualiza pesos en D[]" << endl;

  indice_v = buscarIndiceCaracter(V, v);
  while (VS[i] != ' ') {
    if (VS[i] != v) {
      indice_w = buscarIndiceCaracter(V, VS[i]);
      D[indice_w] =
          calcularMinimo(D[indice_w], D[indice_v], M[indice_v][indice_w]);
    }
    i++;
  }
}

void agregarVerticeHaciaS(char S[N], char vertice) {
  int i;
  // Recorre buscando un espacio vacio
  for (i = 0; i < N; i++) {
    if (S[i] == ' ') {
      S[i] = vertice;
      return;
    }
  }
}
// Elige el vértice no visitado con la menor distancia actual
int elegirVertice(char VS[N], int D[N], char V[N]) {
  int i = 0;
  int menor = 0;
  int peso;
  int vertice;

  while (VS[i] != ' ') {
    peso = D[buscarIndiceCaracter(V, VS[i])];
    // Descarta valores infinitos (-1) y 0.
    if ((peso != -1) && (peso != 0)) {
      if (i == 0) {
        menor = peso;
        vertice = VS[i];
      } else {
        if (peso < menor) {
          menor = peso;
          vertice = VS[i];
        }
      }
    }

    i++;
  }
  cout << "vertice: " << vertice << endl;
  return vertice;
}

// Busca la aparición de un caracter en un vector de caracteres
int buscaCaracter(char c, char vector[N]) {
  int j;
  for (j = 0; j < N; j++) {
    if (c == vector[j]) {
      return TRUE;
    }
  }
  return FALSE;
}

// Actualiza VS[] cada ves que se agrega un elemnto a S[]
void actualizarVS(char V[N], char S[N], char VS[N]) {
  int j;
  int k = 0;
  inicializarVectorCaracter(VS);
  for (j = 0; j < N; j++) {
    // Por cada caracter de V[] evalua si está en S[]
    // Sino está, lo agrega a VS[]
    if (buscaCaracter(V[j], S) != TRUE) {
      VS[k] = V[j];
      k++;
    }
  }
}

// Lee datos de los nodos inicializa utilizando código ASCII.
void leerNodos(char vector[N]) {
  int i;
  int inicio = 97;

  for (i = 0; i < N; i++) {
    vector[i] = inicio + i;
  }
}

// imprime el contenido de un vector de caracteres.
void imprimirVectorCaracter(char vector[N], char *nomVector) {
  int i;
  for (int i = 0; i < N; ++i) {
    cout << nomVector << "[" << i << "]: " << vector[i] << " ";
  }
  cout << endl;
}

// Imprime el contenido de un vector de enteros
void imprimirVectorEntero(int vector[N]) {
  int i;
  for (int i = 0; i < N; ++i) {
    cout << "D[" << i << "]: " << vector[i] << " ";
  }
  cout << endl;
}

// imprime el contenido de una matriz bidimensional de enteros.
void imprimir_matriz(int matriz[N][N]) {
  int i, j;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cout << "matriz[" << i << "," << j << "]: " << matriz[i][j] << " ";
    }
    cout << endl;
  }
}

void imprimirGrafo(int matriz[N][N], char vector[N]) {

  ofstream file("grafo.txt");
  if (!file) {
    cerr << "No se pudo abrir el archivo." << endl;
    return;
  }

  file << "digraph G {\n";
  file << "graph [rankdir=LR]\n";
  file << "node [style=filled fillcolor=springgreen];\n";

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      // Evalúa la diagonal principal.
      if (i != j && matriz[i][j] > 0) {
        file << vector[i] << "->" << vector[j] << " [label=" << matriz[i][j]
             << "];\n";
      }
    }
  }

  file << "}\n";
  file.close();

  system("dot -Tpng -ografo.png grafo.txt");
  system("eog grafo.png &");
}

// aplica el algoritmo.
void aplicarDijkstra(char V[N], char S[N], char VS[N], int D[N], int M[N][N]) {
  int i;
  int v;

  // inicializar vector D[] segun datos de la matriz M[][]
  // estado inicial.
  inicializarVectorD(D, M);

  //
  cout << "---------Estados iniciales ---------------------------------------"
       << endl;
  imprimir_matriz(M);
  cout << endl;
  imprimirVectorCaracter(S, "S");
  imprimirVectorCaracter(VS, "VS");
  imprimirVectorEntero(D);
  cout << "------------------------------------------------------------------"
       << endl;

  // agrega primer véctice.
  cout << "> agrega primer valor V[0] a S[] y actualiza VS[]\n" << endl;
  agregarVerticeHaciaS(S, V[0]);
  imprimirVectorCaracter(S, "S");
  //
  actualizarVS(V, S, VS);
  imprimirVectorCaracter(VS, "VS");
  imprimirVectorEntero(D);

  //
  for (i = 1; i < N; i++) {
    // elige un vértice en v de VS[] tal que D[v] sea el mínimo
    cout << "\n> elige vertice menor en VS[] según valores en D[]" << endl;
    cout << "> lo agrega a S[] y actualiza VS[]" << endl;
    v = elegirVertice(VS, D, V);

    //
    agregarVerticeHaciaS(S, v);
    imprimirVectorCaracter(S, "S");

    //
    actualizarVS(V, S, VS);
    imprimirVectorCaracter(VS, "VS");

    //
    actualizarPesos(D, VS, M, V, v);
    imprimirVectorEntero(D);
  }
}

int main(int argc, char **argv) {
  char V[N], S[N], VS[N];
  int D[N];

  // valores de prueba1.
  /*
  int M[N][N] = {{0, 4, 11, -1, -1},
                 {-1, 0, -1, 6, 2},
                 {-1, 3, 0, 6, -1},
                 {-1, -1, -1, 0, -1},
                 {-1, -1, 5, 3, 0}};
  */
  // valores de prueba2.
  int M[N][N] = {{0, 2, 1, -1, 3},
                 {-1, 0, -1, 4, -1},
                 {-1, 1, 0, -1, 1},
                 {1, -1, 3, 0, 5},
                 {-1, -1, -1, -1, 0}};

  //
  inicializarVectorCaracter(V);
  inicializarVectorCaracter(S);
  inicializarVectorCaracter(VS);

  //
  leerNodos(V);

  //
  aplicarDijkstra(V, S, VS, D, M);

  //
  imprimirGrafo(M, V);

  return 0;
}
