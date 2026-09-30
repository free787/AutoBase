#include "Car.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace std;

int Car::total_cars_in_fleet_ = 0;

Car::Car() : Vehicle(), needs_repair_(false), max_load_capacity_(20000), is_loaded_(false), cargo_type_("None"), current_mileage(0), fuel_level(0), current_location("База") {
    total_cars_in_fleet_++;
    cout << "[Car] Конструктор без параметрів.\n";
}

// [Лаб 4, П. 5] Передача параметрів конструктору базового класу (Vehicle) всередині похідного
Car::Car(string brand, string plate, double capacity, bool repair, int year, int mileage, double fuel, string location)
    : Vehicle(brand, plate, true, capacity, year, 15000.0, "VIN_TRUCK", 450),
    needs_repair_(repair), max_load_capacity_(20000), is_loaded_(false), cargo_type_("Стандарт"), current_mileage(mileage), fuel_level(fuel), current_location(location) {
    total_cars_in_fleet_++;
    cout << "[Car] Конструктор з параметрами вантажівки.\n";
}

Car::Car(const Car& other) : Vehicle(other) {
    needs_repair_ = other.needs_repair_;
    max_load_capacity_ = other.max_load_capacity_;
    is_loaded_ = other.is_loaded_;
    cargo_type_ = other.cargo_type_;
    current_mileage = other.current_mileage;
    fuel_level = other.fuel_level;
    current_location = other.current_location;
    total_cars_in_fleet_++;
}

Car::~Car() {
    total_cars_in_fleet_--;
    cout << "[Car Деструктор] Видалено вантажівку.\n";
}

void Car::CustomEngineStart() {
    // [Лаб 4, П. 6] Доступ до методу базового класу через оператор ::
    cout << "Перевірка систем вантажівки... ";
    Vehicle::StartEngine();
}

void Car::ShowTotalFleetCount() {
    cout << "--> [Статика] Загальна кількість машин: " << total_cars_in_fleet_ << "\n";
}

void Car::Refuel(double amount) {
    fuel_level += amount;
    cout << brand_ << " заправлено. В баку: " << fuel_level << " л.\n";
}

void Car::Refuel(double amount, bool fill_full_tank) {
    if (fill_full_tank) {
        fuel_level = fuel_capacity_;
        cout << brand_ << " заправлено до повного.\n";
    }
    else { Refuel(amount); }
}

void Car::RequestRepair() { needs_repair_ = true; }
void Car::RequestRepair(string reason) { needs_repair_ = true; }
Car Car::GetClone() { return *this; }
void Car::CopyDataFrom(Car other) { current_mileage = other.current_mileage; }
void Car::GenerateAndSortRouteDistances() { cout << "Генерація пробігів...\n"; }