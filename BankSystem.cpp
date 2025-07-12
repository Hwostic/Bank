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

// Создание клиента
void BankSystem::createClient() {
    string name;
    int type;

    cout << "Введите ФИО/название клиента: ";
    getline(cin, name);

    cout << "Выберите тип клиента (1 - Физическое лицо, 2 - Юридическое лицо): ";
    while (!(cin >> type) || (type != 1 && type != 2)) {
        cout << "Неверный ввод. Попробуйте снова: ";
        clearInput();
    }
    clearInput();

    if (type == 1) {
        clients.push_back(make_shared<Individual>(name));
    }
    else {
        clients.push_back(make_shared<LegalEntity>(name));
    }

    cout << "Клиент успешно создан!\n";
}

// Открытие накопительного счета
void BankSystem::createSavingsAccount() {
    if (clients.empty()) {
        cout << "Нет клиентов. Сначала создайте клиента." << endl;
        return;
    }

    listClients();
    int clientIndex;
    long long initialBalance;
        double interestRate;

    cout << "Выберите клиента (1-" << clients.size() << "): ";
    while (!(cin >> clientIndex) || clientIndex < 1 || clientIndex > clients.size()) {
        cout << "Неверный ввод. Попробуйте снова: ";
        clearInput();
    }
    clearInput();

    cout << "Введите начальный баланс: ";
    while (!(cin >> initialBalance) || initialBalance < 0)  //!(cin >> initialBalance)  = cin.fail()
    {
        cout << "Неверный ввод. Попробуйте снова: ";
        clearInput();
    }
    clearInput();

    cout << "Введите процентную ставку: ";
    while (!(cin >> interestRate) || interestRate < 0) {
        cout << "Неверный ввод. Попробуйте снова: ";
        clearInput();
    }
    clearInput();

    accounts.push_back(make_shared<SavingsAccount>(
        nextAccountId++, initialBalance, clients[clientIndex - 1], interestRate));

    cout << "Накопительный счет успешно создан! ID: " << (nextAccountId - 1) <<endl;
}

// Открытие кредитного счета
void BankSystem::createCreditAccount() {
    if (clients.empty()) {
        cout << "Нет клиентов. Сначала создайте клиента." << endl;
        return;
    }

    listClients();
    int clientIndex;
    long long initialBalance, creditLimit;
    double commissionRate;

    cout << "Выберите клиента (1-" << clients.size() << "): ";
    while (!(cin >> clientIndex) || clientIndex < 1 || clientIndex > clients.size()) {
        cout << "Неверный ввод. Попробуйте снова: ";
        clearInput();
    }
    clearInput();


    cout << "Введите кредитный лимит: ";
    while (!(cin >> creditLimit) || creditLimit < 0) {
        cout << "Неверный ввод. Попробуйте снова: ";
        clearInput();
    }
    clearInput();
    initialBalance = creditLimit;

    cout << "Введите комиссию за использование кредита (%): ";
    while (!(cin >> commissionRate) || commissionRate < 0) {
        cout << "Неверный ввод. Попробуйте снова: ";
        clearInput();
    }
    clearInput();

    accounts.push_back(make_shared<CreditAccount>(
        nextAccountId++, initialBalance, clients[clientIndex - 1],
        creditLimit, commissionRate));

    cout << "Кредитный счет успешно создан! ID: " << (nextAccountId - 1) << endl;
}

// Пополнение счета
void BankSystem::depositToAccount() {
    if (accounts.empty()) {
        cout << "Нет счетов." << endl;
        return;
    }

    int accountId;
    double amount;

    cout << "Введите ID счета: ";
    while (!(cin >> accountId)) {
        cout << "Неверный ввод. Попробуйте снова: ";
        clearInput();
    }
    clearInput();

    auto it = find_if(accounts.begin(), accounts.end(),[accountId](const shared_ptr<Account>& acc) 
        { 
            return acc->getId() == accountId; 
        });

    if (it == accounts.end()) {
        cout << "Счет с таким ID не найден." << endl;
        return;
    }

    cout << "Введите сумму для пополнения: ";
    while (!(cin >> amount) || amount <= 0) {
        cout << "Неверный ввод. Попробуйте снова: ";
        clearInput();
    }
    clearInput();

    (*it)->deposit(amount);
    cout << "Счет успешно пополнен. Новый баланс: " << (*it)->getBalance() << endl;
}

