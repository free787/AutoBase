#include "Management.h"
#include <iostream>

using namespace std;

Dispatcher::Dispatcher(string name) : name_(name), car_count_(0) {}

void Dispatcher::AssignCarToFleet(Car* car) {
    if (car_count_ < 10) {
        fleet_[car_count_++] = car;
        cout << "Диспетчер " << name_ << " додав авто " << car->GetBrand() << " до списку.\n";
    }
}

TripAssignment::TripAssignment(Dispatcher* disp, Driver* drv, Car* car)
    : dispatcher_(disp), driver_(drv), car_(car) {}

void TripAssignment::PrintAssignmentInfo() const {
    cout << "--- ЗАЯВКА (Асоціація) ---\n"
        << "Диспетчер: " << dispatcher_->GetName() << "\n"
        << "Призначив водія: " << driver_->GetName() << "\n"
        << "На авто: " << car_->GetBrand() << "\n--------------------------\n";
}