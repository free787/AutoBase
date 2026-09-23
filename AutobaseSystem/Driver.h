#ifndef DRIVER_H_
#define DRIVER_H_

#include <string>

class Driver {
private:
	std::string name_;

	// [Лаб 3, П. 2] Поля як константа і посилання
	const int license_id_;
	double& base_salary_rate_;

public:
	// [Лаб 3, П. 2] Конструктор за допомогою списку ініціалізації
	Driver(std::string name, int license, double& salary_rate);
	~Driver();
	std::string GetName() const { return name_; }
};

#endif // DRIVER_H_