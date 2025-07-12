#include "Client.h"
#include <iostream>
#include <string>
using namespace std;

#pragma once

// Абстрактный класс счета

class Account {
public:
 
    virtual ~Account() = default;

    virtual string getType() const = 0;     //тип счета - накопительный или кредитный
    virtual int getId() const = 0;          //ай ди счета
    virtual long long getBalance() const = 0;
    virtual double getRate() = 0;
    virtual shared_ptr<Client> getClient() const = 0; //shared_ptr - умный указатель, автоматически управляющий памятью. Для безопасного хранения
    virtual void deposit(long long  amount) = 0;
    virtual bool withdraw(long long  amount) = 0; // Снятие средств
    virtual void monthlyUpdate() = 0;
    virtual void printInfo() const = 0;
};

