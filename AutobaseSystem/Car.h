#ifndef CAR_H_
#define CAR_H_

#include <string>

#include "Vehicle.h"

// Лаб 4, п. 1: Car - вантажівка, похідний клас від Vehicle
// Лаб 5, п. 2: віртуальне наслідування
class Car : virtual public Vehicle {
public:
    int current_mileage;
    double fuel_level;
    std::string current_location;

    // Лаб 4, п. 6: доступ до protected членів бази через using
    using Vehicle::fuel_capacity_;
    using Vehicle::PerformMaintenance;

    Car();
    Car(std::string brand, std::string plate, double capacity, bool repair,
        int year, int mileage, double fuel, std::string location);
    Car(const Car& other);
    Car& operator=(const Car& other) = default;

    // Лаб 5, п. 3: віртуальний деструктор
    ~Car() override;

    // Лаб 5, п. 4: перевизначені віртуальні функції
    void PerformWork() override;
    std::string GetTypeName() const override;
    double CalculateTripCost(double km) const override;
    void PrintType() const override;

    // Лаб 5, п. 7: запис і читання з файлу
    void Write(std::ofstream& out) const override;
    void Read(std::ifstream& in) override;

    // Лаб 5, п. 4: власна віртуальна функція Car
    virtual void LoadCargo(double kg);

    // Лаб 5, п. 10: невіртуальний метод з такою ж назвою, як у Vehicle
    void DisplayVehicleInfo() const;

    // Лаб 6, п. 1: унарні оператори ++ і -- (префіксні та постфіксні)
    Car& operator++();     // ++car - долити 10 л пального
    Car operator++(int);   // car++ - долити 10 л пального
    Car& operator--();     // --car - витратити 10 л пального
    Car operator--(int);   // car-- - витратити 10 л пального

    // Лаб 6, п. 4: шаблонна функція-член класу.
    // Працює з будь-яким числовим типом: int, double, float
    template <typename T>
    void AddFuel(T amount) {
        fuel_level += amount;
        std::cout << brand_ << ": заправлено " << amount << " л, в баку "
            << fuel_level << " л\n";
    }

    // Методи з лабораторних 2-4
    static void ShowTotalFleetCount();
    void Refuel(double amount);
    void Refuel(double amount, bool fill_full_tank);
    void RequestRepair();
    void RequestRepair(std::string reason);
    Car GetClone();
    void CopyDataFrom(Car other_car);
    void GenerateAndSortRouteDistances();
    void CustomEngineStart();
    std::string GetBrand() const { return brand_; }
    double GetFuelLevel() const { return fuel_level; }
    void SetFuelLevel(double fuel) { fuel_level = fuel; }

protected:
    bool needs_repair_;
    double max_load_;      // максимальний вантаж, кг
    double cargo_weight_;  // поточний вантаж, кг
    static int total_cars_in_fleet_;
};

#endif  // CAR_H_