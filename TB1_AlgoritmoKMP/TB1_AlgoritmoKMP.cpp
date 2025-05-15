#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// Función de menu de asignar valor a un patrón
string menu_asignar_patron(size_t tam_texto)
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
            do
            {
                cout << "Ingrese el valor del patron (cadena de texto): ";
                cin >> patron;

                if (patron.size() > 1 && patron.size() < tam_texto) { break; }
            } while (true);
            
            break;
        case 2:
            tam = 2 + rand() % ((tam_texto - 1) - 2 + 1);
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

// Opción 1: Asigne el número de casos de prueba y también los valores de cada patrón
vector<string> menu_asignar_patrones(size_t tam_texto)
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
            string patron = menu_asignar_patron(tam_texto);
            patrones.push_back(patron);
        }
    }
    
    return patrones;
}

// Opción 2: Asigne el valor del texto
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
            tam = 10 + rand() % (30 - 10 + 1);
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

// Función de datos ya colocados
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

// -> Función modificada para obtener las posiciones de los patrones hallados
vector<size_t> getVectorPosicionesKMP(string text, string pattern) {
    int m = text.length();
    int n = pattern.length();
    vector<size_t> posiciones;  // Vector para almacenar las posiciones encontradas

    if (n == 0) {
        //cout << "El patrón está vacío. No se realizará la búsqueda." << endl;
        return posiciones;
    }

    if (m < n) {
        //cout << "El texto es menor que el patrón. No se puede buscar." << endl;
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
                posiciones.push_back(posicion); // Guarda la posición en el vector
                //cout << "El patrón se encuentra en la posición " << posicion << endl;

                j = 0;  // Reinicia la búsqueda para encontrar más coincidencias
            }
        }
        else if (j > 0) {
            j = next[j];
            i--;
        }
    }

    return posiciones;
}

string eliminarPatron(string text, string pattern) {
    int m = text.length();
    int n = pattern.length();

    // Validaciones iniciales
    if (n == 0 || m < n) {
        return "";
    }

    vector<int> next(n + 1, 0);

    // Construcción de la tabla de prefijos
    for (int i = 1; i < n; i++) {
        int j = next[i];

        while (j > 0 && pattern[j] != pattern[i]) {
            j = next[j];
        }

        if (j > 0 || pattern[j] == pattern[i]) {
            next[i + 1] = j + 1;
        }
    }

    string resultado;
    int i = 0, j = 0;

    while (i < m) {
        if (text[i] == pattern[j]) {
            if (++j == n) {
                // Se encontró el patrón, se omite en el resultado
                i++;
                j = 0;  // Reiniciar la búsqueda para seguir eliminando más ocurrencias
                continue;
            }
        }
        else if (j > 0) {
            j = next[j];
            continue;
        }

        resultado += text[i++];
    }

    return resultado;
}

// Opción 3: Obtención de los patrones hallados mediante el Algoritmo KMP
void calcularPatrones_algoritmoKMP(string texto, vector<string> patrones)
{
    // Mostrar todos los datos ya colocados
    mostrarDatosColocados(texto, patrones);

    cout << "Mediante el algoritmo KMP se hallo lo siguiente:" << endl;
    for (size_t i = 0; i < patrones.size(); i++)
    {
        cout << "   > Patron n" << i + 1 << " son: ";
        vector<size_t> posiciones = getVectorPosicionesKMP(texto, patrones.at(i));
        string text_res = eliminarPatron(texto, patrones.at(i));

        if (!posiciones.empty())
        {
            // Mostrar el texto resultante por cada patrón que se repite
            cout << endl; 
            cout << "     Texto resultante (sin los patrones dentro): ";
            cout << text_res << endl;

            // Calcular las posiciones y las veces que se repite
            cout << "     Patrones encontrados: ";
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
        else { cout << "No se encontro patron."; }
        cout << endl;
    }
}

// Función principal: main
int main()
{
    // Inicializar la semilla para generar números aleatorios
    srand(time(nullptr));

    // Atributos necesarios para realizar el Algoritmo KMP
    vector<string> patrones;
    string texto;

    bool salir = false;
    while (salir == false)
    {
        mostrarDatosColocados(texto, patrones);
        cout << endl << endl;
        // Menú de opciones
        size_t opc;
        cout << "::::: Algoritmo KMP :::::" << endl;
        cout << "1. Asigne el valor del texto (el texto donde se buscara uno o mas patrones)." << endl;
        cout << "2. Asigne el numero de casos de prueba (cuantos patrones se buscaran) y" << endl;
        cout << "   tambien asigne el valor de cada patron (la cadena de valores a buscar en el texto)." << endl;
        cout << "3. Calcular cuantas veces se repiten el/los patron(es) (con el algoritmo de KMP)." << endl;
        cout << "0. Salir del programa." << endl;
        cout << "Respuesta: "; cin >> opc;

        // Casos según la opción elegida
        switch (opc)
        {
        case 1:
            texto = menu_asignar_texto();
            break;
        case 2:
            if (!texto.empty())
            {
                patrones = menu_asignar_patrones(texto.size());
            }
            else { cout << "No se asigno un texto." << endl; }
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