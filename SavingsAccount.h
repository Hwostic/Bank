#include "Account.h"
#include "Client.h"
#include <iostream>
#include <string>
using namespace std;
#pragma once

//Класс накопительного счета

class SavingsAccount : public Account
{
    int id; // Уникальный идентификатор
    long long balance; // Текущий баланс
    shared_ptr<Client> client; // Владелец счета
    double interestRate; // Процентная ставка

public:
    // Конструктор
    SavingsAccount(int id, long long balance, shared_ptr<Client> client, double interestRate)
        : id(id), balance(balance), client(client), interestRate(interestRate) {
    };

    // Реализация виртуальных функций
    string getType() const override;
    int getId() const override;
    long long getBalance() const override;
    double getRate() override;
    shared_ptr<Client> getClient() const override;
 

    void deposit(long long  amount) override;
    bool withdraw(long long  amount) override;
    void monthlyUpdate() override;
    void printInfo() const override;
};