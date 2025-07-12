
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

//Класс банковской системы, основная реализация программы

class BankSystem {
private:
    vector<shared_ptr<Client>> clients;
    vector<shared_ptr<Account>> accounts;
    int nextAccountId = 1;

    // Очистка буфера ввода
    void clearInput() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }



public:
    // Создание клиента
    void createClient();

    // Открытие накопительного счета
    void createSavingsAccount();

    // Открытие кредитного счета
    void createCreditAccount();

    // Пополнение счета
    void depositToAccount();

    // Снятие средств
    void withdrawFromAccount();

    // Просмотр всех счетов
    void listAllAccounts() const;

    // Месячное обновление
    void monthlyUpdate();

    // Поиск счетов клиента
    void findClientAccounts() const;

    // Список клиентов
    void listClients() const;

    // Сохранение данных в файл
    void saveToFile(const string& filename) const;

    // Загрузка данных из файла
    void loadFromFile(const string& filename);
};
