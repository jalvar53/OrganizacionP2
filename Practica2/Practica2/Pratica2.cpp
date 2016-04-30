#include <iostream>
#include <math.h>
#include <time.h>
#include "Practica2.h"

#define MSIZE 4

using namespace std;

int main()
{
	srand((unsigned)time(NULL)); //Se genera la semilla para los numeros aleatorios
	int input;
	int operacion;
	float matriz1[MSIZE][MSIZE];
	float matriz2[MSIZE][MSIZE];
	float matrizResultado[MSIZE][MSIZE];
	for (int i = 0; i < MSIZE; i++)
		for (int j = 0; j < MSIZE; j++) {
			matrizResultado[i][j] = 0;
			matriz1[i][j] = 0;
			matriz2[i][j] = 0;
		}
	
	while(true){ // El programa correra hasta que el usuario escoja cerrarlo
		input = mostrarMenu(); // Muestra las opciones
		operacion = 0; // Limpia la operacion anterior si es que existe
		switch (input){ // Escoge la opcion que recibio en MostrarMenu();
			case 1:
				// Ingresar matriz dato a dato
				cout << endl << "Escoja la matriz a llenar:" << endl;
				cout << "1) Matriz #1" << endl;
				cout << "2) Matriz #2" << endl;
				cout << "3) Volver al menu." << endl << endl;
				cout << "Opcion:";
				cin >> input;
				if (input == 1) {
					cout << "Ingrese los valores para la matriz #1" << endl;
					//matriz1 = LlenarMatriz(matriz1);
					llenarMatriz(matriz1);
				}
				else if(input == 2){
					cout << "Ingrese los valores para la matriz #2" << endl;
					//matriz2 = LlenarMatriz(matriz2);
					llenarMatriz(matriz2);
				}
				break;
			case 2:
				//Llenar la matriz de forma aleatorioa
				cout << endl << "Escoja la matriz a llenar:" << endl;
				cout << "1) Matriz #1" << endl;
				cout << "2) Matriz #2" << endl;
				cout << "3) Volver al menu." << endl << endl;
				cout << "Opcion:";
				cin >> input;
				if (input == 1) {
					llenarAleatorios(matriz1);
				}
				else if (input == 2) {
					llenarAleatorios(matriz2);
				}
				break;
			case 3:
				//Imprimir toda la matriz
				cout << endl << "Escoja la matriz a imprimir:" << endl;
				cout << "1) Matriz #1" << endl;
				cout << "2) Matriz #2" << endl;
				cout << "3) Matriz Resultado" << endl;
				cout << "4) Imprimir todas" << endl;
				cout << "5) Volver al menu." << endl << endl;
				cout << "Opcion:";
				cin >> input;
				if (input == 1) {
					imprimirMatriz(matriz1);
				}
				else if (input == 2) {
					imprimirMatriz(matriz2);
				}
				else if(input == 3){
					imprimirMatriz(matrizResultado);
				}
				else if (input == 4) {
					cout << endl << "Matriz 1:";
					imprimirMatriz(matriz1);
					cout << endl << "Matriz 2:";
					imprimirMatriz(matriz2);
					cout << endl << "Matriz Resultado:";
					imprimirMatriz(matrizResultado);
				}
				break;
			case 4:
				//Mostrar operaciones
				operacion = mostrarOperaciones();
				break;
			case 5:
				exit(1);
			default:
				//Excepción
				cout << "Entrada invalida." << endl;
				break;
		}

		if (operacion != 0) {
			int funcion;	//Guarda la operacion a realizar
			int iteradorEDX;
			int iteradorEBX;
			int recolector;

			//Se carga la operacion indicada en la variable funcion para luego ser llamada al recorrer la matriz
			_asm {
				MOV EAX,operacion
				CMP EAX,1
				JE SUMA
				CMP EAX,2
				JE RESTA
				CMP EAX,3
				JE MULTIPLICACION
				CMP EAX,4
				JE DIVISION
				JMP FIN
				SUMA:
					MOV EAX,pSuma
					MOV funcion,EAX
					JMP FIN
				RESTA:
					MOV EAX,pResta
					MOV funcion,EAX
					JMP FIN
				MULTIPLICACION:
					MOV EAX,pMultiplicacion
					MOV funcion,EAX
					JMP FIN
				DIVISION:
					MOV EAX,pDivision
					MOV funcion,EAX
					JMP FIN
				FIN:
					NOP
			}

			//Recorrido de la matriz para realizar la operacion
			_asm{
				MOV EDX, 0	//Coloca en cero los iteradores de las filas y las columnas
				MOV EBX, 0
				CICLO_DE_RECORRIDO_FILAS:
					CICLO_DE_RECORRIDO_COLUMNAS:
						MOV iteradorEDX,EDX	//Se guarda el valor de EDX en la variable iterador pues este registro es usado en la multiplicacion
						MOV EAX,4	//Se guarda 4 en eax, pues la matriz es de 4 filas
						MUL EBX		//Se multiplica EBX por 4(EAX) para obtener la posicion del primer dato de la fila
						MOV EDX, iteradorEDX	//Se carga EDX
						ADD EAX,EDX	//Se suma la columna a EAX para obtener la posicion exacta en la matriz
						MOV EAX,matriz2[EAX*TYPE float]	//Se accede a la posicion de la matriz 2 con la direccion de memoria
						PUSH EAX
						MOV EAX,4
						MUL EBX
						MOV EDX, iteradorEDX
						ADD EAX,EDX
						MOV EAX,matriz1[EAX*TYPE float]
						PUSH EAX
						MOV EAX,funcion	//Se carga la operacion definida en EAX
						MOV iteradorEBX,EBX
						MOV iteradorEDX,EDX
						CALL EAX	//Se llama la operacion
						POP recolector
						POP recolector
						MOV EBX,iteradorEBX
						MOV EDX,iteradorEDX
						MOV EAX,4
						MUL EBX
						MOV EDX, iteradorEDX
						ADD EAX,EDX
						FST matrizResultado[EAX*TYPE float]
						INC EDX
						CMP EDX,4
						JNE CICLO_DE_RECORRIDO_COLUMNAS
					MOV EDX,0
					INC EBX
					CMP EBX,4
					JNE CICLO_DE_RECORRIDO_FILAS
			}
		}
	}
	return 0;
}

