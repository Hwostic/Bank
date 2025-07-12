#include "BankSystem.h"
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

// �������� �������
void BankSystem::createClient() {
    string name;
    int type;

    cout << "������� ���/�������� �������: ";
    getline(cin, name);

    cout << "�������� ��� ������� (1 - ���������� ����, 2 - ����������� ����): ";
    while (!(cin >> type) || (type != 1 && type != 2)) {
        cout << "�������� ����. ���������� �����: ";
        clearInput();
    }
    clearInput();

    if (type == 1) {
        clients.push_back(make_shared<Individual>(name));
    }
    else {
        clients.push_back(make_shared<LegalEntity>(name));
    }

    cout << "������ ������� ������!\n";
}

// �������� �������������� �����
void BankSystem::createSavingsAccount() {
    if (clients.empty()) {
        cout << "��� ��������. ������� �������� �������." << endl;
        return;
    }

    listClients();
    int clientIndex;
    long long initialBalance;
        double interestRate;

    cout << "�������� ������� (1-" << clients.size() << "): ";
    while (!(cin >> clientIndex) || clientIndex < 1 || clientIndex > clients.size()) {
        cout << "�������� ����. ���������� �����: ";
        clearInput();
    }
    clearInput();

    cout << "������� ��������� ������: ";
    while (!(cin >> initialBalance) || initialBalance < 0)  //!(cin >> initialBalance)  = cin.fail()
    {
        cout << "�������� ����. ���������� �����: ";
        clearInput();
    }
    clearInput();

    cout << "������� ���������� ������: ";
    while (!(cin >> interestRate) || interestRate < 0) {
        cout << "�������� ����. ���������� �����: ";
        clearInput();
    }
    clearInput();

    accounts.push_back(make_shared<SavingsAccount>(
        nextAccountId++, initialBalance, clients[clientIndex - 1], interestRate));

    cout << "������������� ���� ������� ������! ID: " << (nextAccountId - 1) <<endl;
}

// �������� ���������� �����
void BankSystem::createCreditAccount() {
    if (clients.empty()) {
        cout << "��� ��������. ������� �������� �������." << endl;
        return;
    }

    listClients();
    int clientIndex;
    long long initialBalance, creditLimit;
    double commissionRate;

    cout << "�������� ������� (1-" << clients.size() << "): ";
    while (!(cin >> clientIndex) || clientIndex < 1 || clientIndex > clients.size()) {
        cout << "�������� ����. ���������� �����: ";
        clearInput();
    }
    clearInput();


    cout << "������� ��������� �����: ";
    while (!(cin >> creditLimit) || creditLimit < 0) {
        cout << "�������� ����. ���������� �����: ";
        clearInput();
    }
    clearInput();
    initialBalance = creditLimit;

    cout << "������� �������� �� ������������� ������� (%): ";
    while (!(cin >> commissionRate) || commissionRate < 0) {
        cout << "�������� ����. ���������� �����: ";
        clearInput();
    }
    clearInput();

    accounts.push_back(make_shared<CreditAccount>(
        nextAccountId++, initialBalance, clients[clientIndex - 1],
        creditLimit, commissionRate));

    cout << "��������� ���� ������� ������! ID: " << (nextAccountId - 1) << endl;
}

// ���������� �����
void BankSystem::depositToAccount() {
    if (accounts.empty()) {
        cout << "��� ������." << endl;
        return;
    }

    int accountId;
    double amount;

    cout << "������� ID �����: ";
    while (!(cin >> accountId)) {
        cout << "�������� ����. ���������� �����: ";
        clearInput();
    }
    clearInput();

    auto it = find_if(accounts.begin(), accounts.end(),[accountId](const shared_ptr<Account>& acc) 
        { 
            return acc->getId() == accountId; 
        });

    if (it == accounts.end()) {
        cout << "���� � ����� ID �� ������." << endl;
        return;
    }

    cout << "������� ����� ��� ����������: ";
    while (!(cin >> amount) || amount <= 0) {
        cout << "�������� ����. ���������� �����: ";
        clearInput();
    }
    clearInput();

    (*it)->deposit(amount);
    cout << "���� ������� ��������. ����� ������: " << (*it)->getBalance() << endl;
}

