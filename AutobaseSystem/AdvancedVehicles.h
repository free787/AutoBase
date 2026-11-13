#ifndef ADVANCED_VEHICLES_H_
#define ADVANCED_VEHICLES_H_

#include <string>

#include "Car.h"
#include "Vehicle.h"

// Лаб 4, п. 3: закрите наслідування (евакуатор)
class TowTruck : private Vehicle {
public:
    TowTruck(std::string brand, double crane_capacity);
    ~TowTruck() override;
    void ExecuteTowing();

    // Лаб 5, п. 1: реалізація чисто віртуальних функцій
    void PerformWork() override;
    std::string GetTypeName() const override;

private:
    double crane_capacity_;
};

// Лаб 4, п. 4: GPS-модуль
class GPSDevice {
public:
    GPSDevice();
    // Лаб 5, п. 3: віртуальний деструктор
    virtual ~GPSDevice();
    // Лаб 5, п. 4: віртуальна функція
    virtual void PingLocation() const;

protected:
    std::string coordinates_;
};

// Лаб 4, п. 4: холодильна установка
class RefrigerationUnit {
public:
    RefrigerationUnit();
    // Лаб 5, п. 3: віртуальний деструктор
    virtual ~RefrigerationUnit();
    // Лаб 5, п. 4: віртуальна функція
    virtual void SetTemperature(double temp);

protected:
    double temperature_;
};

// Лаб 4, п. 4: множинне наслідування (рефрижератор)
class RefrigeratedTruck : public Car,
    public GPSDevice,
    public RefrigerationUnit {
public:
    RefrigeratedTruck(std::string brand, std::string plate, int year = 2023);

    // Лаб 5, п. 3: віртуальний деструктор
    ~RefrigeratedTruck() override;

    void StartColdDelivery();

    // Лаб 5, п. 4: перевизначені віртуальні функції
    void PerformWork() override;
    std::string GetTypeName() const override;
    double CalculateTripCost(double km) const override;
    void PrintType() const override;
    void LoadCargo(double kg) override;
    void SetTemperature(double temp) override;

    // Лаб 5, п. 7: запис і читання з файлу
    void Write(std::ofstream& out) const override;
    void Read(std::ifstream& in) override;
};

#endif  // ADVANCED_VEHICLES_H_