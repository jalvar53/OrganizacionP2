#include "iostream"
#include "Practica2.h"
#define mSize 4

using namespace std;

int main()
{
	int input;
	int operacion;
	float** matriz1 = AsignarMatriz();
	float** matriz2 = AsignarMatriz();
	float** matrizResultado = AsignarMatriz();;
	float resultado;

	while(true){ // El programa correra hasta que el usuario escoja cerrarlo
		input = mostrarMenu(); // Muestra las opciones
		operacion = 0; // Limpia la operacion anterior si es que existe
		switch (input) // Escoge la opcion que recibio en MostrarMenu();
		{
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
			//Ingresar toda la matriz
			cout << "Operacion aun no soportada." << endl;
			system("pause");
			cout << endl;
			break;
		case 3:
			//Ingresar toda la matriz
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
			for (int i = 0; i < mSize; i++) {
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
			switch (input)
			{
			case 0:
				for (int i = 0; i < mSize; ++i) {
					for (int j = 0; j < mSize; ++j) {
						resultado = pSuma(matriz1[i][j], matriz2[i][j]);
						matrizResultado[i][j] = resultado;
					}
				}
			case 1:
				for (int i = 0; i < mSize; ++i) {
					for (int j = 0; j < mSize; ++j) {
						resultado = pResta(matriz1[i][j], matriz2[i][j]);
						matrizResultado[i][j] = resultado;
					}
				}
			case 2:
				for (int i = 0; i < mSize; ++i) {
					for (int j = 0; j < mSize; ++j) {
						resultado = pMultiplicacion(matriz1[i][j], matriz2[i][j]);
						matrizResultado[i][j] = resultado;
					}
				}
			case 3:
				for (int i = 0; i < mSize; ++i) {
					for (int j = 0; j < mSize; ++j) {
						resultado = pDivision(matriz1[i][j], matriz2[i][j]);
						matrizResultado[i][j] = resultado;
					}
				}
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
	cout << "3) Imprmir una matriz." << endl;
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
	for (int i = 0; i < mSize; ++i){
		cout << endl;
		for (int j = 0; j < mSize; ++j){
			cout << matriz[i][j] << "\t";
		}
	}
	cout << endl;
}

float** AsignarMatriz() {
	float** matriz;
	matriz = new float*[mSize];
	for (int i = 0; i < mSize; ++i)
	{
		matriz[i] = new float[mSize];
	}
	for (int i = 0; i < mSize; ++i) {
		for (int j = 0; j < mSize; ++j) {
			matriz[i][j] = 0.0;
		}
	}
	return matriz;
}

float** LlenarMatriz(float** matriz) {
	for (int i = 0; i < mSize; ++i) {
		for (int j = 0; j < mSize; ++j) {
			cout << "[" << i << "][" << j << "]: ";
			cin >> matriz[i][j];
		}
	}
	return matriz;
}

float pSuma(float numA, float numB) {

	__asm {

	}

	return 0.0;
}

float pResta(float numA, float numB) {

	__asm {

	}

	return 0.0;
}

float pMultiplicacion(float numA, float numB) {

	__asm {

	}

	return 0.0;
}

float pDivision(float numA, float numB) {

	__asm {

	}

	return 0.0;
}