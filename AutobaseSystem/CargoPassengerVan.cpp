#include "CargoPassengerVan.h"

#include <stdexcept>

using namespace std;

CargoPassengerVan::CargoPassengerVan()
    : Vehicle(), Car(), Bus(), partition_(true) {
    max_load_ = 1200;
    seats_ = 8;
    cout << "[CargoPassengerVan] Конструктор без параметрів\n";
}

// Лаб 5, п. 2: конструктор Vehicle викликає сам фургон,
// тому Vehicle створюється тільки один раз
CargoPassengerVan::CargoPassengerVan(string brand, string plate, int year,
    int seats)
    : Vehicle(brand, plate, true, 90.0, year, 3500.0, "VIN_VAN", 160),
    Car(brand, plate, 90.0, false, year, 0, 60.0, "База"),
    Bus(brand, plate, year, seats),
    partition_(true) {
    max_load_ = 1200;
    cout << "[CargoPassengerVan] Конструктор з параметрами\n";
}

// Конструктор копіювання
CargoPassengerVan::CargoPassengerVan(const CargoPassengerVan& other)
    : Vehicle(other), Car(other), Bus(other), partition_(other.partition_) {
    cout << "[CargoPassengerVan] Конструктор копіювання\n";
}

// Лаб 5, п. 3: віртуальний деструктор
CargoPassengerVan::~CargoPassengerVan() {
    cout << "[CargoPassengerVan] Деструктор: " << brand_ << "\n";
}

// Лаб 5, п. 4: перевизначені віртуальні функції
void CargoPassengerVan::PerformWork() {
    cout << brand_ << " виконує ВАНТАЖОПАСАЖИРСЬКИЙ рейс: " << cargo_weight_
        << " кг вантажу і " << passengers_ << " пасажирів\n";
}

string CargoPassengerVan::GetTypeName() const {
    return "CargoPassengerVan";
}

// Лаб 5, п. 11: явний виклик версій Car, Bus і Vehicle
double CargoPassengerVan::CalculateTripCost(double km) const {
    return Car::CalculateTripCost(km) + Bus::CalculateTripCost(km) -
        Vehicle::CalculateTripCost(km);
}

void CargoPassengerVan::PrintType() const {
    cout << "Тип: CargoPassengerVan (Car + Bus)\n";
}

// Лаб 5, п. 7: запис полів у файл (поля Vehicle записуються один раз)
void CargoPassengerVan::Write(ofstream& out) const {
    Vehicle::Write(out);
    out << cargo_weight_ << "\n" << seats_ << "\n" << passengers_ << "\n"
        << partition_ << "\n";
}

// Лаб 5, п. 7: читання полів з файлу
void CargoPassengerVan::Read(ifstream& in) {
    Vehicle::Read(in);
    in >> cargo_weight_ >> seats_ >> passengers_ >> partition_;
    in.ignore(1000, '\n');
    if (in.fail()) {
        throw range_error("Дані CargoPassengerVan у файлі пошкоджені!");
    }
}

// Лаб 5, п. 4: з пасажирами можна взяти тільки половину вантажу
void CargoPassengerVan::LoadCargo(double kg) {
    if (passengers_ > 0 && kg > max_load_ / 2) {
        cout << brand_ << ": з пасажирами можна взяти максимум " << max_load_ / 2
            << " кг!\n";
        return;
    }
    Car::LoadCargo(kg);
}

// Лаб 5, п. 4: без перегородки не можна садити людей до вантажу
void CargoPassengerVan::BoardPassengers(int count) {
    if (cargo_weight_ > 0 && !partition_) {
        cout << brand_ << ": посадка заборонена, немає перегородки!\n";
        return;
    }
    Bus::BoardPassengers(count);
}

void CargoPassengerVan::SetPartition(bool installed) {
    partition_ = installed;
    if (installed) {
        cout << brand_ << ": перегородку встановлено\n";
    }
    else {
        cout << brand_ << ": перегородку знято\n";
    }
}