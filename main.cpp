#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

int caracter_a_entero(char c);
bool leer_archivo(char nombre[], ifstream& f);
bool obtener_numero_valido(char numero_secreto[], ifstream& f);
void jugar(char numero_secreto[]);

int main() {
  char nombre_archivo[15];
  char numero_secreto[21];
  bool archivo_valido, numero_valido;
  ifstream archivo;

  do {
    cout << "Ingresa el nombre del archivo con números o un punto para salir: ";
    cin >> nombre_archivo;
    if (nombre_archivo[0] == '.') return 0;
  } while (leer_archivo(nombre_archivo, archivo) == false);

  while (obtener_numero_valido(numero_secreto, archivo)) {
    jugar(numero_secreto);
  }

  archivo.close();
  cout << "No quedan más números válidos en el archivo.\n";
  return 0;
}

int caracter_a_entero(char c) {
  return c - '0';
}

bool leer_archivo(char nombre[], ifstream &f) {
  f.open(nombre);
  return f.fail() ? false : true;
}

bool validar_longitud(int longitud) {
  return (longitud < 10 || longitud > 20) ? false : true;
}

bool validar_diferentes(char num[], int longitud_num) {
  int digito[10] = { 0 };
  int num_actual;
  int suma_diferentes = 0;

  for (int i = 0; i < longitud_num; i++) {
    num_actual = caracter_a_entero(num[i]);
    digito[num_actual] = 1;
  }

  for (int i = 0; i < 10; i++) {
    suma_diferentes += digito[i];
  }

  return (suma_diferentes > 3) ? true : false;
}

bool validar_no_consecutivos(char num[], int longitud_num) {
  for (int i = 0; i <= longitud_num - 4; i++) {
    if (
      num[i] == num[i + 1] &&
      num[i + 1] == num[i + 2] &&
      num[i + 2] == num[i + 3]
    ) return false;
  }
  return true;
}

bool numero_valido(char num[]) {
  int cuenta_digitos = strlen(num);

  if (
    !validar_longitud(cuenta_digitos) ||
    !validar_no_consecutivos(num, cuenta_digitos) ||
    !validar_diferentes(num, cuenta_digitos)
  ) return false;

  return true;
}

bool obtener_numero_valido(char numero_secreto[], ifstream &f) {
  char c;
  while (!f.eof()) {
    f.get(numero_secreto, 22, '\n');
    do (f.get(c)); while (c != '\n'&& !f.eof());

    if (numero_valido(numero_secreto)) {
      cout << numero_secreto << endl;
      return true;
    }

  }
  return false;
}

void identificar_digitos(char numero_secreto[], int digitos[], int longitud_num) {
  int digito_actual;
  for (int i = 0; i < longitud_num; i++) {
    digito_actual = caracter_a_entero(numero_secreto[i]);
    digitos[digito_actual] = 1;
  }
}

void mostrar_adivinados(char numero_secreto[], int adivinados[], int longitud_num) {
  int digito_actual;
  for (int i = 0; i < longitud_num; i++) {
    digito_actual = caracter_a_entero(numero_secreto[i]);
    (adivinados[digito_actual] == 1) ? cout << digito_actual << "  " : cout << '_' << "  ";
  }
}

void jugar(char numero_secreto[]) {
  int longitud_num = strlen(numero_secreto);
  int intentos = 5;
  int digitos[10] = { 0 };
  int adivinados[10] = { 0 };
  int numero_ingresado;

  identificar_digitos(numero_secreto, digitos, longitud_num);
  while (true) {
    cout << "\nIngresa un numero: ";
    cin >> numero_ingresado;

    adivinados[numero_ingresado] = 1;
    mostrar_adivinados(numero_secreto, adivinados, longitud_num);
  }
}