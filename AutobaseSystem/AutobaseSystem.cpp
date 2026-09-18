#include <iostream>
#include "Car.h"
#include "Trip.h"

using namespace std;

// 14. Оформлення за Google C++ Style Guide
int main() {
    system("chcp 65001 > nul");
    srand(time(0));

    cout << "--- Лабораторна робота: Система Автобаза ---\n\n";

    // 6. 5 об'єктів у статичній пам'яті (реальні тягачі)
    Car fleet[5] = {
        Car("DAF XF 105", "BX 4921 CE", 800.0, false, 2017, 540000, 320.5, "Хмельницький"),
        Car("MAN TGX 18.440", "BX 7390 HT", 900.0, false, 2019, 410000, 450.0, "Тернопіль"),
        Car("Volvo FH16", "BX 1204 MK", 850.0, true, 2015, 780000, 100.0, "СТО Хмельницький"),
        Car("Mercedes-Benz Actros", "BX 5582 PI", 800.0, false, 2020, 290000, 750.0, "Київ"),
        Car("Scania R500", "BX 8831 OK", 1000.0, false, 2021, 150000, 890.0, "Львів")
    };

    // 6. 5 об'єктів у динамічній пам'яті
    Car* extra_cars = new Car[5];
    extra_cars[0] = Car("Renault Magnum", "BX 2944 TA", 750.0, false, 2012, 920000, 200.0, "Вінниця");

    // 7. 2 масиви об'єктів
    Trip morning_trips[3];
    Trip evening_trips[2];

    cout << "[8] Робота з масивами об'єктів:\n";
    for (int i = 0; i < 3; i++) {
        morning_trips[i] = Trip("Міжміський", 320 + (i * 45), "Хмельницький - Київ", "Іванов О.", fleet[i], false, 5, 2);
        cout << "Рейс " << i + 1 << " додано в розклад.\n";
    }

    // 11. Використання покажчика на екземпляр
    cout << "\n[11] Покажчики:\n";
    Car* active_truck = &fleet[0];
    cout << "Пробіг обраної фури через покажчик: " << active_truck->current_mileage << " км.\n";

    cout << "\n[9] Демонстрація методів:\n";
    active_truck->Refuel(150.0);
    active_truck->Refuel(0.0, true);
    fleet[2].RequestRepair("Проблема з пневмопідвіскою");

    Car backup_truck = active_truck->GetClone();
    extra_cars[1].CopyDataFrom(backup_truck);

    morning_trips[0].StartTrip();
    morning_trips[1].StartTrip("Обережно, туман на трасі.");

    Trip detour = morning_trips[1].GetAlternativeTrip();
    evening_trips[0].MergeWithTrip(detour);

    cout << "\n[10] Взаємодія об'єктів (завершення рейсу):\n";
    morning_trips[0].CompleteTrip("Все добре, розвантажились.");

    cout << "\n[12] Робота з пам'яттю (множина значень):\n";
    active_truck->GenerateAndSortRouteDistances();

    // 5. Читання/запис
    active_truck->SaveToFile("daf_data.txt");
    morning_trips[0].SaveToFile("trip_1.txt");

    // Очищення пам'яті
    delete[] extra_cars;

    cout << "\nПрограма завершена.\n";
    return 0;
}