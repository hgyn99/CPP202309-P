#include "ItemManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>

using namespace std;
using namespace chrono;

// 전역 변수 정의
vector<Item> items;  // 모든 물품을 저장하는 벡터
vector<Renter> renters;  // 모든 대여자를 저장하는 벡터
vector<Renter> penalizedRenters;  // 연체자를 저장하는 벡터

// 관리자 인증 함수
bool authenticateAdmin() {
    string password;
    cout << "관리자 비밀번호를 입력하세요: ";
    cin >> password;

    const string adminPassword = "admin123";  // 정적 비밀번호 생성
    return password == adminPassword;
}

// 물품을 추가하는 함수
void addItem() {
    string name;
    int quantity;

    cout << "\n[물품 추가]\n";
    cout << "물품 이름: ";
    cin >> name;

    // 같은 이름의 물품이 있는지 검사
    for (const auto& item : items) {
        if (item.name == name) {
            cout << "오류: 이미 같은 이름의 물품이 있습니다." << endl;
            return; // 함수 종료
        }
    }

    cout << "물품 수량: ";
    cin >> quantity;

    // 수량이 0인지 검사
    if (quantity <= 0) {
        cout << "오류: 물품 수량은 0보다 커야 합니다." << endl;
        return; // 함수 종료
    }

    // 같은 이름의 물품이 없고 수량이 0보다 크면 추가
    items.push_back(Item(name, quantity));
    cout << "물품이 추가되었습니다." << endl;
}

// 물품 수량을 수정하는 함수
void modifyItem() {
    string name;
    int newQuantity;

    cout << "\n[물품 수정]\n";
    // 현재 물품 리스트 출력
    viewItems();
    cout << endl;
    cout << "수정할 물품 이름: ";
    cin >> name;

    for (auto& item : items) {
        if (item.name == name) {
            cout << "현재 총 수량: " << item.totalQuantity << ", 현재 남은 수량: " << item.availableQuantity << endl;
            cout << "새로운 총 수량 (대여 중인 수량을 포함): ";
            cin >> newQuantity;

            if (newQuantity < item.totalQuantity - item.availableQuantity) {
                cout << "오류: 새로운 총 수량은 현재 대여 중인 수량보다 작을 수 없습니다." << endl;
                return;
            }

            // 남은 수량을 조정한다.
            item.availableQuantity = newQuantity - (item.totalQuantity - item.availableQuantity);
            item.totalQuantity = newQuantity;

            cout << "물품 정보가 수정되었습니다." << endl;
            return;
        }
    }

    cout << "해당 이름의 물품을 찾을 수 없습니다." << endl;
}

// 물품을 삭제하는 함수
void deleteItem() {
    string name;
    cout << "\n[물품 삭제]\n";
    // 현재 물품 리스트 출력
    viewItems();
    cout << endl;
    cout << "삭제할 물품 이름: ";
    cin >> name;

    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->name == name) {
            items.erase(it);
            cout << "물품이 삭제되었습니다." << endl;
            return;
        }
    }

    cout << "해당 이름의 물품을 찾을 수 없습니다." << endl;
}


// 물품을 관리(추가, 수정, 삭제)하는 함수
void manageItems() {
    int choice;
    while (true) {
        cout << "\n[물품 관리]" << endl;
        cout << "1. 물품 추가" << endl;
        cout << "2. 물품 수정" << endl;
        cout << "3. 물품 삭제" << endl;
        cout << "0. 메인 메뉴로 돌아가기" << endl;
        cout << "선택: ";
        cin >> choice;

        switch (choice) {
        case 1: addItem(); break;
        case 2: modifyItem(); break;
        case 3: deleteItem(); break;
        case 0: return;
        default: cout << "잘못된 선택입니다." << endl;
        }
    }
}



// 물품을 대여하는 함수
void rentItem() {
    string department, studentID, studentName, itemName;

    cout << "\n[물품 대여]\n";
    cout << "학과: ";
    cin >> department;
    cout << "학번: ";
    cin >> studentID;
    cout << "이름: ";
    cin >> studentName;
    // 대여자의 편의를 위한 현재 물품 리스트 출력
    viewItems();
    cout << endl;
    cout << "대여하려는 물품 이름: ";
    cin >> itemName;

    bool itemFound = false;
    for (auto& item : items) {
        if (item.name == itemName) {
            itemFound = true;
            if (item.availableQuantity > 0) {
                item.availableQuantity--;

                auto now = system_clock::now();
                auto due = now + hours(48); // 반납 예정 시간을 48시간 후로 설정
                // auto due = now + seconds(30); // 반납 예정 시간 작동 테스트용 코드(30초로 설정)

                // 시간 출력을 위한 코드
                time_t dueTime_t = system_clock::to_time_t(due);
                struct tm dueTm;
                localtime_s(&dueTm, &dueTime_t);

                // 대여자가 연체 패널티를 받은 경우 대여 해주지 않음
                for (auto& renter : penalizedRenters) {
                    // 시간 출력을 위한 코드
                    time_t penaltyEndTime_t = system_clock::to_time_t(renter.penaltyEnd);
                    struct tm penaltyEndTm;
                    localtime_s(&penaltyEndTm, &penaltyEndTime_t);

                    if (renter.studentID == studentID && now < renter.penaltyEnd) {
                        cout << "연체로 인해 대여가 금지되었습니다." << endl;
                        cout << "대여 가능 시간: " << put_time(&penaltyEndTm, "%Y-%m-%d %H:%M:%S") << endl;
                        return;
                    }
                }

                renters.push_back(Renter(department, studentID, studentName, itemName, now, due));
                cout << "대여 완료! 반납 예정 시간: " << put_time(&dueTm, "%Y-%m-%d %H:%M:%S") << endl;
                return;
            }
            else {
                cout << "죄송합니다. 현재 해당 물품은 대여할 수 없습니다. (재고 부족)" << endl;
                return;
            }
        }
    }

    if (!itemFound) {
        cout << "해당 물품을 찾을 수 없습니다." << endl;
    }
}

