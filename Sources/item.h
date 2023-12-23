#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;

// Item 클래스: 물품 정보를 저장한다.
class Item {
public:
    string name;  // 물품 이름
    int totalQuantity;  // 물품의 총 수량
    int availableQuantity;  // 현재 대여 가능한 물품 수량

    Item(string n, int q);  // 생성자1
    Item(string n, int totalQ, int availableQ);  // 생성자2
};

#endif
