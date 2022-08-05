#include <iostream>
#include <ctime>//libreria para ver la hora y fecha
using namespace std;

int registros = 1;
void registrar_transaccion();
void Registrar_fecha(int);
void registrar_datos();
void visualizar();
char** transacciones = new char* [1]; //Aqui se guardaran las transacciones con las fechas
char* fecha = new char[40]{}; //Declaro e inicializo la cadena que contendra la fecha de una transaccion
int posicionFecha = 0; //Variable para moverse entre la cadena que contiene la fecha



int main() {
    int opcion = 0;
    bool salir = 0;
    while (!salir)
    {
        do
        {
            cout << "Escoja entre las siguientes opciones: \n";
            cout << "1) Ingresar transaccion\n2) Ver transacciones realizadas\n3)Salir\n";
            cin >> opcion;
            cin.ignore();
        } while (opcion > 3 || opcion <= 0);
        switch (opcion)
        {
        case 1:
            registrar_datos();
            cout << "Transaccion completada\n\n"; break;
        case 2:
            if (registros == 1)
                cout << "No se tienen datos registrados sobre las transacciones\n";
            else
                visualizar(); break;
        case 3:
            salir = 1; break;
        default:
            cout << "Numero no valido\n";
            break;
        }
    }
    
    if (registros == 1)                             // Se libera toda la memoria utilizada en arreglos dinamicos
        delete[] transacciones[0];
    else
        for (int i = 0; i < registros - 1; i++)
            delete[] transacciones[i];

    delete[] transacciones;
    delete[] fecha;

    
    return 0;
}


void Registrar_fecha(int numero)
{
    int n = numero;     // Copia del numero
    int digitos = 0;    // digitos del numero
    while (numero != 0) // Verificamos cuantos digitos tiene el numero
    {
        numero = numero / 10; // division entera entre 10
        digitos++;
    }
    int potencia = 1; // variable para guardar una potencia de 10 segun los digitos que tenga el numero
    for (int i = 0; i < digitos - 1; i++)
        potencia *= 10;

    int caracter = 0;
    digitos += posicionFecha;
    for (int i = posicionFecha; i < digitos; i++)
    {
        caracter = n / potencia; // se divide el numero restante entre una potencia de 10 para conseguir el primer digito
        n = n % potencia;        // se elimina el primer digito y quedan los restantes
        potencia /= 10;
        fecha[i] = caracter + '0'; // se convierte de entero a char
        posicionFecha++;
    }
 }

void registrar_transaccion() {
    char transaccion[15]{};//Arreglo para almacenar el valor de la transaccion
    bool valido = 1;
    do
    {
        cout << "Ingrese el valor de la transaccion: ";
        cin.getline(transaccion, 15);
        for (auto c : transaccion) {
            if (isdigit(c) == 0 && (int)c != 0) {//Compruebo que lo que halla ingresado si sea un numero
                valido = 0;
                break;
            }
        }
    } while (!valido);
    for (char c : transaccion)
    {
        fecha[posicionFecha++] = c;//Transfiero los valores al arreglo con los datos de la transaccion
        if (int(c) == 0)
            break;
    }

    //********************SE COMIENZA A AGREGAR EL VALOR DE LA TRANSACCION REALIZADA************************************
    if (registros == 1)
        transacciones[registros - 1] = fecha;  //Guardo los datos de la transaccion en transacciones
        
    else
    {
        char** transacciones2 = new char* [registros]; //Creo un nuevo arreglo mas grande para agregar una nueva transaccion
        for (int i = 0; i < (registros - 1); i++)
            transacciones2[i] = transacciones[i]; //transfiero los valores al nuevo arreglo
        
        transacciones2[registros - 1] = fecha; //Guardo la direccion de los datos de la transaccion en transacciones

        delete[] transacciones; //Libero la memoria asociada a los antiguos punteros
        transacciones = transacciones2; //Le asigno a transacciones la nueva direccion que contiene los datos de las fechas
    }
    registros += 1;//Agrego un nuevo espacio
}

//funcion que permite visualizar todas las transacciones
void visualizar() {
    cout << "Transacciones realizadas:\n";
    for (int t = 0; t <(registros-1); t++) {
        cout << t + 1 << ".  ";
        for (int i = 0; i < 40; i++)
            cout << *((transacciones[t]) + i);

        cout << endl;
    }
    cout << endl;
}

//Funcion principal que registra la informacion utilizando las otras funciones
void registrar_datos() {
    time_t now = time(0);
    struct tm time;
    localtime_s(&time, &now);

    Registrar_fecha(time.tm_mday);//Empiezo a guardar los datos de fecha y hora en la que se realiza la transaccion
    fecha[posicionFecha++] = '/';
    Registrar_fecha(time.tm_mon + 1);
    fecha[posicionFecha++] = '/';
    Registrar_fecha(time.tm_year + 1900);
    fecha[posicionFecha++] = ' ';
    Registrar_fecha(time.tm_hour);
    fecha[posicionFecha++] = ':';
    Registrar_fecha(time.tm_min);
    fecha[posicionFecha++] = ':';
    Registrar_fecha(time.tm_sec);
    fecha[posicionFecha++] = ' ';

    registrar_transaccion();//Registramos los datos de la transaccion
    fecha = nullptr;
    fecha = new char[40]{}; // asigno mas espacio en memoria y cambio la direccion hacia la que apunta el puntero fecha
    posicionFecha = 0;//reinicio el conteo de la posicion en el arreglo fecha
}
