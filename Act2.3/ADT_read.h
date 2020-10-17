#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

class Entry
{
public:
    string date;
    string hour;
    string orIP;
    string orPort;
    string Name;
    string desIP;
    string desPort;
    string mail;

    Entry()
    {
        date = "";
        hour = "";
        orIP = "";
        orPort = "";
        Name = "";
        desIP = "";
        desPort = "";
        mail = "";
    }

    Entry(string date_, string hour_, string orIP_, string orPort_, string Name_, string desIP_, string desPort_, string mail_)
    {
        date = date_;
        hour = hour_;
        orIP = orIP_;
        orPort = orPort_;
        Name = Name_;
        desIP = desIP_;
        desPort = desPort_;
        mail = mail_;
    }





};