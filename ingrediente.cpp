#include "ingrediente.h"

void ConcreteObserver::stock_check()
{
    cout << name << " checked the stock" << endl;
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
        for (auto& ingredient : ingrediente)
        {
            if (ingredient.cantitate < 10)
            {
                cout << "Warning! " << ingredient.nume << " is running low!" << endl;
            }
        }
        observer->stock_check();
    }
}

void Debara::handle_order(Meniu& meniu)
{
    try
    {
        ifstream file(order_file_path);
        if (!file.is_open())
        {
            throw runtime_error("Could not open the file!");
        }
        string line;
        getline(file, line); //skip first
        while (getline(file, line))
        {
            size_t start = 0;
            string item_name = parse_field(line, start);
            float item_quantity = stof(parse_field(line, start));
            vector<Item> all_items_on_menu = meniu.cafele;
            all_items_on_menu.insert(all_items_on_menu.end(), meniu.bauturi.begin(), meniu.bauturi.end());
            all_items_on_menu.insert(all_items_on_menu.end(), meniu.deserturi.begin(), meniu.deserturi.end());

            /// for each ingredient in debara
            for (auto& ingredient : ingrediente)
            {
                /// searching for the required item in the whole menu
                for (auto& item : all_items_on_menu)
                {
                    if (item.nume == item_name)
                    {
                        /// if match, check if the ingredient is needed
                        for (auto& ingredient_info : item.ingrediente_necesare)
                        {
                            if (ingredient_info.name == ingredient.nume)
                            {
                                ///update quantity
                                if (ingredient.cantitate < ingredient_info.cantitate_necesara * item_quantity)
                                {
                                    throw runtime_error("Not enough "+ingredient.nume + " for " + item_name);
                                }
                                else
                                {
                                    ingredient.cantitate -= ingredient_info.cantitate_necesara * item_quantity;
                                }
                            }
                        }
                    }
                }

            }
        }
        notify_observers();
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
    }
}

Debara RomanianDebaraBuilder::build_debara()
{
    Debara debara;
    debara.order_file_path = "../RO/orders.csv";
    try
    {
        ifstream file("../RO/debara.csv");
        if (!file.is_open())
        {
            throw runtime_error("Could not open the file!");
        }
        string line;
        getline(file, line); //skip first
        while (getline(file, line))
        {
            Ingredient read_ingredient;
            size_t start = 0;
            read_ingredient.nume = parse_field(line, start);
            read_ingredient.cantitate = stof(parse_field(line, start));
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
    debara.order_file_path = "../ENG/orders.csv";
    try
    {
        ifstream file("../ENG/debara.csv");
        if (!file.is_open())
        {
            throw runtime_error("Could not open the file!");
        }
        string line;
        getline(file, line); //skip first
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