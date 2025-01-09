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
    DebaraDirector debara_director;
    cout<<"Bine ati venit la cafenea!"<<endl;
    cout<<"Alegeti limba:"<<endl;
    cout<<"1. Romana"<<endl;
    cout<<"2. Engleza"<<endl;
    int choice;
    cin>>choice;
    if (choice==1)
    {
        RomanianDebaraBuilder romanian_debara_builder;
        debara_director.set_builder(&romanian_debara_builder);
        Debara romanian_debara;
        romanian_debara= debara_director.construct_debara();
        ConcreteObserver ro_observer("Romanian Observer");
        romanian_debara.register_observer(&ro_observer);
        romanian_debara.notify_observers();
        vector<client_info> clients;
        RomanianMeniuBuilder romanian_meniu_builder;
        MenuDirector meniu_director;
        meniu_director.set_builder(&romanian_meniu_builder);
        Meniu romanian_meniu= meniu_director.construct_menu();
        float total_profit = 0;
        float total_cost = 0;
        romanian_debara.handle_order(romanian_meniu, total_profit, total_cost, clients);
        cout<<"Profit total:"<<total_profit<<endl;
        cout<<"Cost total:"<<total_cost<<endl;
        romanian_debara.handle_special_order(romanian_meniu, total_profit, total_cost);

        string file_path;
        cout<<"Introduceti calea catre fisierul cu angajati:"<<endl;
        cin>>file_path;
        Team angajati= read_angajati(file_path);
        cout<<"Profit total pentru toata ziua:"<<total_profit<<endl;
        cout<<"Cost total pentru toata ziua:"<<total_cost<<endl<<endl;
        cout<<"Angajati:"<<endl;
        cout<<"Bariste:"<<endl;
        for (auto& angajat : angajati.bariste)
        {
            cout<<"Nume: "<<angajat.nume<<endl;
            cout<<"Ora inceput: "<<angajat.ora_inceput<<endl;
            cout<<"Ora sfarsit: "<<angajat.ora_sfarsit<<endl;
            cout<<"Salariu: "<<angajat.salariu<<endl<<endl;
        }
        cout<<"Manageri:"<<endl;
        for (auto& angajat : angajati.manageri)
        {
            cout<<"Nume: "<<angajat.nume<<endl;
            cout<<"Ora inceput: "<<angajat.ora_inceput<<endl;
            cout<<"Ora sfarsit: "<<angajat.ora_sfarsit<<endl;
            cout<<"Salariu: "<<angajat.salariu<<endl<<endl;
        }
        cout<<"Ospatari:"<<endl;
        for (auto& angajat : angajati.ospatari)
        {
            cout<<"Nume: "<<angajat.nume<<endl;
            cout<<"Ora inceput: "<<angajat.ora_inceput<<endl;
            cout<<"Ora sfarsit: "<<angajat.ora_sfarsit<<endl;
            cout<<"Salariu: "<<angajat.salariu<<endl<<endl;
        }
        cout<<"Pentru a salva lista de ingrediente in fisier, introduceti calea catre fisierul dorit:"<<endl;
        cout<<"Altfel, introduceti 0."<<endl;
        string file_path2;
        cin>>file_path2;
        if (file_path2!="0")
        {
            romanian_debara.save_list(file_path2);
        }
    }
    else
    {
        EnglishDebaraBuilder english_debara_builder;
        debara_director.set_builder(&english_debara_builder);
        Debara english_debara = debara_director.construct_debara();
        ConcreteObserver en_observer("English Observer");
        english_debara.register_observer(&en_observer);
        english_debara.notify_observers();
        vector<client_info> clients;
        EnglishMeniuBuilder english_meniu_builder;
        MenuDirector meniu_director;
        meniu_director.set_builder(&english_meniu_builder);
        Meniu english_meniu = meniu_director.construct_menu();
        float total_profit = 0;
        float total_cost = 0;
        english_debara.handle_order(english_meniu, total_profit, total_cost, clients);
        cout << "Total profit:" << total_profit << endl;
        cout << "Total cost:" << total_cost << endl;
        english_debara.handle_special_order(english_meniu, total_profit, total_cost);

        string file_path;
        cout << "Enter the path to the employees file:" << endl;
        cin >> file_path;
        Team angajati = read_angajati(file_path);
        cout << "Total profit for the whole day:" << total_profit << endl;
        cout << "Total cost for the whole day:" << total_cost << endl << endl;
        cout << "Employees:" << endl;
        cout << "Baristas:" << endl;
        for (auto& angajat : angajati.bariste)
        {
            cout << "Name: " << angajat.nume << endl;
            cout << "Start time: " << angajat.ora_inceput << endl;
            cout << "End time: " << angajat.ora_sfarsit << endl;
            cout << "Salary: " << angajat.salariu << endl << endl;
        }
        cout << "Managers:" << endl;
        for (auto& angajat : angajati.manageri)
        {
            cout << "Name: " << angajat.nume << endl;
            cout << "Start time: " << angajat.ora_inceput << endl;
            cout << "End time: " << angajat.ora_sfarsit << endl;
            cout << "Salary: " << angajat.salariu << endl << endl;
        }
        cout << "Waiters:" << endl;
        for (auto& angajat : angajati.ospatari)
        {
            cout << "Name: " << angajat.nume << endl;
            cout << "Start time: " << angajat.ora_inceput << endl;
            cout << "End time: " << angajat.ora_sfarsit << endl;
            cout << "Salary: " << angajat.salariu << endl << endl;
        }
        cout << "To save the ingredient list to a file, enter the desired file path:" << endl;
        cout << "Otherwise, enter 0." << endl;
        string file_path2;
        cin >> file_path2;
        if (file_path2 != "0")
        {
            english_debara.save_list(file_path2);
        }
    }

    // 1 ../RO/debara.csv ../RO/produse.csv ../RO/orders.csv ../RO/evenimente_speciale.csv ../RO/angajati.csv ../RO/lista_salvata.csv
    // 2 ../ENG/debara.csv ../ENG/produse.csv ../ENG/orders.csv ../ENG/evenimente_speciale.csv ../ENG/angajati.csv ../ENG/lista_salvata.csv
    return 0;
}
