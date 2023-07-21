/******************************************************************************
Trabajo 1: Ahorcado numérico
Problema: Realizar un juego para adivinar números naturales grandes entre 10 y 20 dígitos. Para ello debe:
  1. Tener un archivo con números naturales.
  2. Sacar un número del archivo que:
    a) Tenga entre 10 y 20 dígitos.
    b) Tenga al menos 4 dígitos diferentes.
    c) No contenga un mismo dígito 4 o más veces en forma consecutiva.
  3. En 5 intentos debe adivinar el número. A partir del tercer intento dar pistas.

Estudiante: Víctor Gutiérrez
Profesor: Yuri Cáceres

Programa compilado con g++ (Debian 10.2.1-6) 10.2.1 20210110
*******************************************************************************/

#include <iostream>
#include <fstream>
using namespace std;

// Función que limpia la pantalla
void limpiar_pantalla();
// Función que imprime un número de saltos de línea
void imprimir_lineas(int numero_lineas);
// Función que convierte un caracter a entero
int caracter_a_entero(char c);
// Función que lee un archivo
bool leer_archivo(string nombre, ifstream& f);
// Función que obtiene un número válido de un archivo
bool obtener_numero_valido(string &numero_secreto, ifstream& f);
// Función que comprueba si un número es válido llamando a distintas funciones de validación
bool numero_valido(string num);
// Función para validar la longitud de un número
bool validar_longitud(int longitud);
// Función que valida que un número tenga al menos 4 dígitos diferentes
bool validar_diferentes(string num, int longitud_num);
// Función que valida que un mismo dígito no se encuentre 4 o más veces de forma consecutiva en un número
bool validar_no_consecutivos(string num, int longitud_num);
// Función que encapsula la lógica del juego
void jugar(string numero_secreto);
// Función que activa una nueva pista aleatoriamente
void activar_nueva_pista(bool pistas_activas[]);
// Función que detecta una entrada inválida de parte del usuario
bool entrada_invalida(string numero_ingresado);
// Función que imprime la parte principal del juego
void imprimir_juego(string numero_secreto, int adivinados[], int longitud_num, int vidas, bool pistas_activas[]);
// Función que calcula la cantidad de dígitos que faltan por adivinar
int obtener_por_adivinar(string numero_secreto, int adivinados[], int longitud_num);
// Función que administra la lógica de la impresión de los dígitos adivinados
void mostrar_adivinados(string numero_secreto, int adivinados[], int longitud_num);
// Función que imprime los números propiamente tales
void imprimir_numero(int numero, int linea);
// Función que imprime las pistas
void mostrar_pistas(string numero_secreto, int adivinados[], int longitud_num, bool pistas_activas[]);
// Tipo de dato agregado utilizado para mostrar pistas pertinentes
struct infoPistas {
  int primos = 0;
  int pares = 0;
  int cuadrados = 0;
  int multiplo_3 = 0;
  int multiplo_4 = 0;
  int mayor_5 = 0;
  int fibonaccis = 0;
  int oblongos = 0;
  int pi = 0;
  int e = 0;
};
// Función que procesa la información de las pistas operando sobre el tipo de dato agregado anterior
void procesar_info_pistas(int numero, infoPistas& info);
// Función que muestra las pistas en pantalla
void mensaje_pistas(bool pistas_activas[], infoPistas info);

