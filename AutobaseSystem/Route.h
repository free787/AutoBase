#pragma once
#ifndef ROUTE_H_
#define ROUTE_H_

#include <string>

// Лаб 3: маршрут (частина рейсу, композиція)
// Лаб 6, п. 2, 3: перевантаження операторів для маршруту
class Route {
public:
	static const int kMaxStops = 10;

	Route();
	Route(std::string path, double distance);
	Route(const Route& other);

	void AddStop(std::string stop);
	void Print() const;
	std::string GetRouteInfo() const;
	double GetDistance() const { return distance_km_; }
	int GetStopCount() const { return stop_count_; }

	// Лаб 6, п. 2: бінарні оператори + і -
	Route operator+(const Route& other) const;  // з'єднати два маршрути
	Route operator-(double km) const;           // скоротити маршрут на km

	// Лаб 6, п. 3: оператори *, =, +=, -=, *=, []
	Route operator*(int times) const;           // проїхати маршрут times разів
	Route& operator=(const Route& other);       // присвоєння
	Route& operator+=(const Route& other);      // дописати інший маршрут
	Route& operator-=(double km);               // скоротити на km
	Route& operator*=(int times);               // повторити times разів
	std::string& operator[](int index);         // зупинка за номером

private:
	std::string path_;
	double distance_km_;
	std::string stops_[kMaxStops];
	int stop_count_;
};

#endif  // ROUTE_H_