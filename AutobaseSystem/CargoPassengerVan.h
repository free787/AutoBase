#ifndef CARGO_PASSENGER_VAN_H_
#define CARGO_PASSENGER_VAN_H_

#include <string>

#include "Bus.h"
#include "Car.h"

// Лаб 5, п. 1: новий похідний клас - вантажопасажирський фургон
// Лаб 5, п. 2: множинне наслідування від Car і Bus ("ромб"),
// завдяки virtual у Car і Bus у фургоні тільки одна копія Vehicle
class CargoPassengerVan : public Car, public Bus {
public:
	CargoPassengerVan();
	CargoPassengerVan(std::string brand, std::string plate, int year, int seats);
	CargoPassengerVan(const CargoPassengerVan& other);

	// Лаб 5, п. 3: віртуальний деструктор
	~CargoPassengerVan() override;

	// Лаб 5, п. 2: функції, які є і в Car, і в Bus, треба перевизначити
	void PerformWork() override;
	std::string GetTypeName() const override;
	double CalculateTripCost(double km) const override;
	void PrintType() const override;
	void Write(std::ofstream& out) const override;
	void Read(std::ifstream& in) override;

	// Лаб 5, п. 4: перевизначені функції з новою логікою
	void LoadCargo(double kg) override;
	void BoardPassengers(int count) override;

	void SetPartition(bool installed);

private:
	bool partition_;  // перегородка між салоном і вантажем
};

#endif  // CARGO_PASSENGER_VAN_H_