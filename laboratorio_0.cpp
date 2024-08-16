#include <iostream>
#include <string>

int longitud_string(const std::string &cadena) { return cadena.length(); }

bool esPar(int numero) { return numero % 2 == 0; }

void imprimir(int numero) {
  if (esPar(numero)) {
    std::cout << numero << " es espar" << std::endl;
  } else {
    std::cout << numero << " es impar" << std::endl;
  }
}

int main() {

  int numero = 0;

  std::cout << "Ingrese un numero: ";
  std::cin >> numero;
  std::cin.ignore(); // Limpiar el buffer de entrada porque si no se pasa de
                     // largo y no pregunta el string

  std::cout << "El número que ingresó es: " << numero << std::endl;

  std::cout << "Para el número ingresado: ";
  imprimir(numero);

  std::cout << "\nPara los números del 1 al 10: " << std::endl;
  for (int i = 1; i <= 10; ++i) {
    imprimir(i);
  }
  std::string cadena_usuario;

  std::cout << "Ingrese un texto:";
  std::getline(std::cin, cadena_usuario);

  int longitud = longitud_string(cadena_usuario);
  std::cout << "El string ingresada tiene un largo de : " << longitud
            << std::endl;

  std::string cadena = "Hola mundo cruel!";

  int longitud_cadena = longitud_string(cadena);
  std::cout << "El string " << cadena
            << " tiene un largo de : " << longitud_cadena << std::endl;

  return 0;
}
