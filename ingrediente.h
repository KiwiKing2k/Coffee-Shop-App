
#ifndef INGREDIENTE_H
#define INGREDIENTE_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "menu.h"
using namespace std;

class Debara
{
public:
    vector<Ingredient> ingrediente;
    /// watcher to be implemented
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
