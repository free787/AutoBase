#include "Trip.h"
#include <iostream>
#include <fstream>

using namespace std;

Trip::Trip() : trip_type_("Вантажний"), distance_km_(0), route_description_("База"), driver_name_("Немає"), is_completed(false), duration_hours(0), stop_count(0) {}

Trip::Trip(string type, double dist, string route, string driver, Car car, bool completed, int duration, int stops)
    : trip_type_(type), distance_km_(dist), route_description_(route), driver_name_(driver), assigned_car_(car), is_completed(completed), duration_hours(duration), stop_count(stops) {}

void Trip::StartTrip() {
    cout << "Рейс " << route_description_ << " почався. Водій: " << driver_name_ << ".\n";
}

void Trip::StartTrip(string dispatcher_note) {
    StartTrip();
    cout << "Нотатка диспетчера: " << dispatcher_note << "\n";
}

void Trip::CompleteTrip() {
    is_completed = true;
    // 10. Взаємодія двох об'єктів
    assigned_car_.current_mileage += distance_km_;
    cout << "Рейс виконано. Додано " << distance_km_ << " км до пробігу.\n";
}

void Trip::CompleteTrip(string driver_report) {
    CompleteTrip();
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