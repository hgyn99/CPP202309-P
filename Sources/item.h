#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;

// Item Ŭ����: ��ǰ ������ �����Ѵ�.
class Item {
public:
    string name;  // ��ǰ �̸�
    int totalQuantity;  // ��ǰ�� �� ����
    int availableQuantity;  // ���� �뿩 ������ ��ǰ ����

    Item(string n, int q);  // ������1
    Item(string n, int totalQ, int availableQ);  // ������2
};

#endif
