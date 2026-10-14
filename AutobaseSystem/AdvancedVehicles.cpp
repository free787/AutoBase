#include "AdvancedVehicles.h"
using namespace std;

// --- TowTruck (Private Inheritance) ---
// [Лаб 4, П. 3] Визначити додатковий похідний клас, який демонструє закритий спосіб наслідування.
TowTruck::TowTruck(string brand, double crane_cap)
// [Лаб 4, П. 5] Передача параметрів конструктору базового класу всередині похідного.
    : Vehicle(brand, "TOW001", true, 200, 2022, 8000, "VIN_TOW", 500), crane_capacity_(crane_cap), is_towing_(false) {
    cout << "[TowTruck] Евакуатор створено.\n";
}
TowTruck::~TowTruck() { cout << "[TowTruck Деструктор] Евакуатор видалено.\n"; }

// [Лаб 4, П. 3] Об'єкти, які оперують методами з різних класів ієрархії.
void TowTruck::ExecuteTowing() {
    // Можемо викликати методи Vehicle тільки зсередини через private наслідування
    Vehicle::StartEngine();
    cout << "Евакуатор " << brand_ << " розпочав буксирування. Вантажопідйомність крана: " << crane_capacity_ << " кг.\n";
}

// --- GPSDevice ---
// [Лаб 4, П. 4] Побудувати додаткові класи в наявну ієрархію для реалізації множинного наслідування.
GPSDevice::GPSDevice() : coordinates_("49.4229, 26.9871") { cout << "[GPS] Трекер увімкнено.\n"; }
GPSDevice::~GPSDevice() { cout << "[GPS Деструктор] Трекер вимкнено.\n"; }
void GPSDevice::PingLocation() { cout << "GPS Координати: " << coordinates_ << "\n"; }

// --- RefrigerationUnit ---
// [Лаб 4, П. 4] Побудувати додаткові класи в наявну ієрархію.
RefrigerationUnit::RefrigerationUnit() : temperature_(4.0) { cout << "[Рефрижератор] Холодильник увімкнено.\n"; }
RefrigerationUnit::~RefrigerationUnit() { cout << "[Рефрижератор Деструктор] Холодильник вимкнено.\n"; }
void RefrigerationUnit::SetTemperature(double temp) {
    temperature_ = temp;
    cout << "Температуру встановлено на: " << temperature_ << " C.\n";
}

// --- RefrigeratedTruck (Множинне наслідування) ---
// [Лаб 4, П. 4] Реалізація множинного наслідування.
RefrigeratedTruck::RefrigeratedTruck(string brand, string plate)
// [Лаб 5, П. 2] Додано виклик конструктора базового абстрактного класу через віртуальне успадкування!
    : Vehicle(brand, plate, true, 600, 2023, 16000, "VIN_REF", 500),
    Car(brand, plate, 600, false, 2023, 0, 100, "Склад"), GPSDevice(), RefrigerationUnit() {
    cout << "[RefrigeratedTruck] Авторефрижератор повністю зібрано!\n";
}
RefrigeratedTruck::~RefrigeratedTruck() {
    cout << "[RefrigeratedTruck Деструктор] Авторефрижератор списано.\n";
}

void RefrigeratedTruck::StartColdDelivery() {
    // [Лаб 4, П. 6] Демонстрація доступу до методів різних базових класів з похідного класу.
    CustomEngineStart();
    PingLocation();
    SetTemperature(-18.5);
    cout << "Рефрижератор " << GetBrand() << " готовий до рейсу!\n";
}