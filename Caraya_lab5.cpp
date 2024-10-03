#include <fstream>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

#define TRUE 1
#define FALSE 0

enum { IZQUIERDO, DERECHO };

struct Nodo {
  int dato;
  int FE;
  Nodo *derecho;
  Nodo *izquierdo;
  Nodo *padre;
};

typedef Nodo *pNodo;
typedef Nodo *Arbol;

void GenerarGrafo(Arbol ArbolInt);
void Podar(Arbol *a);
void Modificar(Arbol *a, int antiguo, int nuevo);
pNodo Minimo(pNodo nodo);
void Eliminar(Arbol *a, int dat);
void Insertar(Arbol *a, int dat);
void Equilibrar(Arbol *a, pNodo nodo, int rama, int nuevo);
void RotaIzquierdaDerecha(Arbol *raiz, pNodo nodo);
void RotaDerechaIzquierda(Arbol *a, pNodo nodo);
void RotaIzquierdaIzquierda(Arbol *a, pNodo nodo);
void RotaDerechaDerecha(Arbol *a, pNodo nodo);
void PreOrden(Arbol, std::ofstream &fp);


void PreOrden(Arbol a, std::ofstream &fp) {
  if (a) {
    fp << a->dato << ";\n";
    if (a->izquierdo) {
      fp << a->dato << "->" << a->izquierdo->dato << ";\n";
      PreOrden(a->izquierdo, fp);
    }
    if (a->derecho) {
      fp << a->dato << "->" << a->derecho->dato << ";\n";
      PreOrden(a->derecho, fp);
    }
  }
}

void GenerarGrafo(Arbol ArbolInt) {
  std::ofstream fp("grafo.txt");

  fp << "digraph G {\n";
  fp << "node [style=filled fillcolor=yellow];\n";

  fp << "nullraiz [shape=point];\n";
  fp << "nullraiz->" << ArbolInt->dato << " [label=" << ArbolInt->FE << "];\n";
  PreOrden(ArbolInt, fp);

  fp << "}\n";
  fp.close();

  system("dot -Tpng -ografo.png grafo.txt");
  system("eog grafo.png &");
}

void Podar(Arbol *a) {
  if (*a) {
    Podar(&(*a)->izquierdo);
    Podar(&(*a)->derecho);
    free(*a);
    *a = NULL;
  }
}


// Esta funcion  la adapte de el codigo anterior (lab4)
void Modificar(Arbol *a, int antiguo, int nuevo) {
    Eliminar(a, antiguo);
    Insertar(a, nuevo);
}

// Esta funcion  la adapte de el codigo anterior (lab4)
pNodo Minimo(pNodo nodo) {
    while (nodo->izquierdo != NULL) nodo = nodo->izquierdo;
    return nodo;
}


// Esta funcion  la adapte de el codigo anterior (lab4)
void Eliminar(Arbol *a, int dat) {
    if (*a == NULL) return;

    if (dat < (*a)->dato)
        Eliminar(&(*a)->izquierdo, dat);
    else if (dat > (*a)->dato)
        Eliminar(&(*a)->derecho, dat);
    else {
        if ((*a)->izquierdo == NULL && (*a)->derecho == NULL) {
            delete *a;
            *a = NULL;
        } else if ((*a)->izquierdo == NULL) {
            pNodo temp = *a;
            *a = (*a)->derecho;
            delete temp;
        } else if ((*a)->derecho == NULL) {
            pNodo temp = *a;
            *a = (*a)->izquierdo;
            delete temp;
        } else {
            pNodo temp = Minimo((*a)->derecho);
            (*a)->dato = temp->dato;
            Eliminar(&(*a)->derecho, temp->dato);
        }
    }
}


