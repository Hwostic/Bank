#include "Account.h"
#include "Client.h"
#include <iostream>
#include <string>
using namespace std;

#pragma once

//Класс кредитного счета

class CreditAccount : public Account {
    int id;
    long long balance;
    shared_ptr<Client> client;
    long long creditLimit;
    double commissionRate;

public:
    // Конструктор
    CreditAccount(int id, long long balance, shared_ptr<Client> client,
        long long creditLimit, double commissionRate)
        : id(id), balance(balance), client(client),
        creditLimit(creditLimit), commissionRate(commissionRate) {
    }

   
    string getType() const override;
    int getId() const override;
    long long getBalance() const override;
    double getRate() override;
    long long getCreditLimit();
    shared_ptr<Client> getClient() const override;
    void deposit(long long  amount) override;
    bool withdraw(long long  amount) override;
    void monthlyUpdate() override;
    void printInfo() const override;
};
