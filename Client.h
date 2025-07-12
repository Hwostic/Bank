#pragma once

#include <iostream>
#include <string>
using namespace std;

// АБСТРАКТНЫЙ КЛАСС КЛИЕНТА (для физ и юр лиц)

class Client
{
public:
  
    
    virtual string getType() const = 0; //для получения типа клиента (физ или юр)
    virtual string getName() const = 0; //получение ФИО
    virtual void printInfo() const = 0; 
    virtual ~Client() = default;

};

