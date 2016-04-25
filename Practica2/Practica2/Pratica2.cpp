#include "iostream"
#define mSize 4

using namespace std;

float** inicializarMatriz();

int main(int argc, char* argv[])
{

	cout << "Ingrese 0 para entrar la matriz elemento por elemento." << endl;
	cout << "Ingrese 1 para entrar la matriz entera." << endl;

	int input;
	cin >> input;

	float** matriz1;
	float** matriz2;
	float** matrizResultado;
	float resultado;

	switch (input)
	{
	case 0:
		cout << "Ingrese los valores para la matriz #1" << endl;
		matriz1 = inicializarMatriz();
		cout << "Ingrese los valores para la matriz #2" << endl;
		matriz2 = inicializarMatriz();
	case 1:
		//Ingresar toda la matriz
	default:
		//Excepción
		break;
	}

	cout << "Ingrese 0 para suma, 1 para resta, 2 para multiplicacion o 3 para división" << endl;
	int operacion;
	cin >> operacion;

	switch (operacion)
	{
	case 0:
		for (int i = 0; i < mSize; ++i){
			for (int j = 0; j < mSize; ++j){
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

	for (int i = 0; i < mSize; i++){
		delete[] matriz1[i];
		delete[] matriz2[i];
	}
	delete[] matriz1;
	delete[] matriz2;

	return 0;
}

void imprimirMatriz(float** matriz) {
	for (int i = 0; i < mSize; ++i){
		cout << "Fila " << i << endl;
		for (int j = 0; j < mSize; ++j){
			cout << "Columna " << j << endl;
			cout << matriz[i][j] << endl;
		}
	}
}

float** inicializarMatriz() {

	float** matriz;
	matriz = new float*[mSize];

	for (int i = 0; i < mSize; ++i)
	{
		matriz[i] = new float[mSize];
	}
	for (int i = 0; i < mSize; ++i) {
		cout << "Fila " << i << " " << endl;
		for (int j = 0; j < mSize; ++j) {
			cout << "Columna " << j << " " << endl;
			cin >> matriz[i][j];
		}
	}
	return matriz;
}

float pSuma(float numA, float numB) {

	__asm {

	}

	return;
}

float pResta(float numA, float numB) {

	__asm {

	}

	return;
}

float pMultiplicacion(float numA, float numB) {

	__asm {

	}

	return;
}

float pDivision(float numA, float numB) {

	__asm {

	}

	return;
}