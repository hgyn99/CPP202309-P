#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Item {
public:
    string name;
    int totalQuantity;
    int availableQuantity;

    Item(string n, int q) : name(n), totalQuantity(q), availableQuantity(q) {}
};

class Renter {
public:
    string department;
    string studentID;
    string studentName;
    string itemName;

    Renter(string dept, string id, string name, string item) {
        department = dept;
        studentID = id;
        studentName = name;
        itemName = item;
    }

};

vector<Item> items;
vector<Renter> renters;

void addItem() {
    string name;
    int quantity;

    cout << "\n[��ǰ �߰�]\n";
    cout << "��ǰ �̸�: ";
    cin >> name;
    cout << "��ǰ ����: ";
    cin >> quantity;

    items.push_back(Item(name, quantity));
}

void rentItem() {
    string department, studentID, studentName, itemName;

    cout << "\n[��ǰ �뿩]\n";
    cout << "�а�: ";
    cin >> department;
    cout << "�й�: ";
    cin >> studentID;
    cout << "�̸�: ";
    cin >> studentName;
    cout << "�뿩�Ϸ��� ��ǰ �̸�: ";
    cin >> itemName;


    for (auto& item : items) {
        if (item.name == itemName && item.availableQuantity > 0) {
            item.availableQuantity--;
            renters.push_back(Renter(department, studentID, studentName, itemName));
            cout << "�뿩 �Ϸ�!" << endl;
            return;
        }
    }

    cout << "�ش� ��ǰ�� �뿩�� �� �����ϴ�." << endl;
}

void returnItem() {
    string studentID, itemName;

    cout << "\n[��ǰ �ݳ�]\n";
    cout << "�й�: ";
    cin >> studentID;
    cout << "�ݳ��Ϸ��� ��ǰ �̸�: ";
    cin >> itemName;

    for (size_t i = 0; i < renters.size(); ++i) {
        if (renters[i].studentID == studentID && renters[i].itemName == itemName) {
            for (auto& item : items) {
                if (item.name == itemName) {
                    item.availableQuantity++;
                    cout << "�ݳ� �Ϸ�!" << endl;
                    renters.erase(renters.begin() + i);
                    return;
                }
            }
        }
    }
    cout << "�ݳ��� ��ǰ�� ã�� �� �����ϴ�." << endl;
}

int main() {
    while (true) {
        cout << "\n��ǰ ���� ���α׷�" << endl;
        cout << "1. ��ǰ �߰�" << endl;
        cout << "2. ��ǰ �뿩" << endl;
        cout << "3. ��ǰ �ݳ�" << endl;
        cout << "0. ����" << endl;
        cout << "����: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: addItem(); break;
        case 2: rentItem(); break;
        case 3: returnItem(); break;
        case 0: return 0;
        default: cout << "�߸��� �����Դϴ�." << endl;
        }
    }

    return 0;
}
