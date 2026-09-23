#ifndef TRIP_H_
#define TRIP_H_

#include <string>
#include "Car.h" 

// [Лаб 3] Допоміжний клас для композиції
class Route {
private:
	std::string path_;
	double distance_km_;
public:
	Route();
	Route(std::string path, double distance);
	std::string GetRouteInfo() const;
};

class Trip {
private:
	std::string trip_type_;
	double distance_km_;
	std::string route_description_;
	std::string driver_name_;
	Car assigned_car_;

	// [Лаб 3, П. 13] Сценарій взаємодії за КОМПОЗИЦІЇ 
	Route detailed_route_;

public:
	bool is_completed;
	int duration_hours;
	int stop_count;

	Trip();
	Trip(std::string type, double dist, std::string route, std::string driver, Car car, bool completed, int duration, int stops);
	~Trip();

	void StartTrip();
	void StartTrip(std::string dispatcher_note);
	void CompleteTrip(Car& car);
	void CompleteTrip(Car& car, std::string driver_report);
	Trip GetAlternativeTrip();
	void MergeWithTrip(Trip other);
	void SaveToFile(std::string filename);
	void LoadFromFile(std::string filename);

	void ShowCompositionInfo() const;
};

#endif // TRIP_H_