#include "Driver.h"
#include <iostream>

using namespace std;

// [Лаб 3, П. 2] Реалізація списку ініціалізації
Driver::Driver(string name, int license, double& salary_rate)
    : name_(name), license_id_(license), base_salary_rate_(salary_rate) {
    cout << "[Driver] Водій " << name_ << " прийнятий.\n";
}

Driver::~Driver() {
    cout << "[Деструктор] Водій " << name_ << " пішов.\n";
}