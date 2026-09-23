#ifndef CAR_H_
#define CAR_H_

#include <string>

class Car {
private:
	std::string brand_;
	std::string plate_number_;
	double fuel_capacity_;
	bool needs_repair_;
	int year_built_;

	// [Лаб 3, П. 4] Статичне поле класу
	static int total_cars_in_fleet_;

public:
	int current_mileage;
	double fuel_level;
	std::string current_location;

	// [Лаб 3, П. 1] Конструктор без параметрів
	Car();
	// Конструктор з параметрами (збережений з Лаб 2)
	Car(std::string brand, std::string plate, double capacity, bool repair, int year, int mileage, double fuel, std::string location);
	// [Лаб 3, П. 1] Конструктор копіювання
	Car(const Car& other);

	// [Лаб 3, П. 3] Деструктор
	~Car();

	// [Лаб 3, П. 4] Статичний метод
	static void ShowTotalFleetCount();

	// Методи з Лаб 2
	void Refuel(double amount);
	void Refuel(double amount, bool fill_full_tank);
	void RequestRepair();
	void RequestRepair(std::string reason);
	Car GetClone();
	void CopyDataFrom(Car other_car);
	void SaveToFile(std::string filename);
	void LoadFromFile(std::string filename);
	void GenerateAndSortRouteDistances();

	std::string GetBrand() const { return brand_; }
	double GetFuelLevel() const { return fuel_level; }
	void SetFuelLevel(double fuel) { fuel_level = fuel; }
};

#endif // CAR_H_