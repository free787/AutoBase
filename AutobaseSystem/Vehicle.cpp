#include "Vehicle.h"
#include <iostream>

using namespace std;

Vehicle::Vehicle() : brand_("Unknown"), plate_number_("0000"), is_active_(false), fuel_capacity_(0), year_built_(2000), weight_(0), vin_code_("NONE"), engine_power_(0) {
    cout << "[Vehicle] Конструктор без параметрів.\n";
}

// [Лаб 4, П. 5] Передача не менше 5 аргументів у базовий клас
Vehicle::Vehicle(string brand, string plate, bool active, double capacity, int year, double weight, string vin, int power)
    : brand_(brand), plate_number_(plate), is_active_(active), fuel_capacity_(capacity), year_built_(year), weight_(weight), vin_code_(vin), engine_power_(power) {
    cout << "[Vehicle] Конструктор з параметрами для: " << brand_ << "\n";
}

Vehicle::Vehicle(const Vehicle& other)
    : brand_(other.brand_ + "_copy"), plate_number_(other.plate_number_), is_active_(other.is_active_), fuel_capacity_(other.fuel_capacity_), year_built_(other.year_built_), weight_(other.weight_), vin_code_(other.vin_code_), engine_power_(other.engine_power_) {
    cout << "[Vehicle] Конструктор копіювання.\n";
}

Vehicle::~Vehicle() {
    // [Лаб 4, П. 8] Відслідковування виходу з блоку
    cout << "[Vehicle Деструктор] Базове авто видалено: " << brand_ << "\n";
}

void Vehicle::StartEngine() {
    cout << "Двигун " << brand_ << " запущено.\n";
}

void Vehicle::DisplayVehicleInfo() const {
    cout << "Базова інформація: " << brand_ << " [" << plate_number_ << "], Рік: " << year_built_ << "\n";
}

void Vehicle::PerformMaintenance() {
    cout << "Базове ТО виконано.\n";
}

void Vehicle::LogInternalSystem() {
    cout << "Лог системи збережено (VIN: " << vin_code_ << ").\n";
}