#include "Account.h"
#include "Client.h"
#include <iostream>
#include <string>
using namespace std;
#pragma once

//����� �������������� �����

class SavingsAccount : public Account
{
    int id; // ���������� �������������
    long long balance; // ������� ������
    shared_ptr<Client> client; // �������� �����
    double interestRate; // ���������� ������

public:
    // �����������
    SavingsAccount(int id, long long balance, shared_ptr<Client> client, double interestRate)
        : id(id), balance(balance), client(client), interestRate(interestRate) {
    };

    // ���������� ����������� �������
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