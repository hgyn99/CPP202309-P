#include "Item.h"

// ������1
Item::Item(string n, int q) : name(n), totalQuantity(q), availableQuantity(q) {}

// ������2
Item::Item(string n, int totalQ, int availableQ) : name(n), totalQuantity(totalQ), availableQuantity(availableQ) {}
