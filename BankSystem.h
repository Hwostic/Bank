
#include "Client.h"
#include "Individual.h"
#include "LegalEntity.h"
#include "Account.h"
#include "SavingsAccount.h"
#include "CreditAccount.h"
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <algorithm>
#include <limits>

using namespace std;

#pragma once

//����� ���������� �������, �������� ���������� ���������

class BankSystem {
private:
    vector<shared_ptr<Client>> clients;
    vector<shared_ptr<Account>> accounts;
    int nextAccountId = 1;

    // ������� ������ �����
    void clearInput() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }



public:
    // �������� �������
    void createClient();

    // �������� �������������� �����
    void createSavingsAccount();

    // �������� ���������� �����
    void createCreditAccount();

    // ���������� �����
    void depositToAccount();

    // ������ �������
    void withdrawFromAccount();

    // �������� ���� ������
    void listAllAccounts() const;

    // �������� ����������
    void monthlyUpdate();

    // ����� ������ �������
    void findClientAccounts() const;

    // ������ ��������
    void listClients() const;

    // ���������� ������ � ����
    void saveToFile(const string& filename) const;

    // �������� ������ �� �����
    void loadFromFile(const string& filename);
};
