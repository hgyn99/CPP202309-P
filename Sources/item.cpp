#include "Item.h"

// 持失切1
Item::Item(string n, int q) : name(n), totalQuantity(q), availableQuantity(q) {}

// 持失切2
Item::Item(string n, int totalQ, int availableQ) : name(n), totalQuantity(totalQ), availableQuantity(availableQ) {}
