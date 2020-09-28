#include "ADT_read.h"
#include <iostream>
#include "search.h"
#include "sorter.h"
#include <string>

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
    string path = "equipo2.csv";
    vector<Entry> entries = open(path);

    //Primera Pregunta
    cout << "Registros en el archivo: " << entries.size() << endl << endl;

    //Segunda pregunta
    string day1 = entries[0].date;

    int i = 0;
    while(entries[i].date == day1)
        i++;
    string day2 = entries[i].date;

    int countDay2 = 0;
    while(entries[i].date == day2)
    {
        i++;
        countDay2++;
    }

    cout << "Cantidad de records del segundo día registrado: " << countDay2 << endl << endl;
    
    //Tercera pregunta
    vector<string> nameSearch = {"jeffrey.reto.com", "betty.reto.com",
                    "katherine.reto.com", "scott.reto.com",
                    "benjamin.reto.com", "samuel.reto.com",
                    "raymond.reto.com"};
    vector<string> names;

    for (size_t i = 0; i < entries.size(); i++)
        names.push_back(entries[i].Name);
    
    QuickSort<string> qSort;
    qSort.sort(names, 0, names.size() - 1);

    BinarySearch<string> biSearch;
    bool isName = false;

    for (size_t i = 0; i < nameSearch.size(); i++)
        isName = biSearch.search(nameSearch[i], names);
    
    cout << "Alguna de las computadoras pertenece a Jeffrey, Betty, Katherine, Scott, Benjamin, Samuel o Raymond?" << endl << "No = [0] Si = [1]: " << isName << endl << endl;
    
    //Cuarta pregunta
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
        cout << intDir[i] << '.';

    cout << '0' << endl << endl;
    
    
    //Quinta pregunta
    cout << "Alguna computadora se llama server.reto.com?" << endl << "No = [0] Si = [1]: " << biSearch.search("server.reto.com", names) << endl;
    
    //Sexta pregunta
    vector<string> mailSearch = {"gmail.com", "protonmail.com", "hotmail.com", "outlook.com"};
    vector<string> mails;
    for (size_t i = 0; i < entries.size(); i++)
        mails.push_back(entries[i].mail);

    qSort.sort(mails, 0, mails.size() - 1); 

    
    cout << "Se usó gmail?" << endl;

    if (biSearch.search("gmail.com", mails) == 1)
        cout << "Si." << endl;
    else
        cout << "No." << endl;

    cout << "Se usó protonmail?" << endl;

    if (biSearch.search("protonmail.com", mails) == 1)
        cout << "Si." << endl;
    else
        cout << "No." << endl;

    cout << "Se usó hotmail?" << endl;

    if (biSearch.search("hotmail.com", mails) == 1)
        cout << "Si." << endl;
    else
        cout << "No." << endl;

    cout << "Se usó outlook?" << endl;

    if (biSearch.search("outlook.com", mails) == 1)
        cout << "Si." << endl;
    else
        cout << "No." << endl;
    
    
    //Septima pregunta
    vector<int> ports;
    int temp;
    SecuentialSearch<int> secSearch;
    for (size_t i = 0; i < entries.size(); i++)
    {   
        if(entries[i].desPort != "-")
            temp = stoi(entries[i].desPort);
            if(temp < 1000 && secSearch.search(temp, ports) == false)
                ports.push_back(temp);
    }
    for (size_t i = 0; i < entries.size(); i++)
    {
        if(entries[i].desPort != "-")
            temp = stoi(entries[i].orPort);
            if(temp < 1000 && secSearch.search(temp, ports) == false)
                ports.push_back(temp);
    }

    cout << "Puertos abajo de 1000 que se están usando: " << endl;
    for (size_t i = 0; i < ports.size(); i++)
    {
        cout << ports[i] << endl;
    }
    
    
}