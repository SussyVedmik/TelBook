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









/*#include <iostream>
#include <fstream>
using namespace std;

const int NameLength = 100;

class Contact {
private:
    char name[NameLength];
    char homePhone[20];
    char workPhone[20];
    char mobilePhone[20];
    char additionalInfo[100];

public:
    void addContact() {
        cout << "Введите имя: ";
        cin.getline(name, NameLength);

        cout << "Введите домашний номер: ";
        cin.getline(homePhone, 20);

        cout << "Введите рабочий номер: ";
        cin.getline(workPhone, 20);

        cout << "Введите номер мобильного телефона: ";
        cin.getline(mobilePhone, 20);

        cout << "Введите доп. информацию: ";
        cin.getline(additionalInfo, 100);
    }

    void displayContact() {
        cout << "Имя: " << name << endl;
        cout << "Домашний телефон: " << homePhone << endl;
        cout << "Рабочий телефон: " << workPhone << endl;
        cout << "Мобильный телефон: " << mobilePhone << endl;
        cout << "Доп. инфо об абоненте: " << additionalInfo << endl;
    }

    bool searchContact(const char* searchTerm) {
        return strcmp(name, searchTerm) == 0;
    }

    void saveToFile(ofstream& file) {
        file.write(name, NameLength);
        file.write(homePhone, 20);
        file.write(workPhone, 20);
        file.write(mobilePhone, 20);
        file.write(additionalInfo, 100);
    }

    void loadFromFile(ifstream& file) {
        file.read(name, NameLength);
        file.read(homePhone, 20);
        file.read(workPhone, 20);
        file.read(mobilePhone, 20);
        file.read(additionalInfo, 100);
    }
};

void addContact(Contact* contacts, int& numContacts) {
    Contact newContact;
    newContact.addContact();
    contacts[numContacts] = newContact;
    numContacts++;
}

void deleteContact(Contact* contacts, int& numContacts, const char* searchTerm) {
    for (int i = 0; i < numContacts; i++) {
        if (contacts[i].searchContact(searchTerm)) {
            for (int j = i; j < numContacts - 1; j++) {
                contacts[j] = contacts[j + 1];
            }
            numContacts--;
            break;
        }
    }
}

void searchContact(Contact* contacts, int numContacts, const char* searchTerm) {
    bool found = false;
    for (int i = 0; i < numContacts; i++) {
        if (contacts[i].searchContact(searchTerm)) {
            contacts[i].displayContact();
            found = true;
        }
    }
    if (!found) {
        cout << "Нет такого абонента" << endl;
    }
}

void displayAllContacts(Contact* contacts, int numContacts) {
    for (int i = 0; i < numContacts; i++) {
        contacts[i].displayContact();
        cout << endl;
    }
}

void saveContactsToFile(Contact* contacts, int numContacts) {
    ofstream file("contacts.dat", ios::binary);
    if (file.is_open()) {
        for (int i = 0; i < numContacts; i++) {
            contacts[i].saveToFile(file);
        }
        file.close();
        cout << "Сохранено в файл" << endl;
    }
    else {
        cout << "Нет такого файла" << endl;
    }
}

void loadContactsFromFile(Contact* contacts, int& numContacts) {
    ifstream file("contacts.dat", ios::binary);
    if (file.is_open()) {
        while (!file.eof()) {
            Contact newContact;
            newContact.loadFromFile(file);
            contacts[numContacts] = newContact;
            numContacts++;
        }
        file.close();
        cout << "Загружено из файла" << endl;
    }
    else {
        cout << "Нет такого файла" << endl;
    }
}

int main() {

    setlocale(LC_ALL, "Russian");

    const int MAX_CONTACTS = 100;
    Contact contacts[MAX_CONTACTS];
    int numContacts = 0;

    int choice;
    char searchTerm[NameLength];

    do {
        cout << "Телефонная книга: " << endl;
        cout << "1. Добавить абонента" << endl;
        cout << "2. Удалить абонента" << endl;
        cout << "3. Искать абонента по ФИО" << endl;
        cout << "4. Показать всех абонентов" << endl;
        cout << "5. Сохранить информацию в файл" << endl;
        cout << "6. Загрузить информацию из файла" << endl;
        cout << "9. Выход" << endl;
        cout << "Введите опцию: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addContact(contacts, numContacts);
            break;
        case 2:
            cout << "Введите имя для удаления: ";
            cin.ignore();
            cin.getline(searchTerm, NameLength);
            deleteContact(contacts, numContacts, searchTerm);
            break;
        case 3:
            cout << "Введите имя для поиска: ";
            cin.ignore();
            cin.getline(searchTerm, NameLength);
            searchContact(contacts, numContacts, searchTerm);
            break;
        case 4:
            displayAllContacts(contacts, numContacts);
            break;
        case 5:
            saveContactsToFile(contacts, numContacts);
            break;
        case 6:
            loadContactsFromFile(contacts, numContacts);
            break;
        case 9:
            cout << "Конец работы" << endl;
            break;
        default:
            cout << "Такого варианта нет" << endl;
            break;
        }

        cout << endl;
    } while (choice != 0);

    return 0;
}

*/