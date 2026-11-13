#pragma once
#ifndef CARGO_H_
#define CARGO_H_

#include <iostream>
#include <string>

// Лаб 6, п. 6: користувацький клас Cargo (вантаж),
// який використовується як параметр шаблону TripStats<Cargo>
class Cargo {
public:
	Cargo();
	Cargo(std::string name, double weight);

	std::string GetName() const { return name_; }
	double GetWeight() const { return weight_; }

	// Лаб 6, п. 6: оператори, потрібні шаблону TripStats
	Cargo operator+(const Cargo& other) const;  // разом два вантажі
	bool operator<(const Cargo& other) const;   // легший за вагою
	bool operator>(const Cargo& other) const;   // важчий за вагою

	// Виведення вантажу через cout << cargo
	friend std::ostream& operator<<(std::ostream& out, const Cargo& cargo);

private:
	std::string name_;
	double weight_;  // вага, кг
};

#endif  // CARGO_H_