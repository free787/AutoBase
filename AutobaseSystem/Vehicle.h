#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <fstream>
#include <iostream>
#include <string>

// Лаб 4, п. 1: базовий клас ієрархії
// Лаб 5, п. 1: абстрактний клас (має чисто віртуальні функції)
class Vehicle {
public:
    // Лаб 4, п. 2: public дані
    std::string brand_;
    std::string plate_number_;
    bool is_active_;

    Vehicle();
    // Лаб 4, п. 5: конструктор з більше ніж 5 параметрами
    Vehicle(std::string brand, std::string plate, bool active, double capacity,
        int year, double weight, std::string vin, int power);
    Vehicle(const Vehicle& other);
    Vehicle& operator=(const Vehicle& other) = default;

    // Лаб 5, п. 3: віртуальний деструктор
    virtual ~Vehicle();

    void StartEngine();
    // Лаб 5, п. 10: невіртуальний метод (раннє зв'язування)
    void DisplayVehicleInfo() const;
    int GetYear() const { return year_built_; }

    // Лаб 5, п. 1: чисто віртуальні функції
    virtual void PerformWork() = 0;
    virtual std::string GetTypeName() const = 0;

    // Лаб 5, п. 4: віртуальні функції
    virtual double CalculateTripCost(double km) const;
    virtual void PrintType() const;

    // Лаб 5, п. 7: запис у файл і читання з файлу
    virtual void Write(std::ofstream& out) const;
    virtual void Read(std::ifstream& in);

protected:
    // Лаб 4, п. 2: protected дані і метод
    double fuel_capacity_;
    int year_built_;
    double weight_;
    void PerformMaintenance();

private:
    // Лаб 4, п. 2: private дані і метод
    std::string vin_code_;
    int engine_power_;
    void LogInternalSystem();
};

#endif  // VEHICLE_H_