#pragma once
#ifndef CAR_H_
#define CAR_H_

#include <string>

// 1. Користувацький клас 1
class Car {
private:
	// 2. 5 приватних елементів
	std::string brand_;
	std::string plate_number_;
	double fuel_capacity_;
	bool needs_repair_;
	int year_built_;

public:
	// 2. 3 загальні елементи
	int current_mileage;
	double fuel_level;
	std::string current_location;

	Car();
	Car(std::string brand, std::string plate, double capacity, bool repair, int year, int mileage, double fuel, std::string location);

	// 4. 6 методів
	void Refuel(double amount);
	void Refuel(double amount, bool fill_full_tank);
	void RequestRepair();
	void RequestRepair(std::string reason);
	Car GetClone();
	void CopyDataFrom(Car other_car);

	// 5. Робота з файлами
	void SaveToFile(std::string filename);
	void LoadFromFile(std::string filename);

	// 12. Робота з динамічною пам'яттю
	void GenerateAndSortRouteDistances();
};

#endif // CAR_H_