#include "Car.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>

using namespace std;

// [Лаб 3, П. 4] Ініціалізація статичного поля
int Car::total_cars_in_fleet_ = 0;

Car::Car() : brand_("Unknown"), plate_number_("0000"), fuel_capacity_(400.0), needs_repair_(false), year_built_(2010), current_mileage(0), fuel_level(0.0), current_location("База") {
    total_cars_in_fleet_++;
    cout << "[Конструктор без параметрів] Створено пусте авто.\n";
}

Car::Car(string brand, string plate, double capacity, bool repair, int year, int mileage, double fuel, string location)
    : brand_(brand), plate_number_(plate), fuel_capacity_(capacity), needs_repair_(repair), year_built_(year), current_mileage(mileage), fuel_level(fuel), current_location(location) {
    total_cars_in_fleet_++;
}

// [Лаб 3, П. 1] Реалізація конструктора копіювання
Car::Car(const Car& other) {
    brand_ = other.brand_ + " (Копія)";
    plate_number_ = other.plate_number_;
    fuel_capacity_ = other.fuel_capacity_;
    needs_repair_ = other.needs_repair_;
    year_built_ = other.year_built_;
    current_mileage = other.current_mileage;
    fuel_level = other.fuel_level;
    current_location = other.current_location;
    total_cars_in_fleet_++;
    cout << "[Конструктор копіювання] Дані тягача скопійовано.\n";
}

Car::~Car() {
    total_cars_in_fleet_--;
    // [Лаб 3, П. 3] Відслідковування виходу з блоку
    cout << "[Деструктор] Видалено з пам'яті авто: " << brand_ << ".\n";
}

void Car::ShowTotalFleetCount() {
    cout << "--> [Статика] Загальна кількість машин на балансі бази: " << total_cars_in_fleet_ << "\n";
}

// === ЗБЕРЕЖЕНІ МЕТОДИ З ЛАБ 2 (РОЗГОРНУТІ) ===
void Car::Refuel(double amount) {
    fuel_level += amount;
    cout << brand_ << " (" << plate_number_ << "): Заправлено " << amount << " л. В баку: " << fuel_level << " л.\n";
}

void Car::Refuel(double amount, bool fill_full_tank) {
    if (fill_full_tank) {
        fuel_level = fuel_capacity_;
        cout << brand_ << " заправлено до повного баку (" << fuel_capacity_ << " л).\n";
    }
    else {
        Refuel(amount);
    }
}

void Car::RequestRepair() {
    needs_repair_ = true;
    cout << "Увага! " << brand_ << " потребує ремонту. Локація: " << current_location << ".\n";
}

void Car::RequestRepair(string reason) {
    RequestRepair();
    cout << "Причина ремонту: " << reason << "\n";
}

Car Car::GetClone() {
    return *this;
}

void Car::CopyDataFrom(Car other_car) {
    brand_ = other_car.brand_;
    plate_number_ = other_car.plate_number_;
    fuel_capacity_ = other_car.fuel_capacity_;
    needs_repair_ = other_car.needs_repair_;
    year_built_ = other_car.year_built_;
    current_mileage = other_car.current_mileage;
    fuel_level = other_car.fuel_level;
    current_location = other_car.current_location;
    cout << "Дані тягача скопійовано.\n";
}

void Car::SaveToFile(string filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << brand_ << "\n" << plate_number_ << "\n" << fuel_capacity_ << "\n" << needs_repair_ << "\n"
            << year_built_ << "\n" << current_mileage << "\n" << fuel_level << "\n" << current_location << "\n";
        file.close();
    }
}

void Car::LoadFromFile(string filename) {
    ifstream file(filename);
    if (file.is_open()) {
        file >> brand_ >> plate_number_ >> fuel_capacity_ >> needs_repair_ >> year_built_ >> current_mileage >> fuel_level >> current_location;
        file.close();
    }
}

void Car::GenerateAndSortRouteDistances() {
    int size = 5 + rand() % 10;
    int* predicted_mileages = new int[size];
    for (int i = 0; i < size; i++) {
        predicted_mileages[i] = current_mileage + (rand() % 800 + 100);
    }
    sort(predicted_mileages, predicted_mileages + size);
    cout << "Можливі пробіги після наступних рейсів (відсортовано): ";
    for (int i = 0; i < size; i++) {
        cout << predicted_mileages[i] << " ";
    }
    cout << "\n";
    delete[] predicted_mileages;
}