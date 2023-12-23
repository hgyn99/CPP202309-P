#include "Renter.h"

// »ý¼ºÀÚ
Renter::Renter(string dept, string id, string name, string item, chrono::system_clock::time_point rented, chrono::system_clock::time_point due)
    : department(dept), studentID(id), studentName(name), itemName(item), rentedTime(rented), dueTime(due), isPenalized(false) {}
