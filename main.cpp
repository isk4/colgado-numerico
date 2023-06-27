#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

bool leer_archivo(char nombre[15], ifstream& f);
bool obtener_numero_valido(char numero_secreto[21], ifstream& f);

int main()
{
  char nombre_archivo[15];
  char numero_secreto[21];
  bool archivo_valido, numero_valido;
  ifstream archivo;

  do {
    cout << "Ingresa el nombre del archivo con números o un punto para salir: \n";
    cin >> nombre_archivo;
    if (nombre_archivo[0] == '.') return 0;
  } while (leer_archivo(nombre_archivo, archivo) == false);

  do {
    numero_valido = obtener_numero_valido(numero_secreto, archivo);

  } while (numero_valido);

  archivo.close();
  cout << "No quedan más números válidos en el archivo.\n";
  return 0;
}

bool leer_archivo(char nombre[15], ifstream &f) {
  f.open(nombre);
  return f.fail() ? false : true;
}

bool validar_longitud(int longitud) {
  return (longitud < 10 || longitud > 20) ? false : true;
}

bool validar_diferentes(char num[21], int longitud_num) {
  int digito[10] = { 0 };
  int num_actual;
  int suma_diferentes = 0;

  for (int i = 0; i < longitud_num; i++) {
    num_actual = num[i] - '0';
    digito[num_actual] = 1;
  }

  for (int i = 0; i < 10; i++) {
    suma_diferentes += digito[i];
  }

  return (suma_diferentes > 3) ? true : false;
}

bool numero_valido(char num[21]) {
  int cuenta_digitos = strlen(num);

  if (!validar_longitud(cuenta_digitos)) return false;
  if (!validar_diferentes(num, cuenta_digitos)) return false;

  return true;
}

bool obtener_numero_valido(char numero_secreto[21], ifstream &f) {
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