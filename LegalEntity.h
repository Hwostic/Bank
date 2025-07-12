#include "Client.h"
#pragma once


//����� ������������ ����

class LegalEntity : public Client {
    string name; // �������� �����������
public:
    // �����������
    LegalEntity(const string& name) : name(name) {}

    // ���������� ����������� �������
    string getType() const override 
    { 
        return "����������� ����"; 
    }
    string getName() const override 
    { 
        return name; 
    }

    void printInfo() const override 
    {
        cout << "���: " << getType() << ", ��������: " << name;
    }
};
