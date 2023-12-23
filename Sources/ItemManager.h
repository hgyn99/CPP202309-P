#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include "Item.h"
#include "Renter.h"
#include <vector>

// 각 기능을 구현하는 함수 선언
bool authenticateAdmin();
void viewItems();
void addItem();
void modifyItem();
void deleteItem();
void manageItems();
void rentItem();
void returnItem();
void viewRenters();
void saveItemsToFile();
void saveRentersToFile();
void loadItemsFromFile();
void loadRentersFromFile();

// 기능 구현에 필요한 벡터 선언
extern vector<Item> items;
extern vector<Renter> renters;
extern vector<Renter> penalizedRenters;

#endif
