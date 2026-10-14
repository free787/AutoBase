#include <iostream>
#include <string>
#include "Vehicle.h"
#include "Car.h"
#include "AdvancedVehicles.h"
#include "ServiceFunctions.h"
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

// Демонстрація Лаб 2, 3, 4 (Повністю збережено з коментарями)
void RunOldLabsDemo() {
    cout << "\n=== ЗАПУСК ДЕМОНСТРАЦІЇ ЛАБОРАТОРНИХ 2, 3 ТА 4 ===\n";

    // [Лаб 3, П. 9] Розміщення об'єктів у статичній пам'яті (статичний масив)
    Car fleet[3] = {
        Car("DAF XF 105", "BX 4921 CE", 800.0, false, 2017, 540000, 320.5, "Хмельницький"),
        Car("MAN TGX 18.440", "BX 7390 HT", 900.0, false, 2019, 410000, 450.0, "Тернопіль"),
        Car("Volvo FH16", "BX 1204 MK", 850.0, false, 2015, 780000, 100.0, "СТО Хмельницький")
    };

    // [Лаб 3, П. 13] Композиція Маршруту в Рейсі
    Trip morning_trip("Міжміський", 320.0, "Хмельницький - Київ", "Іванов О.", fleet[0], false, 5, 2);
    morning_trip.ShowCompositionInfo();

    // [Лаб 3, П. 11, 12] Агрегація та Асоціація
    double rate = 1.5;
    Driver drv1("Іванов О.", 77492, rate);
    Dispatcher disp("Петренко");
    disp.AssignCarToFleet(&fleet[0]);
    TripAssignment assignment(&disp, &drv1, &fleet[0]);
    assignment.PrintAssignmentInfo();

    CalculateFuelExternal(fleet[1], 150.0);

    cout << "\n--- ЗАКРИТЕ НАСЛІДУВАННЯ (Private) [Лаб 4, П. 3, 8] ---\n";
    {
        TowTruck rescuer("Scania", 5000);
        rescuer.ExecuteTowing();
    }

    cout << "=== ДЕМОНСТРАЦІЮ ЗАВЕРШЕНО ===\n\n";
}

// [Лаб 5, П. 7] Ім'я створюваного файлу є параметром командного рядка (argc, argv)
int main(int argc, char* argv[]) {
    system("chcp 65001 > nul");

    string filename = "default_data.txt";
    if (argc > 1) {
        filename = argv[1];
        cout << "Використовується файл з командного рядка: " << filename << "\n";
    }
    else {
        cout << "Параметр файлу не задано. Використовується стандартний: " << filename << "\n";
    }

    Vehicle* active_vehicle = nullptr; // Вказівник для поліморфізму
    int choice = -1;

    // [Лаб 5, П. 8] Можливість вибору створення та знищення об'єкта засобами меню
    while (choice != 0) {
        cout << "\n=== МЕНЮ СИСТЕМИ (ЛАБ 5) ===\n";
        cout << "1. Створити об'єкт Car (Вантажівка)\n";
        cout << "2. Створити об'єкт RefrigeratedTruck (Множинне наслідування)\n";
        cout << "3. Знищити поточний об'єкт\n";
        cout << "4. [Поліморфізм] Зміна форми та виклик методів (П. 9, 10, 11)\n";
        cout << "5. [Масиви] Тестування статичних/динамічних масивів по 5 шт (П. 5, 6)\n";
        cout << "6. [Файли] Робота з файлом через Service (П. 7)\n";
        cout << "7. ЗАПУСТИТИ КОД СТАРИХ ЛАБОРАТОРНИХ (2, 3, 4)\n";
        cout << "0. Вихід\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
        case 1:
            if (active_vehicle) delete active_vehicle;
            active_vehicle = new Car("MAN", "BX1111", 500, false, 2020, 1000, 200, "База");
            cout << "Вантажівку створено.\n";
            break;
        case 2:
            if (active_vehicle) delete active_vehicle;
            active_vehicle = new RefrigeratedTruck("Volvo Ice", "BX2222");
            cout << "Рефрижератор створено.\n";
            break;
        case 3:
            if (active_vehicle) {
                delete active_vehicle;
                active_vehicle = nullptr;
                cout << "Об'єкт знищено.\n";
            }
            else cout << "Немає об'єкта для знищення.\n";
            break;
        case 4:
            if (active_vehicle) {
                // [Лаб 5, П. 10] Пізнє зв'язування
                cout << "\n--- Пізнє (динамічне) зв'язування ---\n";
                active_vehicle->PrintType();

                // [Лаб 5, П. 11] Обхід віртуальності / Раннє зв'язування
                cout << "\n--- Раннє (статичне) зв'язування / Обхід віртуальності (П. 11) ---\n";
                active_vehicle->Vehicle::PrintType();

                // [Лаб 5, П. 9] Зміна форми об'єкта із застосуванням принципу поліморфізму
                cout << "\n--- Зміна форми об'єкта (П. 9) ---\n";
                Vehicle* temp = new Car("Фура", "АА0000", 500, false, 2010, 1000, 300, "Київ");
                temp->PerformWork();
                delete temp;
                temp = new RefrigeratedTruck("Реф-Змінний", "ВВ1111");
                temp->PerformWork();
                delete temp;
            }
            else cout << "Створіть об'єкт (Пункт 1 або 2)!\n";
            break;
        case 5: {
            // [Лаб 5, П. 5, 6] 2 типи об'єктів по 5, відловлювання помилок
            cout << "\n--- Статичний масив (5 шт) ---\n";
            Car stat_fleet[5];
            int s_size = 5;
            stat_fleet[0].fuel_level = 50; stat_fleet[1].fuel_level = 150;
            Service_Static(stat_fleet, s_size, 100.0);

            cout << "\n--- Динамічний масив (5 шт) ---\n";
            Car** dyn_fleet = new Car * [5];
            for (int i = 0; i < 5; i++) dyn_fleet[i] = new Car();
            int d_size = 5;
            dyn_fleet[0]->fuel_level = 30; dyn_fleet[1]->fuel_level = 200;
            Service_Dynamic(dyn_fleet, d_size, 100.0);

            for (int i = 0; i < d_size; i++) delete dyn_fleet[i];
            delete[] dyn_fleet;
            break;
        }
        case 6:
            if (active_vehicle) Service(active_vehicle, filename);
            else cout << "Створіть об'єкт!\n";
            break;
        case 7:
            RunOldLabsDemo(); // Виклик всього старого коду!
            break;
        }
    }

    if (active_vehicle) delete active_vehicle;
    return 0;
}