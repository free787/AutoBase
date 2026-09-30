#include "AdvancedVehicles.h"
using namespace std;

// --- TowTruck (Private Inheritance) ---
TowTruck::TowTruck(string brand, double crane_cap)
    : Vehicle(brand, "TOW001", true, 200, 2022, 8000, "VIN_TOW", 500), crane_capacity_(crane_cap), is_towing_(false) {
    cout << "[TowTruck] Евакуатор створено.\n";
}
TowTruck::~TowTruck() { cout << "[TowTruck Деструктор] Евакуатор видалено.\n"; }

void TowTruck::ExecuteTowing() {
    // Можемо викликати методи Vehicle тільки зсередини через private наслідування
    Vehicle::StartEngine();
    cout << "Евакуатор " << brand_ << " розпочав буксирування. Вантажопідйомність крана: " << crane_capacity_ << " кг.\n";
}

// --- GPSDevice ---
GPSDevice::GPSDevice() : coordinates_("49.4229, 26.9871") { cout << "[GPS] Трекер увімкнено.\n"; }
GPSDevice::~GPSDevice() { cout << "[GPS Деструктор] Трекер вимкнено.\n"; }
void GPSDevice::PingLocation() { cout << "GPS Координати: " << coordinates_ << "\n"; }

// --- RefrigerationUnit ---
RefrigerationUnit::RefrigerationUnit() : temperature_(4.0) { cout << "[Рефрижератор] Холодильник увімкнено.\n"; }
RefrigerationUnit::~RefrigerationUnit() { cout << "[Рефрижератор Деструктор] Холодильник вимкнено.\n"; }
void RefrigerationUnit::SetTemperature(double temp) {
    temperature_ = temp;
    cout << "Температуру встановлено на: " << temperature_ << " C.\n";
}

// --- RefrigeratedTruck (Множинне наслідування) ---
RefrigeratedTruck::RefrigeratedTruck(string brand, string plate)
    : Car(brand, plate, 600, false, 2023, 0, 100, "Склад"), GPSDevice(), RefrigerationUnit() {
    cout << "[RefrigeratedTruck] Авторефрижератор повністю зібрано!\n";
}
RefrigeratedTruck::~RefrigeratedTruck() {
    cout << "[RefrigeratedTruck Деструктор] Авторефрижератор списано.\n";
}

void RefrigeratedTruck::StartColdDelivery() {
    CustomEngineStart();      // Метод з Car
    PingLocation();           // Метод з GPSDevice
    SetTemperature(-18.5);    // Метод з RefrigerationUnit
    cout << "Рефрижератор " << GetBrand() << " готовий до рейсу!\n";
}