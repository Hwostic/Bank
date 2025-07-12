#include "CreditAccount.h"
#include "Account.h"
#include "Client.h"
#include <iostream>
#include <string>
using namespace std;

string CreditAccount::getType() const
{ 
    return "Кредитный"; 
}

int CreditAccount::getId() const
{ 
    return id; 
}

long long CreditAccount::getBalance() const
{ 
    return balance; 
}

double CreditAccount::getRate()
{
    return commissionRate;
}

long long CreditAccount::getCreditLimit()
{
    return creditLimit;
}


shared_ptr<Client> CreditAccount::getClient() const
{ 
    return client; 
}

void CreditAccount::deposit(long long  amount)
{
    balance += amount;
}

bool CreditAccount::withdraw(long long  amount)
{
    if (amount > balance + creditLimit) {
        return false;
    }
    balance -= amount;
    return true;
}

void CreditAccount::monthlyUpdate()
{
    if (balance < 0) {
        double commission = -balance * commissionRate / 100;
        balance -= commission;
    }
}

void CreditAccount::printInfo() const
{
    cout << "ID: " << id << ", Тип: " << getType()
        << ", Баланс: " << balance << ", Клиент: " << client->getName()
        << ", Кредитный лимит: " << creditLimit
        << ", Комиссия: " << commissionRate << "%";
}
