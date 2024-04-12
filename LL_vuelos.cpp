#include <iostream>
#include <fstream>
#include <string.h>
#include <cstring>
#include <Windows.h>

using namespace std;

struct nodo_vuelos {
	int ID_vuelo;
	char Estatus[10];
	char Origen[20];
	char Destino[20];
	int Asientos_T;
	int Asientos_E;
	float Precio_T;
	float Precio_E;
	nodo_vuelos* ant, * sig;
} *ini_vuelos, * fin_vuelos, * aux_vuelos;
//Agregar vuelo
void agregar_vuelo(nodo_vuelos* nuevo) {
	// agregar a la lista
	if (ini_vuelos == 0) {
		ini_vuelos = nuevo;
		fin_vuelos = nuevo;
	}
	else {
		fin_vuelos->sig = nuevo;
		nuevo->ant = fin_vuelos;
		fin_vuelos = nuevo;
	}
}

//Capturar Vuelo
void captura_vuelo(nodo_vuelos* nodo) {
	system("cls");
	printf("--Captura de vuelos--\n");
	cout << "ID: ";cin >> nodo->ID_vuelo;
	cout << "Estatus: "; cin >> nodo->Estatus;
	cout << "Origen: "; cin >> nodo->Origen;
	cout << "Destino: "; cin >> nodo->Destino;
	cout << "Asientos tipo turista: "; cin >> nodo->Asientos_T;
	cout << "Costo por asiento: "; cin >> nodo->Precio_T;
	cout << "Asientos tipo Ejecutivo:"; cin >> nodo->Asientos_T;
	cout << "Costo por asiento: "; cin >> nodo->Precio_E;
}

//Eliminar vuelo
void elimina_vuelo() {
	if (aux_vuelos == ini_vuelos) {
		//elimina el primero
		aux_vuelos = ini_vuelos;
		if (ini_vuelos != 0) {
			if (ini_vuelos == fin_vuelos) {
				ini_vuelos = 0;
				fin_vuelos = 0;
			}
			else {
				ini_vuelos = aux_vuelos->sig;
				ini_vuelos->ant = 0;
			}
			delete aux_vuelos;
		}
	}
	else {
		//elimina el ultimo
		if (aux_vuelos == fin_vuelos) {
			aux_vuelos = fin_vuelos;
			if (fin_vuelos != 0) {
				if (ini_vuelos == fin_vuelos) {
					ini_vuelos = 0;
					fin_vuelos = 0;
				}
				else {
					fin_vuelos = aux_vuelos->ant;
					fin_vuelos->sig = 0;
				}
				delete aux_vuelos;
			}
		}
		else
		{
			aux_vuelos->ant->sig = aux_vuelos->sig;
			aux_vuelos->sig->ant = aux_vuelos->ant;
			delete aux_vuelos;
		}
	}

}

//Leer archivo
void leer_arch_vuelos(char archivo[]) {
	ifstream archivaldo;
	archivaldo.open(archivo, ios::binary);
	if (archivaldo.is_open()) {
		//leer archivo, byte x byte y crear la lista ligada
		aux_vuelos = new nodo_vuelos;
		archivaldo.read((char*)aux_vuelos, sizeof(nodo_vuelos));
		aux_vuelos->ant = 0;
		aux_vuelos->sig = 0;
		while (!archivaldo.eof()) {
			agregar_vuelo(aux_vuelos);

			aux_vuelos = new nodo_vuelos;
			archivaldo.read((char*)aux_vuelos, sizeof(nodo_vuelos));
			aux_vuelos->ant = 0;
			aux_vuelos->sig = 0;
		}
	}
	archivaldo.close();
}