int mostrarMenu() {
	cout << endl << "Menu principal:" << endl;
	cout << "1) Para ingresar una matriz elemento por elemento." << endl;
	cout << "2) Llenar la matriz con numeros aleatorios." << endl;
	cout << "3) Imprimir una matriz." << endl;
	cout << "4) Realizar una operacion sobre las matrices." << endl;
	cout << "5) Cerrar el programa." << endl << endl;
	cout << "Opcion:";
	int input;
	cin >> input;
	return input;
}

int mostrarOperaciones() {
	cout << "Menu operaciones:" << endl;
	cout << "1) Suma." << endl;
	cout << "2) Resta." << endl;
	cout << "3) Multiplicacion." << endl;
	cout << "4) Division." << endl;
	cout << "5) Volver al menu." << endl << endl;
	cout << "Opcion:";
	int input;
	cin >> input;
	return input;
}

void imprimirMatriz(float matriz[MSIZE][MSIZE]) {
	for (int i = 0; i < MSIZE; ++i){
		cout << endl << "[|";
		for (int j = 0; j < MSIZE; ++j){
			cout << matriz[i][j] << "|";
		}
		cout << "]";
	}
	cout << endl;
}

void llenarMatriz(float matriz[MSIZE][MSIZE]) {
	for (int i = 0; i < MSIZE; ++i) {
		for (int j = 0; j < MSIZE; ++j) {
			cout << "[" << i << "][" << j << "]: ";
			cin >> matriz[i][j];
		}
	}
	//return matriz;
}

float pSuma(float numA, float numB) {
	__asm {
		FFREE ST(0)	//Se limpia la pila para asegurarse de que no haya registros anteriores
		FLD numA	//Se carga numA en la pila del coprocesador matematico
		FLD numB	//Se carga numB en la pila del coprocesador matematico
		FADD ST(0),ST(1)	//Se hace la operacion st(0) = st(0)+st(1)
		FFREE ST(1)			//Se limpia st(1) para que la en la pila solo quede el resultado
	}
	//El valor de retorno queda en ST(0)
}

float pResta(float numA, float numB) {
	__asm {
		FFREE ST(0)
		FLD numB	//Se agrega primero numB para que este quede en st(1) al agregar numA
		FLD numA	//Se agrega numA y queda en st(0) en la pila del coprocesador matematico
		FSUB ST(0),ST(1)	//Se hace la operacion st(0)=st(0)-st(1)
		FFREE ST(1)
	}
}

float pMultiplicacion(float numA, float numB) {
	__asm {
		FFREE ST(0)
		FLD numA
		FLD numB
		FMUL ST(0),ST(1)
		FFREE ST(1)
	}
}

float pDivision(float numA, float numB) {
	__asm {
		FFREE ST(0)
		FLD numB
		FLD numA
		FDIV ST(0),ST(1)
		FFREE ST(1)
	}
}

void llenarAleatorios(float matriz[MSIZE][MSIZE]) {
	for (int i = 0; i < MSIZE; i++)
		for (int j = 0; j < MSIZE; j++) {
			matriz[i][j] = (sin((float)rand()) + 1.0)*50.0;
		}
}