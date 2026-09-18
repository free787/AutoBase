#pragma once
#ifndef TRIP_H_
#define TRIP_H_

#include <string>
#include "Car.h" // Підключення класу Car для композиції

// 1. Користувацький клас 2
class Trip {
private:
	// 2. 5 приватних елементів
	std::string trip_type_;
	double distance_km_;
	std::string route_description_;
	std::string driver_name_;

	// 3. Зв'язок двох об'єктів
	Car assigned_car_;

public:
	// 2. 3 загальні елементи
	bool is_completed;
	int duration_hours;
	int stop_count;

	Trip();
	Trip(std::string type, double dist, std::string route, std::string driver, Car car, bool completed, int duration, int stops);

	// 4. 6 методів
	void StartTrip();
	void StartTrip(std::string dispatcher_note);
	void CompleteTrip();
	void CompleteTrip(std::string driver_report);
	Trip GetAlternativeTrip();
	void MergeWithTrip(Trip other);

	// 5. Робота з файлами
	void SaveToFile(std::string filename);
	void LoadFromFile(std::string filename);
};

#endif // TRIP_H_