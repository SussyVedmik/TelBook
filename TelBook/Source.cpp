#include <iostream>
#include <fstream>

using namespace std;

const int nameLength = 100;

class Contact {
private:
    char* name;
    char homeNum[20];
    char workNum[20];
    char mobileNum[20];
    char addlInfo[100];

public:
    Contact() {
        name = new char[nameLength];
    }

    ~Contact() {
        delete[] name;
    }

    void addContact() {
        cout << "Введите ФИО: ";
        cin.getline(name, nameLength);

        cout << "Введите домашний телефон: ";
        cin.getline(homeNum, 20);

        cout << "Введите рабочий телефон: ";
        cin.getline(workNum, 20);

        cout << "Введите мобильный телефон: ";
        cin.getline(mobileNum, 20);

        cout << "Введите дополнительную информацию о контакте: ";
        cin.getline(addlInfo, 100);
    }

    void deleteContact() {
        delete[] name;
        name = nullptr;
    }

    bool searchContact(const char* searchName) {
        return strcmp(name, searchName) == 0;
    }

    void displayContact() {
        cout << "ФИО: " << name << endl;
        cout << "Домашний телефон: " << homeNum << endl;
        cout << "Рабочий телефон: " << workNum << endl;
        cout << "Мобильный телефон: " << mobileNum << endl;
        cout << "Дополнительная информация: " << addlInfo << endl;
    }

    void saveContact(ofstream& file) {
        file.write(name, nameLength);
        file.write(homeNum, 20);
        file.write(workNum, 20);
        file.write(mobileNum, 20);
        file.write(addlInfo, 100);
    } 

    void loadContact(ifstream& file) {
        file.read(name, nameLength);
        file.read(homeNum, 20);
        file.read(workNum, 20);
        file.read(mobileNum, 20);
        file.read(addlInfo, 100);
    }
};

int main() {
    Contact contacts[100];
    int numContacts = 0;
    char searchName[nameLength];
    setlocale(LC_ALL, "Russian");

    while (true) {
        cout << "\n";
        cout << "Меню:" << endl;
        cout << "1. Добавить абонента" << endl;
        cout << "2. Удалить абонента" << endl;
        cout << "3. Поиск абонента по ФИО" << endl;
        cout << "4. Показать всех абонентов" << endl;
        cout << "5. Сохранить информацию в файл" << endl;
        cout << "6. Загрузить информацию из файла" << endl;
        cout << "7. Выход" << endl;
        cout << "Выберите пункт меню: ";

        int choice;
        cin >> choice;

        cout << "\n";

        cin.ignore();

        switch (choice) {
        case 1:
            contacts[numContacts].addContact();
            numContacts++;
            break;
        case 2:
            cout << "Введите ФИО для удаления: ";
            char searchName[nameLength];
            cin.getline(searchName, nameLength);

            for (int i = 0; i < numContacts; i++) {
                if (contacts[i].searchContact(searchName)) {
                    contacts[i].deleteContact();

                    // Сдвигаем остальные контакты на одну позицию влево
                    for (int j = i; j < numContacts - 1; j++) {
                        contacts[j] = contacts[j + 1];
                    }

                    numContacts--;
                    break;
                }
            }
            break;
        case 3:
            cout << "Введите ФИО для поиска: ";
            cin.getline(searchName, nameLength);

            for (int i = 0; i < numContacts; i++) {
                if (contacts[i].searchContact(searchName)) {
                    contacts[i].displayContact();
                    break;
                }
            }
            break;
        case 4:
            for (int i = 0; i < numContacts; i++) {
                contacts[i].displayContact();
                cout << endl;
            }
            break;
        case 5:
        {
            ofstream file("contacts.dat", ios::binary);
            if (file.is_open()) {
                file.write(reinterpret_cast<char*>(&numContacts), sizeof(int));
                for (int i = 0; i < numContacts; i++) {
                    contacts[i].saveContact(file);
                }
                file.close();
                cout << "Информация сохранена в файл." << endl;
            }
            else {
                cout << "Ошибка открытия файла." << endl;
            }
        }
        break;
        case 6:
        {
            ifstream file("contacts.dat", ios::binary);
            if (file.is_open()) {
                file.read(reinterpret_cast<char*>(&numContacts), sizeof(int));
                for (int i = 0; i < numContacts; i++) {
                    contacts[i].loadContact(file);
                }
                file.close();
                cout << "Информация загружена из файла." << endl;
            }
            else {
                cout << "Ошибка открытия файла." << endl;
            }
        }
        break;
        case 7:
            return 0;
        default:
            cout << "Неверный выбор. Попробуйте еще раз." << endl;
            break;
        }
    }

    return 0;
}