// 물품을 반납하는 함수
void returnItem() {
    string studentID, itemName;

    cout << "\n[물품 반납]\n";
    cout << "학번: ";
    cin >> studentID;
    cout << "반납하려는 물품 이름: ";
    cin >> itemName;

    auto now = system_clock::now(); // 반납 시각 저장

    // 대여자 목록에서 해당 대여자 찾기
    for (size_t i = 0; i < renters.size(); ++i) {
        if (renters[i].studentID == studentID && renters[i].itemName == itemName) {
            if (now > renters[i].dueTime) {
                cout << "물품 반납이 연체되어 7일간 대여가 금지됩니다." << endl;
                renters[i].isPenalized = true;
                renters[i].penaltyEnd = now + hours(168);  // 현재로부터 7일 후

                // 시간 출력을 위한 코드
                time_t penaltyEndTime_t = system_clock::to_time_t(renters[i].penaltyEnd);
                struct tm penaltyEndTm;
                localtime_s(&penaltyEndTm, &penaltyEndTime_t);

                cout << "대여 가능 시간: " << put_time(&penaltyEndTm, "%Y-%m-%d %H:%M:%S") << endl;
                penalizedRenters.push_back(renters[i]);  // 연체자 목록에 추가
            }

            for (auto& item : items) {
                if (item.name == itemName) {
                    item.availableQuantity++;
                    cout << "반납 완료!" << endl;
                }
            }

            renters.erase(renters.begin() + i);  // 대여자 목록에서 제거
            return;
        }
    }
    cout << "반납할 물품을 찾을 수 없습니다." << endl;
}

// 모든 물품의 목록을 보여주는 함수
void viewItems() {
    cout << "\n[모든 물품 리스트]\n";
    for (const auto& item : items) {
        cout << item.name << " - 총 수량: " << item.totalQuantity << ", 남은 수량: " << item.availableQuantity
            << ", 대여 중: " << item.totalQuantity - item.availableQuantity << endl;
    }
}

// 현재 대여 중인 물품과 대여자 정보를 보여주는 함수
void viewRenters() {
    cout << "\n[대여 중인 물품 리스트]\n";
    for (const auto& renter : renters) {
        time_t rentedTime_t = system_clock::to_time_t(renter.rentedTime);
        struct tm rentedTm;
        localtime_s(&rentedTm, &rentedTime_t);

        time_t dueTime_t = system_clock::to_time_t(renter.dueTime);
        struct tm dueTm;
        localtime_s(&dueTm, &dueTime_t);

        cout << "학과: " << renter.department
            << ", 학번: " << renter.studentID
            << ", 이름: " << renter.studentName
            << ", 대여 물품: " << renter.itemName << endl;
        cout << "대여 시간: " << put_time(&rentedTm, "%Y-%m-%d %H:%M:%S")
            << ", 반납 예정 시간: " << put_time(&dueTm, "%Y-%m-%d %H:%M:%S") << endl;
    }
}

// 물품 리스트를 파일에 저장하는 함수
void saveItemsToFile() {
    ofstream outFile("items.txt");
    for (const auto& item : items) {
        outFile << item.name << "," << item.totalQuantity << "," << item.availableQuantity << "\n";
    }
    outFile.close();
    cout << "물품 리스트가 저장되었습니다." << endl;
}

// 대여자 리스트를 파일에 저장하는 함수
void saveRentersToFile() {
    ofstream outFile("renters.txt");
    for (const auto& renter : renters) {
        outFile << renter.department << "," << renter.studentID << "," << renter.studentName << ","
            // 시간 데이터를 저장하기 위한 코드
            << renter.itemName << "," << duration_cast<seconds>(renter.rentedTime.time_since_epoch()).count() << ","
            << duration_cast<seconds>(renter.dueTime.time_since_epoch()).count() << "\n";
    }
    outFile.close();
    cout << "대여자 리스트가 저장되었습니다." << endl;
}


// 물품 리스트를 파일에서 불러오는 함수
void loadItemsFromFile() {
    ifstream inFile("items.txt");
    if (!inFile.is_open()) {
        cerr << "파일을 열 수 없습니다." << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string name, totalStr, availableStr;
        getline(ss, name, ',');
        getline(ss, totalStr, ',');
        getline(ss, availableStr);
        int total = stoi(totalStr);
        int available = stoi(availableStr);
        items.push_back(Item(name, total, available));
    }

    inFile.close();
}

// 대여자 리스트를 파일에서 불러오는 함수
void loadRentersFromFile() {
    ifstream inFile("renters.txt");
    if (!inFile.is_open()) {
        cerr << "파일을 열 수 없습니다." << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string dept, id, name, itemName, rentedSecStr, dueSecStr;
        getline(ss, dept, ',');
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, itemName, ',');
        getline(ss, rentedSecStr, ',');
        getline(ss, dueSecStr);
        long long rentedSec = stoll(rentedSecStr);
        long long dueSec = stoll(dueSecStr);
        time_point<system_clock> rented = system_clock::from_time_t(rentedSec);
        time_point<system_clock> due = system_clock::from_time_t(dueSec);
        renters.push_back(Renter(dept, id, name, itemName, rented, due));
    }

    inFile.close();
}