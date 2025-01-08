#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

class Ingredient
{
public:
    string nume;
    float cantitate;
    float cost;
};

typedef struct ingredient_info
{
    string name;
    float cantitate_necesara;
}ingredient_info;

class Item
{
public:
    string nume;
    float pret;
    vector<ingredient_info> ingrediente_necesare;
};


class Meniu
{
public:
    vector<Item> cafele;
    vector<Item> bauturi;
    vector<Item> deserturi;
};

string parse_field(const string& line, size_t& start);

class MeniuBuilderInterface
{
public:
    virtual Meniu build_meniu() = 0;
};

class RomanianMeniuBuilder : public MeniuBuilderInterface
{
public:
    Meniu build_meniu() override;
};

class EnglishMeniuBuilder : public MeniuBuilderInterface
{
public:
    Meniu build_meniu() override;
};

class MenuDirector
{
private:
    MeniuBuilderInterface* builder = nullptr;

public:
    void set_builder(MeniuBuilderInterface* newBuilder);
    Meniu construct_menu();
};

#endif // MENU_H