#include <iostream>

using namespace std;

int funcion_hash(int valor) { return valor % 20; }

// Lineal
void insercion_Lineal(int tabla[], int valor) {

  int posicion = funcion_hash(valor);
  int posicion_original = posicion;
  bool colision = false;

  // Prueba lineal en caso de colisión
  while (tabla[posicion] != -1) {
    colision = true;
    cout << "Colisión detectada al intentar insertar " << valor
         << " en la posición " << posicion
         << ". Desplazamiento a la siguiente posición." << endl;
    posicion = (posicion + 1) % 20;
  }

  tabla[posicion] = valor;

  if (colision) {
    cout << "Elemento " << valor << " insertado en la posición " << posicion
         << " (desplazamiento desde " << posicion_original << ")." << endl;
  } else {
    cout << "Elemento " << valor << " insertado en la posición " << posicion
         << endl;
  }
}

void busqueda_Lineal(int tabla[], int valor) {
  int posicion = funcion_hash(valor);
  int posicion_original = posicion;
  int pasos = 0;

  while (tabla[posicion] != -1) {
    if (tabla[posicion] == valor) {
      cout << "Elemento " << valor << " encontrado en la posición " << posicion
           << " después de " << pasos << " desplazamientos." << endl;
    }

    posicion = (posicion + 1) % 20;
    pasos++;

    // si volvemos al índice significa que dimos la vuelta completa
    if (posicion == posicion_original) {
      cout << "Elemento " << valor
           << " no encontrado después de recorrer la tabla." << endl;
    }
  }
}

// Cuadratica

void insercion_Cuadratica(int tabla[], int valor) {
  int posicion = funcion_hash(valor);
  int i = 1; 
  bool colision = false;

  // en caso de colisión
  while (tabla[posicion] != -1) {
    colision = true;
    cout << "Colisión detectada al intentar insertar " << valor
         << " en la posición " << posicion
         << ". Desplazamiento cuadrático al intentar " << i * i
         << " posiciones más." << endl;

    posicion = (posicion + i * i) % 20;
    i++; // Aumenta el factor
  }

  tabla[posicion] = valor;
  cout << "Elemento " << valor << " insertado en la posición " << posicion
       << endl;
}

void busqueda_Cuadratica(int tabla[], int valor) {
  int posicion = funcion_hash(valor);
  int posicion_original = posicion;
  int i = 0;
  int pasos = 0;

  while (tabla[posicion] != -1 && pasos < 20) {
    if (tabla[posicion] == valor) {
      cout << "Elemento " << valor << " encontrado en la posicion " << posicion
           << " después de " << pasos << " intentos" << endl;
      return;
    }

    i++;
    posicion = (posicion_original + i * i) % 20;
    pasos++;
  }

  cout << "Elemento " << valor << " no encontrado después de " << pasos
       << " intentos." << endl;
}

// Doble Direccion

int segunda_funcion_hash(int key) { return 7 - (key % 7); }

void insertar_Doble_Hash(int tabla[], int valor) {
  int posicion = funcion_hash(valor);
  int paso = segunda_funcion_hash(valor);
  bool colision = false;

  while (tabla[posicion] != -1) {
    colision = true;
    cout << "Colision detectada al intentar insertar " << valor
         << " en la posicion " << posicion
         << ". Desplazamiento mediante doble hash." << endl;
    posicion = (posicion + paso) % 20;
  }

  tabla[posicion] = valor;
  cout << "Elemento " << valor << " insertado en la posicion " << posicion
       << endl;
}

void busqueda_doble_hash(int tabla[], int valor) {
  int posicion = funcion_hash(valor);
  int posicion_original = posicion;
  int paso = segunda_funcion_hash(valor);
  int pasos = 0;

  while (tabla[posicion] != -1 && pasos < 20) {
    if (tabla[posicion] == valor) {
      cout << "Elemento " << valor << " encontrado en la posicion " << posicion
           << " después de " << pasos << " intentos" << endl;
      return;
    }
    posicion = (posicion_original + paso * (pasos + 1)) % 20;
    pasos++;
  }

  cout << "Elemento " << valor << " no encontrado después de " << pasos
       << " intentos." << endl;
}

void inicializar_tabla(int tabla[]) {
  for (int i = 0; i < 20; i++) {
    tabla[i] = -1; 
  }
}

int main(int argc, char **argv) {
  int hashTabla[20];
  inicializar_tabla(hashTabla);

  if (argc != 2) {
    return 1;
  }

  char opcion = argv[1][0];

  while (true) {
    int respuesta = 0;
    int valor_usuario = 0;

    if (opcion == 'l' || opcion == 'L') {
      cout << "Método de Reasignación Lineal\n1. Ingresar\n2. Buscar\n3. "
              "Salir\n";
      cin >> respuesta;

      switch (respuesta) {
      case 1:
        cout << "Ingrese valor: ";
        cin >> valor_usuario;
        insercion_Lineal(hashTabla, valor_usuario);
        break;
      case 2:
        cout << "Ingrese valor a buscar: ";
        cin >> valor_usuario;
        busqueda_Lineal(hashTabla, valor_usuario);
        break;
      case 3:
        return 0;
      default:
        cout << "Opción inválida\n";
      }
    } else if (opcion == 'c' || opcion == 'C') {
      cout << "Método Cuadrático\n1. Ingresar\n2. Buscar\n3. Salir\n";
      cin >> respuesta;

      switch (respuesta) {
      case 1:
        cout << "Ingrese valor: ";
        cin >> valor_usuario;
        insercion_Cuadratica(hashTabla, valor_usuario);
        break;
      case 2:
        cout << "Ingrese valor a buscar: ";
        cin >> valor_usuario;
        busqueda_Cuadratica(hashTabla, valor_usuario);
        break;
      case 3:
        return 0;
      default:
        cout << "Opción inválida\n";
      }
    } else if (opcion == 'd' || opcion == 'D') {
      cout << "Método Doble Hash\n1. Ingresar\n2. Buscar\n3. Salir\n";
      cin >> respuesta;

      switch (respuesta) {
      case 1:
        cout << "Ingrese valor: ";
        cin >> valor_usuario;
        insertar_Doble_Hash(hashTabla, valor_usuario);
        break;
      case 2:
        cout << "Ingrese valor a buscar: ";
        cin >> valor_usuario;
        busqueda_doble_hash(hashTabla, valor_usuario);
        break;
      case 3:
        return 0;
      default:
        cout << "Opción inválida\n";
      }
    } else {
      cout << "Método no válido\n";
      return 1;
    }
  }
}
