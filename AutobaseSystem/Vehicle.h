#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <string>

// [Лаб 4, П. 1] Ієрархія класів. Базовий клас Vehicle (має 8 полів)
class Vehicle {
public:
	// [Лаб 4, П. 2] Public дані
	std::string brand_;
	std::string plate_number_;
	bool is_active_;

	// [Лаб 4, П. 5] Конструктор базового класу (більше 5 аргументів)
	Vehicle();
	Vehicle(std::string brand, std::string plate, bool active, double capacity, int year, double weight, std::string vin, int power);
	Vehicle(const Vehicle& other);
	virtual ~Vehicle(); // [Лаб 4, П. 3, 7] Деструктор

	// [Лаб 4, П. 2] Public метод
	void StartEngine();
	// [Лаб 4, П. 5] Зчитування та виведення полів на екран
	void DisplayVehicleInfo() const;

protected:
	// [Лаб 4, П. 2] Protected дані
	double fuel_capacity_;
	int year_built_;
	double weight_;

	// [Лаб 4, П. 2] Protected метод
	void PerformMaintenance();

private:
	// [Лаб 4, П. 2] Private дані
	std::string vin_code_;
	int engine_power_;

	// [Лаб 4, П. 2] Private метод
	void LogInternalSystem();
};

#endif // VEHICLE_H_