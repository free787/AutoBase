#include "Car.h"

#include <stdexcept>

using namespace std;

int Car::total_cars_in_fleet_ = 0;

// Лаб 6, п. 1: скільки літрів доливає ++ і витрачає --
const double kFuelStep = 10.0;

Car::Car()
    : Vehicle(), current_mileage(0), fuel_level(0), current_location("База"),
    needs_repair_(false), max_load_(20000), cargo_weight_(0) {
    total_cars_in_fleet_++;
    cout << "[Car] Конструктор без параметрів\n";
}

// Лаб 4, п. 5: передача параметрів конструктору базового класу
Car::Car(string brand, string plate, double capacity, bool repair, int year,
    int mileage, double fuel, string location)
    : Vehicle(brand, plate, true, capacity, year, 15000.0, "VIN_TRUCK", 450),
    current_mileage(mileage), fuel_level(fuel), current_location(location),
    needs_repair_(repair), max_load_(20000), cargo_weight_(0) {
    total_cars_in_fleet_++;
    cout << "[Car] Конструктор з параметрами\n";
}

// Конструктор копіювання
Car::Car(const Car& other)
    : Vehicle(other), current_mileage(other.current_mileage),
    fuel_level(other.fuel_level), current_location(other.current_location),
    needs_repair_(other.needs_repair_), max_load_(other.max_load_),
    cargo_weight_(other.cargo_weight_) {
    total_cars_in_fleet_++;
    cout << "[Car] Конструктор копіювання\n";
}

// Лаб 5, п. 3: віртуальний деструктор
Car::~Car() {
    total_cars_in_fleet_--;
    cout << "[Car] Деструктор: " << brand_ << "\n";
}

// Лаб 5, п. 4: перевизначені віртуальні функції
void Car::PerformWork() {
    cout << brand_ << " виконує ВАНТАЖНИЙ рейс (вантаж " << cargo_weight_
        << " кг)\n";
}

string Car::GetTypeName() const {
    return "Car";
}

// Ставка Vehicle + 2 грн за тонну вантажу на 1 км
double Car::CalculateTripCost(double km) const {
    // Лаб 5, п. 11: виклик версії Vehicle в обхід віртуальності
    return Vehicle::CalculateTripCost(km) + km * 2.0 * cargo_weight_ / 1000;
}

void Car::PrintType() const {
    cout << "Тип: Car (вантажівка)\n";
}

// Лаб 5, п. 7: запис полів у файл
void Car::Write(ofstream& out) const {
    Vehicle::Write(out);
    out << current_mileage << "\n" << fuel_level << "\n" << current_location
        << "\n" << cargo_weight_ << "\n";
}

// Лаб 5, п. 7: читання полів з файлу
void Car::Read(ifstream& in) {
    Vehicle::Read(in);
    in >> current_mileage >> fuel_level;
    in.ignore(1000, '\n');
    getline(in, current_location);
    in >> cargo_weight_;
    in.ignore(1000, '\n');
    if (in.fail()) {
        throw range_error("Дані Car у файлі пошкоджені!");
    }
}

// Лаб 5, п. 4: власна віртуальна функція - завантаження вантажу
void Car::LoadCargo(double kg) {
    if (kg <= 0 || kg > max_load_) {
        cout << brand_ << ": не можна завантажити " << kg << " кг (максимум "
            << max_load_ << " кг)\n";
        return;
    }
    cargo_weight_ = kg;
    cout << brand_ << ": завантажено " << kg << " кг\n";
}

// Лаб 5, п. 10: невіртуальний метод Car
void Car::DisplayVehicleInfo() const {
    cout << "[Car] Вантажівка " << brand_ << ", пробіг " << current_mileage
        << " км, пальне " << fuel_level << " л\n";
}

void Car::ShowTotalFleetCount() {
    cout << "Загальна кількість машин: " << total_cars_in_fleet_ << "\n";
}

void Car::Refuel(double amount) {
    fuel_level += amount;
    cout << brand_ << " заправлено. В баку: " << fuel_level << " л\n";
}

void Car::Refuel(double amount, bool fill_full_tank) {
    if (fill_full_tank) {
        fuel_level = fuel_capacity_;
        cout << brand_ << " заправлено до повного\n";
    }
    else {
        Refuel(amount);
    }
}

void Car::RequestRepair() {
    needs_repair_ = true;
    cout << brand_ << ": подано заявку на ремонт\n";
}

void Car::RequestRepair(string reason) {
    needs_repair_ = true;
    cout << brand_ << ": подано заявку на ремонт. Причина: " << reason << "\n";
}

Car Car::GetClone() {
    return *this;
}

void Car::CopyDataFrom(Car other_car) {
    current_mileage = other_car.current_mileage;
}

void Car::GenerateAndSortRouteDistances() {
    cout << "Генерація пробігів...\n";
}

void Car::CustomEngineStart() {
    // Лаб 4, п. 6: виклик методу базового класу через ::
    cout << "Перевірка систем вантажівки... ";
    Vehicle::StartEngine();
}

// Лаб 6, п. 1: префіксний ++ (долити 10 л, але не більше, ніж вміщає бак)
Car& Car::operator++() {
    fuel_level += kFuelStep;
    if (fuel_level > fuel_capacity_) {
        fuel_level = fuel_capacity_;
        cout << brand_ << ": бак повний!\n";
    }
    return *this;
}

// Лаб 6, п. 1: постфіксний ++ (повертає копію старого стану)
Car Car::operator++(int) {
    Car old_state(*this);
    ++(*this);
    return old_state;
}

// Лаб 6, п. 1: префіксний -- (витратити 10 л, але не менше 0)
Car& Car::operator--() {
    fuel_level -= kFuelStep;
    if (fuel_level < 0) {
        fuel_level = 0;
        cout << brand_ << ": бак порожній!\n";
    }
    return *this;
}

// Лаб 6, п. 1: постфіксний --
Car Car::operator--(int) {
    Car old_state(*this);
    --(*this);
    return old_state;
}