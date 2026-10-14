#ifndef ADVANCED_VEHICLES_H_
#define ADVANCED_VEHICLES_H_

#include "Vehicle.h"
#include "Car.h"
#include <iostream>
#include <fstream>

// ==========================================
// [Лаб 4, П. 3] Закритий спосіб наслідування
// ==========================================
class TowTruck : private Vehicle {
private:
	double crane_capacity_;
	bool is_towing_;
public:
	TowTruck(std::string brand, double crane_cap);
	~TowTruck() override;
	// Оперування методами різних класів ієрархії
	void ExecuteTowing();

	// [Лаб 5] Реалізація чисто віртуальних функцій для компіляції
	void PerformWork() override { std::cout << "Евакуатор транспортує пошкоджене авто.\n"; }
	void WriteToFile(std::ofstream& out) const override { out << brand_ << "\n"; }
	void ReadFromFile(std::ifstream& in) override {}
};

// ==========================================
// [Лаб 4, П. 4] Множинне наслідування (3 нових класи)
// ==========================================
// Клас 1: GPS Модуль
class GPSDevice {
protected:
	std::string coordinates_;
public:
	GPSDevice();
	virtual ~GPSDevice();
	void PingLocation();
};

// Клас 2: Рефрижератор (Охолодження)
class RefrigerationUnit {
protected:
	double temperature_;
public:
	RefrigerationUnit();
	virtual ~RefrigerationUnit();
	void SetTemperature(double temp);
};

// Клас 3: Авторефрижератор (Множинне наслідування від Car, GPS та Холодильника)
class RefrigeratedTruck : public Car, public GPSDevice, public RefrigerationUnit {
public:
	RefrigeratedTruck(std::string brand, std::string plate);
	~RefrigeratedTruck() override;

	void StartColdDelivery();

	// [Лаб 5, П. 4] Віртуальні функції
	void PerformWork() override { std::cout << "Рефрижератор везе заморожені продукти.\n"; }
	void PrintType() const override { std::cout << "Тип: RefrigeratedTruck (Множинне наслідування)\n"; }
};

#endif