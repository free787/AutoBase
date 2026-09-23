#include <iostream>
#include "Car.h"
#include "Driver.h"
#include "Trip.h"
#include "Management.h"

using namespace std;

// [Лаб 3, П. 5] Функція поза межами класу, використовує об’єкт класу як параметр (передача за значенням)
void CalculateFuelExternal(Car c, double distance) {
    double needed = distance * 0.3;
    cout << "[Пункт 5] Зовнішня функція (копія). Для " << distance << " км потрібно " << needed << " л.\n";
}

// [Лаб 3, П. 6] Перевантажити функцію з п.5, яка використовує адресу об’єкту класу
void CalculateFuelExternal(Car* c, double distance) {
    double needed = distance * 0.3;
    cout << "[Пункт 6] Перевантажена функція (адреса) для авто " << c->GetBrand() << ". Потрібно " << needed << " л.\n";
}

// [Лаб 3, П. 7] Оголосити функцію типу описаного класу, яка повертатиме об’єкт класу
Car UpgradeCarExternally(Car original) {
    cout << "[Пункт 7] Функція модернізації авто (повертає об'єкт).\n";
    original.SetFuelLevel(original.GetFuelLevel() + 100.0);
    return original;
}

int main() {
    system("chcp 65001 > nul");
    srand(time(0));

    cout << "=== ЛАБОРАТОРНІ РОБОТИ 2 ТА 3: СИСТЕМА АВТОБАЗА ===\n\n";

    // --- БЛОК З ЛАБ 2 (СТАРА ДЕМОНСТРАЦІЯ АВТОПАРКУ) ---
    Car fleet[5] = {
        Car("DAF XF 105", "BX 4921 CE", 800.0, false, 2017, 540000, 320.5, "Хмельницький"),
        Car("MAN TGX 18.440", "BX 7390 HT", 900.0, false, 2019, 410000, 450.0, "Тернопіль"),
        Car("Volvo FH16", "BX 1204 MK", 850.0, true, 2015, 780000, 100.0, "СТО Хмельницький"),
        Car("Mercedes-Benz Actros", "BX 5582 PI", 800.0, false, 2020, 290000, 750.0, "Київ"),
        Car("Scania R500", "BX 8831 OK", 1000.0, false, 2021, 150000, 890.0, "Львів")
    };

    Car* extra_cars = new Car[5];
    extra_cars[0] = Car("Renault Magnum", "BX 2944 TA", 750.0, false, 2012, 920000, 200.0, "Вінниця");

    Trip morning_trips[3];
    Trip evening_trips[2];

    cout << "[Лаб 2] Робота з масивами об'єктів:\n";
    for (int i = 0; i < 3; i++) {
        morning_trips[i] = Trip("Міжміський", 320 + (i * 45), "Хмельницький - Київ", "Іванов О.", fleet[i], false, 5, 2);
        cout << "Рейс " << i + 1 << " додано в розклад.\n";
    }

    cout << "\n[Лаб 2] Покажчики:\n";
    Car* active_truck = &fleet[0];
    cout << "Пробіг обраної фури через покажчик: " << active_truck->current_mileage << " км.\n";

    cout << "\n[Лаб 2] Демонстрація методів:\n";
    active_truck->Refuel(150.0);
    active_truck->Refuel(0.0, true);
    fleet[2].RequestRepair("Проблема з пневмопідвіскою");

    Car backup_truck = active_truck->GetClone();
    extra_cars[1].CopyDataFrom(backup_truck);

    morning_trips[0].StartTrip();
    morning_trips[1].StartTrip("Обережно, туман на трасі.");

    Trip detour = morning_trips[1].GetAlternativeTrip();
    evening_trips[0].MergeWithTrip(detour);

    cout << "\n[Лаб 2] Взаємодія об'єктів (завершення рейсу):\n";
    morning_trips[0].CompleteTrip(*active_truck, "Все добре, розвантажились.");

    cout << "\n[Лаб 2] Робота з пам'яттю (множина значень):\n";
    active_truck->GenerateAndSortRouteDistances();


    // --- НОВИЙ БЛОК З ЛАБ 3 ---
    cout << "\n\n=== ФУНКЦІОНАЛ ЛАБОРАТОРНОЇ 3 ===\n\n";

    // [Лаб 3, П. 8] Три способи створення об'єктів
    cout << "[Пункт 8] Створення об'єктів трьома способами:\n";
    Car car1;                               // 1. Простий
    Car car2 = Car("DAF XF", "BX 1111", 500, false, 2020, 1000, 200, "База"); // 2. Явний
    Car* car3 = new Car("MAN TGX", "BX 2222", 500, false, 2020, 1000, 200, "База"); // 3. Скорочений

    cout << "\n";
    // [Лаб 3, П. 4] Метод класу через оголошення його як статичного
    Car::ShowTotalFleetCount();

    cout << "\n";
    // [Лаб 3, П. 5, 6, 7] Виклик зовнішніх функцій
    cout << "[Пункт 5, 6, 7] Зовнішні функції:\n";
    CalculateFuelExternal(car2, 150.0);
    CalculateFuelExternal(&car2, 250.0);
    Car upgraded_car = UpgradeCarExternally(car2);

    cout << "\n";
    // [Лаб 3, П. 13] Композиція 
    cout << "[Пункт 13] Композиція Маршруту в Рейсі:\n";
    morning_trips[0].ShowCompositionInfo();

    cout << "\n";
    // [Лаб 3, П. 11, 12] Агрегація та Асоціація
    cout << "[Пункт 11, 12] Агрегація та Асоціація (Диспетчер, Водій, Авто):\n";
    double driver_rate = 1.5;
    Driver drv1("Іванов О.", 77492, driver_rate); // Використання констант і посилань (П.2)
    Dispatcher disp("Петренко");

    disp.AssignCarToFleet(&car2); // Агрегація

    TripAssignment assignment(&disp, &drv1, &car2); // Асоціація
    assignment.PrintAssignmentInfo();

    delete[] extra_cars;
    delete car3;

    cout << "\nПрограма завершена.\n";
    return 0;
}