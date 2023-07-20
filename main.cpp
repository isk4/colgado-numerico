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
struct infoPistas {
  int primos = 0;
  int pares = 0;
  int cuadrados = 0;
  int multiplo_3 = 0;
  int multiplo_4 = 0;
  int mayor_5 = 0;
  int fibonaccis = 0;
};


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
     cout << "\nGracias por jugar.\n";
     exit(0); 
    }
  }

  archivo.close();

  imprimir_lineas(2);
  cout << "Lo sentimos. No quedan más números válidos en el archivo.\n";
  cout << "\nGracias por jugar.\n";
  return 0;
}

int caracter_a_entero(char c) {
  return c - '0';
}

bool leer_archivo(char nombre[], ifstream &f) {
  f.open(nombre);
  return !f.fail();
}

bool validar_longitud(int longitud) {
  return !(longitud < 10 || longitud > 20);
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

  return suma_diferentes > 3;
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
  while (f >> numero_secreto) {
  // while (!f.eof()) {
    // f.get(numero_secreto, 22, '\n');
    // do f.get(c); while (c != '\n'&& !f.eof());

    if (numero_valido(numero_secreto)) return true;
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

void procesar_info_pistas(int numero, infoPistas& info) {
  switch(numero) {
    case 0: {
      info.pares++;
      break;
    }
    case 1: {
      info.cuadrados++;
      info.fibonaccis++;
      break;
    }
    case 2: {
      info.pares++;
      info.primos++;
      info.fibonaccis++;
      break;
    }
    case 3: {
      info.primos++;
      info.multiplo_3++;
      info.fibonaccis++;
      break;
    }
    case 4: {
      info.cuadrados++;      
      info.pares++;
      info.multiplo_4++;
      break;
    }
    case 5: {
      info.primos++;
      info.fibonaccis++;
      info.mayor_5++;
      break;
    }
    case 6: {
      info.pares++;
      info.multiplo_3++;
      info.mayor_5++;
      break;
    }
    case 7: {
      info.primos++;
      info.mayor_5++;
      break;
    }
    case 8: {
      info.pares++;
      info.fibonaccis++;
      info.multiplo_4++;
      info.mayor_5++;
      break;
    }
    case 9: {
      info.cuadrados++;
      info.multiplo_3++;
      info.mayor_5++;
      break;
    }
  }
}

void mensaje_pistas(bool pistas_activas[], infoPistas info) {
  cout << "\t =================================================================\n";
  cout << "\t|| Pistas:                                                       ||\n";
  for (int i = 0; i < 10; i++) {
    if (pistas_activas[i]) {
      switch (i) {
        case 0:
          if (info.pares == 0)
            cout << "\t||  - No quedan pares por adivinar\t\t\t\t ||\n";
          else if (info.pares == 1)
            cout << "\t||  - Te queda 1 par por adivinar\t\t\t\t ||\n";
          else
            cout << "\t||  - Te quedan " << info.pares << " pares por adivinar\t\t\t\t ||\n";
          break;
        case 1:
          if (info.cuadrados == 0)
            cout << "\t||  - No quedan cuadrados por adivinar\t\t\t\t ||\n";
          else if (info.cuadrados == 1)
            cout << "\t||  - Te queda 1 cuadrado por adivinar\t\t\t\t ||\n";
          else
            cout << "\t||  - Te quedan " << info.cuadrados << " cuadrados por adivinar\t\t\t ||\n";
          break;
        case 2:
          if (info.primos == 0)
            cout << "\t||  - No quedan primos por adivinar\t\t\t\t ||\n";
          else if (info.primos == 1)
            cout << "\t||  - Te queda 1 primo por adivinar\t\t\t\t ||\n";
          else
            cout << "\t||  - Te quedan " << info.primos << " primos por adivinar\t\t\t\t ||\n";
          break;
        case 3:
          if (info.multiplo_3 == 0)
            cout << "\t||  - No quedan múltiplos de 3 por adivinar\t\t\t ||\n";
          else if (info.multiplo_3 == 1)
            cout << "\t||  - Te queda 1 múltiplo de 3 por adivinar\t\t\t ||\n";
          else
            cout << "\t||  - Te quedan " << info.multiplo_3 << " múltiplos de 3 por adivinar\t\t\t ||\n";
          break;
        case 4:
          if (info.multiplo_4 == 0)
            cout << "\t||  - No quedan múltiplos de 4 por adivinar\t\t\t ||\n";
          else if (info.multiplo_4 == 1)
            cout << "\t||  - Te queda 1 múltiplo de 4 por adivinar\t\t\t ||\n";
          else
            cout << "\t||  - Te quedan " << info.multiplo_4 << " múltiplos de 4 por adivinar\t\t\t ||\n";
          break;
        case 5:
          if (info.mayor_5 == 0)
            cout << "\t||  - No quedan mayores o iguales a 5 por adivinar\t\t ||\n";
          else if (info.mayor_5 == 1)
            cout << "\t||  - Te queda 1 mayor o igual a 5 por adivinar\t\t\t ||\n";
          else
            cout << "\t||  - Te quedan " << info.mayor_5 << " mayores o iguales a 5 por adivinar\t\t ||\n";
          break;
        case 6:
          if (info.fibonaccis == 0)
            cout << "\t||  - No quedan números de la secuencia Fibonacci por adivinar   ||\n";
          else if (info.fibonaccis == 1)
            cout << "\t||  - Te queda 1 número de la secuencia Fibonacci por adivinar   ||\n";
          else
            cout << "\t||  - Te quedan " << info.fibonaccis << " números de la secuencia Fibonacci por adivinar ||\n";
          break;
      }
    }
  }
  cout << "\t ================================================================\n";
}

void activar_nueva_pista(bool pistas_activas[]) {
  srand((unsigned) time(NULL));
  int opcion = rand() % 8;
  while (pistas_activas[opcion]) opcion = rand() % 8;
  pistas_activas[opcion] = true;
}


void mostrar_pistas(char numero_secreto[], int adivinados[], int longitud_num, bool pistas_activas[]) {
  int digito_actual;
  infoPistas info;

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < longitud_num; j++) {
      digito_actual = caracter_a_entero(numero_secreto[j]);
      if (adivinados[i] == 0 && i == digito_actual) {
        procesar_info_pistas(digito_actual, info);
        break;
      }
    }
  }

  mensaje_pistas(pistas_activas, info);
}

