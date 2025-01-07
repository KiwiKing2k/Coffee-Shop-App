#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "angajati.h"
#include "ingrediente.h"
#include "menu.h"
using namespace std;


int main()
{
    RomanianDebaraBuilder romanian_debara_builder;
    EnglishDebaraBuilder english_debara_builder;
    DebaraDirector debara_director;

    debara_director.set_builder(&romanian_debara_builder);
    Debara romanian_debara;
    romanian_debara= debara_director.construct_debara();
    ConcreteObserver ro_observer("Observer1");
    romanian_debara.register_observer(&ro_observer);

    /*for (const auto& ingredient : romanian_debara.ingrediente)
    {
        cout << ingredient.nume << " " << ingredient.cantitate << " " << ingredient.cost << endl;
    }*/

    /*debara_director.set_builder(&english_debara_builder);
    Debara english_debara = debara_director.construct_debara();

    for (const auto& ingredient : english_debara.ingrediente)
    {
        cout << ingredient.nume << " " << ingredient.cantitate << " " << ingredient.cost << endl;
    }*/



    return 0;
}
