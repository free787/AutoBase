#ifndef ADVANCED_VEHICLES_H_
#define ADVANCED_VEHICLES_H_

#include "Vehicle.h"
#include "Car.h"
#include <iostream>

// ==========================================
// [Лаб 4, П. 3] Закритий спосіб наслідування
// ==========================================
class TowTruck : private Vehicle {
private:
	double crane_capacity_;
	bool is_towing_;
public:
	TowTruck(std::string brand, double crane_cap);
	~TowTruck();
	// Оперування методами різних класів ієрархії
	void ExecuteTowing();
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
	~GPSDevice();
	void PingLocation();
};

// Клас 2: Рефрижератор (Охолодження)
class RefrigerationUnit {
protected:
	double temperature_;
public:
	RefrigerationUnit();
	~RefrigerationUnit();
	void SetTemperature(double temp);
};

// Клас 3: Авторефрижератор (Множинне наслідування від Car, GPS та Холодильника)
class RefrigeratedTruck : public Car, public GPSDevice, public RefrigerationUnit {
public:
	RefrigeratedTruck(std::string brand, std::string plate);
	~RefrigeratedTruck();
	void StartColdDelivery();
};

#endif