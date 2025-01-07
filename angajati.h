
#ifndef CLASSES_H
#define CLASSES_H
#include <vector>
#include <string>
using namespace std;

class Angajat
{
public:
    string nume;
    string ora_inceput;
    string ora_sfarsit;
    float salariu;
};

class Barista : public Angajat
{
    ///mostenire
public:
    string nume;
    string ora_inceput;
    string ora_sfarsit;
    const int salariu = 2500; /// salariu mediu starbucks
};

class Manager : public Angajat
{
    ///mostenire
public:
    string nume;
    string ora_inceput;
    string ora_sfarsit;
    const int salariu = 4800; /// tot starbucks
};

class Ospatar : public Angajat
{
    ///mostenire
public:
    string nume;
    string ora_inceput;
    string ora_sfarsit;
    const int salariu = 2900;
};

#endif //CLASSES_H
