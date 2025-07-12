#include "Client.h"
#pragma once


//Класс юридического лица

class LegalEntity : public Client {
    string name; // Название организации
public:
    // Конструктор
    LegalEntity(const string& name) : name(name) {}

    // Реализация виртуальных функций
    string getType() const override 
    { 
        return "Юридическое лицо"; 
    }
    string getName() const override 
    { 
        return name; 
    }

    void printInfo() const override 
    {
        cout << "Тип: " << getType() << ", Название: " << name;
    }
};
