#include <iostream>
#include "Practica2.h"
#define MSIZE 4

using namespace std;

int main()
{
	int input;
	int operacion;
	float** matriz1 = AsignarMatriz(); 
	float** matriz2 = AsignarMatriz();
	float** matrizResultado = AsignarMatriz();

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
					matriz1 = LlenarMatriz(matriz1);
				}
				else if(input == 2){
					cout << "Ingrese los valores para la matriz #2" << endl;
					matriz2 = LlenarMatriz(matriz2);
				}
				break;
			case 2:
				//Ingresar toda la matriz por archivo
				cout << "Operacion aun no soportada." << endl;
				system("pause");
				cout << endl;
				break;
			case 3:
				//Imprimir toda la matriz
				cout << endl << "Escoja la matriz a imprimir:" << endl;
				cout << "1) Matriz #1" << endl;
				cout << "2) Matriz #2" << endl;
				cout << "3) Matriz Resultado" << endl;
				cout << "4) Volver al menu." << endl << endl;
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
				break;
			case 4:
				//Mostrar operaciones
				operacion = mostrarOperaciones();
				break;
			case 5:
				//Termina el programa y borra las matrices
				for (int i = 0; i < MSIZE; i++) {
					delete[] matriz1[i];
					delete[] matriz2[i];
					delete[] matrizResultado[i];
				}
				delete[] matriz1;
				delete[] matriz2;
				delete[] matrizResultado;
				exit(1);
			default:
				//Excepción
				cout << "Entrada invalida." << endl;
				break;
		}

		if (operacion != 0) {
			// Esto no es así porque hay que iterar en Assembler.
			expMatrices(matriz1,matriz2); //Carga las matrices en posiciones accesibles desde ASM
			
			switch (operacion){
				case 1:
					//Suma en ASM
					_asm {

					}
					matrizResultado[0][0] = pSuma(matriz1[0][0], matriz2[0][0]);
					break;
				case 2:
					//Resta en ASM
					matrizResultado[0][0] = pResta(matriz1[0][0], matriz2[0][0]);
					break;
				case 3:
					//Multiplicacion en ASM
					matrizResultado[0][0] = pMultiplicacion(matriz1[0][0], matriz2[0][0]);
					break;
				case 4:
					//Division en ASM
					matrizResultado[0][0] = pDivision(matriz1[0][0], matriz2[0][0]);
					break;
				case 5:
					//TEST PARA SACAR EL VALOR DE LA MATRIZ EN LA POSICION 0,0 DE LA MATRIZ 1 CON ASM
					float valor;
					_asm {
						MOV EAX,matriz1
						MOV EAX,[EAX]
						MOV EAX,[EAX]
						MOV valor,EAX
					}
					cout << valor << endl;
					break;
				default:
					break;
			}
		}
	}
	return 0;
}

int mostrarMenu() {
	cout << endl << "Menu principal:" << endl;
	cout << "1) Para ingresar una matriz elemento por elemento." << endl;
	cout << "2) Ingresar una matriz por archivo." << endl;
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

void imprimirMatriz(float** matriz) {
	for (int i = 0; i < MSIZE; ++i){
		cout << endl;
		for (int j = 0; j < MSIZE; ++j){
			cout << matriz[i][j] << "\t";
		}
	}
	cout << endl;
}

float** AsignarMatriz() {
	float** matriz;
	matriz = new float*[MSIZE];
	for (int i = 0; i < MSIZE; ++i)
	{
		matriz[i] = new float[MSIZE];
	}
	for (int i = 0; i < MSIZE; ++i) {
		for (int j = 0; j < MSIZE; ++j) {
			matriz[i][j] = 0.0;
		}
	}
	return matriz;
}

float** LlenarMatriz(float** matriz) {
	for (int i = 0; i < MSIZE; ++i) {
		for (int j = 0; j < MSIZE; ++j) {
			cout << "[" << i << "][" << j << "]: ";
			cin >> matriz[i][j];
		}
	}
	return matriz;
}

void expMatrices(float** matriz1, float** matriz2) {
	__asm {
		MOV eax, ecx
		MOV ebx, edx
	}
}

float pSuma(float numA, float numB) {

	__asm {
		FFREE ST(0)	//Se limpia la pila para asegurarse de que nohaya registros anteriores
		FLD numA	//Se carga numA en la pila del coprocesador matematico
		FLD numB	//Se carga numB en la pila del coprocesador matematico
		FADD ST(0),ST(1)	//Se hace la operacion st(0) = st(0)+st(1)
		FFREE ST(1)			//Se limpia st(1) para que la pila quede limpia
	}
	//Se retorna el valor que queda en ST(0) automaticamente
}

float pResta(float numA, float numB) {
	__asm {
		FFREE ST(0)
		FLD numB	//Se agrega primero numB para que este quede en st(1) al agregar numa
		FLD numA	//Se agrega numA y queda en st(0) en la pila del coprocesador matematico
		FSUB ST(0),ST(1)	//Se hace la operacion st(0)=st(0)-st(1)
		FFREE ST(1)
	}
}

float pMultiplicacion(float numA, float numB) {
	__asm {
		FFREE ST(1)
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