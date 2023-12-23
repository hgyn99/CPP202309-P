#ifndef RENTER_H
#define RENTER_H

#include <string>
#include <chrono>

using namespace std;

// Renter 클래스: 대여자 정보를 저장한다.
class Renter {
public:
    string department;  // 대여자의 학과
    string studentID;  // 대여자의 학번
    string studentName;  // 대여자의 이름
    string itemName;  // 대여한 물품 이름
    chrono::system_clock::time_point rentedTime;  // 대여한 시간
    chrono::system_clock::time_point dueTime;  // 반납 예정 시간
    bool isPenalized;  // 연체로 인한 패널티 여부
    chrono::system_clock::time_point penaltyEnd;  // 패널티 종료 시간

    Renter(string dept, string id, string name, string item, chrono::system_clock::time_point rented, chrono::system_clock::time_point due);  // 생성자
};

#endif
