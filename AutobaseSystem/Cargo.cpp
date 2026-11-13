#include "Cargo.h"

using namespace std;

Cargo::Cargo() : name_("немає"), weight_(0) {}

Cargo::Cargo(string name, double weight) : name_(name), weight_(weight) {}

// Лаб 6, п. 6: два вантажі разом - назви через "+", вага сумується
Cargo Cargo::operator+(const Cargo& other) const {
	return Cargo(name_ + " + " + other.name_, weight_ + other.weight_);
}

// Лаб 6, п. 6: порівняння вантажів за вагою
bool Cargo::operator<(const Cargo& other) const {
	return weight_ < other.weight_;
}

bool Cargo::operator>(const Cargo& other) const {
	return weight_ > other.weight_;
}

ostream& operator<<(ostream& out, const Cargo& cargo) {
	out << cargo.name_ << " (" << cargo.weight_ << " кг)";
	return out;
}