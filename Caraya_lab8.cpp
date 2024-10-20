#include <chrono>
#include <iostream>
#include <string>

using namespace std;

void selectionSort(int arr[], int size) {
  for (int i = 0; i < size - 1; ++i) {
    int min_idx = i;
    for (int j = i + 1; j < size; ++j) {
      if (arr[j] < arr[min_idx]) {
        min_idx = j;
      }
    }
    swap(arr[i], arr[min_idx]);
  }
}

void llenarArreglo(int *arr, int size) {
  for (int i = 0; i < size; ++i) {
    arr[i] = rand() % 1000000 + 1;
  }
}

void mostrarArreglo(int *arr, int size) {
  for (int i = 0; i < size; ++i) {
    cout << arr[i] << " ";
  }
  cout << endl;
}

int partition(int arr[], int low, int high) {
  int pivot = arr[high];
  int i = low - 1;
  for (int j = low; j < high; ++j) {
    if (arr[j] < pivot) {
      ++i;
      swap(arr[i], arr[j]);
    }
  }
  swap(arr[i + 1], arr[high]);
  return i + 1;
}

void quickSort(int arr[], int low, int high) {
  if (low < high) {
    int pi = partition(arr, low, high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}

double ejecutarQuick(int *arr, int size) {
  auto start = chrono::high_resolution_clock::now();
  quickSort(arr, 0, size - 1);
  auto end = chrono::high_resolution_clock::now();
  chrono::duration<double> duration = end - start;
  return duration.count();
}

double ejecutarSelection(int *arr, int size) {
  auto start = chrono::high_resolution_clock::now();
  selectionSort(arr, size);
  auto end = chrono::high_resolution_clock::now();
  chrono::duration<double> duration = end - start;
  return duration.count();
}

int main(int argc, char **argv) {
  const int SIZE_tmp = 10000000;

  // Si lo hacia con un arreglo normal me da error por lo que use memoria
  // dinamica
  int *arr_1 = new int[SIZE_tmp];
  int *arr_2 = new int[SIZE_tmp];

  if (argc != 4) {
    cerr << "Uso: " << argv[0]
         << " <N (tamaño del arreglo)> <T/F (mostrar arreglo)> <S/M "
            "(segundos/milisegundos)>"
         << endl;
    delete[] arr_1;
    delete[] arr_2;
    return 1;
  }

  int N = atoi(argv[1]);
  if (N > SIZE_tmp) {
    cout << "Advertencia: El tamaño solicitado (" << N
         << ") excede el tamaño máximo permitido (" << SIZE_tmp
         << "). El tamaño se ajustará a " << SIZE_tmp << "." << endl;
    N = SIZE_tmp;
  }

  char verArreglo = argv[2][0];
  char Tiempo = argv[3][0];
  double timeValor = 1.0;
  string timeValorString;

  // Definir los valores para mostrar el resultado
  if (Tiempo == 'S') {

    timeValorString = " Segundos ";
  } else if (Tiempo == 'M') {

    timeValor = 1000.0;
    timeValorString = " Milisegundos ";

  } else {

    cerr << "Error: El tercer argumento debe ser 'S' (segundos) o 'M' "
            "(milisegundos)"
         << endl;
    delete[] arr_1;
    delete[] arr_2;
    return 1;
  }

  srand(static_cast<unsigned int>(time(0)));
  llenarArreglo(arr_1, N);

  // Copiar arr_1 a arr_2
  for (int i = 0; i < N; i++) {
    arr_2[i] = arr_1[i];
  }

  if (verArreglo == 'T' || verArreglo == 't') {
    cout << "\nQuick Sort" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Arreglo desordenado: ";
    mostrarArreglo(arr_1, N);

    double resultado = ejecutarQuick(arr_1, N);

    cout << "El algoritmo Quick Sort tardó: " << resultado * timeValor
         << timeValorString << endl;
    cout << "Arreglo ordenado: ";
    mostrarArreglo(arr_1, N);
    cout << "-------------------------------------------" << endl;

    cout << "\nSelection Sort" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Arreglo desordenado: ";
    mostrarArreglo(arr_2, N);

    resultado = ejecutarSelection(arr_2, N);

    cout << "El algoritmo Selection Sort tardó: " << resultado * timeValor
         << timeValorString << endl;
    cout << "Arreglo ordenado: ";
    mostrarArreglo(arr_2, N);
    cout << "-------------------------------------------" << endl;

  } else if (verArreglo == 'F' || verArreglo == 'f') {

    double resultado_quick = ejecutarQuick(arr_1, N);
    double resultado_selection = ejecutarSelection(arr_2, N);

    cout << "-------------------------------------------" << endl;
    cout << "Resultados:" << endl;
    cout << "Quick Sort: " << resultado_quick * timeValor << timeValorString
         << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Selection Sort: " << resultado_selection * timeValor
         << timeValorString << endl;
    cout << "-------------------------------------------" << endl;

  } else {
    cerr << "Error: El segundo argumento debe ser 'T' (mostrar arreglos) o 'F' "
            "(no mostrar)"
         << endl;
    delete[] arr_1;
    delete[] arr_2;
    return 1;
  }

  delete[] arr_1;
  delete[] arr_2;
  return 0;
}
