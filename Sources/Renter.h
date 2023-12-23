#ifndef RENTER_H
#define RENTER_H

#include <string>
#include <chrono>

using namespace std;

// Renter Ŭ����: �뿩�� ������ �����Ѵ�.
class Renter {
public:
    string department;  // �뿩���� �а�
    string studentID;  // �뿩���� �й�
    string studentName;  // �뿩���� �̸�
    string itemName;  // �뿩�� ��ǰ �̸�
    chrono::system_clock::time_point rentedTime;  // �뿩�� �ð�
    chrono::system_clock::time_point dueTime;  // �ݳ� ���� �ð�
    bool isPenalized;  // ��ü�� ���� �г�Ƽ ����
    chrono::system_clock::time_point penaltyEnd;  // �г�Ƽ ���� �ð�

    Renter(string dept, string id, string name, string item, chrono::system_clock::time_point rented, chrono::system_clock::time_point due);  // ������
};

#endif
