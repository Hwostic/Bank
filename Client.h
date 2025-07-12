#pragma once

#include <iostream>
#include <string>
using namespace std;

// ����������� ����� ������� (��� ��� � �� ���)

class Client
{
public:
  
    
    virtual string getType() const = 0; //��� ��������� ���� ������� (��� ��� ��)
    virtual string getName() const = 0; //��������� ���
    virtual void printInfo() const = 0; 
    virtual ~Client() = default;

};

