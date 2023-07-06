#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

int caracter_a_entero(char c);
bool leer_archivo(char nombre[], ifstream& f);
bool obtener_numero_valido(char numero_secreto[], ifstream& f);
void jugar(char numero_secreto[]);
void imprimir_lineas(int numero_lineas);
void limpiar_pantalla();
void imprimir_numero(int numero, int linea);
bool validar_longitud(int longitud);
int caracter_a_entero(char c);
void mostrar_adivinados(char numero_secreto[], int adivinados[], int longitud_num);
int obtener_por_adivinar(char numero_secreto[], int adivinados[], int longitud_num);

int main() {
  char nombre_archivo[15], numero_secreto[21];
  char opcion;
  bool archivo_valido, numero_valido;
  ifstream archivo;

  do {
    limpiar_pantalla();
    imprimir_lineas(10);
    cout << "\t\tIngresa el nombre del archivo con números o un punto para salir: ";
    cin >> nombre_archivo;
    if (nombre_archivo[0] == '.') return 0;
  } while (leer_archivo(nombre_archivo, archivo) == false);

  while (obtener_numero_valido(numero_secreto, archivo)) {
    jugar(numero_secreto);

    cout << "¿Deseas seguir jugando? (s/n): ";
    cin >> opcion;

    if (opcion == 'n') {
     cout << "Gracias por jugar.\n";
     exit(0); 
    }
  }

  archivo.close();

  imprimir_lineas(2);
  cout << "Lo sentimos. No quedan más números válidos en el archivo.\n";
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


void imprimir_numero(int numero, int linea) {
  switch(numero) {
    case -1: {
      if (linea == 0) cout << "   ";
      if (linea == 1) cout << "   ";
      if (linea == 2) cout << "   ";
      if (linea == 3) cout << "___";
      break;
    }
    case 0: {
      if (linea == 0) cout << " _ ";
      if (linea == 1) cout << "| |";
      if (linea == 2) cout << "|_|";
      if (linea == 3) cout << "___";
      break;
    }
    case 1: {
      if (linea == 0) cout << "   ";
      if (linea == 1) cout << "  |";
      if (linea == 2) cout << "  |";
      if (linea == 3) cout << "___";

      break;
    }
    case 2: {
      if (linea == 0) cout << " _ ";
      if (linea == 1) cout << " _|";
      if (linea == 2) cout << "|_ ";
      if (linea == 3) cout << "___";
      break;
    }
    case 3: {
      if (linea == 0) cout << " _ ";
      if (linea == 1) cout << " _|";
      if (linea == 2) cout << " _|";
      if (linea == 3) cout << "___";
      break;
    }
    case 4: {
      if (linea == 0) cout << "   ";
      if (linea == 1) cout << "|_|";
      if (linea == 2) cout << "  |";
      if (linea == 3) cout << "___";
      break;
    }
    case 5: {
      if (linea == 0) cout << " _ ";
      if (linea == 1) cout << "|_ ";
      if (linea == 2) cout << " _|";
      if (linea == 3) cout << "___";
      break;
    }
    case 6: {
      if (linea == 0) cout << " _ ";
      if (linea == 1) cout << "|_ ";
      if (linea == 2) cout << "|_|";
      if (linea == 3) cout << "___";
      break;
    }
    case 7: {
      if (linea == 0) cout << " _ ";
      if (linea == 1) cout << "  |";
      if (linea == 2) cout << "  |";
      if (linea == 3) cout << "___";
      break;
    }
    case 8: {
      if (linea == 0) cout << " _ ";
      if (linea == 1) cout << "|_|";
      if (linea == 2) cout << "|_|";
      if (linea == 3) cout << "___";
      break;
    }
    case 9: {
      if (linea == 0) cout << " _ ";
      if (linea == 1) cout << "|_|";
      if (linea == 2) cout << " _|";
      if (linea == 3) cout << "___";
      break;
    }
  }
}

void mostrar_adivinados(char numero_secreto[], int adivinados[], int longitud_num) {
  int digito_actual;
  for (int linea = 0; linea < 4; linea++) {
    cout << "\t\t\t";

    for (int i = 0; i < longitud_num; i++) {
      digito_actual = caracter_a_entero(numero_secreto[i]);
        
      if (adivinados[digito_actual] == 1) {
        imprimir_numero(digito_actual, linea);
      } else {
        imprimir_numero(-1, linea);
      }
      cout << " ";
    }
    cout << endl;
  }
}

void limpiar_pantalla() {
  cout<< u8"\033[2J\033[1;1H";
}

void imprimir_lineas(int numero_lineas) {
  for (int i = 0; i < numero_lineas; i++) cout << endl;
}

int obtener_por_adivinar(char numero_secreto[], int adivinados[], int longitud_num) {
  int por_adivinar = 0;
  int digito_actual;
  for (int i = 0; i < longitud_num; i++) {
    digito_actual = caracter_a_entero(numero_secreto[i]);
    if (adivinados[digito_actual] == 0) por_adivinar++;
  }
  return por_adivinar;
}

void obtener_pistas(int numero, char mensaje[]) {
  switch(numero) {
    case 0: {
      strcat(mensaje, "- Te falta el 0\n");
      break;
    }
    case 1: {
      strcat(mensaje, "- Te falta el 1\n");
      break;
    }
    case 2: {
      strcat(mensaje, "- Te falta el 2\n");
      break;
    }
    case 3: {
      strcat(mensaje, "- Te falta el 3\n");
      break;
    }
    case 4: {
      strcat(mensaje, "- Te falta el 4\n");
      break;
    }
    case 5: {
      strcat(mensaje, "- Te falta el 5\n");
      break;
    }
    case 6: {
      strcat(mensaje, "- Te falta el 6\n");
      break;
    }
    case 7: {
      strcat(mensaje, "- Te falta el 7\n");
      break;
    }
    case 8: {
      strcat(mensaje, "- Te falta el 8\n");
      break;
    }
    case 9: {
      strcat(mensaje, "- Te falta el 9\n");
      break;
    }
  }
}


void mostrar_pistas(char numero_secreto[], int adivinados[], int longitud_num, char mensaje[]) {
  int digito_actual;
  int primos, pares, impares, cuadrados;
  primos = pares = impares = 0;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < longitud_num; j++) {
      digito_actual = caracter_a_entero(numero_secreto[j]);
      if (adivinados[i] == 0 && i == digito_actual) {

        obtener_pistas(digito_actual, mensaje);



        break;
      }
    }
  }
  cout << mensaje;
}