// Снятие средств
void BankSystem::withdrawFromAccount() {
    if (accounts.empty()) {
        cout << "Нет счетов." << endl;
        return;
    }

    int accountId;
    double amount;

    cout << "Введите ID счета: ";
    while (!(cin >> accountId)) {
        cout << "Неверный ввод. Попробуйте снова: ";
        clearInput();
    }
    clearInput();

    auto it = find_if(accounts.begin(), accounts.end(),
        [accountId](const shared_ptr<Account>& acc) { return acc->getId() == accountId; });

    if (it == accounts.end()) {
        cout << "Счет с таким ID не найден." << endl;
        return;
    }

    cout << "Введите сумму для снятия: ";
    while (!(cin >> amount) || amount <= 0) {
        cout << "Неверный ввод. Попробуйте снова: ";
        clearInput();
    }
    clearInput();

    if ((*it)->withdraw(amount)) {
        cout << "Средства успешно сняты. Новый баланс: " << (*it)->getBalance() <<endl;
    }
    else {
        cout << "Недостаточно средств на счете." << endl;
    }
}

// Просмотр всех счетов
void BankSystem::listAllAccounts() const {
    if (accounts.empty()) {
        cout << "Нет счетов." << endl;
        return;
    }

    cout << "Список всех счетов:" << endl;
    for (const auto& account : accounts) {
        account->printInfo();
        cout << "\n";
    }
}

// Месячное обновление
void BankSystem::monthlyUpdate() {
    if (accounts.empty()) {
        cout << "Нет счетов для обновления." << endl;
        return;
    }

    for (auto& account : accounts) {
        account->monthlyUpdate();
    }

    cout << "Месячное обновление выполнено для всех счетов. Проценты начислены"<<endl;
}

// Поиск счетов клиента
void BankSystem::findClientAccounts() const {
    if (clients.empty()) {
        cout << "Нет клиентов." << endl;
        return;
    }

    string name;
    cout << "Введите имя клиента: ";
    getline(cin, name);

    vector<shared_ptr<Account>> clientAccounts;
    for (const auto& account : accounts) {
        if (account->getClient()->getName() == name) {
            clientAccounts.push_back(account);
        }
    }

    if (clientAccounts.empty()) {
        cout << "Счета для клиента '" << name << "' не найдены." << endl;
        return;
    }

    cout << "Счета клиента '" << name << "':\n";
    for (const auto& account : clientAccounts) {
        account->printInfo();
        cout <<endl;
    }
}

// Список клиентов
void BankSystem::listClients() const {
    if (clients.empty()) {
        cout << "Нет клиентов."<<endl;
        return;
    }

    cout << "Список клиентов:" << endl;
    for (size_t i = 0; i < clients.size(); ++i) {
        cout << (i + 1) << ". ";
        clients[i]->printInfo();
        cout << endl;
    }
}

// Сохранение данных в файл
void BankSystem::saveToFile(const string& filename) const {
    ofstream file(filename);
    if (!file) {
        cerr << "Ошибка открытия файла для записи.\n";
        return;
    }
    int i = 0;
    // Сохраняем клиентов
    file << "Количество клиентов: " << clients.size() << endl << endl;
    for (const auto& client : clients) {
       
        file << ++i<< ". Тип клиента: " << client->getType() << endl;
        file << "ФИО/название клиента: " << client->getName() << endl << endl;
       
    }

    // Сохраняем счета
   
    file << "---------------------------------\nКоличество счетов: " << accounts.size() << endl;
    for (const auto& account : accounts) {
        int i = 0;
        file << ++i << ". ID счета: " << account->getId() << endl;
        file << ++i << ". Тип счета: " << account->getType() << endl;
        file << ++i << ". Баланс: " << account->getBalance() << endl;
        file << ++i << ". ФИО/название клиента : " << account->getClient()->getName() << endl;

        if (auto savings = dynamic_pointer_cast<SavingsAccount>(account)) {
            file << ++i << ". Процентная ставка: " << savings->getRate() << endl << endl;
        }
        else if (auto credit = dynamic_pointer_cast<CreditAccount>(account)) {
            file << ++i << ". Кредитный лимит: " << credit->getCreditLimit() << endl; 
            file << ++i << ". Комиссия: " << credit->getRate() << endl << endl;
        }
        i = 0;
        file << "---------------------------------\n" <<endl;
    }

  
    file.close();
    cout << "Данные успешно сохранены в файл '" << filename << "'.\n";
}

