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

    cout << "\n[물품 추가]\n";
    cout << "물품 이름: ";
    cin >> name;
    cout << "물품 수량: ";
    cin >> quantity;

    items.push_back(Item(name, quantity));
}

void rentItem() {
    string department, studentID, studentName, itemName;

    cout << "\n[물품 대여]\n";
    cout << "학과: ";
    cin >> department;
    cout << "학번: ";
    cin >> studentID;
    cout << "이름: ";
    cin >> studentName;
    cout << "대여하려는 물품 이름: ";
    cin >> itemName;


    for (auto& item : items) {
        if (item.name == itemName && item.availableQuantity > 0) {
            item.availableQuantity--;
            renters.push_back(Renter(department, studentID, studentName, itemName));
            cout << "대여 완료!" << endl;
            return;
        }
    }

    cout << "해당 물품은 대여할 수 없습니다." << endl;
}

void returnItem() {
    string studentID, itemName;

    cout << "\n[물품 반납]\n";
    cout << "학번: ";
    cin >> studentID;
    cout << "반납하려는 물품 이름: ";
    cin >> itemName;

    for (size_t i = 0; i < renters.size(); ++i) {
        if (renters[i].studentID == studentID && renters[i].itemName == itemName) {
            for (auto& item : items) {
                if (item.name == itemName) {
                    item.availableQuantity++;
                    cout << "반납 완료!" << endl;
                    renters.erase(renters.begin() + i);
                    return;
                }
            }
        }
    }
    cout << "반납할 물품을 찾을 수 없습니다." << endl;
}


void viewItems() {
    cout << "\n[모든 물품 리스트]\n";
    for (const auto& item : items) {
        cout << item.name << " - 총 수량: " << item.totalQuantity << ", 남은 수량: " << item.availableQuantity << ", 대여 중: " << item.totalQuantity - item.availableQuantity << endl;
    }
}

void viewRenters() {
    cout << "\n[대여 중인 물품 리스트]\n";
    for (const auto& renter : renters) {
        cout << "학과: " << renter.department << ", 학번: " << renter.studentID << ", 이름: " << renter.studentName << ", 대여 물품: " << renter.itemName << endl;
    }
}

int main() {
    while (true) {
        cout << "\n물품 관리 프로그램" << endl;
        cout << "1. 물품 추가" << endl;
        cout << "2. 물품 대여" << endl;
        cout << "3. 물품 반납" << endl;
        cout << "4. 모든 물품 리스트 보기" << endl;
        cout << "5. 대여 중인 물품 리스트 보기" << endl;
        cout << "0. 종료" << endl;
        cout << "선택: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: addItem(); break;
        case 2: rentItem(); break;
        case 3: returnItem(); break;
        case 4: viewItems(); break;
        case 5: viewRenters(); break;
        case 0: return 0;
        default: cout << "잘못된 선택입니다." << endl;
        }
    }

    return 0;
}
