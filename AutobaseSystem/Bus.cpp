#include "Bus.h"

#include <stdexcept>

using namespace std;

Bus::Bus() : Vehicle(), seats_(40), passengers_(0) {
    cout << "[Bus] Конструктор без параметрів\n";
}

Bus::Bus(string brand, string plate, int year, int seats)
    : Vehicle(brand, plate, true, 250.0, year, 11000.0, "VIN_BUS", 300),
    seats_(seats), passengers_(0) {
    cout << "[Bus] Конструктор з параметрами\n";
}

// Конструктор копіювання
Bus::Bus(const Bus& other)
    : Vehicle(other), seats_(other.seats_), passengers_(other.passengers_) {
    cout << "[Bus] Конструктор копіювання\n";
}

// Лаб 5, п. 3: віртуальний деструктор
Bus::~Bus() {
    cout << "[Bus] Деструктор: " << brand_ << "\n";
}

// Лаб 5, п. 4: перевизначені віртуальні функції
void Bus::PerformWork() {
    cout << brand_ << " виконує ПАСАЖИРСЬКИЙ рейс (пасажирів " << passengers_
        << "/" << seats_ << ")\n";
}

string Bus::GetTypeName() const {
    return "Bus";
}

// Ставка Vehicle + 0.4 грн за кожного пасажира на 1 км
double Bus::CalculateTripCost(double km) const {
    return Vehicle::CalculateTripCost(km) + km * 0.4 * passengers_;
}

void Bus::PrintType() const {
    cout << "Тип: Bus (автобус)\n";
}

// Лаб 5, п. 7: запис полів у файл
void Bus::Write(ofstream& out) const {
    Vehicle::Write(out);
    out << seats_ << "\n" << passengers_ << "\n";
}

// Лаб 5, п. 7: читання полів з файлу
void Bus::Read(ifstream& in) {
    Vehicle::Read(in);
    in >> seats_ >> passengers_;
    in.ignore(1000, '\n');
    if (in.fail()) {
        throw range_error("Дані Bus у файлі пошкоджені!");
    }
}

// Лаб 5, п. 4: власна віртуальна функція - посадка пасажирів
void Bus::BoardPassengers(int count) {
    if (count <= 0) {
        cout << brand_ << ": кількість пасажирів має бути більше 0\n";
        return;
    }
    if (passengers_ + count > seats_) {
        cout << brand_ << ": немає стільки вільних місць!\n";
        return;
    }
    passengers_ += count;
    cout << brand_ << ": сіло " << count << " пасажирів, всього "
        << passengers_ << "/" << seats_ << "\n";
}

// Лаб 6, п. 1: префіксний ++ (спочатку змінює, потім повертає сам об'єкт)
Bus& Bus::operator++() {
    if (passengers_ < seats_) {
        passengers_++;
    }
    else {
        cout << brand_ << ": вільних місць немає!\n";
    }
    return *this;
}

// Лаб 6, п. 1: постфіксний ++ (повертає копію старого стану, потім змінює)
Bus Bus::operator++(int) {
    Bus old_state(*this);
    ++(*this);
    return old_state;
}

// Лаб 6, п. 1: префіксний --
Bus& Bus::operator--() {
    if (passengers_ > 0) {
        passengers_--;
    }
    else {
        cout << brand_ << ": в салоні вже нікого немає!\n";
    }
    return *this;
}

// Лаб 6, п. 1: постфіксний --
Bus Bus::operator--(int) {
    Bus old_state(*this);
    --(*this);
    return old_state;
}