// Загрузка данных из файла
void BankSystem::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла '" << filename << "' для чтения.\n";
        return;
    }

    clients.clear();
    accounts.clear();
    nextAccountId = 1;

    string line;
    int clientCount = 0;
    int accountCount = 0;

    // Чтение клиентов
    try {
        // Поиск блока клиентов
        while (getline(file, line)) {
            if (line.find("Количество клиентов: ") != string::npos) {
                clientCount = stoi(line.substr(line.find(": ") + 2));
                break;
            }
        }
        getline(file, line);

        for (int i = 0; i < clientCount; ++i) {
            string type, name;

            // Чтение типа клиента
            if (!getline(file, line)) throw runtime_error("Ошибка чтения типа клиента");
            size_t pos = line.find(": ");
            if (pos == string::npos) throw runtime_error("Неверный формат типа клиента");
            type = line.substr(pos + 2);

            // Чтение имени клиента
            if (!getline(file, line)) throw runtime_error("Ошибка чтения имени клиента");
            pos = line.find(": ");
            if (pos == string::npos) throw runtime_error("Неверный формат имени клиента");
            name = line.substr(pos + 2);

            // Создание клиента
            if (type == "Физическое лицо") {
                clients.push_back(make_shared<Individual>(name));
            }
            else if (type == "Юридическое лицо") {
                clients.push_back(make_shared<LegalEntity>(name));
            }
            else {
                throw runtime_error("Неизвестный тип клиента: " + type);
            }

            // Пропускаем пустую строку
            if (!getline(file, line)) break;
        }

        getline(file, line);
        // Чтение счетов
        while (getline(file, line)) {
            if (line.find("Количество счетов: ") != string::npos) {
                accountCount = stoi(line.substr(line.find(": ") + 2));
                break;
            }
        }

        for (int i = 0; i < accountCount; ++i) {
          

            int id;
            string type;
            double balance;
            string clientName;

            // Чтение ID счета
            if (!getline(file, line)) throw runtime_error("Ошибка чтения ID счета");
            size_t pos = line.find(": ");
            if (pos == string::npos) throw runtime_error("Неверный формат ID счета");
            id = stoi(line.substr(pos + 2));

            // Чтение типа счета
            if (!getline(file, line)) throw runtime_error("Ошибка чтения типа счета");
            pos = line.find(": ");
            if (pos == string::npos) throw runtime_error("Неверный формат типа счета");
            type = line.substr(pos + 2);

            // Чтение баланса
            if (!getline(file, line)) throw runtime_error("Ошибка чтения баланса");
            pos = line.find(": ");
            if (pos == string::npos) throw runtime_error("Неверный формат баланса");
            balance = stod(line.substr(pos + 2));

            // Чтение имени клиента
            if (!getline(file, line)) throw runtime_error("Ошибка чтения имени клиента");
            pos = line.find(": ");
           if (pos == string::npos) throw runtime_error("Неверный формат имени клиента");
            clientName = line.substr(pos + 2);

            // Поиск клиента
            auto clientIt = find_if(clients.begin(), clients.end(),
                [&clientName](const shared_ptr<Client>& c) { return c->getName() == clientName; });

            if (clientIt == clients.end()) {
                cerr << "Предупреждение: клиент '" << clientName << "' не найден, пропускаем счет\n";
                // Пропускаем остаток записи счета
                while (getline(file, line) && line != "---------------------------------") {}
                continue;
            }

            // Обработка разных типов счетов
            if (type == "Накопительный") {
                if (!getline(file, line)) throw runtime_error("Ошибка чтения процентной ставки");
                pos = line.find(": ");
                if (pos == string::npos) throw runtime_error("Неверный формат процентной ставки");
                double rate = stod(line.substr(pos + 2));

                accounts.push_back(make_shared<SavingsAccount>(id, balance, *clientIt, rate));
            }
            else if (type == "Кредитный") {
                // Чтение кредитного лимита
                if (!getline(file, line)) throw runtime_error("Ошибка чтения кредитного лимита");
                pos = line.find(": ");
                if (pos == string::npos) throw runtime_error("Неверный формат кредитного лимита");
                double limit = stod(line.substr(pos + 2));

                // Чтение комиссии
                if (!getline(file, line)) throw runtime_error("Ошибка чтения комиссии");
                pos = line.find(": ");
                if (pos == string::npos) throw runtime_error("Неверный формат комиссии");
                double commission = stod(line.substr(pos + 2));

                accounts.push_back(make_shared<CreditAccount>(id, balance, *clientIt, limit, commission));
            }

            // Пропускаем пустую строку и разделитель
            if (!getline(file, line)) break; // Пустая строка
         

            // Обновляем nextAccountId
            if (id >= nextAccountId) {
                nextAccountId = id + 1;
            }
            getline(file, line);
             getline(file, line);
        }
    }
    catch (const exception& e) {
        cerr << "Ошибка при загрузке файла: " << e.what() << endl;
        // Частичная загрузка - очищаем всё
        clients.clear();
        accounts.clear();
        nextAccountId = 1;
        file.close();
        return;
    }

    file.close();
    cout << "Успешно загружено: " << clients.size() << " клиентов и " << accounts.size() << " счетов\n";
}
