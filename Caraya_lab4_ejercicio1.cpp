#include <fstream>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

struct Node {
  int info;
  Node *left;
  Node *right;
};

// Crear un nuevo nodo
Node *createNode(int data) {
  Node *newNode = new Node;
  newNode->info = data;
  newNode->left = nullptr;
  newNode->right = nullptr;
  return newNode;
}

class Arbol {
private:
  Node *root;

  Node *insertNode(Node *node, int data) {
    if (node == nullptr) {
      return createNode(data);
    }

    if (data < node->info) {
      node->left = insertNode(node->left, data);
    } else if (data > node->info) {
      node->right = insertNode(node->right, data);
    } else {
      cout << "El nodo ya se encuentra en el árbol: " << data << endl;
    }
    return node;
  }

  // para encontrar el valor mínimo en un subárbol, que se utiliza en el proceso
  // de eliminación.
  Node *Min(Node *node) {
    while (node->left != nullptr) {
      node = node->left;
    }
    return node;
  }

  Node *deleteNode(Node *node, int data) {
    if (node == nullptr) {
      return node;
    }

    if (data < node->info) {
      node->left = deleteNode(node->left, data);
    } else if (data > node->info) {
      node->right = deleteNode(node->right, data);
    } else {
      // Nodo con el valor a eliminar encontrado
      if (node->left == nullptr) {
        Node *temp = node->right;
        delete node;
        return temp;
      } else if (node->right == nullptr) {
        Node *temp = node->left;
        delete node;
        return temp;
      }

      // Nodo con dos hijos
      Node *temp = Min(node->right);
      node->info = temp->info;
      node->right = deleteNode(node->right, temp->info);
    }
    return node;
  }

  void printPreOrder(Node *node) const {
    if (node == nullptr) {
      return;
    }
    cout << node->info << " ";
    printPreOrder(node->left);
    printPreOrder(node->right);
  }

  void printInOrder(Node *node) const {
    if (node == nullptr) {
      return;
    }
    printInOrder(node->left);
    cout << node->info << " ";
    printInOrder(node->right);
  }

  void printPostOrder(Node *node) const {
    if (node == nullptr) {
      return;
    }
    printPostOrder(node->left);
    printPostOrder(node->right);
    cout << node->info << " ";
  }

  void recorrer(Node *node, ofstream &fp) {
    if (node != nullptr) {
      if (node->left != nullptr) {
        fp << "\"" << node->info << "\"->\"" << node->left->info << "\";"
           << endl;
      } else {
        string cadena = "null" + to_string(node->info) + "l";
        fp << "\"" << cadena << "\"[shape=point];" << endl;
        fp << "\"" << node->info << "\"->\"" << cadena << "\";" << endl;
      }
      if (node->right != nullptr) {
        fp << "\"" << node->info << "\"->\"" << node->right->info << "\";"
           << endl;
      } else {
        string cadena = "null" + to_string(node->info) + "r";
        fp << "\"" << cadena << "\"[shape=point];" << endl;
        fp << "\"" << node->info << "\"->\"" << cadena << "\";" << endl;
      }
      recorrer(node->left, fp);
      recorrer(node->right, fp);
    }
  }

public:
  Arbol() : root(nullptr) {}

  void insert(int data) { root = insertNode(root, data); }

  void remove(int data) { root = deleteNode(root, data); }

  void modify(int antiguo, int nuevo) {
    remove(antiguo);
    insert(nuevo);
  }

  // Metodo publico para imprimir el arbol en preorden
  void printPreOrder() const {
    printPreOrder(root);
    cout << endl;
  }

  void printInOrder() const {
    printInOrder(root);
    cout << endl;
  }

  void printPostOrder() const {
    printPostOrder(root);
    cout << endl;
  }

  void visualize() {
    ofstream fp("grafo.dot");
    if (!fp.is_open()) {
      cerr << "Error al abrir el archivo arbol.dot" << endl;
      return;
    }
    fp << "digraph G {" << endl;
    fp << "node [style=filled fillcolor=yellow];" << endl;
    recorrer(root, fp);
    fp << "}" << endl;
    fp.close();
    // Generar y mostrar la imagen del árbol
    system("dot -Tpng -o grafo.png grafo.dot");
    system("eog grafo.png");
  }
};

int main() {
  Arbol arbol;

  arbol.insert(120);
  arbol.insert(87);
  arbol.insert(140);
  arbol.insert(43);
  arbol.insert(99);
  arbol.insert(130);
  arbol.insert(22);
  arbol.insert(65);
  arbol.insert(93);
  arbol.insert(135);
  arbol.insert(56);

  while (true) {
    int respuesta = 0;
    cout << "-------------------------------------" << endl;
    cout << "1. Eliminar un elemento del arbol." << endl;
    cout << "2. Modificar un elemento del arbol." << endl;
    cout << "3. Agregar un elemento al arbol." << endl;
    cout << "4. imprimir en preorden." << endl;
    cout << "5. imprimir en InOrder." << endl;
    cout << "6. imprimir en PostOrder." << endl;
    cout << "7. Generar imagen del arbol." << endl;
    cout << "8. Salir." << endl;
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
      arbol.remove(n);
      cout << "\nÁrbol después de eliminar " << n << ":" << endl;
      cout << "Recorrido en inorden: ";
      arbol.printInOrder();
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
      arbol.modify(n, m);
      cout << "\nÁrbol después de modificar " << n << " a " << m << ":" << endl;
      cout << "Recorrido en inorden: ";
      arbol.printInOrder();
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
      arbol.insert(n);
      cout << "El numero " << n << " fue ingresado en el arbol" << endl;
      cout << "Recorrido en Inorden: ";
      arbol.printInOrder();
      break;
    }
    case 4: {
      cout << "-------------------------------------" << endl;
      cout << " PreOrden: ";
      arbol.printPreOrder();
      break;
    }
    case 5: {
      cout << "-------------------------------------" << endl;
      cout << " InOrden: ";
      arbol.printInOrder();
      break;
    }
    case 6: {
      cout << "-------------------------------------" << endl;
      cout << " PostOrder: ";
      arbol.printPostOrder();
      break;
    }
    case 7: {
      arbol.visualize();
      break;
    }
    case 8: {
      return 0;
    }
    default:
      cout << "Ingrese una opcion valida" << endl;
    }
  }
  return 0;
}
