#ifndef BUS_H_
#define BUS_H_

#include <string>

#include "Vehicle.h"

// Лаб 5, п. 1: новий похідний клас Bus - автобус
// Лаб 5, п. 2: віртуальне наслідування
class Bus : virtual public Vehicle {
public:
	Bus();
	Bus(std::string brand, std::string plate, int year, int seats);
	Bus(const Bus& other);

	// Лаб 5, п. 3: віртуальний деструктор
	~Bus() override;

	// Лаб 5, п. 4: перевизначені віртуальні функції
	void PerformWork() override;
	std::string GetTypeName() const override;
	double CalculateTripCost(double km) const override;
	void PrintType() const override;

	// Лаб 5, п. 7: запис і читання з файлу
	void Write(std::ofstream& out) const override;
	void Read(std::ifstream& in) override;

	// Лаб 5, п. 4: власна віртуальна функція Bus
	virtual void BoardPassengers(int count);

	// Лаб 6, п. 1: унарні оператори ++ і -- (префіксні та постфіксні)
	Bus& operator++();     // ++bus - посадити одного пасажира
	Bus operator++(int);   // bus++ - посадити одного пасажира
	Bus& operator--();     // --bus - висадити одного пасажира
	Bus operator--(int);   // bus-- - висадити одного пасажира

	int GetPassengers() const { return passengers_; }

protected:
	int seats_;       // кількість місць
	int passengers_;  // кількість пасажирів у салоні
};

#endif  // BUS_H_