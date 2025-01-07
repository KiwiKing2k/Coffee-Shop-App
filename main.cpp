#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "angajati.h"
using namespace std;


class Ingredient
{
public:
    string nume;
    int cantitate;
    float cost;
};

class Item
{
public:
    string nume;
    float pret;
    vector<string> nume_ingrediente;
};

class Meniu
{
public:
    vector<Item> cafele;
    vector<Item> bauturi;
    vector<Item> deserturi;
};

string parse_field(const string& line, size_t& start)
{
    size_t end = line.find(',', start);
    if (end == string::npos)
    {
        return "empty";
    }
    string field = line.substr(start, end - start);
    start = end + 1;
    return field;
}

class MeniuBuilderInterface
{
public:
    virtual Meniu build_meniu() = 0;
};

class RomanianMeniuBuilder : public MeniuBuilderInterface
{
public:
    Meniu build_meniu() override
    {
        Meniu meniu;
        try
        {
            ifstream file("../RO/produse.csv");
            if (!file.is_open())
            {
                throw runtime_error("Could not open the file!");
            }
            string line;

            while (getline(file, line))
            {
                Item read_item;
                size_t start = 0;
                string type = parse_field(line, start);
                read_item.nume = parse_field(line, start);
                read_item.pret = stof(parse_field(line, start));
                string read = parse_field(line, start);
                while (read != "empty")
                {
                    read_item.nume_ingrediente.push_back(read);
                    read = parse_field(line, start);
                }
                if (type == "cafele")
                {
                    meniu.cafele.push_back(read_item);
                }
                else if (type == "bauturi")
                {
                    meniu.bauturi.push_back(read_item);
                }
                else if (type == "deserturi")
                {
                    meniu.deserturi.push_back(read_item);
                }
                else
                {
                    throw runtime_error("Tip invalid de produs!");
                }
            }
        }
        catch (exception& e)
        {
            cout << e.what() << endl;
        }
        return meniu;
    }
};

class EnglishMeniuBuilder : public MeniuBuilderInterface
{
public:
    Meniu build_meniu() override
    {
        Meniu meniu;
        try
        {
            ifstream file("../ENG/produse.csv");
            if (!file.is_open())
            {
                throw runtime_error("Could not open the file!");
            }
            string line;

            while (getline(file, line))
            {
                Item read_item;
                size_t start = 0;
                string type = parse_field(line, start);
                read_item.nume = parse_field(line, start);
                read_item.pret = stof(parse_field(line, start));
                string read = parse_field(line, start);
                while (read != "empty")
                {
                    read_item.nume_ingrediente.push_back(read);
                    read = parse_field(line, start);
                }
                if (type == "coffees")
                {
                    meniu.cafele.push_back(read_item);
                }
                else if (type == "drinks")
                {
                    meniu.bauturi.push_back(read_item);
                }
                else if (type == "desserts")
                {
                    meniu.deserturi.push_back(read_item);
                }
                else
                {
                    throw runtime_error("Invalid type!");
                }
            }
        }
        catch (exception& e)
        {
            cout << e.what() << endl;
        }
        return meniu;
    }
};

class MenuDirector
{
    ///example of builder design pattern made for multiple menu entries
private:
    MeniuBuilderInterface* builder = nullptr;

public:
    void set_builder(MeniuBuilderInterface* newBuilder)
    {
        builder = newBuilder;
    }

    Meniu construct_menu()
    {
        return builder->build_meniu();
    }
};

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
