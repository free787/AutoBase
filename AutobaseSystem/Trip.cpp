#include "Trip.h"
#include <iostream>
#include <fstream>

using namespace std;

Route::Route() : path_("Unknown"), distance_km_(0) {}
Route::Route(string path, double distance) : path_(path), distance_km_(distance) {}
string Route::GetRouteInfo() const { return path_ + " (" + to_string(distance_km_) + " км)"; }

Trip::Trip() : trip_type_("Вантажний"), distance_km_(0), route_description_("База"), driver_name_("Немає"), is_completed(false), duration_hours(0), stop_count(0) {}

// [Лаб 3, П. 13] Ініціалізація композиції (Route) в конструкторі
Trip::Trip(string type, double dist, string route, string driver, Car car, bool completed, int duration, int stops)
    : trip_type_(type), distance_km_(dist), route_description_(route), driver_name_(driver), assigned_car_(car), is_completed(completed), duration_hours(duration), stop_count(stops), detailed_route_(route, dist) {}

Trip::~Trip() {}

void Trip::ShowCompositionInfo() const {
    cout << "Деталі маршруту (Композиція): " << detailed_route_.GetRouteInfo() << "\n";
}

// === ЗБЕРЕЖЕНІ МЕТОДИ З ЛАБ 2 (РОЗГОРНУТІ) ===
void Trip::StartTrip() {
    cout << "Рейс " << route_description_ << " почався. Водій: " << driver_name_ << ".\n";
}

void Trip::StartTrip(string dispatcher_note) {
    StartTrip();
    cout << "Нотатка диспетчера: " << dispatcher_note << "\n";
}

void Trip::CompleteTrip(Car& car) {
    is_completed = true;
    car.current_mileage += distance_km_;
    car.fuel_level -= (distance_km_ * 0.3); // Витрата 30л на 100км
    car.current_location = "Кінцева точка маршруту";
    cout << "Рейс виконано. Дані автомобіля оновлено:\n"
        << " - Новий пробіг: " << car.current_mileage << " км\n"
        << " - Залишок пального: " << car.fuel_level << " л.\n";
}

void Trip::CompleteTrip(Car& car, string driver_report) {
    CompleteTrip(car);
    cout << "Звіт водія: " << driver_report << "\n";
}

Trip Trip::GetAlternativeTrip() {
    Trip alt = *this;
    alt.route_description_ += " (в об'їзд)";
    alt.distance_km_ += 35.0;
    return alt;
}

void Trip::MergeWithTrip(Trip other) {
    distance_km_ += other.distance_km_;
    route_description_ += " -> " + other.route_description_;
    stop_count += other.stop_count;
}

void Trip::SaveToFile(string filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << trip_type_ << "\n" << distance_km_ << "\n" << route_description_ << "\n" << driver_name_ << "\n" << is_completed << "\n";
        file.close();
    }
}

void Trip::LoadFromFile(string filename) {
    ifstream file(filename);
    if (file.is_open()) {
        file >> trip_type_ >> distance_km_ >> route_description_ >> driver_name_ >> is_completed;
        file.close();
    }
}