void jugar(char numero_secreto[]) {
  int numero_ingresado, por_adivinar;
  int longitud_num = por_adivinar = strlen(numero_secreto);
  int intentos = 5;
  int adivinados[10] = { 0 };
  char mensaje_pistas[256] = "";

  while (intentos != 0 && por_adivinar != 0) {
    limpiar_pantalla();
    imprimir_lineas(6);

    cout << "\t\t\tAdivina el número de " << longitud_num << " dígitos\n";
    cout << "\t\t\tTienes " << intentos << " intentos\n";

    imprimir_lineas(2);    
    mostrar_adivinados(numero_secreto, adivinados, longitud_num);
    cout << "\t\t\tNúmeros por adivinar: " << por_adivinar << endl;

    imprimir_lineas(3);
    mostrar_pistas(numero_secreto, adivinados, longitud_num, mensaje_pistas);
    cout << "\n\t\t\tIngresa un número: ";
    cin >> numero_ingresado;


    adivinados[numero_ingresado] = 1;
    por_adivinar = obtener_por_adivinar(numero_secreto, adivinados, longitud_num);
    intentos--;
  }

  limpiar_pantalla();
  imprimir_lineas(6);
  if (por_adivinar == 0) {
    cout << "¡\t\t\tFelicidades, ganaste!\n";
  } else {
    cout << "\t\t\tPerdiste. El número era: " << numero_secreto << endl;
  }
  imprimir_lineas(6);
}