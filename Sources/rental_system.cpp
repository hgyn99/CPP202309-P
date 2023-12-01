#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

// Item 클래스: 물품 정보를 저장한다.
class Item {
public:
    string name;  // 물품 이름
    int totalQuantity;  // 물품의 총 수량
    int availableQuantity;  // 현재 대여 가능한 물품 수량

    // 생성자: 물품 이름과 수량을 초기화한다.
    Item(string n, int q) : name(n), totalQuantity(q), availableQuantity(q) {}
};

// Renter 클래스: 대여자 정보를 저장한다.
class Renter {
public:
    string department;  // 대여자의 학과
    string studentID;  // 대여자의 학번
    string studentName;  // 대여자의 이름
    string itemName;  // 대여한 물품 이름
    system_clock::time_point rentedTime;  // 대여한 시간
    system_clock::time_point dueTime;  // 반납 예정 시간
    bool isPenalized;  // 연체로 인한 패널티 여부
    system_clock::time_point penaltyEnd;  // 패널티 종료 시간


    // 생성자: 대여자 정보와 대여 시간, 반납 예정 시간을 초기화한다.
    Renter(string dept, string id, string name, string item, system_clock::time_point rented, system_clock::time_point due)
        : department(dept), studentID(id), studentName(name), itemName(item), rentedTime(rented), dueTime(due) {}
};


vector<Item> items;  // 모든 물품을 저장하는 벡터
vector<Renter> renters;  // 모든 대여자를 저장하는 벡터
vector<Renter> penalizedRenters;  // 연체자를 저장하는 벡터

// 관리자 인증 함수
bool authenticateAdmin() {
    string password;
    cout << "접근을 위한 관리자 비밀번호를 입력하세요: ";
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
    cout << "물품 수량: ";
    cin >> quantity;

    items.push_back(Item(name, quantity));
}

// 물품 수량을 수정하는 함수
void modifyItem() {
    string name;
    int newQuantity;

    cout << "\n[물품 수정]\n";
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

// 메인 함수: 사용자 인터페이스와 프로그램의 메인 루프를 담당
int main() {
    while (true) {
        cout << "\n물품 관리 프로그램" << endl;
        cout << "1. 물품 관리" << endl;
        cout << "2. 물품 대여" << endl;
        cout << "3. 물품 반납" << endl;
        cout << "4. 모든 물품 리스트 보기" << endl;
        cout << "5. 대여 중인 물품 리스트 보기" << endl;
        cout << "0. 종료" << endl;
        cout << "선택: ";

        int choice;
        cin >> choice;

        switch (choice) {
            // 관리자 인증이 필요한 기능 영역
        case 1: 
        case 5:
            if (!authenticateAdmin()) {
                cout << "인증 실패: 접근 권한이 없습니다." << endl;
                break;
            }
              // 관리자 인증 성공 시, 해당 기능 수행
              if (choice == 1) manageItems();
              else if (choice == 5) viewRenters();
              break;
            // 관리자 인증이 필요하지 않는 기능 영역
        case 2: rentItem(); break;
        case 3: returnItem(); break;
        case 4: viewItems(); break;
        case 0: return 0;
        default: cout << "잘못된 선택입니다." << endl;
        }
    }

    return 0;
}