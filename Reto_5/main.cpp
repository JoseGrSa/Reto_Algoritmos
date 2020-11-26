#include "ADT_read.h"
#include "graph.h"
#include <map>


/* 

En este programa primero definimos los valores de A (Nuestra IP interna elegida), B (Nuestro sitio web anomalo) y C (La pagina normal con mas visitas anomalas)
Despues de esto creamos un set con los dias para asegurarnos de que no se hagan repeticiones. En la pregunta 1, hicimos un map donde juntamos en dia con su respectivo objeto de graph
y despues con un iterador fuimos añadiendo valores con las condiciones de que solo fueran con la red interna y al mismo tiempo contamos por dia cuantas conexiones tiene A por dia
Despues de esto hicimos lo mismo pero al reves para calcular las conexiones que fueron hacia A por dia

En la 3 hicimos un graph con todas las conexiones, no solo las internas y vimos cuantas computadores se han conectado a nuestro B y para la cuatro hicimos lo mismo
pero con C.

*/

//José Granger Salgado - A01023661
//Jorge Cabiedes A01024053

// 25/11/2020


using namespace std;

//Open File------------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------------------------


int main()
{
    //Variables para creacion de graphos---------------
    set<string> ips;
    map<string, int> nodes_idx;
    int idx = 0;
    int src;
    int dst;
    //-------------------------------------------------
    string int_ip = "10.250.184";
    string path = "nuevo2.csv";
    vector<Entry> entries = open(path);

    Graph<string> graph;
    string A = "10.250.184.1"; //Ip interna que pertenece a pamela.reto.com
    string B = "27.100.132.18"; //Ip que pertenece a 3oyp3rbdrclsnuy92kak.org
    string C = "95.199.92.180"; //Ip que pertenece a craigslist.org

    cout << "\n" <<"La dirección A es pamela.reto.com y su ip es: " << A << endl;
    cout << "La dirección B es 3oyp3rbdrclsnuy92kak.org y su ip es: " << B << endl;
    cout << "La dirección C es craigslist.org y su ip es: " << C << endl << endl;


    //Define una lista con los dias a considerar---------------------------------
    set<string> dias;
    for (size_t i = 0; i < entries.size(); i++)
    {
        dias.insert(entries[i].date);
    }
    //---------------------------------------------------------------------------
    cout << "Preguntas 1 y 2 -----------------------------------" << endl << endl;
    //Creates graphs for each day using only local conections--------------------
    map<string, Graph<string>> l_cnx_per_day;
    
    for(auto it : dias)
    {
        Graph<string> h;
        l_cnx_per_day.insert({it, h});
        nodes_idx.clear();
        ips.clear();
        idx = 0;

        for (size_t i = 0; i < entries.size(); i++)
        {
            if (entries[i].date == l_cnx_per_day.find(it)->first && entries[i].orIP.find(int_ip) != string::npos && entries[i].desIP.find(int_ip) != string::npos)
            {
                if (ips.find(entries[i].orIP) == ips.end() && entries[i].orIP != "-")
                {
                    l_cnx_per_day.find(it)->second.add_node(entries[i].orIP);
                    nodes_idx.insert({entries[i].orIP, idx});
                    idx++;
                }
                    
                if (ips.find(entries[i].desIP) == ips.end() && entries[i].desIP != "-")
                {
                    l_cnx_per_day.find(it)->second.add_node(entries[i].desIP);
                    nodes_idx.insert({entries[i].desIP, idx});
                    idx++;
                }
                    
                if (entries[i].orIP != "-")
                    ips.insert(entries[i].orIP);
                if (entries[i].desIP != "-")
                    ips.insert(entries[i].desIP);
                
                if (entries[i].orIP != "-" && entries[i].desIP != "-")
                {
                    src = nodes_idx.find(entries[i].orIP)->second;
                    dst = nodes_idx.find(entries[i].desIP)->second;

                    l_cnx_per_day.find(it)->second.add_edge(src, dst);
                }  
            }
        }

        int idx_A = nodes_idx.find(A)->second;
        int A_cnx = l_cnx_per_day.find(it)->second.nodes[idx_A].get_adj().size();
        bool is_big = true;
        bool has_cnx = false;
        for(auto itr : l_cnx_per_day.find(it)->second.nodes)
        {
            set<int> set_adj = itr.get_adj();

            if (set_adj.size() > A_cnx)
               is_big = false;

            if (set_adj.find(idx_A) != set_adj.end())
                has_cnx = true;
        }

        cout << "Dia: " << it << endl;
        if(is_big == false)
            cout << "A NO es el vertice que mas conexiones salientes tiene hacia la red interna. " << endl;
        else
            cout << "A SI es el vertice que mas conexiones salientes tiene hacia la red interna. " << endl;

        if(has_cnx == true)
            cout << "Otras computadoras SI tienen conexiones hacia A." << endl << endl;
        else
            cout << "Otras computadores NO tienen conexiones hacia A." << endl << endl;
        
    }
    cout << "Preguntas 3 y 4 -----------------------------------" << endl << endl;
    //---------------------------------------------------------------------------
    map<string, Graph<string>> cnx_per_day;

    for(auto it : dias)
    {
        Graph<string> h;
        cnx_per_day.insert({it, h});
        nodes_idx.clear();
        ips.clear();
        idx = 0;
        for (size_t i = 0; i < entries.size(); i++)
        {
            if(entries[i].date == it)
            {
                if (ips.find(entries[i].orIP) == ips.end() && entries[i].orIP != "-")
                {
                    cnx_per_day.find(it)->second.add_node(entries[i].orIP);
                    nodes_idx.insert({entries[i].orIP, idx});
                    idx++;
                }
                
                if (ips.find(entries[i].desIP) == ips.end() && entries[i].desIP != "-")
                {
                    cnx_per_day.find(it)->second.add_node(entries[i].desIP);
                    nodes_idx.insert({entries[i].desIP, idx});
                    idx++;
                }
                    
                if (entries[i].orIP != "-")
                    ips.insert(entries[i].orIP);
                if (entries[i].desIP != "-")
                    ips.insert(entries[i].desIP);
                
                if (entries[i].orIP != "-" && entries[i].desIP != "-")
                {
                    src = nodes_idx.find(entries[i].orIP)->second;
                    dst = nodes_idx.find(entries[i].desIP)->second;

                    cnx_per_day.find(it)->second.add_edge(src, dst);
                }
            }
        }   

        int idx_B = nodes_idx.find(B)->second;
        int comp_count = 0;
        cout << "Dia: " << it << endl;

        for(auto itr : cnx_per_day.find(it)->second.nodes)
        {
            set<int> set_adj = itr.get_adj();
            if(set_adj.find(idx_B) != set_adj.end())
                comp_count++;
        }

        cout << "Se conectaron " << comp_count << " computadoras al dominio B." << endl;

        int idx_C = nodes_idx.find(C)->second;
        comp_count = 0;
        

        for(auto itr : cnx_per_day.find(it)->second.nodes)
        {
            set<int> set_adj = itr.get_adj();
            if(set_adj.find(idx_C) != set_adj.end())
                comp_count++;
        }
        
        cout << "Se conectaron " << comp_count << " computadoras al dominio C." << endl << endl;
    }
    return 0;
}