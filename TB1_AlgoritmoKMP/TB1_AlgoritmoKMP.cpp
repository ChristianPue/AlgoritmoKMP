#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// Funci�n de menu de asignar valor a un patr�n
string menu_asignar_patron()
{
    string patron = "", caracteres = "ABCDEFGHIJKLMNOPQRSTUVWX";
    size_t tam;

    size_t opc;
    while (patron == "")
    {
        cout << "Asignar el valor del patron de manera:" << endl;
        cout << "1. Manual." << endl;
        cout << "2. Aleatoria." << endl;
        cout << "Respuesta: "; cin >> opc;

        switch (opc)
        {
        case 1:
            cout << "Ingrese el valor del patron (cadena de texto): ";
            cin >> patron;
            break;
        case 2:
            tam = 2 + rand() % (5 - 2 + 1);
            for (size_t i = 0; i < tam; i++)
            {
                patron += caracteres[rand() % caracteres.length()];
            }
            break;
        default:
            break;
        }
    }

    return patron;
}

// Opci�n 1: Asigne el n�mero de casos de prueba y tambi�n los valores de cada patr�n
vector<string> menu_asignar_patrones()
{
    // Atributos necesarios
    size_t cant_casos = 0; vector<string> patrones;

    size_t opc;
    cout << "Asignar el numero de casos de prueba de manera:" << endl;
    cout << "1. Manual." << endl;
    cout << "2. Aleatoria." << endl;
    cout << "3. Salir." << endl;
    cout << "Respuesta: "; cin >> opc;

    switch (opc)
    {
    case 1:
        do
        {
            cout << "Ingrese el numero de casos de prueba (numero entero de entre 1 a 1000): ";
            cin >> cant_casos;
            
            if (cant_casos >= 1 && cant_casos <= 1000) { break; }
        } while (true);
        break;
    case 2:
        cant_casos = 1 + rand() % (1000 - 1 + 1);
        break;
    default:
        break;
    }

    // Asignar valores a los patrones
    if (cant_casos != 0)
    {
        for (size_t i = 0; i < cant_casos; i++)
        {
            cout << "Para el Patron n" << i + 1 << ":" << endl;
            string patron = menu_asignar_patron();
            patrones.push_back(patron);
        }
    }
    
    return patrones;
}

// Opci�n 2: Asigne el valor del texto
string menu_asignar_texto()
{
    string texto = "", caracteres = "ABCDEFGHIJKLMNOPQRSTUVWX";
    size_t tam;

    size_t opc;
    while (texto == "")
    {
        cout << "Asignar el valor del texto de manera:" << endl;
        cout << "1. Manual." << endl;
        cout << "2. Aleatoria." << endl;
        cout << "Respuesta: "; cin >> opc;

        switch (opc)
        {
        case 1:
            cout << "Ingrese el valor del texto (cadena de texto): ";
            cin >> texto;
            break;
        case 2:
            tam = 10 + rand() % (20 - 10 + 1);
            for (size_t i = 0; i < tam; i++)
            {
                texto += caracteres[rand() % caracteres.length()];
            }
            break;
        default:
            break;
        }
    }

    return texto;
}


// Funci�n de datos ya colocados
void mostrarDatosColocados(string texto, vector<string> patrones)
{
    cout << "Datos ya colocados:" << endl;
    cout << "   > Texto: ";
    if (!texto.empty())
    {
        cout << texto;
    }
    else
    {
        cout << "No se ingreso ni un texto.";
    }
    cout << endl;
    cout << "   > Patrones:" << endl;
    if (!patrones.empty())
    {
        for (size_t i = 0; i < patrones.size(); i++)
        {
            cout << "     Patron n" << i + 1 << ": " << patrones.at(i);
            if (i + 1 != patrones.size()) { cout << endl; }
        }
    }
    else
    {
        cout << "     No se ingreso ni un patron.";
    }
    cout << endl;
}

