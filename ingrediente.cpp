#include "ingrediente.h"

void ConcreteObserver::stock_check()
{
    cout << "Stock check" << endl;
}

void Debara::register_observer(Observer* observer)
{
    observers.push_back(observer);
}

void Debara::remove_observer(Observer* observer)
{
    erase(observers, observer);
    cout << "Observer died" << endl;
}

void Debara::notify_observers()
{
    for (auto& observer : observers)
    {
        observer->stock_check();
    }
}

Debara RomanianDebaraBuilder::build_debara()
{
    Debara debara;
    try
    {
        ifstream file("../RO/debara.csv");
        if (!file.is_open())
        {
            throw runtime_error("Could not open the file!");
        }
        string line;

        while (getline(file, line))
        {
            Ingredient read_ingredient;
            size_t start = 0;
            read_ingredient.nume = parse_field(line, start);
            read_ingredient.cantitate = stoi(parse_field(line, start));
            read_ingredient.cost = stof(parse_field(line, start));
            debara.ingrediente.push_back(read_ingredient);
        }
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
    }
    return debara;
}

Debara EnglishDebaraBuilder::build_debara()
{
    Debara debara;
    try
    {
        ifstream file("../ENG/debara.csv");
        if (!file.is_open())
        {
            throw runtime_error("Could not open the file!");
        }
        string line;

        while (getline(file, line))
        {
            Ingredient read_ingredient;
            size_t start = 0;
            read_ingredient.nume = parse_field(line, start);
            read_ingredient.cantitate = stoi(parse_field(line, start));
            read_ingredient.cost = stof(parse_field(line, start));
            debara.ingrediente.push_back(read_ingredient);
        }
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
    }
    return debara;
}

void DebaraDirector::set_builder(DebaraBuilderInterface* newBuilder)
{
    builder = newBuilder;
}

Debara DebaraDirector::construct_debara()
{
    if (builder == nullptr)
    {
        throw runtime_error("No builder set!");
    }
    return builder->build_debara();
}