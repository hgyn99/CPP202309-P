#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include "Item.h"
#include "Renter.h"
#include <vector>

// �� ����� �����ϴ� �Լ� ����
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

// ��� ������ �ʿ��� ���� ����
extern vector<Item> items;
extern vector<Renter> renters;
extern vector<Renter> penalizedRenters;

#endif