// -> Funci�n modificada para obtener las posiciones de los patrones hallados
vector<int> getVectorPosicionesKMP(string text, string pattern) {
    int m = text.length();
    int n = pattern.length();
    vector<int> posiciones;  // Vector para almacenar las posiciones encontradas

    if (n == 0) {
        //cout << "El patr�n est� vac�o. No se realizar� la b�squeda." << endl;
        return posiciones;
    }

    if (m < n) {
        //cout << "El texto es menor que el patr�n. No se puede buscar." << endl;
        return posiciones;
    }

    vector<int> next(n + 1, 0);

    for (int i = 1; i < n; i++) {
        int j = next[i];

        while (j > 0 && pattern[j] != pattern[i]) {
            j = next[j];
        }

        if (j > 0 || pattern[j] == pattern[i]) {
            next[i + 1] = j + 1;
        }
    }

    for (int i = 0, j = 0; i < m; i++) {
        if (text[i] == pattern[j]) {
            if (++j == n) {
                int posicion = i - j + 1;
                posiciones.push_back(posicion); // Guarda la posici�n en el vector
                //cout << "El patr�n se encuentra en la posici�n " << posicion << endl;

                j = 0;  // Reinicia la b�squeda para encontrar m�s coincidencias
            }
        }
        else if (j > 0) {
            j = next[j];
            i--;
        }
    }

    return posiciones;
}

// Opci�n 3: Algoritmo KMP
void calcularPatrones_algoritmoKMP(string texto, vector<string> patrones)
{
    // Mostrar todos los datos ya colocados
    mostrarDatosColocados(texto, patrones);

    // Calcular las posiciones y las veces que se repite
    cout << "Las posiciones encontradas para el:" << endl;
    for (size_t i = 0; i < patrones.size(); i++)
    {
        cout << "   > Patron n" << i + 1 << " son: ";
        vector<int> posiciones = getVectorPosicionesKMP(texto, patrones.at(i));
        if (!posiciones.empty())
        {
            for (size_t j = 0; j < posiciones.size(); j++)
            {
                cout << posiciones.at(j) << " ";
            }
            cout << endl;
            cout << "     Cantidad de veces que se repite: " << posiciones.size();
            if (posiciones.size() > 3)
            {
                cout << endl;
                cout << "     (i) El patron es muy frecuente en el texto.";
            }
        }
        else { cout << "No se encontro repiticiones con este patron."; }
        cout << endl;
    }
}


// Funci�n principal
int main()
{
    // Inicializar la semilla para generar n�meros aleatorios
    srand(time(nullptr));

    // Atributos necesarios para realizar el Algoritmo KMP
    vector<string> patrones;
    string texto;

    bool salir = false;
    while (salir == false)
    {
        mostrarDatosColocados(texto, patrones);
        cout << endl << endl;
        // Men� de opciones
        size_t opc;
        cout << "::::: Algoritmo KMP :::::" << endl;
        cout << "1. Asigne el tamano y los valores del texto (el texto donde se buscara el patron)." << endl;
        cout << "2. Asigne el numero de casos de prueba (las veces que buscara un patron) y" << endl;
        cout << "   tambien asigne el valor de cada patron (la cadena de texto a buscar)." << endl;
        
        cout << "3. Calcular cuantas veces se repiten el/los patron(es) mediante el algoritmo de KMP." << endl;
        cout << "0. Salir del programa." << endl;
        cout << "Respuesta: "; cin >> opc;

        // Casos seg�n la opci�n elegida
        switch (opc)
        {
        case 1:
            texto = menu_asignar_texto();
            break;
        case 2:
            patrones = menu_asignar_patrones();
            break;
        case 3:
            system("cls");
            if (!texto.empty() && !patrones.empty())
            {
                calcularPatrones_algoritmoKMP(texto, patrones);
            }
            else { cout << "No se asigno texto y/o algun patron." << endl; }
            break;
        case 0:
            salir = true;
            break;
        default:
            break;
        }

        system("pause");
        system("cls");
    }
}