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
        cout << "������� ���: ";
        cin.getline(name, nameLength);

        cout << "������� �������� �������: ";
        cin.getline(homeNum, 20);

        cout << "������� ������� �������: ";
        cin.getline(workNum, 20);

        cout << "������� ��������� �������: ";
        cin.getline(mobileNum, 20);

        cout << "������� �������������� ���������� � ��������: ";
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
        cout << "���: " << name << endl;
        cout << "�������� �������: " << homeNum << endl;
        cout << "������� �������: " << workNum << endl;
        cout << "��������� �������: " << mobileNum << endl;
        cout << "�������������� ����������: " << addlInfo << endl;
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
        cout << "����:" << endl;
        cout << "1. �������� ��������" << endl;
        cout << "2. ������� ��������" << endl;
        cout << "3. ����� �������� �� ���" << endl;
        cout << "4. �������� ���� ���������" << endl;
        cout << "5. ��������� ���������� � ����" << endl;
        cout << "6. ��������� ���������� �� �����" << endl;
        cout << "7. �����" << endl;
        cout << "�������� ����� ����: ";

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
            cout << "������� ��� ��� ��������: ";
            char searchName[nameLength];
            cin.getline(searchName, nameLength);

            for (int i = 0; i < numContacts; i++) {
                if (contacts[i].searchContact(searchName)) {
                    contacts[i].deleteContact();

                    // �������� ��������� �������� �� ���� ������� �����
                    for (int j = i; j < numContacts - 1; j++) {
                        contacts[j] = contacts[j + 1];
                    }

                    numContacts--;
                    break;
                }
            }
            break;
        case 3:
            cout << "������� ��� ��� ������: ";
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
                cout << "���������� ��������� � ����." << endl;
            }
            else {
                cout << "������ �������� �����." << endl;
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
                cout << "���������� ��������� �� �����." << endl;
            }
            else {
                cout << "������ �������� �����." << endl;
            }
        }
        break;
        case 7:
            return 0;
        default:
            cout << "�������� �����. ���������� ��� ���." << endl;
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
        cout << "������� ���: ";
        cin.getline(name, NameLength);

        cout << "������� �������� �����: ";
        cin.getline(homePhone, 20);

        cout << "������� ������� �����: ";
        cin.getline(workPhone, 20);

        cout << "������� ����� ���������� ��������: ";
        cin.getline(mobilePhone, 20);

        cout << "������� ���. ����������: ";
        cin.getline(additionalInfo, 100);
    }

    void displayContact() {
        cout << "���: " << name << endl;
        cout << "�������� �������: " << homePhone << endl;
        cout << "������� �������: " << workPhone << endl;
        cout << "��������� �������: " << mobilePhone << endl;
        cout << "���. ���� �� ��������: " << additionalInfo << endl;
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
        cout << "��� ������ ��������" << endl;
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
        cout << "��������� � ����" << endl;
    }
    else {
        cout << "��� ������ �����" << endl;
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
        cout << "��������� �� �����" << endl;
    }
    else {
        cout << "��� ������ �����" << endl;
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
        cout << "���������� �����: " << endl;
        cout << "1. �������� ��������" << endl;
        cout << "2. ������� ��������" << endl;
        cout << "3. ������ �������� �� ���" << endl;
        cout << "4. �������� ���� ���������" << endl;
        cout << "5. ��������� ���������� � ����" << endl;
        cout << "6. ��������� ���������� �� �����" << endl;
        cout << "9. �����" << endl;
        cout << "������� �����: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addContact(contacts, numContacts);
            break;
        case 2:
            cout << "������� ��� ��� ��������: ";
            cin.ignore();
            cin.getline(searchTerm, NameLength);
            deleteContact(contacts, numContacts, searchTerm);
            break;
        case 3:
            cout << "������� ��� ��� ������: ";
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
            cout << "����� ������" << endl;
            break;
        default:
            cout << "������ �������� ���" << endl;
            break;
        }

        cout << endl;
    } while (choice != 0);

    return 0;
}

*/