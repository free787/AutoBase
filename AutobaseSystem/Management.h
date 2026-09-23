#ifndef MANAGEMENT_H_
#define MANAGEMENT_H_

#include "Car.h"
#include "Driver.h"
#include <string>

class Dispatcher {
private:
	std::string name_;
	// [Лаб 3, П. 12] Сценарій взаємодії за АГРЕГАЦІЇ
	Car* fleet_[10];
	int car_count_;
public:
	Dispatcher(std::string name);
	void AssignCarToFleet(Car* car);
	std::string GetName() const { return name_; }
};

// [Лаб 3, П. 11] Сценарій взаємодії трьох об’єктів за допомогою класу АСОЦІАЦІЙ
class TripAssignment {
private:
	Dispatcher* dispatcher_;
	Driver* driver_;
	Car* car_;
public:
	TripAssignment(Dispatcher* disp, Driver* drv, Car* car);
	void PrintAssignmentInfo() const;
};

#endif // MANAGEMENT_H_