void Insertar(Arbol *a, int dat) {
  pNodo padre = NULL;
  pNodo actual = *a;

  while (actual != NULL && dat != actual->dato) {
    padre = actual;

    if (dat < actual->dato)
      actual = actual->izquierdo;
    else if (dat > actual->dato)
      actual = actual->derecho;
  }

  if (actual != NULL)
    return;

  if (padre == NULL) {
    *a = new Nodo{dat, 0, NULL, NULL, NULL};
  } else if (dat < padre->dato) {
    actual = new Nodo{dat, 0, NULL, NULL, padre};
    padre->izquierdo = actual;
    Equilibrar(a, padre, IZQUIERDO, TRUE);
  } else if (dat > padre->dato) {
    actual = new Nodo{dat, 0, NULL, NULL, padre};
    padre->derecho = actual;
    Equilibrar(a, padre, DERECHO, TRUE);
  }
}

void Equilibrar(Arbol *a, pNodo nodo, int rama, int nuevo) {
  int salir = FALSE;

  while (nodo && !salir) {
    if (nuevo) {
      if (rama == IZQUIERDO) {
        nodo->FE -= 1;
      } else {
        nodo->FE += 1;
      }
    } else {
      if (rama == IZQUIERDO) {
        nodo->FE += 1;
      } else {
        nodo->FE -= 1;
      }
    }

    if (nodo->FE == 0)
      salir = TRUE;
    else if (nodo->FE == -2) {
      if (nodo->izquierdo->FE == 1)
        RotaIzquierdaDerecha(a, nodo);
      else
        RotaIzquierdaIzquierda(a, nodo);
      salir = TRUE;
    } else if (nodo->FE == 2) {
      if (nodo->derecho->FE == -1)
        RotaDerechaIzquierda(a, nodo);
      else
        RotaDerechaDerecha(a, nodo);
      salir = TRUE;
    }

    if (nodo->padre) {
      if (nodo->padre->derecho == nodo) {
        rama = DERECHO;
      } else {
        rama = IZQUIERDO;
      }
    }
    nodo = nodo->padre;
  }
}

void RotaIzquierdaDerecha(Arbol *raiz, pNodo nodo) {
  pNodo Padre = nodo->padre;
  pNodo P = nodo;
  pNodo Q = P->izquierdo;
  pNodo R = Q->derecho;
  pNodo B = R->izquierdo;
  pNodo C = R->derecho;

  if (Padre) {
    if (Padre->derecho == nodo) {
      Padre->derecho = R;
    } else {
      Padre->izquierdo = R;
    }
  } else
    *raiz = R;

  Q->derecho = B;
  P->izquierdo = C;
  R->izquierdo = Q;
  R->derecho = P;

  R->padre = Padre;
  P->padre = Q->padre = R;
  if (B)
    B->padre = Q;
  if (C)
    C->padre = P;

  switch (R->FE) {
  case -1:
    Q->FE = 0;
    P->FE = 1;
    break;
  case 0:
    Q->FE = 0;
    P->FE = 0;
    break;
  case 1:
    Q->FE = -1;
    P->FE = 0;
    break;
  }

  R->FE = 0;
}

void RotaDerechaIzquierda(Arbol *a, pNodo nodo) {
  pNodo Padre = nodo->padre;
  pNodo P = nodo;
  pNodo Q = P->derecho;
  pNodo R = Q->izquierdo;
  pNodo B = R->izquierdo;
  pNodo C = R->derecho;

  if (Padre) {
    if (Padre->derecho == nodo) {
      Padre->derecho = R;
    } else {
      Padre->izquierdo = R;
    }
  } else
    *a = R;

  P->derecho = B;
  Q->izquierdo = C;
  R->izquierdo = P;
  R->derecho = Q;

  R->padre = Padre;
  P->padre = Q->padre = R;
  if (B)
    B->padre = P;
  if (C)
    C->padre = Q;

  switch (R->FE) {
  case -1:
    P->FE = 0;
    Q->FE = 1;
    break;
  case 0:
    P->FE = 0;
    Q->FE = 0;
    break;
  case 1:
    P->FE = -1;
    Q->FE = 0;
    break;
  }
  R->FE = 0;
}

