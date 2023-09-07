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

