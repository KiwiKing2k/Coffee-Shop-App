#include "ingrediente.h"

void ConcreteObserver::stock_check(vector<Ingredient> ingrediente)
{
    for (auto& ingredient : ingrediente)
    {
        if (ingredient.cantitate < 10)
        {
            cout << "Low stock for " << ingredient.nume << endl;
        }
    }
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
        observer->stock_check(this->ingrediente);
    }
}

void Debara::handle_order(Meniu& meniu, float& total_profit, float& total_cost, vector<client_info>& clients)
{
    vector<client_info> clients_reserve=clients;
    try
    {
        cout << "Enter order file path:" << endl;
        cin >> order_file_path;
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
            string client_name = parse_field(line, start);
            string item_name = parse_field(line, start);
            int item_quantity = stoi(parse_field(line, start));
            client_info* current_client;
            bool found = false;
            for (auto& client : clients)
            {
                if (client.name == client_name)
                {
                    current_client = &client;//found the client
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                current_client = new client_info;
                current_client->name = client_name;
                current_client->loyalty = 0;
                clients.push_back(*current_client);
                current_client = &clients.back();
            }

            vector<Item> all_items_on_menu = meniu.cafele;
            all_items_on_menu.insert(all_items_on_menu.end(), meniu.bauturi.begin(), meniu.bauturi.end());
            all_items_on_menu.insert(all_items_on_menu.end(), meniu.deserturi.begin(), meniu.deserturi.end());
            //identify item price
            for (auto& item : all_items_on_menu)
            {
                if (item.nume == item_name)
                {
                    //applying loyalty discount
                    if (current_client->loyalty > 20)
                    {
                        total_profit += item.pret * item_quantity * 0.9f;
                    }
                    else if (current_client->loyalty > 100)
                    {
                        total_profit += item.pret * item_quantity * 0.8f;
                    }
                    else
                    {
                        total_profit += item.pret * item_quantity;
                    }
                }
            }

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
                                    throw runtime_error("Not enough " + ingredient.nume + " for " + item_name);
                                }
                                else
                                {
                                    ingredient.cantitate -= ingredient_info.cantitate_necesara * item_quantity;
                                    total_cost += ingredient_info.cantitate_necesara * item_quantity * ingredient.cost;
                                }
                            }
                        }
                    }
                }
            }

            current_client->loyalty += item_quantity;//this is the loyalty
        }
        notify_observers();
    }
    catch (exception& e)
    {
        clients=clients_reserve;//rollback
        total_cost = 0;
        total_profit = 0;
        cout << e.what() << endl;
        cout << "Order failed" << endl;
    }
}

void Debara::handle_special_order(Meniu& meniu, float &total_profit, float &total_cost)
{
    float profit_saved = total_profit;
    float cost_saved = total_cost;
    try
    {
        cout << "Special order, enter file location:" << endl;
        string file_location;
        cin >> file_location;
        ifstream file(file_location);
        if (!file.is_open())
        {
            throw runtime_error("Could not open the file!");
        }
        string line;
        getline(file, line);//first line
        size_t start = 0;
        parse_field(line, start);//skip name
        total_profit+=stof(parse_field(line, start));//total profit
        total_cost+=stof(parse_field(line, start));//auxiliary costs(ex: delivery, lights, sound, etc.)
        while (getline(file, line))
        {
            //all lines are treated like normal orders without name and loyalty
            start = 0;
            string item_name = parse_field(line, start);
            int item_quantity = stoi(parse_field(line, start));
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
                                    throw runtime_error("Not enough " + ingredient.nume + " for " + item_name);
                                }
                                else
                                {
                                    ingredient.cantitate -= ingredient_info.cantitate_necesara * item_quantity;
                                    total_cost += ingredient_info.cantitate_necesara * item_quantity * ingredient.cost;
                                }
                            }
                        }
                    }
                }
            }
        }
    }catch(exception& e)
    {
        total_profit = profit_saved;
        total_cost = cost_saved;
        cout<<e.what()<<endl;
    }
}

void Debara::save_list(string file_path)
{
    ofstream file(file_path);
    if (!file.is_open())
    {
        throw runtime_error("Could not open the file!");
    }
    file<<"ingredient_name,initial_quantity,price per gram/liter"<<endl;
    for (auto& ingredient : ingrediente)
    {
        file << ingredient.nume << "," << ingredient.cantitate << "," << ingredient.cost << endl;
    }
}


Debara RomanianDebaraBuilder::build_debara()
{
    Debara debara;
    debara.order_file_path = "../RO/orders.csv";
    try
    {
        cout << "Enter debara file path:" << endl;
        string debara_file_path;
        cin >> debara_file_path;
        ifstream file(debara_file_path);
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
        string debara_file_path;
        cout << "Enter debara file path:" << endl;
        cin >> debara_file_path;
        ifstream file(debara_file_path);
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
