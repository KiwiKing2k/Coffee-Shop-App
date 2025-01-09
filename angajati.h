
#ifndef CLASSES_H
#define CLASSES_H
#include <vector>
#include <string>
#include "menu.h"
using namespace std;

class Angajat
{
public:
    string nume;
    string ora_inceput;
    string ora_sfarsit;
};

class Barista : public Angajat
{
    ///mostenire
public:
    const int salariu = 2500; /// salariu mediu starbucks
};

class Manager : public Angajat
{
    ///mostenire
public:
    const int salariu = 4800; /// tot starbucks
};

class Ospatar : public Angajat
{
    ///mostenire
public:
    const int salariu = 2900;
};

typedef struct client_info
{
    string name;
    int loyalty;// abstract system for loyalty
}client_info;

class Team
{
public:
    vector<Barista> bariste;
    vector<Manager> manageri;
    vector<Ospatar> ospatari;
};

Team read_angajati(string file_path);



#endif //CLASSES_H
