#include "AdvancedVehicles.h"

#include <stdexcept>

using namespace std;

// ---------- TowTruck ----------

// Лаб 4, п. 5: передача параметрів конструктору базового класу
TowTruck::TowTruck(string brand, double crane_capacity)
    : Vehicle(brand, "TOW001", true, 200, 2022, 8000, "VIN_TOW", 500),
    crane_capacity_(crane_capacity) {
    cout << "[TowTruck] Евакуатор створено\n";
}

TowTruck::~TowTruck() {
    cout << "[TowTruck] Деструктор\n";
}

// Лаб 4, п. 3: методи Vehicle доступні тільки всередині класу
void TowTruck::ExecuteTowing() {
    Vehicle::StartEngine();
    cout << "Кран евакуатора: " << crane_capacity_ << " кг\n";
    PerformWork();
}

// Лаб 5, п. 1: реалізація чисто віртуальних функцій
void TowTruck::PerformWork() {
    cout << "Евакуатор " << brand_ << " транспортує пошкоджене авто\n";
}

string TowTruck::GetTypeName() const {
    return "TowTruck";
}

// ---------- GPSDevice ----------

GPSDevice::GPSDevice() : coordinates_("49.4229, 26.9871") {
    cout << "[GPS] Трекер увімкнено\n";
}

// Лаб 5, п. 3: віртуальний деструктор
GPSDevice::~GPSDevice() {
    cout << "[GPS] Деструктор\n";
}

// Лаб 5, п. 4: віртуальна функція
void GPSDevice::PingLocation() const {
    cout << "GPS координати: " << coordinates_ << "\n";
}

// ---------- RefrigerationUnit ----------

RefrigerationUnit::RefrigerationUnit() : temperature_(4.0) {
    cout << "[Холодильник] Увімкнено\n";
}

// Лаб 5, п. 3: віртуальний деструктор
RefrigerationUnit::~RefrigerationUnit() {
    cout << "[Холодильник] Деструктор\n";
}

// Лаб 5, п. 4: віртуальна функція
void RefrigerationUnit::SetTemperature(double temp) {
    temperature_ = temp;
    cout << "Температуру встановлено: " << temperature_ << " C\n";
}

// ---------- RefrigeratedTruck ----------

// Лаб 5, п. 2: Vehicle (віртуальну базу) викликає сам рефрижератор
RefrigeratedTruck::RefrigeratedTruck(string brand, string plate, int year)
    : Vehicle(brand, plate, true, 600, year, 16000, "VIN_REF", 500),
    Car(brand, plate, 600, false, year, 0, 100, "Склад"),
    GPSDevice(),
    RefrigerationUnit() {
    cout << "[RefrigeratedTruck] Рефрижератор зібрано\n";
}

// Лаб 5, п. 3: віртуальний деструктор
RefrigeratedTruck::~RefrigeratedTruck() {
    cout << "[RefrigeratedTruck] Деструктор: " << brand_ << "\n";
}

// Лаб 4, п. 6: виклик методів різних базових класів
void RefrigeratedTruck::StartColdDelivery() {
    CustomEngineStart();
    PingLocation();
    SetTemperature(-18.5);
    cout << "Рефрижератор " << brand_ << " готовий до рейсу!\n";
}

// Лаб 5, п. 4: перевизначені віртуальні функції
void RefrigeratedTruck::PerformWork() {
    cout << brand_ << " везе заморожені продукти при " << temperature_
        << " C (вантаж " << cargo_weight_ << " кг)\n";
}

string RefrigeratedTruck::GetTypeName() const {
    return "RefrigeratedTruck";
}

// Ставка Car + 3.5 грн за 1 км за роботу холодильника
double RefrigeratedTruck::CalculateTripCost(double km) const {
    return Car::CalculateTripCost(km) + km * 3.5;
}

void RefrigeratedTruck::PrintType() const {
    cout << "Тип: RefrigeratedTruck (Car + GPS + холодильник)\n";
}

// Вантажити можна тільки коли камера охолоджена до -15 C
void RefrigeratedTruck::LoadCargo(double kg) {
    if (temperature_ > -15) {
        cout << brand_ << ": камера тепла (" << temperature_
            << " C), спочатку охолодіть!\n";
        return;
    }
    Car::LoadCargo(kg);
}

// Холодильник працює тільки від -25 до +8 C
void RefrigeratedTruck::SetTemperature(double temp) {
    if (temp < -25 || temp > 8) {
        cout << "Температура " << temp << " C недопустима!\n";
        return;
    }
    RefrigerationUnit::SetTemperature(temp);
}

// Лаб 5, п. 7: запис полів у файл
void RefrigeratedTruck::Write(ofstream& out) const {
    Car::Write(out);
    out << temperature_ << "\n";
}

// Лаб 5, п. 7: читання полів з файлу
void RefrigeratedTruck::Read(ifstream& in) {
    Car::Read(in);
    in >> temperature_;
    in.ignore(1000, '\n');
    if (in.fail()) {
        throw range_error("Дані RefrigeratedTruck у файлі пошкоджені!");
    }
}