void imprimir_juego(char numero_secreto[], int adivinados[], int longitud_num, int intentos, bool pistas_activas[]) {
  limpiar_pantalla();
  imprimir_lineas(6);

  cout << "\t\t\tAdivina el número de " << longitud_num << " dígitos\n";
  cout << "\t\t\tTienes " << intentos << " intentos\n";

  imprimir_lineas(2);    
  mostrar_adivinados(numero_secreto, adivinados, longitud_num);

  imprimir_lineas(3);
  if (intentos < 3) mostrar_pistas(numero_secreto, adivinados, longitud_num, pistas_activas);
  cout << endl;
}

void jugar(char numero_secreto[]) {
  int numero_ingresado, por_adivinar, previo_por_adivinar;
  int longitud_num = por_adivinar = strlen(numero_secreto);
  int intentos = 5;
  int adivinados[10] = { 0 };
  bool pistas_activas[10] = { 0 };

  while (intentos != 0 && por_adivinar != 0) {
    if (intentos < 3 && intentos != 0) activar_nueva_pista(pistas_activas);
    imprimir_juego(numero_secreto, adivinados, longitud_num, intentos, pistas_activas);

    cout << "\n\t\t\tIngresa un número: ";
    cin >> numero_ingresado;
    adivinados[numero_ingresado] = 1;

    previo_por_adivinar = por_adivinar;
    por_adivinar = obtener_por_adivinar(numero_secreto, adivinados, longitud_num);

    if (previo_por_adivinar == por_adivinar) intentos--;
  }

  imprimir_juego(numero_secreto, adivinados, longitud_num, intentos, pistas_activas);
  imprimir_lineas(3);
  if (por_adivinar == 0) {
    cout << "\t\t\t\t\t¡Felicidades, ganaste!\n";
  } else {
    cout << "\t\t\tPerdiste. El número era: ";
    for (int i = 0; i < longitud_num; i++) cout << numero_secreto[i] << " ";
    cout << endl;
  }
  imprimir_lineas(3);
}