void RotaIzquierdaIzquierda(Arbol *a, pNodo nodo) {
  pNodo Padre = nodo->padre;
  pNodo P = nodo;
  pNodo Q = P->izquierdo;
  pNodo B = Q->derecho;

  if (Padre) {
    if (Padre->derecho == P) {
      Padre->derecho = Q;
    } else {
      Padre->izquierdo = Q;
    }
  } else
    *a = Q;

  P->izquierdo = B;
  Q->derecho = P;

  P->padre = Q;
  if (B)
    B->padre = P;
  Q->padre = Padre;

  P->FE = 0;
  Q->FE = 0;
}

void RotaDerechaDerecha(Arbol *a, pNodo nodo) {
  pNodo Padre = nodo->padre;
  pNodo P = nodo;
  pNodo Q = P->derecho;
  pNodo B = Q->izquierdo;

  if (Padre) {
    if (Padre->derecho == P) {
      Padre->derecho = Q;
    } else {
      Padre->izquierdo = Q;
    }
  } else
    *a = Q;

  P->derecho = B;
  Q->izquierdo = P;

  P->padre = Q;

  if (B) {
    B->padre = P;
  }
  Q->padre = Padre;

  P->FE = 0;
  Q->FE = 0;
}



int main() {

  Arbol ArbolInt = NULL;
  int opcion = 0;
  int valor;

  //120, 87, 140, 43, 99, 130, 22, 65, 93, 135, 56
  Insertar(&ArbolInt, 120);
  Insertar(&ArbolInt, 87);
  Insertar(&ArbolInt, 140);
  Insertar(&ArbolInt, 43);
  Insertar(&ArbolInt, 99);
  Insertar(&ArbolInt, 130);
  Insertar(&ArbolInt, 22);
  Insertar(&ArbolInt, 65);
  Insertar(&ArbolInt, 93);
  Insertar(&ArbolInt, 135);
  Insertar(&ArbolInt, 56);

  while (true) {
    int respuesta = 0;
    cout << "-------------------------------------" << endl;
    cout << "1. Eliminar un elemento del arbol." << endl;
    cout << "2. Modificar un elemento del arbol." << endl;
    cout << "3. Agregar un elemento al arbol." << endl;
    cout << "4. Generar imagen del arbol." << endl;
    cout << "5. Salir." << endl;
    cout << "-------------------------------------" << endl;

    if (!(cin >> respuesta)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Por favor, ingrese un número válido." << endl;
      continue;
    }
    switch (respuesta) {
    case 1: {
      int n = 0;
      cout << "Ingrese el el elemento que desea eliminar ";
      if (!(cin >> n)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Por favor, ingrese un número válido." << endl;
        continue;
      }
      Eliminar(&ArbolInt, n);
      cout  << n << ": fue eliminado del arbol" << endl;
      
      break;
    }
    case 2: {
      int n = 0;
      cout << "Que elemento desea eliminar ? : ";
      if (!(cin >> n)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Por favor, ingrese un número válido." << endl;
        continue;
      }
      int m = 0;
      cout << "Ingrese el valor por el cual quiere modificar : ";
      if (!(cin >> m)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Por favor, ingrese un número válido." << endl;
        continue;
      }
      Modificar(&ArbolInt, n, m);
      cout << n << ": fue modificado a " << m << endl;
      break;
    }
    case 3: {
      int n = 0;
      cout << "Ingrese el elemento que quiere ingresar al arbol : ";
      if (!(cin >> n)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Por favor, ingrese un número válido." << endl;
        continue;
      }
      Insertar(&ArbolInt, valor);
      break;
    }
    case 4: {
      GenerarGrafo(ArbolInt);
      break;
    }
    case 5: {
      Podar(&ArbolInt);
      return 0;
    }
    default:
      cout << "Ingrese una opcion valida" << endl;
    }
  }
}
