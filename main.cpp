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
    DebaraDirector debara_director;

    debara_director.set_builder(&romanian_debara_builder);
    Debara romanian_debara;
    romanian_debara= debara_director.construct_debara();
    ConcreteObserver ro_observer("Observer1");
    romanian_debara.register_observer(&ro_observer);
    romanian_debara.notify_observers();

    RomanianMeniuBuilder romanian_meniu_builder;
    MenuDirector meniu_director;
    meniu_director.set_builder(&romanian_meniu_builder);
    Meniu romanian_meniu= meniu_director.construct_menu();
    romanian_debara.handle_order(romanian_meniu);

    EnglishDebaraBuilder english_debara_builder;
    debara_director.set_builder(&english_debara_builder);
    Debara english_debara;
    english_debara= debara_director.construct_debara();
    ConcreteObserver en_observer("Observer2");
    english_debara.register_observer(&en_observer);
    english_debara.notify_observers();
    EnglishMeniuBuilder english_meniu_builder;
    meniu_director.set_builder(&english_meniu_builder);
    Meniu english_meniu= meniu_director.construct_menu();
    english_debara.handle_order(english_meniu);



    return 0;
}
