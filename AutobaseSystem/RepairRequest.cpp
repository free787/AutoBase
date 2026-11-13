#include "RepairRequest.h"

#include <iostream>

using namespace std;

RepairRequest::RepairRequest(string plate) : plate_(plate) {
    cout << "[RepairRequest] Заявку створено\n";
}

// Лаб 5, п. 3: невіртуальний деструктор
RepairRequest::~RepairRequest() {
    cout << "[RepairRequest] Деструктор\n";
}

// Лаб 5, п. 4: віртуальна функція
void RepairRequest::Describe() const {
    cout << "Заявка на ремонт авто " << plate_ << "\n";
}

UrgentRepairRequest::UrgentRepairRequest(string plate, int parts_count)
    : RepairRequest(plate), parts_count_(parts_count) {
    parts_ = new int[parts_count_];
    for (int i = 0; i < parts_count_; i++) {
        parts_[i] = 100 + i;
    }
    cout << "[UrgentRepairRequest] Виділено пам'ять під " << parts_count_
        << " запчастин\n";
}

// Цей деструктор звільняє пам'ять, але при delete через RepairRequest*
// він не викличеться
UrgentRepairRequest::~UrgentRepairRequest() {
    delete[] parts_;
    cout << "[UrgentRepairRequest] Деструктор: пам'ять звільнено\n";
}

// Лаб 5, п. 4: перевизначена віртуальна функція
void UrgentRepairRequest::Describe() const {
    cout << "ТЕРМІНОВА заявка на ремонт авто " << plate_ << ", запчастин: "
        << parts_count_ << "\n";
}