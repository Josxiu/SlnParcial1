#pragma warning(disable : 4996)
#include <iostream>
#include <string.h>
using namespace std;

//Sin estructuras
//punteros y datos
char** usuarios,**nombres,**profesiones,**origenes;// Punteros dobles que contendran la informacion de todos los datos de los usuarios (matriz)
char* usuario,*nombre,*profesion,*origen;// Punteros que se utilizaran para introducir la informacion en cada fila de los punteros dobles
int* edad;long long *cedula;//Punteros para crear arreglos dinamicos que almacenen los datos de cada usuario sobre la cedula y edad
int datos = 1; //cantidad de datos de usuarios ingresados, se usa para recorrer todos los datos de los arreglos

//funciones

//Funcion encargada de hacer todo el registro de los datos, para luego almacenarlo la direccion en cada puntero
void ingreso_datos();
//Funcion para visualizar los datos de cada usuario
void visualizar();

int main() {
	
	int opcion = 0;
	bool salir = 0;
	while (!salir)
	{
		do
		{
			cout << "Escoja entre las siguientes opciones: \n";
			cout << "1) Ingresar datos de usuario\n2) Ver datos de cada usuario\n3)Salir\n";
			cin >> opcion;
			cin.ignore();
		} while (opcion > 3 || opcion <= 0);
		switch (opcion)
		{
		case 1:
			ingreso_datos();
			break;
		case 2:
			if (datos == 1)
				cout << "No se tiene ningun dato registrado de ningun usuario\n";
			else
				visualizar(); break;
		case 3:
			salir = 1; break;
		default:
			cout << "Numero no valido\n";
			break;
		}
	}
	

	return 0;
}

void ingreso_datos() {
	//Primero pedimos el nombre de usuario y verificamos que haya ingresado ya sus datos para continuar con el resto de la funcion
	char usuarioN[30]{};
	cout << "Ingrese el nombre de usuario para completar su informacion personal: ";
	cin>>usuarioN;
	if (datos > 1)
	{
		for (int i = 0; i < (datos - 1); i++) {
			if (!strcmp(usuarioN, usuarios[i])) {
				cout << "El nombre de usuario que ingresa ya tiene registrados sus datos\n";
				return;
			}
		}
	}fflush(stdin); //vaciamos el bufer para que no halla error al pedir datos despues
	

	//A continuacion reservo espacio en la memoria con los datos que voy a almacenar

	char** usuarios2 = new char* [datos];
	char** nombres2 = new char* [datos];
	char** profesiones2 = new char* [datos];
	char** origenes2 = new char* [datos];

	
	char nombreN[30]{};
	char profesionN[30]{};
	char origenN[30]{};

	int* edad2 = new int[datos];
	long long* cedula2 = new long long[datos];

	//Pido los nuevos datos del usuario

	cout << "Ingrese su nombre completo: ";
	cin.getline(nombreN, 30);
	cout << "Ingrese el nombre de su profesion: ";
	cin.getline(profesionN, 30);
	cout << "Ingrese su lugar de origen: ";
	cin.getline(origenN, 30);

	cout << "Digite el numero de su documento: ";
	cin >> cedula2[datos - 1];
	cout << "Digite su edad: ";
	cin >> edad2[datos - 1];

	//Almaceno la informacion de los datos en una direccion de memoria y se la asigno a los punteros fila de las matrices dinamicas
	//Reservo espacios en la memoria dependiendo de la longitud de los datos ingresados
	usuario = new char[strlen(usuarioN) + 1];
	strcpy(usuario, usuarioN);
	nombre = new char[strlen(nombreN) + 1];
	strcpy(nombre, nombreN);
	profesion = new char[strlen(profesionN) + 1];
	strcpy(profesion, profesionN);
	origen = new char[strlen(origenN) + 1];
	strcpy(origen, origenN);


	if (datos == 1) {//Asigno la direccion de los datos ingresados a cada puntero
		cedula = cedula2;
		edad = edad2;

		usuarios2[datos - 1] = usuario; usuarios = usuarios2;
		nombres2[datos - 1] = nombre; nombres = nombres2;
		profesiones2[datos - 1] = profesion; profesiones = profesiones2;
		origenes2[datos - 1] = origen; origenes = origenes2;
	}
	else
	{
		for (int i = 0; i < (datos - 1); i++)
		{
			//Transfiero los valores antiguos a un nuevo puntero para aumentar su longitud
			cedula2[i] = cedula[i];
			edad2[i] = edad[i];

			//transfiero las direcciones de las filas de las antiguas matrices a unas nuevas con mayor longitud
			usuarios2[i] = usuarios[i];
			nombres2[i] = nombres[i];
			profesiones2[i] = profesiones[i];
			origenes2[i] = origenes[i];
		}
		//Transfiero los nuevos datos al nuevo usuario agregado
		usuarios2[datos - 1] = usuario;
		nombres2[datos - 1] = nombre;
		profesiones2[datos - 1] = profesion;
		origenes2[datos - 1] = origen;

		//vacio memoria y asigno una nueva direccion a cada puntero con los datos anteriores y nuevos

		delete[] cedula; cedula = cedula2;
		delete[] edad; edad = edad2;

		delete[] usuarios; usuarios = usuarios2;
		delete[] nombres; nombres = nombres2;
		delete[] profesiones; profesiones = profesiones2;
		delete[] origenes; origenes = origenes2;
	}

	datos += 1; //Incremento la variable datos para luego ingresar mas datos a cada arreglo
	cout << "Datos guardados\n\n"; //Se confirma al usuario que se guardaron con exito los datos
}


void visualizar() {
	cout << "Datos de usuarios:\n";
	cout << "Usuario - cedula - nombre - origen - edad - profesion\n";
	for (int dato = 0; dato < (datos - 1); dato++) {
		cout << dato + 1 << ".  ";
		cout <<usuarios[dato]<<" - " << cedula[dato] << " - " << nombres[dato] << " - " << origenes[dato];
		cout << " - " << edad[dato] << " - " << profesiones[dato];

		cout << endl;
	}
	cout << endl;
}