// ������ �������
void BankSystem::withdrawFromAccount() {
    if (accounts.empty()) {
        cout << "��� ������." << endl;
        return;
    }

    int accountId;
    double amount;

    cout << "������� ID �����: ";
    while (!(cin >> accountId)) {
        cout << "�������� ����. ���������� �����: ";
        clearInput();
    }
    clearInput();

    auto it = find_if(accounts.begin(), accounts.end(),
        [accountId](const shared_ptr<Account>& acc) { return acc->getId() == accountId; });

    if (it == accounts.end()) {
        cout << "���� � ����� ID �� ������." << endl;
        return;
    }

    cout << "������� ����� ��� ������: ";
    while (!(cin >> amount) || amount <= 0) {
        cout << "�������� ����. ���������� �����: ";
        clearInput();
    }
    clearInput();

    if ((*it)->withdraw(amount)) {
        cout << "�������� ������� �����. ����� ������: " << (*it)->getBalance() <<endl;
    }
    else {
        cout << "������������ ������� �� �����." << endl;
    }
}

// �������� ���� ������
void BankSystem::listAllAccounts() const {
    if (accounts.empty()) {
        cout << "��� ������." << endl;
        return;
    }

    cout << "������ ���� ������:" << endl;
    for (const auto& account : accounts) {
        account->printInfo();
        cout << "\n";
    }
}

// �������� ����������
void BankSystem::monthlyUpdate() {
    if (accounts.empty()) {
        cout << "��� ������ ��� ����������." << endl;
        return;
    }

    for (auto& account : accounts) {
        account->monthlyUpdate();
    }

    cout << "�������� ���������� ��������� ��� ���� ������. �������� ���������"<<endl;
}

// ����� ������ �������
void BankSystem::findClientAccounts() const {
    if (clients.empty()) {
        cout << "��� ��������." << endl;
        return;
    }

    string name;
    cout << "������� ��� �������: ";
    getline(cin, name);

    vector<shared_ptr<Account>> clientAccounts;
    for (const auto& account : accounts) {
        if (account->getClient()->getName() == name) {
            clientAccounts.push_back(account);
        }
    }

    if (clientAccounts.empty()) {
        cout << "����� ��� ������� '" << name << "' �� �������." << endl;
        return;
    }

    cout << "����� ������� '" << name << "':\n";
    for (const auto& account : clientAccounts) {
        account->printInfo();
        cout <<endl;
    }
}

// ������ ��������
void BankSystem::listClients() const {
    if (clients.empty()) {
        cout << "��� ��������."<<endl;
        return;
    }

    cout << "������ ��������:" << endl;
    for (size_t i = 0; i < clients.size(); ++i) {
        cout << (i + 1) << ". ";
        clients[i]->printInfo();
        cout << endl;
    }
}

// ���������� ������ � ����
void BankSystem::saveToFile(const string& filename) const {
    ofstream file(filename);
    if (!file) {
        cerr << "������ �������� ����� ��� ������.\n";
        return;
    }
    int i = 0;
    // ��������� ��������
    file << "���������� ��������: " << clients.size() << endl << endl;
    for (const auto& client : clients) {
       
        file << ++i<< ". ��� �������: " << client->getType() << endl;
        file << "���/�������� �������: " << client->getName() << endl << endl;
       
    }

    // ��������� �����
   
    file << "---------------------------------\n���������� ������: " << accounts.size() << endl;
    for (const auto& account : accounts) {
        int i = 0;
        file << ++i << ". ID �����: " << account->getId() << endl;
        file << ++i << ". ��� �����: " << account->getType() << endl;
        file << ++i << ". ������: " << account->getBalance() << endl;
        file << ++i << ". ���/�������� ������� : " << account->getClient()->getName() << endl;

        if (auto savings = dynamic_pointer_cast<SavingsAccount>(account)) {
            file << ++i << ". ���������� ������: " << savings->getRate() << endl << endl;
        }
        else if (auto credit = dynamic_pointer_cast<CreditAccount>(account)) {
            file << ++i << ". ��������� �����: " << credit->getCreditLimit() << endl; 
            file << ++i << ". ��������: " << credit->getRate() << endl << endl;
        }
        i = 0;
        file << "---------------------------------\n" <<endl;
    }

  
    file.close();
    cout << "������ ������� ��������� � ���� '" << filename << "'.\n";
}