// Función principal
int main() {
  // Nombre del archivo con números, variable donde se guardará cada número encontrado
  // y opción para seguir o no jugando
  string nombre_archivo, numero_secreto, opcion;
  // Variables que indican si un archivo y un número son válidos
  bool archivo_valido, numero_valido;
  // Archivo con números
  ifstream archivo;

  do {
    limpiar_pantalla();
    imprimir_lineas(10);
    cout << "\t\tIngresa el nombre del archivo con números o un punto para salir: ";
    getline(cin, nombre_archivo);

    if (nombre_archivo[0] == '.' && nombre_archivo.length() == 1) return 0;
  } while (!leer_archivo(nombre_archivo, archivo));

  while (obtener_numero_valido(numero_secreto, archivo)) {
    jugar(numero_secreto);

    cout << "¿Deseas seguir jugando? (N para salir/cualquier otro caracter para continuar): ";
    getline(cin, opcion);

    if ((opcion[0] == 'n' || opcion[0] == 'N') && opcion.length() == 1) {
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

void limpiar_pantalla() {
  cout << u8"\033[2J\033[1;1H";
}

void imprimir_lineas(int numero_lineas) {
  for (int i = 0; i < numero_lineas; i++) cout << endl;
}

int caracter_a_entero(char c) {
  return c - '0';
}

bool leer_archivo(string nombre, ifstream &f) {
  f.open(nombre);
  return !f.fail();
}

bool obtener_numero_valido(string &numero_secreto, ifstream &f) {
  while (f >> numero_secreto) {
    if (numero_valido(numero_secreto)) return true;
  }
  return false;
}

bool numero_valido(string num) {
  // Cantidad de dígitos del número secreto
  int cuenta_digitos = num.length();
  if (
    !validar_longitud(cuenta_digitos) ||
    !validar_no_consecutivos(num, cuenta_digitos) ||
    !validar_diferentes(num, cuenta_digitos)
  ) return false;

  return true;
}

bool validar_longitud(int longitud) {
  return !(longitud < 10 || longitud > 20);
}

bool validar_diferentes(string num, int longitud_num) {
  // Arreglo que indica si un dígito ya fue encontrado
  int digito[10] = { 0 };
  // Dígito actual
  int num_actual;
  // Cantidad de dígitos diferentes
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

bool validar_no_consecutivos(string num, int longitud_num) {
  for (int i = 0; i <= longitud_num - 4; i++) {
    if (
      num[i] == num[i + 1] &&
      num[i + 1] == num[i + 2] &&
      num[i + 2] == num[i + 3]
    ) return false;
  }
  return true;
}

void jugar(string numero_secreto) {
  // Entrada por consola del usuario
  string entrada_usuario;
  // Indicador de error de entrada del usuario
  bool error_entrada = false;
  // Número ingresado por el usuario y cantidad de números por adivinar (actual y previamente)
  int numero_ingresado, por_adivinar, previo_por_adivinar;
  // Longitud del número secreto
  int longitud_num = por_adivinar = numero_secreto.length();
  // Cantidad de vidas restantes
  int vidas = 5;
  // Arreglo que indica si un dígito ya fue adivinado/ingresado
  int adivinados[10] = { 0 };
  // Arreglo que maneja las pistas activas
  bool pistas_activas[10] = { 0 };

  while (vidas != 0 && por_adivinar != 0) {
    if (vidas < 3 && vidas != 0 && !error_entrada) activar_nueva_pista(pistas_activas);
    imprimir_juego(numero_secreto, adivinados, longitud_num, vidas, pistas_activas);

    if (error_entrada) cout << "\n\t\t\t\tInfo: Debes ingresar SÓLO un número\n";
    if (vidas == 1) cout << "\n\t\t\t\t\t¡¡¡Última vida!!!\n";
    cout << "\n\t\t\tIngresa un número: ";
    getline(cin, entrada_usuario);
    
    if (entrada_invalida(entrada_usuario)) {
      error_entrada = true;
    } else {
      error_entrada = false;
      numero_ingresado = caracter_a_entero(entrada_usuario[0]);
      adivinados[numero_ingresado] = 1;

      previo_por_adivinar = por_adivinar;
      por_adivinar = obtener_por_adivinar(numero_secreto, adivinados, longitud_num);

      if (previo_por_adivinar == por_adivinar) vidas--;
    }
  }

  imprimir_juego(numero_secreto, adivinados, longitud_num, vidas, pistas_activas);
  imprimir_lineas(3);
  if (por_adivinar == 0) {
    cout << "\t\t\t\t✨ ¡¡¡Felicitationes, ganaste!!! 🎉🥳\n";
  } else {
    cout << "\t\t\tPerdiste 😔. El número era: ";
    for (int i = 0; i < longitud_num; i++) cout << numero_secreto[i] << " ";
    cout << endl;
  }
  imprimir_lineas(3);
}

void activar_nueva_pista(bool pistas_activas[]) {
  // Opción de pista al azar entre 0 y 9
  int opcion;
  // Cantidad de pistas activas
  int cuenta_pistas_activas = 0;

  for (int i = 0; i < 10; i++) if (pistas_activas[i]) cuenta_pistas_activas++;
  if (cuenta_pistas_activas != 10) {
    // Inicialización de obtención de números al azar
    srand((unsigned) time(NULL));
    opcion = rand() % 10;
    while (pistas_activas[opcion]) opcion = rand() % 10;
    pistas_activas[opcion] = true;
  }
}

bool entrada_invalida(string numero_ingresado) {
  if (
    numero_ingresado.length() != 1 ||
    numero_ingresado[0] < '0' ||
    numero_ingresado[0] > '9'
  ) return true;
  
  return false;
}

void imprimir_juego(string numero_secreto, int adivinados[], int longitud_num, int vidas, bool pistas_activas[]) {
  limpiar_pantalla();
  imprimir_lineas(6);

  cout << "\t\t\tAdivina el número de " << longitud_num << " dígitos\n";
  cout << "\t\t\tVidas: ";
  for (int i = 0; i < vidas; i++) cout << "❤️ ";
  cout << endl;
  
  imprimir_lineas(2);    
  mostrar_adivinados(numero_secreto, adivinados, longitud_num);

  imprimir_lineas(3);
  if (vidas < 3) mostrar_pistas(numero_secreto, adivinados, longitud_num, pistas_activas);
  cout << endl;
}

int obtener_por_adivinar(string numero_secreto, int adivinados[], int longitud_num) {
  // Cantidad de números por adivinar
  int por_adivinar = 0;
  // Dígito actual a procesar
  int digito_actual;
  for (int i = 0; i < longitud_num; i++) {
    digito_actual = caracter_a_entero(numero_secreto[i]);
    if (adivinados[digito_actual] == 0) por_adivinar++;
  }
  return por_adivinar;
}

void mostrar_adivinados(string numero_secreto, int adivinados[], int longitud_num) {
  // Dígito procesado actualmente
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

void mostrar_pistas(string numero_secreto, int adivinados[], int longitud_num, bool pistas_activas[]) {
  // Dígito procesado actualmente
  int digito_actual;
  // Tipo de dato agregado que contiene la información de las pistas
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

void procesar_info_pistas(int numero, infoPistas& info) {
  switch(numero) {
    case 0: {
      info.cuadrados++;
      info.pares++;
      info.oblongos++;
      break;
    }
    case 1: {
      info.cuadrados++;
      info.fibonaccis++;
      info.e++;
      info.pi++;
      break;
    }
    case 2: {
      info.pares++;
      info.primos++;
      info.fibonaccis++;
      info.oblongos++;
      info.e++;
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
      info.pi++;
      break;
    }
    case 5: {
      info.primos++;
      info.fibonaccis++;
      info.mayor_5++;
      info.pi++;
      break;
    }
    case 6: {
      info.pares++;
      info.multiplo_3++;
      info.mayor_5++;
      info.oblongos++;
      break;
    }
    case 7: {
      info.primos++;
      info.mayor_5++;
      info.e++;
      break;
    }
    case 8: {
      info.pares++;
      info.fibonaccis++;
      info.multiplo_4++;
      info.mayor_5++;
      info.e++;
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
        case 7:
          if (info.oblongos == 0)
            cout << "\t||  - No quedan números oblongos por adivinar\t\t\t ||\n";
          else if (info.oblongos == 1)
            cout << "\t||  - Te queda 1 número oblongo por adivinar\t\t\t ||\n";
          else
            cout << "\t||  - Te quedan " << info.oblongos << " números oblongos por adivinar\t\t\t ||\n";
          break;
        case 8:
          if (info.pi == 0)
            cout << "\t||  - No quedan de los primeros 4 decimales de pi por adivinar   ||\n";
          else if (info.pi == 1)
            cout << "\t||  - Te queda 1 de los primeros 4 decimales de pi por adivinar  ||\n";
          else
            cout << "\t||  - Te quedan " << info.pi << " de los primeros 4 decimales de pi por adivinar ||\n";
          break;
        case 9:
          if (info.e == 0)
            cout << "\t||  - No quedan de los primeros 4 decimales de e por adivinar\t ||\n";
          else if (info.e == 1)
            cout << "\t||  - Te queda 1 de los primeros 4 decimales de e por adivinar   ||\n";
          else
            cout << "\t||  - Te quedan " << info.e << " de los primeros 4 decimales de e por adivinar  ||\n";
          break;
      }
    }
  }
  cout << "\t ================================================================\n";
}