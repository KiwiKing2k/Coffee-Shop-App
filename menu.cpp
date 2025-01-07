#include "menu.h"

string parse_field(const string& line, size_t& start)
{
    if (start >= line.size())
    {
        return "empty";
    }
    size_t end = line.find(',', start);
    if (end == string::npos)
    {
        end = line.size();
    }
    string field = line.substr(start, end - start);
    start = end + 1;
    return field;
}

Meniu RomanianMeniuBuilder::build_meniu()
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

Meniu EnglishMeniuBuilder::build_meniu()
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

void MenuDirector::set_builder(MeniuBuilderInterface* newBuilder)
{
    builder = newBuilder;
}

Meniu MenuDirector::construct_menu()
{
    return builder->build_meniu();
}