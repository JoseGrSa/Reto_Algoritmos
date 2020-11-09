#include "ConexionesComputadora.h"

// En este programa, usamos las implementaciones de la actividad anterior (Act1.3) y le añadimos un ADT class donde creamos un user typed IP basado en nuestro IP interno
// Despues nos aseguramos de crear un metodo donde podemos arreglar las conexiones depende de un usario, implementando el stack y el queue para poder cumplir con los requerimientos en
// un espacio y tiempo optimizado y adecuado, sin tener que hacer funciones complejas.

//José Granger Salgado - A01023661
//Jorge Cabiedes A01024053

//16/10/2020


using namespace std;


vector<Entry> open(string path)
{
    ifstream fileIn;
    fileIn.open(path);
    string line, sec;
    vector<string> data;
    vector<Entry> entries;


    while(fileIn.good())
    {
        getline(fileIn, line);
        istringstream sIn(line);

        while(getline(sIn, sec, ','))
        {
            data.push_back(sec);
        }

        if (data[7].find('\r') != data[7].npos)
        {
            data[7] = data[7].substr(0, data[7].size() - 1);
        }

        Entry register_(data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
        entries.push_back(register_);
        data.clear();
        
    }
    return entries;
}

int main()
{
    string path = "nuevo2.csv";
    vector<Entry> entries = open(path);
    string ip = "";
    
    bool isIntDir = false;
    int j = 0;
    while(isIntDir == false)
    {
        if(entries[j].Name != "server.reto.com" && entries[j].orIP != "-") 
            isIntDir = true;
        else
            j++;
    }

    string a;
    istringstream intIP(entries[j].orIP);
    vector<string> intDir;
    while(intIP.good())
    {
        getline(intIP, a, '.');
        intDir.push_back(a);
    }

    cout << "La dirección de la red interna de la compañía es: ";
    for (size_t i = 0; i < intDir.size() - 1; i++)
    {
        ip = ip + intDir[i] + '.';
        
    }
    

    ConexionesComputadora comp;

    comp.generateIP(ip);
    comp.conexiones(entries);

    //Primera pregunta

    cout << "Direccion ip que se esta usando: " << comp.ip << endl << endl;

    //Segunda Pregunta
    cout << "La ip de la última conexion que recibió esta computadora fue: ";
    cout << comp.conexionesEntrantes.top().orIP << endl;
    if (comp.conexionesEntrantes.top().orIP.find(ip) != string::npos)
        cout << "La cual es interna." << endl << endl;
    else
        cout << "La cual es externa." << endl << endl;
    
    

    //Tercera pregunta
    cout << "Cantidad de conexiones entrantes: ";
    cout << comp.conexionesEntrantes.size() << endl;

    //Cuarta pregunta
    cout << "Cantidad de conexiones salientes: ";
    cout << comp.conexionesSalientes.size() << endl << endl;

    //Quinta pregunta
    cout << "¿La computadora tuvo 3 conexiones seguidas a un mismo sitio web? SI [1] NO [0]: ";
    cout << comp.threeReps;

}