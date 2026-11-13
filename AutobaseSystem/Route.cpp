#include "Route.h"

#include <iostream>
#include <stdexcept>

using namespace std;

Route::Route() : path_("Unknown"), distance_km_(0), stop_count_(0) {}

Route::Route(string path, double distance)
    : path_(path), distance_km_(distance), stop_count_(0) {}

// Конструктор копіювання
Route::Route(const Route& other)
    : path_(other.path_), distance_km_(other.distance_km_),
    stop_count_(other.stop_count_) {
    for (int i = 0; i < stop_count_; i++) {
        stops_[i] = other.stops_[i];
    }
}

void Route::AddStop(string stop) {
    if (stop_count_ >= kMaxStops) {
        cout << "Не можна додати зупинку " << stop << ": максимум " << kMaxStops
            << "\n";
        return;
    }
    stops_[stop_count_] = stop;
    stop_count_++;
}

void Route::Print() const {
    cout << "Маршрут \"" << path_ << "\": " << distance_km_ << " км, зупинки: ";
    if (stop_count_ == 0) {
        cout << "немає";
    }
    for (int i = 0; i < stop_count_; i++) {
        cout << stops_[i];
        if (i < stop_count_ - 1) {
            cout << ", ";
        }
    }
    cout << "\n";
}

string Route::GetRouteInfo() const {
    return path_ + " (" + to_string(static_cast<int>(distance_km_)) + " км)";
}

// Лаб 6, п. 2: оператор + (новий маршрут = перший + другий)
Route Route::operator+(const Route& other) const {
    Route result(path_ + " -> " + other.path_,
        distance_km_ + other.distance_km_);
    for (int i = 0; i < stop_count_; i++) {
        result.AddStop(stops_[i]);
    }
    for (int i = 0; i < other.stop_count_; i++) {
        result.AddStop(other.stops_[i]);
    }
    return result;
}

// Лаб 6, п. 2: оператор - (новий маршрут, коротший на km)
Route Route::operator-(double km) const {
    Route result(*this);
    result.distance_km_ -= km;
    if (result.distance_km_ < 0) {
        result.distance_km_ = 0;
    }
    return result;
}

// Лаб 6, п. 3: оператор * (маршрут, який проїжджають times разів)
Route Route::operator*(int times) const {
    Route result(*this);
    result *= times;
    return result;
}

// Лаб 6, п. 3: оператор присвоєння
Route& Route::operator=(const Route& other) {
    if (this == &other) {
        return *this;
    }
    path_ = other.path_;
    distance_km_ = other.distance_km_;
    stop_count_ = other.stop_count_;
    for (int i = 0; i < stop_count_; i++) {
        stops_[i] = other.stops_[i];
    }
    return *this;
}

// Лаб 6, п. 3: оператор += (дописати інший маршрут до цього)
Route& Route::operator+=(const Route& other) {
    *this = *this + other;
    return *this;
}

// Лаб 6, п. 3: оператор -= (скоротити цей маршрут на km)
Route& Route::operator-=(double km) {
    distance_km_ -= km;
    if (distance_km_ < 0) {
        distance_km_ = 0;
    }
    return *this;
}

// Лаб 6, п. 3: оператор *= (повторити маршрут times разів)
Route& Route::operator*=(int times) {
    if (times < 1) {
        throw invalid_argument("Кількість повторів має бути більше 0!");
    }
    distance_km_ *= times;
    path_ += " (x" + to_string(times) + ")";
    return *this;
}

// Лаб 6, п. 3: оператор [] (доступ до зупинки за номером)
string& Route::operator[](int index) {
    if (index < 0 || index >= stop_count_) {
        throw out_of_range("Зупинки з номером " + to_string(index) +
            " немає!");
    }
    return stops_[index];
}