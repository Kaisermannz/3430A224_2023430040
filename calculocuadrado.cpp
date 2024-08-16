#include <iostream>

double square(double x) { return x * x; }

void print_square(double x) {
  std::cout << "El cuadrado de " << x << " es " << square(x) << std::endl;
}

int main() {
  print_square(1.234);
  print_square(5.555);
  return 0;
}
