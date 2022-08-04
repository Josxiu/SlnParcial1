// Parcial 1.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
using namespace std;
int largo_palabra(char[]);
char** agregar_registro(char**, int*);
void listado(char**, int);
bool repetida(char**, char[], int, int);

int main()
{
    int registros = 1; // Cantidad de registros iniciales (Categorias)
    int opcion = 0;

    char** categorias = new char* [1]; // Se crea la matriz de char que contendra las categorias

    while (true)
    {
        do
        {
            cout << "Escoja entre las siguientes opciones: \n";
            cout << "1) Agregar una nueva categoria\n2) Ver listado de categorias\n3)Salir\n";
            cin >> opcion;
            cin.ignore();
        } while (opcion > 3 || opcion <= 0);

        switch (opcion)
        {
        case 1:
            if (registros == 1)
            {
                agregar_registro(categorias, &registros);
                registros += 1;
                cout << "\nSe ha agregado la nueva categoria a la lista\n\n";
            }
            else
            {
                categorias = agregar_registro(categorias, &registros);
            }
            break;
        case 2:
            if (registros == 1)
                cout << "No se ha ingresado ninguna categoria a la lista todavia\n\n";
            else
                listado(categorias, (registros - 1));
            break;
        case 3:
            return 0;
            break;
        default:
            cout << "Numero no valido\n";
            break;
        }
    }//Se libera la memoria usada y se termina el programa
    if (registros == 1)
        delete[]categorias[0];
    else {
        for (int i = 0; i < registros - 1; i++)
            delete[] categorias[i];
    }
    delete[] categorias;
    categorias = nullptr;
    return 0;
}

/*Funcion para saber la longitud de la categoria ingresada, y asi asignar despues
el espacio que ocupa en una de las categorias de la matriz de categorias*/
int largo_palabra(char palabra[])
{
    int n = 0;
    for (int i = 0; i < 30; i++)
    {
        n += 1;
        if (int(palabra[i]) == 0) // Se verifica si la palabra ingresada ha terminado
            return n;
    }
    return n;
}

/*Funcion que agrega una nueva categoria a la matriz dinamica
libera la memoria asignada anteriormente para poder crear otra matriz mas grande
y agregar la nueva categoria*/
char** agregar_registro(char** lista, int* registrosP)
{
    int registros = *registrosP;
    char categoria[30]{}; // Arreglo char donde se almacenara el nombre de la categoria ingresada

    cout << "Ingrese el nombre de la categoria: ";
    cin.getline(categoria, 30);

    int longPalabra = largo_palabra(categoria);
    if (registros == 1)
    {
        *lista = new char[longPalabra];
        for (int L = 0; L < longPalabra; L++)
        {
            *(*(lista)+L) = categoria[L]; // Se agrega la categoria a la fila 1 de la matriz
        }
        return lista;
    }
    else
    {
        if (repetida(lista, categoria, longPalabra, registros)) {   //Si hay una palabra repetida no la agrega a la lista
            cout << "La categoria ingresada ya se encuentra en la lista\n\n";
            return lista;
        }


        char** lista2 = new char* [registros]; // se declara una nueva matriz para almacenar los datos de la antigua y aumentar su longitud
        for (int n = 0; n < registros - 1; n++)
            lista2[n] = new char[largo_palabra(lista[n])]; // se reserva la memoria de la palabra que almacenara

        int lpalabra = 0;
        for (int i = 0; i < (registros - 1); i++)
        {
            lpalabra = largo_palabra(lista[i]);// Se mira la longitud de la palabra para agregarla a la nueva matriz
            for (int j = 0; j < lpalabra; j++)
            {
                *(*(lista2 + i) + j) = *(*(lista + i) + j); // Se asignan los valores de la antigua matriz de caracteres
            }
        }

        // Se libera la memoria de la antigua matriz
        for (int i = 0; i < (registros - 1); i++)
            delete[] lista[i];

        lista2[registros - 1] = new char[longPalabra] {};//Se reserva memoria en la ultima fila de la matriz para guardar la nueva palabra
        for (int L = 0; L < longPalabra; L++)
        {
            *(*(lista2 + (registros - 1)) + L) = categoria[L]; // Se agrega la categoria a la ultima fila de la nueva matriz
        }

        *registrosP += 1;//Se agrega un nuevo espacio al valor de registros para guardar otra categoria
        cout << "\nSe ha agregado la nueva categoria a la lista\n\n";


        delete []lista;
        return lista2; // Se retorna la direccion de memoria de la nueva matriz
    }
}

void listado(char** lista, int largo)
{
    int caracter = 0;
    cout << "\nCategorias: \n";
    for (int i = 0; i < largo; i++)
    {
        cout << i + 1 << "-  ";
        for (int letra = 0; letra < 30; letra++)
        {
            caracter = int(*(*(lista + i) + letra));
            if (caracter != 0) {
                cout << *(*(lista + i) + letra);
            }

            else
            {
                break;
            }
        }
        cout << endl;
    }
    cout << endl;
}

//Funcion para saber si la palabra ingresada ya se encuentra en la lista de categorias
bool repetida(char** lista, char palabra[], int largoIngresada, int registros) {
    bool diferentes = 0;

    char letra1{}, letra2{};
    int lpalabra = 0;
    for (int i = 0; i < (registros - 1); i++)
    {
        lpalabra = largo_palabra(lista[i]);// Se mira si tienen igual longitud y se hace la comparacion
        if (lpalabra == largoIngresada) {
            for (int j = 0; j < lpalabra; j++)
            {
                letra1 = palabra[j];
                letra2 = *(*(lista + i) + j);
                if (letra1 != letra2)//Si son diferentes en solo una letra rompe el ciclo interno y asigna un 1 a la variable diferentes
                {
                    diferentes = 1; break;
                }
            }
            if (diferentes == 0)return true;
            diferentes = 0;
        }
    }//Si paso todo el ciclo significa que la palabra ingresada no esta repetida asi que devuelve false
    return false;
}