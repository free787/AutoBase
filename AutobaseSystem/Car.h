#ifndef CAR_H_
#define CAR_H_

#include "Vehicle.h"
#include <string>

// [Лаб 4, П. 1] Просте наслідування (Car розширює Vehicle)
class Car : public Vehicle {
private:
	bool needs_repair_;
	double max_load_capacity_;
	bool is_loaded_;
	std::string cargo_type_;

	static int total_cars_in_fleet_;

public:
	int current_mileage;
	double fuel_level;
	std::string current_location;

	// [Лаб 4, П. 6] Доступ до protected членів бази через using
	using Vehicle::fuel_capacity_;
	using Vehicle::PerformMaintenance;

	Car();
	Car(std::string brand, std::string plate, double capacity, bool repair, int year, int mileage, double fuel, std::string location);
	Car(const Car& other);
	~Car();

	static void ShowTotalFleetCount();

	void Refuel(double amount);
	void Refuel(double amount, bool fill_full_tank);
	void RequestRepair();
	void RequestRepair(std::string reason);
	Car GetClone();
	void CopyDataFrom(Car other_car);
	void GenerateAndSortRouteDistances();

	// [Лаб 4, П. 6] Демонстрація оператора глобального доступу ::
	void CustomEngineStart();

	std::string GetBrand() const { return brand_; } // Доступно, бо brand_ public в Vehicle
	double GetFuelLevel() const { return fuel_level; }
	void SetFuelLevel(double fuel) { fuel_level = fuel; }
};

#endif // CAR_H_