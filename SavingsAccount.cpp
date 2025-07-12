#include "SavingsAccount.h"
#include "Account.h"
#include "Client.h"
#include <iostream>
#include <string>
using namespace std;

   
    string SavingsAccount::getType() const 
    { 
        return "�������������"; 
    }

    int SavingsAccount::getId() const  
    { 
        return id; 
    }
    long long SavingsAccount::getBalance() const
    { 
        return balance; 
    }
    double SavingsAccount::getRate() 
    {
        return interestRate;
    }


    shared_ptr<Client> SavingsAccount::getClient() const  
    { 
        return client; 
    }

    void SavingsAccount::deposit(long long amount)  
    {
        balance += amount;
    }

    bool SavingsAccount::withdraw(long long  amount)
    {
        if (amount > balance) {
            return false;
        }
        balance -= amount;
        return true;
    }

    void SavingsAccount::monthlyUpdate()  
    {
        balance += balance * interestRate / 100;
    }

    void SavingsAccount::printInfo() const  
    {
        cout << "ID: " << id << ", ���: " << getType()
            << ", ������: " << balance << ", ������: " << client->getName()
            << ", ���������� ������: " << interestRate << "%";
    }