//Escribir archivo
void escribe_arch_vuelos(char archivo[]) {
	ofstream archivaldo;
	archivaldo.open(archivo, ios::binary | ios::trunc);
	if (archivaldo.is_open()) {
		aux_vuelos = ini_vuelos;////1
		while (aux_vuelos != 0) {//////2
			// escribir en el archivo, nodo x nodo
			archivaldo.write((char*)aux_vuelos, sizeof(nodo_vuelos));

			aux_vuelos = aux_vuelos->sig;////3
		}
		archivaldo.close();
		printf("archivo guardado");
	}
	else {
		printf("archivo no se pudo abrir");
	}
}

//Buscar Vuelo
bool buscar_vuelo(int busqueda) {
	aux_vuelos = ini_vuelos;//1
	while (aux_vuelos != 0)//2
	{
		if (aux_vuelos->ID_vuelo == busqueda) {
			return true;
			break;
		}

		aux_vuelos = aux_vuelos->sig;//3
	}
	return false;
}

//Imprimir datos

void imprimir_vuelos(nodo_vuelos* nodo) {	
	cout << "ID: " << nodo->ID_vuelo << endl;
	cout << "Estatus: " << nodo->Estatus << endl;
	cout << "Origen: " << nodo->Origen << endl;
	cout << "Destino: " << nodo->Destino<< endl;
	cout << "Asientos tipo turista: " << nodo->Asientos_T << " Costo por asiento: "<< nodo->Precio_T << endl; 
	cout << "Asientos tipo Ejecutivo:" << nodo->Asientos_T << " Costo por asiento: "<< nodo->Precio_E << endl; 
}

int main() {
	//para los archivos de texto
	char carpeta[MAX_PATH] = ""; 
	char archi[] = "\\vuelos.dat";
	GetCurrentDirectory(MAX_PATH, carpeta); 
	strncat_s(carpeta, archi, sizeof(carpeta) - strlen(carpeta) - 1); 
	short opc, opc_;
	int ID;
	leer_arch_vuelos(carpeta);

	do {
		system("cls");
		printf("  SISTEMA DE VUELOS\n");
		printf("1. Agregar vuelo\n");
		printf("2. Eliminar vuelo\n");
		printf("3. Buscar vuelo\n");
		printf("4. Lista de vuelos (ini)\n");
		printf("5. Salir\n");
		cin >> opc; 

		switch (opc)
		{
		case 1: {
			nodo_vuelos* aux_vuelos;
			aux_vuelos = new nodo_vuelos;
			aux_vuelos->ant = nullptr;
			aux_vuelos->sig = nullptr;
			captura_vuelo(aux_vuelos);
			agregar_vuelo(aux_vuelos);

		}break;

		case 2: {
			system("cls");
			cout << "ID del vuelo:";
			cin >> ID; 
			if (buscar_vuelo(ID) == true)
			{
				elimina_vuelo(); 
				cout << endl;
				cout << "Vuelo "<< ID << " eliminado"; 
				system("pause");

			}

		}break;

		case 3: {
			system("cls"); 
			cout << "ID del vuelo:"; 
			cin >> ID; 
			if (buscar_vuelo(ID) == true) 
			{
				system("cls");
				imprimir_vuelos(aux_vuelos);
				cout << "Desea 1) Modificar 2) Eliminar" << endl;
				cin >> opc_;				
				if (opc_ == 1) {
					captura_vuelo(aux_vuelos);
					cout << "Vuelo modificado" << endl;
					system("PAUSE");
				}
				if (opc_ == 2) {
					elimina_vuelo();
					cout << "Vuelo eliminado" << endl;
					system("PAUSE"); 
				}
			}
			else {
				cout << "No existe ese vuelo";
				system("pause"); 
			}
		}break;

		case 4: {
			system("cls"); 
			aux_vuelos = ini_vuelos; 

			while (aux_vuelos != 0)
			{
				imprimir_vuelos(aux_vuelos); 
				 
				aux_vuelos = aux_vuelos->sig;  
			}
			system("pause");
		}break;

		default:
			break;
		}
		


	} while (opc < 5);

	escribe_arch_vuelos(carpeta);

	system("pause"); 
}