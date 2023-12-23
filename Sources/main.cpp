#include "ItemManager.h"
#include <iostream>

using namespace std;

int main() {
    bool isAuthenticated = false;  // 관리자 인증 여부를 저장하는 플래그

    // 최초 접속 시 관리자 인증
    while (!isAuthenticated) {
        isAuthenticated = authenticateAdmin();
        if (!isAuthenticated) {
            cout << "인증 실패: 올바른 비밀번호를 입력하세요." << endl;
        }
        else {
            cout << "인증 완료. 시스템에 접속합니다." << endl;
            break;
        }
    }

    // 메인 메뉴
    while (true) {
        cout << "\n물품 관리 프로그램" << endl;
        cout << "1. 물품 관리" << endl;
        cout << "2. 물품 대여" << endl;
        cout << "3. 물품 반납" << endl;
        cout << "4. 모든 물품 리스트 보기" << endl;
        cout << "5. 대여 중인 물품 리스트 보기" << endl;
        cout << "6. 파일에 데이터 저장하기" << endl;
        cout << "7. 파일에서 데이터 불러오기" << endl;
        cout << "0. 종료" << endl;
        cout << "선택: ";

        // 사용자의 선택
        int choice;
        cin >> choice;

        // 선택에 따른 기능 실행
        switch (choice) {
        case 1: manageItems(); break;
        case 2: rentItem(); break;
        case 3: returnItem(); break;
        case 4: viewItems(); break;
        case 5: viewRenters(); break;
        case 6:
            saveItemsToFile();
            saveRentersToFile();
            break;
        case 7:
            loadItemsFromFile();
            loadRentersFromFile();
            cout << "데이터를 불러왔습니다." << endl;
            break;
        case 0: // 데이터를 자동 저장하고 종료
            saveItemsToFile();
            saveRentersToFile();
            return 0;
        default: cout << "잘못된 선택입니다." << endl;
        }
    }

    return 0;
}
