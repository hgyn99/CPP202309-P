#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

// Item Ŭ����: ��ǰ ������ �����Ѵ�.
class Item {
public:
    string name;  // ��ǰ �̸�
    int totalQuantity;  // ��ǰ�� �� ����
    int availableQuantity;  // ���� �뿩 ������ ��ǰ ����

    // ������: ��ǰ �̸��� ������ �ʱ�ȭ�Ѵ�.
    Item(string n, int q) : name(n), totalQuantity(q), availableQuantity(q) {}
};

// Renter Ŭ����: �뿩�� ������ �����Ѵ�.
class Renter {
public:
    string department;  // �뿩���� �а�
    string studentID;  // �뿩���� �й�
    string studentName;  // �뿩���� �̸�
    string itemName;  // �뿩�� ��ǰ �̸�
    system_clock::time_point rentedTime;  // �뿩�� �ð�
    system_clock::time_point dueTime;  // �ݳ� ���� �ð�

    // ������: �뿩�� ������ �뿩 �ð�, �ݳ� ���� �ð��� �ʱ�ȭ�Ѵ�.
    Renter(string dept, string id, string name, string item, system_clock::time_point rented, system_clock::time_point due)
        : department(dept), studentID(id), studentName(name), itemName(item), rentedTime(rented), dueTime(due) {}
};

vector<Item> items;  // ��� ��ǰ�� �����ϴ� ����
vector<Renter> renters;  // ��� �뿩�ڸ� �����ϴ� ����

// ��ǰ�� �߰��ϴ� �Լ�
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

// ��ǰ�� �뿩�ϴ� �Լ�
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

    bool itemFound = false;
    for (auto& item : items) {
        if (item.name == itemName) {
            itemFound = true;
            if (item.availableQuantity > 0) {
                item.availableQuantity--;

                auto now = system_clock::now();
                auto due = now + hours(48); // 48�ð� �ķ� ����

                time_t dueTime_t = system_clock::to_time_t(due);
                struct tm dueTm;
                localtime_s(&dueTm, &dueTime_t);

                renters.push_back(Renter(department, studentID, studentName, itemName, now, due));
                cout << "�뿩 �Ϸ�! �ݳ� ���� �ð�: " << put_time(&dueTm, "%Y-%m-%d %H:%M:%S") << endl;
                return;
            }
            else {
                cout << "�˼��մϴ�. ���� �ش� ��ǰ�� �뿩�� �� �����ϴ�. (��� ����)" << endl;
                return;
            }
        }
    }

    if (!itemFound) {
        cout << "�ش� ��ǰ�� ã�� �� �����ϴ�." << endl;
    }
}

// ��ǰ�� �ݳ��ϴ� �Լ�
void returnItem() {
    string studentID, itemName;

    cout << "\n[��ǰ �ݳ�]\n";
    cout << "�й�: ";
    cin >> studentID;
    cout << "�ݳ��Ϸ��� ��ǰ �̸�: ";
    cin >> itemName;

    // �뿩�� ��Ͽ��� �ش� �뿩�� ã��
    for (size_t i = 0; i < renters.size(); ++i) {
        if (renters[i].studentID == studentID && renters[i].itemName == itemName) {
            // �ش� ��ǰ�� ���� ����
            for (auto& item : items) {
                if (item.name == itemName) {
                    item.availableQuantity++;
                    cout << "�ݳ� �Ϸ�!" << endl;
                    renters.erase(renters.begin() + i);  // �뿩�� ��Ͽ��� ����
                    return;
                }
            }
        }
    }
    cout << "�ݳ��� ��ǰ�� ã�� �� �����ϴ�." << endl;
}

// ��� ��ǰ�� ����� �����ִ� �Լ�
void viewItems() {
    cout << "\n[��� ��ǰ ����Ʈ]\n";
    for (const auto& item : items) {
        cout << item.name << " - �� ����: " << item.totalQuantity << ", ���� ����: " << item.availableQuantity << ", �뿩 ��: " << item.totalQuantity - item.availableQuantity << endl;
    }
}

// ���� �뿩 ���� ��ǰ�� �뿩�� ������ �����ִ� �Լ�
void viewRenters() {
    cout << "\n[�뿩 ���� ��ǰ ����Ʈ]\n";
    for (const auto& renter : renters) {
        time_t rentedTime_t = system_clock::to_time_t(renter.rentedTime);
        struct tm rentedTm;
        localtime_s(&rentedTm, &rentedTime_t);

        time_t dueTime_t = system_clock::to_time_t(renter.dueTime);
        struct tm dueTm;
        localtime_s(&dueTm, &dueTime_t);

        cout << "�а�: " << renter.department
            << ", �й�: " << renter.studentID
            << ", �̸�: " << renter.studentName
            << ", �뿩 ��ǰ: " << renter.itemName << endl;
        cout << "�뿩 �ð�: " << put_time(&rentedTm, "%Y-%m-%d %H:%M:%S")
            << ", �ݳ� ���� �ð�: " << put_time(&dueTm, "%Y-%m-%d %H:%M:%S") << endl;
    }
}

// ���� �Լ�: ����� �������̽��� ���α׷��� ���� ������ ���
int main() {
    while (true) {
        cout << "\n��ǰ ���� ���α׷�" << endl;
        cout << "1. ��ǰ �߰�" << endl;
        cout << "2. ��ǰ �뿩" << endl;
        cout << "3. ��ǰ �ݳ�" << endl;
        cout << "4. ��� ��ǰ ����Ʈ ����" << endl;
        cout << "5. �뿩 ���� ��ǰ ����Ʈ ����" << endl;
        cout << "0. ����" << endl;
        cout << "����: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: addItem(); break;
        case 2: rentItem(); break;
        case 3: returnItem(); break;
        case 4: viewItems(); break;
        case 5: viewRenters(); break;
        case 0: return 0;
        default: cout << "�߸��� �����Դϴ�." << endl;
        }
    }

    return 0;
}
