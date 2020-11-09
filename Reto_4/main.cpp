#include "ConexionesComputadora.h"
#include <algorithm>
#include <map>
#include <iterator>
#include <set>
#include "BinaryTree.h"

/* 

En este programa tambien pudimos usar la clase de Conexiones que hicimos en el ACT2.3, per esta vez con modificaciones minimas, fuera de esto, creamos una funcion para crear un diccionario o map llamada
ConexionesPorDia donde se recibe una fecha y se regresa cuantas conexiones entrantes hubo por dominio que no sea reto.com o "-" y lo regresa. 
Ademas de esto hicimos una funcion que se llama top, donde recibe un parametro n y una fecha e imprime los n sitios con mas acceso en esa fecha, ademas de esto
esos datos los agregamos a un BST utilizando los parametros especificados.

Una vez hecho esto, solo imprimimos por cada dia de las bitacoras el top 5

*/

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

map<string, int> conexionesPorDia(string fecha, vector<Entry> entries)
{
    map<string, int> m;
    map<string, int>::iterator itr;

    for (size_t i = 0; i < entries.size(); i++)
    {
        if(entries[i].date == fecha && entries[i].mail != "-" && entries[i].mail.find("reto.com") == string::npos)
        {
            m[entries[i].mail]++;
        }
    }
    return m;
}

void top(int n, string fecha, vector<Entry> entries)
{
    BinarySearchTree<pair<int, string>> tree;
    map<string, int> m = conexionesPorDia(fecha, entries);
    for(auto it = m.cbegin(); it != m.cend(); ++it)
    {
        tree.insert_node_recursive(make_pair(it->second, it->first));
    }

    tree.print_inorder_reverse();

    for (size_t i = 0; i < n; i++)
    {
        cout << tree.inorden[i].first << ": " << tree.inorden[i].second << endl;
    }
    
}

int main() 
{
    string path = "nuevo2.csv";
    vector<Entry> entries = open(path);

    map<string, int> m = conexionesPorDia("10-8-2020", entries);

    for(auto it = m.cbegin(); it != m.cend(); ++it)
    {
        cout << it->first << " " << it->second << endl;
    }

    cout << endl << endl;

    set<string> dias;
    for (size_t i = 0; i < entries.size(); i++)
    {
        dias.insert(entries[i].date);
    }
    
    for(auto itr = dias.begin(); itr != dias.end(); itr++)
    {
        cout << *itr << endl;
        top(5, *itr, entries);
        cout << endl << endl;
    }

    //Pregunta 1
    cout << "Existe algún sitio que se mantenga en el top 5 todos los dias?: " << endl << "Si, protonmail.com" << endl << endl;

    //Pregunta 2
    cout << "Existe algun sitio que entre al top 5 a partir de un dia y de ahi aparezca en todos los dias subsecuentes?: " << endl;
    cout << "Si, 3oyp3rbdrclsnuy92kak.org" << "\n\n";

    //Pregunta 3
    cout << "Existe algun sitio quer aparezca en el top 5 con una cantidad de trafico mas alta de lo normal?: " << endl;
    cout << "Si, 3oyp3rbdrclsnuy92kak.org y craigslist.org" << endl << endl;

    return 0;
}