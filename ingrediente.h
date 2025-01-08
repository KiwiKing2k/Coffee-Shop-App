#ifndef INGREDIENTE_H
#define INGREDIENTE_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "menu.h"
using namespace std;

class Observer
{
    /// observer interface
public:
    virtual void stock_check() = 0; /// will check all the ingredients, but before the rewrite of the csv
    virtual ~Observer() = default;
};

class ConcreteObserver : public Observer
{
private:
    string name;
public:
    ConcreteObserver(const std::string& name) : name(name) {}
    void stock_check() override;
};

class Subject
{
    /// interface for overwatch of the stock innate to the debara class
public:
    virtual void register_observer(Observer* observer) = 0;
    virtual void remove_observer(Observer* observer) = 0;
    virtual void notify_observers() = 0;
    virtual ~Subject() = default;
};

class Debara : public Subject
{
public:
    vector<Ingredient> ingrediente;
    vector<Observer*> observers;
    string order_file_path;

    void register_observer(Observer* observer) override;
    void remove_observer(Observer* observer) override;
    void notify_observers() override;
    void handle_order(Meniu& meniu);

};

class DebaraBuilderInterface
{
public:
    virtual Debara build_debara() = 0;
};

class RomanianDebaraBuilder : public DebaraBuilderInterface
{
public:
    Debara build_debara() override;
};

class EnglishDebaraBuilder : public DebaraBuilderInterface
{
public:
    Debara build_debara() override;
};

class DebaraDirector
{
private:
    DebaraBuilderInterface* builder = nullptr;

public:
    void set_builder(DebaraBuilderInterface* newBuilder);
    Debara construct_debara();
};

#endif //INGREDIENTE_H
