#include "ADT_read.h"

using namespace std;


class ConexionesComputadora{
    public:
        string ip; // String ip es donde guardamos el string que creamos, donde tomamos la dirección interna creada.
        string name = ""; // String name es donde ponemos el nombre de la computadora que elegimos en este caso, la cual fue la primera que se encuentra dependiendo de nuestro ip, según las instrucciones de nuestro profesor.
        vector<string> conexiones; // Vector donde guardamos las conexiones que se estan realizando para el ip especifico
        vector<Entry> entries; //Vector donde guardamos los entries para poder analizar en nuestro metodo.

        bool threeReps = false;

        ConexionesComputadora()
        {
            ip = ""; // Contructor default
        }

        ConexionesComputadora(string _ip, vector<Entry> _entries)
        {
            ip = _ip;
            entries = _entries; // Constructor con parametros
        }

        void get_conexiones()
        {
            
            int n = 0;
            string temp = "";
            for (size_t i = 0; i < entries.size(); i++)
            {
                if (name == "" && (ip == entries[i].orIP || ip == entries[i].desIP))
                    name = entries[i].Name;

                if (entries[i].mail != "-" && (ip == entries[i].orIP || ip == entries[i].desIP))
                {
                    if(temp == "")
                        temp = entries[i].mail;
                    else if(entries[i].mail == temp)
                        n++;
                    else
                        n = 0;
                }

                
                if(ip == entries[i].orIP)
                    conexiones.push_back(entries[i].orIP);
                else if(ip == entries[i].desIP)
                    conexiones.push_back(entries[i].desIP);

                if (n == 2)
                    threeReps = true;
            }
            
        }

        /* Este programa sirve igual que el de ACT 2.3 pero en este caso guardamos las conexiones que se encuentran en nuestro vector de conexiones para uso en nuestro map 
        en el main*/


};

