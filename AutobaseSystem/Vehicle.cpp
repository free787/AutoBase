#include "Vehicle.h"

#include <stdexcept>

using namespace std;

Vehicle::Vehicle()
    : brand_("Unknown"), plate_number_("0000"), is_active_(false),
    fuel_capacity_(0), year_built_(2000), weight_(0), vin_code_("NONE"),
    engine_power_(0) {
    cout << "[Vehicle] Конструктор без параметрів\n";
}

// Лаб 4, п. 5: конструктор з параметрами
Vehicle::Vehicle(string brand, string plate, bool active, double capacity,
    int year, double weight, string vin, int power)
    : brand_(brand), plate_number_(plate), is_active_(active),
    fuel_capacity_(capacity), year_built_(year), weight_(weight),
    vin_code_(vin), engine_power_(power) {
    cout << "[Vehicle] Конструктор з параметрами: " << brand_ << "\n";
}

// Конструктор копіювання
Vehicle::Vehicle(const Vehicle& other)
    : brand_(other.brand_), plate_number_(other.plate_number_),
    is_active_(other.is_active_), fuel_capacity_(other.fuel_capacity_),
    year_built_(other.year_built_), weight_(other.weight_),
    vin_code_(other.vin_code_), engine_power_(other.engine_power_) {
    cout << "[Vehicle] Конструктор копіювання\n";
}

// Лаб 5, п. 3: віртуальний деструктор
Vehicle::~Vehicle() {
    cout << "[Vehicle] Деструктор: " << brand_ << "\n";
}

void Vehicle::StartEngine() {
    cout << "Двигун " << brand_ << " запущено\n";
}

// Лаб 5, п. 10: невіртуальний метод
void Vehicle::DisplayVehicleInfo() const {
    cout << "[Vehicle] " << brand_ << " [" << plate_number_ << "], рік "
        << year_built_ << "\n";
}

// Лаб 5, п. 4: базова ставка 12 грн за 1 км
double Vehicle::CalculateTripCost(double km) const {
    return km * 12.0;
}

void Vehicle::PrintType() const {
    cout << "Тип: Vehicle\n";
}

// Лаб 5, п. 7: запис полів у файл
void Vehicle::Write(ofstream& out) const {
    out << brand_ << "\n" << plate_number_ << "\n" << is_active_ << "\n"
        << fuel_capacity_ << "\n" << year_built_ << "\n" << weight_ << "\n"
        << vin_code_ << "\n" << engine_power_ << "\n";
}

// Лаб 5, п. 7: читання полів з файлу
void Vehicle::Read(ifstream& in) {
    getline(in, brand_);
    getline(in, plate_number_);
    in >> is_active_ >> fuel_capacity_ >> year_built_ >> weight_;
    in.ignore(1000, '\n');
    getline(in, vin_code_);
    in >> engine_power_;
    in.ignore(1000, '\n');
    // Лаб 5, п. 7: виняток - дані у файлі пошкоджені
    if (in.fail()) {
        throw range_error("Дані Vehicle у файлі пошкоджені!");
    }
}

void Vehicle::PerformMaintenance() {
    cout << "Базове ТО виконано\n";
    LogInternalSystem();
}

void Vehicle::LogInternalSystem() {
    cout << "Лог системи збережено (VIN: " << vin_code_ << ")\n";
}