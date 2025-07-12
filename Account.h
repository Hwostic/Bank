#include "Client.h"
#include <iostream>
#include <string>
using namespace std;

#pragma once

// ����������� ����� �����

class Account {
public:
 
    virtual ~Account() = default;

    virtual string getType() const = 0;     //��� ����� - ������������� ��� ���������
    virtual int getId() const = 0;          //�� �� �����
    virtual long long getBalance() const = 0;
    virtual double getRate() = 0;
    virtual shared_ptr<Client> getClient() const = 0; //shared_ptr - ����� ���������, ������������� ����������� �������. ��� ����������� ��������
    virtual void deposit(long long  amount) = 0;
    virtual bool withdraw(long long  amount) = 0; // ������ �������
    virtual void monthlyUpdate() = 0;
    virtual void printInfo() const = 0;
};