// �������� ������ �� �����
void BankSystem::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "������ �������� ����� '" << filename << "' ��� ������.\n";
        return;
    }

    clients.clear();
    accounts.clear();
    nextAccountId = 1;

    string line;
    int clientCount = 0;
    int accountCount = 0;

    // ������ ��������
    try {
        // ����� ����� ��������
        while (getline(file, line)) {
            if (line.find("���������� ��������: ") != string::npos) {
                clientCount = stoi(line.substr(line.find(": ") + 2));
                break;
            }
        }
        getline(file, line);

        for (int i = 0; i < clientCount; ++i) {
            string type, name;

            // ������ ���� �������
            if (!getline(file, line)) throw runtime_error("������ ������ ���� �������");
            size_t pos = line.find(": ");
            if (pos == string::npos) throw runtime_error("�������� ������ ���� �������");
            type = line.substr(pos + 2);

            // ������ ����� �������
            if (!getline(file, line)) throw runtime_error("������ ������ ����� �������");
            pos = line.find(": ");
            if (pos == string::npos) throw runtime_error("�������� ������ ����� �������");
            name = line.substr(pos + 2);

            // �������� �������
            if (type == "���������� ����") {
                clients.push_back(make_shared<Individual>(name));
            }
            else if (type == "����������� ����") {
                clients.push_back(make_shared<LegalEntity>(name));
            }
            else {
                throw runtime_error("����������� ��� �������: " + type);
            }

            // ���������� ������ ������
            if (!getline(file, line)) break;
        }

        getline(file, line);
        // ������ ������
        while (getline(file, line)) {
            if (line.find("���������� ������: ") != string::npos) {
                accountCount = stoi(line.substr(line.find(": ") + 2));
                break;
            }
        }

        for (int i = 0; i < accountCount; ++i) {
          

            int id;
            string type;
            double balance;
            string clientName;

            // ������ ID �����
            if (!getline(file, line)) throw runtime_error("������ ������ ID �����");
            size_t pos = line.find(": ");
            if (pos == string::npos) throw runtime_error("�������� ������ ID �����");
            id = stoi(line.substr(pos + 2));

            // ������ ���� �����
            if (!getline(file, line)) throw runtime_error("������ ������ ���� �����");
            pos = line.find(": ");
            if (pos == string::npos) throw runtime_error("�������� ������ ���� �����");
            type = line.substr(pos + 2);

            // ������ �������
            if (!getline(file, line)) throw runtime_error("������ ������ �������");
            pos = line.find(": ");
            if (pos == string::npos) throw runtime_error("�������� ������ �������");
            balance = stod(line.substr(pos + 2));

            // ������ ����� �������
            if (!getline(file, line)) throw runtime_error("������ ������ ����� �������");
            pos = line.find(": ");
           if (pos == string::npos) throw runtime_error("�������� ������ ����� �������");
            clientName = line.substr(pos + 2);

            // ����� �������
            auto clientIt = find_if(clients.begin(), clients.end(),
                [&clientName](const shared_ptr<Client>& c) { return c->getName() == clientName; });

            if (clientIt == clients.end()) {
                cerr << "��������������: ������ '" << clientName << "' �� ������, ���������� ����\n";
                // ���������� ������� ������ �����
                while (getline(file, line) && line != "---------------------------------") {}
                continue;
            }

            // ��������� ������ ����� ������
            if (type == "�������������") {
                if (!getline(file, line)) throw runtime_error("������ ������ ���������� ������");
                pos = line.find(": ");
                if (pos == string::npos) throw runtime_error("�������� ������ ���������� ������");
                double rate = stod(line.substr(pos + 2));

                accounts.push_back(make_shared<SavingsAccount>(id, balance, *clientIt, rate));
            }
            else if (type == "���������") {
                // ������ ���������� ������
                if (!getline(file, line)) throw runtime_error("������ ������ ���������� ������");
                pos = line.find(": ");
                if (pos == string::npos) throw runtime_error("�������� ������ ���������� ������");
                double limit = stod(line.substr(pos + 2));

                // ������ ��������
                if (!getline(file, line)) throw runtime_error("������ ������ ��������");
                pos = line.find(": ");
                if (pos == string::npos) throw runtime_error("�������� ������ ��������");
                double commission = stod(line.substr(pos + 2));

                accounts.push_back(make_shared<CreditAccount>(id, balance, *clientIt, limit, commission));
            }

            // ���������� ������ ������ � �����������
            if (!getline(file, line)) break; // ������ ������
         

            // ��������� nextAccountId
            if (id >= nextAccountId) {
                nextAccountId = id + 1;
            }
            getline(file, line);
             getline(file, line);
        }
    }
    catch (const exception& e) {
        cerr << "������ ��� �������� �����: " << e.what() << endl;
        // ��������� �������� - ������� ��
        clients.clear();
        accounts.clear();
        nextAccountId = 1;
        file.close();
        return;
    }

    file.close();
    cout << "������� ���������: " << clients.size() << " �������� � " << accounts.size() << " ������\n";
}
