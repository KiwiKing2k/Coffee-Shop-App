#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "angajati.h"
#include "menu.h"
using namespace std;


int main()
{
    MenuDirector director;
    RomanianMeniuBuilder roBuilder;
    EnglishMeniuBuilder engBuilder;

    director.set_builder(&roBuilder);
    Meniu roMenu = director.construct_menu();

    director.set_builder(&engBuilder);
    Meniu engMenu = director.construct_menu();

    //Romanian menu
    for (const auto& item : roMenu.cafele)
    {
        cout << "Coffee: " << item.nume << ", Price: " << item.pret << endl;
        for (const auto& ingredient : item.nume_ingrediente)
        {
            cout << "Ingredient: " << ingredient << endl;
        }
    }
    for (const auto& item : roMenu.bauturi)
    {
        cout << "Drink: " << item.nume << ", Price: " << item.pret << endl;
    }
    for (const auto& item : roMenu.deserturi)
    {
        cout << "Dessert: " << item.nume << ", Price: " << item.pret << endl;
    }

    cout<<endl;
    cout<<endl;

    //English menu
    for (const auto& item : engMenu.cafele)
    {
        cout << "Coffee: " << item.nume << ", Price: " << item.pret << endl;
        for (const auto& ingredient : item.nume_ingrediente)
        {
            cout << "Ingredient: " << ingredient << endl;
        }
    }
    for (const auto& item : engMenu.bauturi)
    {
        cout << "Drink: " << item.nume << ", Price: " << item.pret << endl;
    }
    for (const auto& item : engMenu.deserturi)
    {
        cout << "Dessert: " << item.nume << ", Price: " << item.pret << endl;
    }

    return 0;
}
