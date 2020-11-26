#include "ConexionesComputadora.h"


/* En este programa, usando la clase que creamos en el acto anterior (Act2.3) creamos un nuevo programa donde creamos un diccionario
o mapa y usando varios fors, vinculamos las ips con un vector de todas las conecciones entrantes y salientes de estas mismas, ademas de un vector de strings  donde ponemos los nombres de los dominios que no 
son reto.com. Finalizando esto, identificamos dominios anomalos, los cueales encontramos 2 y sus respectivas IPs, y con esto identificamos cuales son las ips que tienen al menos una conexion entrante
Y obtuvimos las ip unicas de las conexiones entrantes de varias computadoras con los parametros de evitar server.reto.com y el servidor DHCP. */

//José Granger Salgado - A01023661
//Jorge Cabiedes A01024053

//08/11/2020
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
    vector<string> domains;
    string domain = "reto.com";
    
    
    
    //Dominios sin reto.com
    for (size_t i = 0; i < entries.size(); i++)
    {
        if (entries[i].mail.find(domain) == string::npos && entries[i].mail != "-")
        {
            domains.push_back(entries[i].mail);
        }
    }

    //Elimina los duplicados de la lista.
    sort(domains.begin(), domains.end());
    domains.erase(unique(domains.begin(), domains.end()), domains.end());
    
    // Consigue los dominios
    cout << "Todos los dominios sin repetir: " << endl;

    for (size_t i = 0; i < domains.size(); i++)
    {
        cout << domains[i] << ", ";
    }
    
    cout << endl << endl;

    // Imprimimos los dominios anomalos
    cout << "Dominio Anomalo: 3oyp3rbdrclsnuy92kak.org " << "IP: 27.100.132.18" <<endl;
    cout << "Dominio Anomalo: boaujv4jn8dh614k73r8.xxx " << "IP: 101.116.39.84" <<endl;


    set<string> all_ips;
    for (size_t i = 0; i < entries.size(); i++)
    {
        if(entries[i].orIP != "-")
            all_ips.insert(entries[i].orIP);
        if(entries[i].desIP != "-")
            all_ips.insert(entries[i].desIP);
    }
    
    map<string, ConexionesComputadora> m;
    //Creamos el mapa
    for (auto itr = all_ips.begin(); itr != all_ips.end(); itr++)
    {
        ConexionesComputadora h(*itr, entries);
        m[*itr] = h;
    }
    
    
    //Pregunta 3

    int count = 0;
    for (auto itr = m.begin(); itr != m.end(); itr++)
    {
        if(itr->first.find("10.250.184") != string::npos)
        {
            itr->second.get_conexiones();
            if(itr->second.conexionesEntrantes.size() > 0)
                count++;
        }
    }
    
    
    cout << endl <<"Computadoras pertenecientes a reto.com con al menos una conexion entrante: " << count << endl;
    
    //Pregunta 4

    set<string> des_ip;
    for (size_t i = 0; i < entries.size(); i++)
    {
        if(entries[i].mail != "server.reto.com" && entries[i].orPort != "68" && entries[i].desPort != "67")
        {
            des_ip.insert(entries[i].orIP);
        }

        if(des_ip.size() == 150)
            i = entries.size();

    }
    
    cout << endl << endl;


    cout << "IP unicas entrantes: " << endl;
    for(auto itr = des_ip.begin(); itr != des_ip.end(); itr++)
    {
        cout << *itr << endl;
    }


    return 0;
}