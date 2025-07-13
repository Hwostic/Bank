
#include "Client.h"
#include "Individual.h"
#include "LegalEntity.h"
#include "Account.h"
#include "SavingsAccount.h"
#include "CreditAccount.h"
#include "BankSystem.h"
#include <iostream>
#include <windows.h>

using namespace std;


int main()
{
    system("chcp1251");
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    BankSystem bank;
    int choice;

    cout << "---------------------------" << endl;
    cout << "    БАНКОВСКАЯ СИСТЕМА" << endl;
    cout << "---------------------------" << endl;
    do {

        cout << "\n\tГлавное меню:" << endl << endl;
        cout << "1. Создать клиента" << endl;
        cout << "2. Открыть накопительный счет" << endl;
        cout << "3. Открыть кредитный счет" << endl;
        cout << "4. Пополнить счет" << endl;
        cout << "5. Снять средства" << endl;
        cout << "6. Просмотреть все счета" << endl;
        cout << "7. Просмотреть всех клиентов" << endl;
        cout << "8. Месячное обновление" << endl;
        cout << "9. Найти счета клиента" << endl;
        cout << "10. Сохранить данные в файл" << endl;
        cout << "11. Загрузить данные из файла" << endl;
        cout << "0. Выход" << endl << endl;
        cout << "Выберите действие: ";

        cin >> choice;
        cout << endl;
        cin.ignore();

        switch (choice) {
        case 1:
            bank.createClient();
            break;
        case 2:
            bank.createSavingsAccount();
            break;
        case 3:
            bank.createCreditAccount();
            break;
        case 4:
            bank.depositToAccount();
            break;
        case 5:
            bank.withdrawFromAccount();
            break;
        case 6:
            bank.listAllAccounts();
            break;
        case 7:
            bank.listClients();
            break;
        case 8:
            bank.monthlyUpdate();
            break;
        case 9:
            bank.findClientAccounts();
            break;
        case 10:
            bank.saveToFile("bank_data.txt");
            break;
        case 11:
            bank.loadFromFile("bank_data.txt");
            break;
        case 0:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}

