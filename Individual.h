#include "Client.h"

#pragma once

//Так как тут функций очень мало с одной строчкой кода, решено оставить реализацию тут

//Класс физического лица

class Individual : public Client
{
    string name; // Имя клиента
public:
    // Конструктор
    Individual(const string& name) : name(name) {}

    // Реализация виртуальных функций
    string getType() const override 
    { 
        return "Физическое лицо"; 
    }
    string getName() const override 
    { 
        return name; 
    }

    void printInfo() const override 
    {
        cout << "Тип: " << getType() << ", ФИО: " << name;
    }
};

