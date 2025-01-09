#include <vector>
#include <string>
#include "angajati.h"

Team read_angajati(string file_path)
{
    Team echipa;
    ifstream file(file_path);
    if (!file.is_open())
    {
        throw runtime_error("Could not open the file!");
    }
    string line;
    getline(file, line); //skip first
    while (getline(file, line))
    {
        size_t start = 0;
        string nume = parse_field(line, start);
        string functie = parse_field(line, start);
        string ora_inceput = parse_field(line, start);
        string ora_sfarsit = parse_field(line, start);

        if (functie == "barista")
        {
            Barista read_angajat;
            read_angajat.nume = nume;
            read_angajat.ora_inceput = ora_inceput;
            read_angajat.ora_sfarsit = ora_sfarsit;
            echipa.bariste.push_back(read_angajat);
        }
        else if (functie == "manager")
        {
            Manager read_angajat;
            read_angajat.nume = nume;
            read_angajat.ora_inceput = ora_inceput;
            read_angajat.ora_sfarsit = ora_sfarsit;
            echipa.manageri.push_back(read_angajat);
        }
        else if (functie == "ospatar")
        {
            Ospatar read_angajat;
            read_angajat.nume = nume;
            read_angajat.ora_inceput = ora_inceput;
            read_angajat.ora_sfarsit = ora_sfarsit;
            echipa.ospatari.push_back(read_angajat);
        }
        else
        {
            throw runtime_error("Invalid function!");
        }
    }
    return echipa;
}
