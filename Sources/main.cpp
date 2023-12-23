#include "ItemManager.h"
#include <iostream>

using namespace std;

int main() {
    bool isAuthenticated = false;  // ������ ���� ���θ� �����ϴ� �÷���

    // ���� ���� �� ������ ����
    while (!isAuthenticated) {
        isAuthenticated = authenticateAdmin();
        if (!isAuthenticated) {
            cout << "���� ����: �ùٸ� ��й�ȣ�� �Է��ϼ���." << endl;
        }
        else {
            cout << "���� �Ϸ�. �ý��ۿ� �����մϴ�." << endl;
            break;
        }
    }

    // ���� �޴�
    while (true) {
        cout << "\n��ǰ ���� ���α׷�" << endl;
        cout << "1. ��ǰ ����" << endl;
        cout << "2. ��ǰ �뿩" << endl;
        cout << "3. ��ǰ �ݳ�" << endl;
        cout << "4. ��� ��ǰ ����Ʈ ����" << endl;
        cout << "5. �뿩 ���� ��ǰ ����Ʈ ����" << endl;
        cout << "6. ���Ͽ� ������ �����ϱ�" << endl;
        cout << "7. ���Ͽ��� ������ �ҷ�����" << endl;
        cout << "0. ����" << endl;
        cout << "����: ";

        // ������� ����
        int choice;
        cin >> choice;

        // ���ÿ� ���� ��� ����
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
            cout << "�����͸� �ҷ��Խ��ϴ�." << endl;
            break;
        case 0: // �����͸� �ڵ� �����ϰ� ����
            saveItemsToFile();
            saveRentersToFile();
            return 0;
        default: cout << "�߸��� �����Դϴ�." << endl;
        }
    }

    return 0;
}
