#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <new>
#include <stdexcept>
#include <string>

#include "AdvancedVehicles.h"
#include "Bus.h"
#include "Car.h"
#include "Cargo.h"
#include "CargoPassengerVan.h"
#include "Driver.h"
#include "FunctorDemo.h"
#include "Management.h"
#include "RepairRequest.h"
#include "Route.h"
#include "ServiceFunctions.h"
#include "StlDemo.h"
#include "Trip.h"
#include "TripStats.h"
#include "Vehicle.h"

using namespace std;

// Пауза, щоб встигнути прочитати результат
void Pause() {
    cout << "\nНатисніть Enter, щоб повернутися в меню...";
    cin.ignore(1000, '\n');
    cin.get();
}

// ==================== Лабораторні 2-4 ====================

// Лаб 3, п. 5: функція поза класом, об'єкт передається за значенням
void CalculateFuelExternal(Car car, double distance) {
    cout << "Для " << car.GetBrand() << " на " << distance << " км потрібно "
        << distance * 0.3 << " л\n";
}

// Лаб 3, п. 6: перевантажена функція, передається адреса об'єкта
void CalculateFuelExternal(Car* car, double distance) {
    cout << "Для " << car->GetBrand() << " (за адресою) на " << distance
        << " км потрібно " << distance * 0.3 << " л\n";
}

// Лаб 3, п. 7: функція повертає об'єкт класу
Car UpgradeCarExternally(Car original) {
    cout << "Модернізація авто " << original.GetBrand() << "\n";
    original.SetFuelLevel(original.GetFuelLevel() + 100.0);
    return original;
}

void RunOldLabsDemo() {
    cout << "\n===== Лабораторні 2-4 =====\n";

    // Лаб 3, п. 9: статичний масив об'єктів
    Car fleet[3] = {
        Car("DAF XF 105", "BX 4921 CE", 800.0, false, 2017, 540000, 320.5,
            "Хмельницький"),
        Car("MAN TGX", "BX 7390 HT", 900.0, false, 2019, 410000, 450.0,
            "Тернопіль"),
        Car("Volvo FH16", "BX 1204 MK", 850.0, false, 2015, 780000, 100.0,
            "Вінниця") };

    // Лаб 3, п. 13: композиція (маршрут всередині рейсу)
    Trip trip("Міжміський", 320.0, "Хмельницький - Київ", "Іванов О.",
        fleet[0], false, 5, 2);
    trip.ShowCompositionInfo();

    // Лаб 3, п. 11, 12: асоціація та агрегація
    double rate = 1.5;
    Driver driver("Іванов О.", 77492, rate);
    Dispatcher dispatcher("Петренко");
    dispatcher.AssignCarToFleet(&fleet[0]);
    TripAssignment assignment(&dispatcher, &driver, &fleet[0]);
    assignment.PrintAssignmentInfo();

    // Лаб 3, п. 5, 6, 7
    CalculateFuelExternal(fleet[1], 150.0);
    CalculateFuelExternal(&fleet[2], 150.0);
    Car upgraded = UpgradeCarExternally(fleet[2]);
    cout << "Пального після модернізації: " << upgraded.GetFuelLevel()
        << " л\n";

    // Лаб 4, п. 3: закрите наслідування
    TowTruck tow("Scania", 5000);
    tow.ExecuteTowing();

    cout << "\nВихід з функції - деструктори:\n";
}

// ==================== Лабораторна 5 ====================

// Лаб 5, п. 2: віртуальне наслідування
void DemoVirtualInheritance() {
    cout << "\n===== Пункт 2: віртуальне наслідування =====\n";
    cout << "Створюємо фургон (Car + Bus). Конструктор Vehicle буде один:\n";
    CargoPassengerVan van("Ford Transit", "BX 1010 TT", 2021, 8);

    // Адреса Vehicle через Car і через Bus однакова - копія одна
    Vehicle* through_car = static_cast<Car*>(&van);
    Vehicle* through_bus = static_cast<Bus*>(&van);
    cout << "\nАдреса Vehicle через Car: " << through_car << "\n";
    cout << "Адреса Vehicle через Bus: " << through_bus << "\n";
    if (through_car == through_bus) {
        cout << "Адреси однакові - у фургоні одна копія Vehicle\n\n";
    }

    // Без virtual тут була б помилка (дві копії brand_)
    van.brand_ = "Ford Transit Kombi";
    van.LoadCargo(1000);
    van.BoardPassengers(3);
    van.LoadCargo(1000);
    van.SetPartition(false);
    van.BoardPassengers(2);
    van.PerformWork();

    cout << "\nВихід з функції - деструктори:\n";
}

// Лаб 5, п. 3: віртуальний і невіртуальний деструктор
void DemoDestructors() {
    cout << "\n===== Пункт 3: віртуальні і невіртуальні деструктори =====\n";

    cout << "\n1) Віртуальний деструктор, delete через Vehicle*:\n";
    Vehicle* vehicle = new CargoPassengerVan("Renault Master", "BX 2020 KM",
        2020, 9);
    delete vehicle;
    cout << "=> Спрацювали всі деструктори\n";

    cout << "\n2) Невіртуальний деструктор, delete через RepairRequest*:\n";
    RepairRequest* request = new UrgentRepairRequest("BX 4921 CE", 5);
    request->Describe();
    delete request;
    cout << "=> Спрацював тільки деструктор RepairRequest,\n"
        << "   пам'ять під запчастини не звільнилась (витік пам'яті)\n";

    cout << "\n3) Той самий об'єкт, delete через UrgentRepairRequest*:\n";
    UrgentRepairRequest* urgent = new UrgentRepairRequest("BX 7390 HT", 3);
    delete urgent;
    cout << "=> Спрацювали обидва деструктори\n";
}

// Лаб 5, п. 5, 6: статичні і динамічні об'єкти
void DemoArrays() {
    cout << "\n===== Пункт 5: 5 статичних об'єктів =====\n";
    // Лаб 5, п. 5: статичні об'єкти
    Car static_cars[5] = {
        Car("DAF XF", "BX 0001 AA", 800, false, 2012, 540000, 320, "Київ"),
        Car("MAN TGX", "BX 0002 AA", 900, false, 2019, 410000, 450, "Львів"),
        Car("Volvo FH16", "BX 0003 AA", 850, false, 2009, 780000, 100, "Рівне"),
        Car("Scania R450", "BX 0004 AA", 700, false, 2021, 120000, 380, "Луцьк"),
        Car("Iveco", "BX 0005 AA", 750, false, 2014, 600000, 210, "Одеса") };
    int static_size = 5;

    // Лаб 5, п. 6: Service_Static (видаляємо авто до 2015 року)
    cout << "\n--- Service_Static: видаляємо авто, випущені до 2015 р. ---\n";
    try {
        Service_Static(static_cars, static_size, 2015);
        for (int i = 0; i < static_size; i++) {
            cout << "  Залишилось: " << static_cars[i].brand_ << "\n";
        }
    }
    catch (const exception& e) {
        cout << "Помилка: " << e.what() << "\n";
    }

    // Лаб 5, п. 6: виключні ситуації Service_Static
    cout << "\n--- Помилки Service_Static ---\n";
    try {
        Service_Static(nullptr, static_size, 2015);
    }
    catch (const invalid_argument& e) {
        cout << "  [invalid_argument] " << e.what() << "\n";
    }
    try {
        int wrong_size = -3;
        Service_Static(static_cars, wrong_size, 2015);
    }
    catch (const out_of_range& e) {
        cout << "  [out_of_range] " << e.what() << "\n";
    }
    try {
        Service_Static(static_cars, static_size, 2077);
    }
    catch (const domain_error& e) {
        cout << "  [domain_error] " << e.what() << "\n";
    }

    cout << "\n===== Пункт 5: 5 динамічних об'єктів =====\n";
    // Лаб 5, п. 5: динамічні об'єкти
    Vehicle** dynamic_cars = new Vehicle * [5];
    dynamic_cars[0] = new Car("Mercedes Actros", "BX 1111 AA", 700, false, 2016,
        300000, 250, "Київ");
    dynamic_cars[1] = new Bus("Bogdan A092", "BX 2222 AA", 2008, 30);
    dynamic_cars[2] = new CargoPassengerVan("Ford Transit", "BX 3333 AA", 2020,
        8);
    dynamic_cars[3] = new RefrigeratedTruck("Volvo Ice", "BX 4444 AA", 2011);
    dynamic_cars[4] = new Bus("Neoplan", "BX 5555 AA", 2022, 50);
    int dynamic_size = 5;

    // Лаб 5, п. 5: виключні ситуації роботи з динамічною пам'яттю
    cout << "\n--- Помилки роботи з динамічною пам'яттю ---\n";
    // Помилка 1: не вистачає пам'яті
    try {
        long long huge_size = 1000000000000LL;
        double* huge_array = new double[huge_size];
        huge_array[0] = 1;
        delete[] huge_array;
    }
    catch (const bad_alloc& e) {
        cout << "  [bad_alloc] Не вдалося виділити пам'ять: " << e.what() << "\n";
    }
    // Помилка 2: індекс за межами масиву
    try {
        GetVehicle(dynamic_cars, dynamic_size, 10)->PerformWork();
    }
    catch (const out_of_range& e) {
        cout << "  [out_of_range] " << e.what() << "\n";
    }
    // Помилка 3: звернення до видаленого об'єкта
    delete dynamic_cars[1];
    dynamic_cars[1] = nullptr;
    try {
        GetVehicle(dynamic_cars, dynamic_size, 1)->PerformWork();
    }
    catch (const logic_error& e) {
        cout << "  [logic_error] " << e.what() << "\n";
    }

    // Лаб 5, п. 6: виключні ситуації Service_Dinamic
    cout << "\n--- Помилки Service_Dinamic ---\n";
    try {
        Service_Dinamic(dynamic_cars, dynamic_size, 2015);
    }
    catch (const logic_error& e) {
        cout << "  [logic_error] " << e.what() << "\n";
    }
    try {
        int wrong_size = 500;
        Service_Dinamic(dynamic_cars, wrong_size, 2015);
    }
    catch (const out_of_range& e) {
        cout << "  [out_of_range] " << e.what() << "\n";
    }
    try {
        Service_Dinamic(dynamic_cars, dynamic_size, 1800);
    }
    catch (const domain_error& e) {
        cout << "  [domain_error] " << e.what() << "\n";
    }

    // Повертаємо видалений автобус на місце
    dynamic_cars[1] = new Bus("Bogdan A092", "BX 2222 AA", 2008, 30);

    // Лаб 5, п. 6: Service_Dinamic (видаляємо авто до 2015 року)
    cout << "\n--- Service_Dinamic: видаляємо авто, випущені до 2015 р. ---\n";
    try {
        Service_Dinamic(dynamic_cars, dynamic_size, 2015);
        for (int i = 0; i < dynamic_size; i++) {
            cout << "  Залишилось: " << dynamic_cars[i]->GetTypeName() << " "
                << dynamic_cars[i]->brand_ << "\n";
        }
    }
    catch (const exception& e) {
        cout << "Помилка: " << e.what() << "\n";
    }

    cout << "\nЗвільняємо динамічну пам'ять:\n";
    for (int i = 0; i < dynamic_size; i++) {
        delete dynamic_cars[i];
    }
    delete[] dynamic_cars;

    cout << "\nВихід з функції - знищуються статичні об'єкти:\n";
}

// Лаб 5, п. 7: виключні ситуації роботи з файлами
void DemoFiles() {
    cout << "\n===== Пункт 7: помилки при роботі з файлами =====\n";
    Car car("MAN TGX", "BX 7390 HT", 900, false, 2019, 410000, 450, "Тернопіль");
    Bus bus("Neoplan", "BX 0707 AT", 2018, 50);

    cout << "\n1) Порожнє ім'я файлу:\n";
    Service(car, "");

    cout << "\n2) Файл не .txt:\n";
    Service(car, "data.doc");

    cout << "\n3) Папки не існує (не відкривається для запису):\n";
    Service(car, "no_folder/data.txt");

    cout << "\n4) Файлу не існує (не відкривається для читання):\n";
    remove("no_file.txt");
    Service(car, "no_file.txt", true);

    cout << "\n5) Порожній файл:\n";
    ofstream empty_file("empty.txt");
    empty_file.close();
    Service(car, "empty.txt", true);

    cout << "\n6) У файлі об'єкт іншого класу:\n";
    Service(bus, "bus.txt");
    Service(car, "bus.txt", true);

    cout << "\n7) Пошкоджені дані у файлі:\n";
    ofstream bad_file("bad.txt");
    bad_file << "Car\nMAN\nBX 1111\nтак\n";
    bad_file.close();
    Car test_car("Test", "BX 0000", 100, false, 2020, 0, 0, "База");
    Service(test_car, "bad.txt", true);

    cout << "\nВихід з функції - деструктори:\n";
}

// Лаб 5, п. 9: спосіб 2 - через посилання на базовий клас
void SendOnTrip(Vehicle& vehicle) {
    vehicle.PrintType();
    vehicle.PerformWork();
    cout << "  Вартість 100 км: " << vehicle.CalculateTripCost(100) << " грн\n";
}

// Лаб 5, п. 9: поліморфізм трьома способами і зміна форми об'єкта
void DemoPolymorphism() {
    cout << "\n===== Пункт 9: поліморфізм трьома способами =====\n";
    Car truck("DAF XF", "BX 4921 CE", 800, false, 2017, 540000, 320, "Київ");
    Bus bus("Bogdan A092", "BX 2222 AB", 2015, 30);
    CargoPassengerVan van("Ford Transit", "BX 3333 AC", 2020, 8);
    truck.LoadCargo(10000);
    bus.BoardPassengers(25);
    van.BoardPassengers(4);
    van.LoadCargo(500);

    // Спосіб 1: через вказівник на базовий клас
    cout << "\nСпосіб 1 - через вказівник:\n";
    Vehicle* pointer = &truck;
    pointer->PerformWork();
    pointer = &bus;
    pointer->PerformWork();

    // Спосіб 2: через посилання на базовий клас
    cout << "\nСпосіб 2 - через посилання:\n";
    SendOnTrip(van);
    SendOnTrip(truck);

    // Спосіб 3: через масив вказівників на базовий клас
    cout << "\nСпосіб 3 - через масив вказівників:\n";
    Vehicle* convoy[3] = { &truck, &bus, &van };
    for (int i = 0; i < 3; i++) {
        cout << convoy[i]->GetTypeName() << ": 100 км = "
            << convoy[i]->CalculateTripCost(100) << " грн\n";
    }

    // Лаб 5, п. 9, 10: зміна форми об'єкта (один вказівник - різні класи)
    cout << "\n===== Зміна форми об'єкта =====\n";
    Vehicle* shape = new Car("Iveco Daily", "BX 9000 AA", 300, false, 2018,
        50000, 80, "База");
    shape->PrintType();
    shape->PerformWork();
    delete shape;

    shape = new Bus("Ataman", "BX 9000 AA", 2019, 30);
    shape->PrintType();
    shape->PerformWork();
    delete shape;

    shape = new RefrigeratedTruck("Volvo Ice", "BX 9000 AA", 2022);
    shape->PrintType();
    shape->PerformWork();
    delete shape;

    cout << "\nВихід з функції - деструктори:\n";
}

// Лаб 5, п. 10, 11: раннє і пізнє зв'язування, обхід віртуальності
void DemoBinding() {
    cout << "\n===== Пункт 10: пізнє і раннє зв'язування =====\n";
    Car truck("Scania R450", "BX 5555 AB", 700, false, 2021, 120000, 380, "Київ");
    truck.LoadCargo(12000);
    Vehicle* pointer = &truck;

    // Лаб 5, п. 10: пізнє зв'язування (віртуальна функція через вказівник)
    cout << "\nПізнє зв'язування (функція обирається під час роботи):\n";
    pointer->PrintType();

    // Лаб 5, п. 10: раннє зв'язування (виклик через сам об'єкт)
    cout << "\nРаннє зв'язування (функція обирається при компіляції):\n";
    truck.PrintType();

    // Невіртуальний метод через вказівник - викликається версія Vehicle
    cout << "\nНевіртуальний метод через Vehicle*:\n";
    pointer->DisplayVehicleInfo();
    cout << "Той самий метод через об'єкт Car:\n";
    truck.DisplayVehicleInfo();

    // Лаб 5, п. 11: обхід механізму віртуальних функцій
    cout << "\n===== Пункт 11: обхід віртуальних функцій =====\n";
    cout << "pointer->CalculateTripCost(100) = "
        << pointer->CalculateTripCost(100) << " грн (версія Car)\n";
    cout << "pointer->Vehicle::CalculateTripCost(100) = "
        << pointer->Vehicle::CalculateTripCost(100) << " грн (версія Vehicle)\n";

    cout << "\nВихід з функції - деструктори:\n";
}

// ==================== Лабораторна 6 ====================

// Лаб 6, п. 1: унарні оператори ++ і --
void DemoUnaryOperators() {
    cout << "\n===== Лаб 6, пункт 1: оператори ++ і -- =====\n";
    Bus bus("Bogdan A092", "BX 2222 AA", 2019, 30);
    bus.BoardPassengers(10);

    // Префіксний ++: спочатку додає пасажира, потім повертає автобус
    cout << "\nПрефіксний ++bus:\n";
    cout << "Результат виразу (++bus): " << (++bus).GetPassengers()
        << " пасажирів\n";
    cout << "В автобусі зараз: " << bus.GetPassengers() << "\n";

    // Постфіксний ++: повертає копію СТАРОГО стану, а потім додає
    cout << "\nПостфіксний bus++ (створюється копія старого стану):\n";
    Bus old_bus = bus++;
    cout << "Результат виразу (bus++): " << old_bus.GetPassengers()
        << " пасажирів (старе значення)\n";
    cout << "В автобусі зараз: " << bus.GetPassengers() << "\n";

    // Префіксний і постфіксний --
    cout << "\nПрефіксний --bus:\n";
    --bus;
    cout << "В автобусі зараз: " << bus.GetPassengers() << "\n";

    cout << "\nПостфіксний bus--:\n";
    Bus old_bus2 = bus--;
    cout << "Результат виразу (bus--): " << old_bus2.GetPassengers()
        << ", в автобусі зараз: " << bus.GetPassengers() << "\n";

    // Ті самі оператори у класі Car: ++ доливає, -- витрачає 10 л пального
    cout << "\n--- Оператори ++ і -- для вантажівки (Car) ---\n";
    Car truck("MAN TGX", "BX 7390 HT", 450, false, 2019, 410000, 200, "Київ");
    cout << "Пального на початку: " << truck.GetFuelLevel() << " л\n";
    ++truck;
    cout << "Після ++truck: " << truck.GetFuelLevel() << " л\n";
    Car old_truck = truck++;
    cout << "Результат виразу (truck++): " << old_truck.GetFuelLevel()
        << " л (старе значення), в баку зараз: " << truck.GetFuelLevel()
        << " л\n";
    --truck;
    cout << "Після --truck: " << truck.GetFuelLevel() << " л\n";
    Car old_truck2 = truck--;
    cout << "Результат виразу (truck--): " << old_truck2.GetFuelLevel()
        << " л, в баку зараз: " << truck.GetFuelLevel() << " л\n";

    cout << "\nВихід з функції - деструктори:\n";
}

// Лаб 6, п. 2, 3: бінарні оператори і оператори *, =, +=, -=, *=, []
void DemoRouteOperators() {
    cout << "\n===== Лаб 6, пункти 2, 3: оператори маршруту =====\n";
    Route route1("Хмельницький - Вінниця", 120);
    route1.AddStop("Хмельницький");
    route1.AddStop("Летичів");
    route1.AddStop("Вінниця");

    Route route2("Вінниця - Київ", 268);
    route2.AddStop("Житомир");
    route2.AddStop("Київ");

    route1.Print();
    route2.Print();

    // Лаб 6, п. 2: оператор +
    cout << "\nroute1 + route2 (з'єднали маршрути):\n";
    Route full = route1 + route2;
    full.Print();

    // Лаб 6, п. 2: оператор -
    cout << "\nfull - 40 (маршрут коротший на 40 км):\n";
    Route shorter = full - 40;
    shorter.Print();

    // Лаб 6, п. 3: оператор *
    cout << "\nroute1 * 2 (проїхати маршрут 2 рази):\n";
    Route twice = route1 * 2;
    twice.Print();

    // Лаб 6, п. 3: оператор =
    cout << "\ncopy = route2 (присвоєння):\n";
    Route copy;
    copy = route2;
    copy.Print();

    // Лаб 6, п. 3: оператор +=
    cout << "\ncopy += route1 (дописали route1):\n";
    copy += route1;
    copy.Print();

    // Лаб 6, п. 3: оператор -=
    cout << "\ncopy -= 50 (скоротили на 50 км):\n";
    copy -= 50;
    copy.Print();

    // Лаб 6, п. 3: оператор *=
    cout << "\ncopy *= 3 (проїхати 3 рази):\n";
    copy *= 3;
    copy.Print();

    // Лаб 6, п. 3: оператор []
    cout << "\nroute1[0] = " << route1[0] << ", route1[2] = " << route1[2]
        << "\n";
    route1[1] = "Меджибіж";
    cout << "Після route1[1] = \"Меджибіж\":\n";
    route1.Print();

    // Помилки: неправильний номер зупинки і неправильна кількість повторів
    try {
        cout << route1[10] << "\n";
    }
    catch (const out_of_range& e) {
        cout << "  [out_of_range] " << e.what() << "\n";
    }
    try {
        route1 *= 0;
    }
    catch (const invalid_argument& e) {
        cout << "  [invalid_argument] " << e.what() << "\n";
    }
}

// Лаб 6, п. 4: шаблонна функція
void DemoTemplateFunction() {
    cout << "\n===== Лаб 6, пункт 4: шаблонна функція =====\n";
    Car truck("MAN TGX", "BX 7390 HT", 900, false, 2019, 410000, 100, "Київ");

    // Та сама функція AddFuel працює з різними типами
    cout << "\nAddFuel(50) - тип int:\n";
    truck.AddFuel(50);
    cout << "AddFuel(25.5) - тип double:\n";
    truck.AddFuel(25.5);
    cout << "AddFuel<float>(10.25f) - тип float, вказаний явно:\n";
    truck.AddFuel<float>(10.25f);

    cout << "\nВихід з функції - деструктори:\n";
}

// Лаб 6, п. 5, 6: шаблон класу і користувацький тип
void DemoTemplateClass() {
    cout << "\n===== Лаб 6, пункт 5: шаблон класу TripStats<T> =====\n";

    // Лаб 6, п. 5: шаблон з типом int
    TripStats<int> passengers("Пасажири за рейс (int)");
    passengers.Add(25);
    passengers.Add(40);
    passengers.Add(12);
    passengers.Add(33);
    passengers.Print();

    // Лаб 6, п. 5: шаблон з типом double
    TripStats<double> distances("Кілометраж рейсів (double)");
    distances.Add(320.5);
    distances.Add(150.0);
    distances.Add(512.3);
    distances.Print();

    cout << "\n===== Лаб 6, пункт 6: користувацький тип у шаблоні =====\n";
    // Лаб 6, п. 6: шаблон з користувацьким класом Cargo
    TripStats<Cargo> cargo_stats("Вантажі за день (Cargo)");
    cargo_stats.Add(Cargo("Цемент", 1200));
    cargo_stats.Add(Cargo("Цегла", 3500));
    cargo_stats.Add(Cargo("Пісок", 800));
    cargo_stats.Print();
    cout << "Найважчий вантаж: " << cargo_stats.GetMax().GetName() << "\n";

    // Метод Clear теж шаблонний
    cargo_stats.Clear();
    cout << "\nПісля Clear():\n";
    cargo_stats.Print();
}

// ==================== Меню ====================

const int kGarageSize = 10;

// Лаб 5, п. 8: перегляд створених об'єктів
void ShowGarage(Vehicle* garage[], int count) {
    if (count == 0) {
        cout << "Гараж порожній\n";
        return;
    }
    for (int i = 0; i < count; i++) {
        cout << i + 1 << ". " << garage[i]->GetTypeName() << " "
            << garage[i]->brand_ << " (" << garage[i]->GetYear() << " р.)\n";
    }
}

int main(int argc, char* argv[]) {
    system("chcp 65001 > nul");

    // Лаб 5, п. 7: ім'я файлу з командного рядка
    string filename = "autobase.txt";
    if (argc > 1) {
        filename = argv[1];
    }
    cout << "Файл для роботи: " << filename << "\n";

    // Лаб 5, п. 7: виклик Service у функції main()
    RefrigeratedTruck start_truck("Volvo FH Ice", "BX 0001 AA", 2023);
    start_truck.SetTemperature(-20);
    start_truck.LoadCargo(8000);
    Service(start_truck, filename);

    // Лаб 5, п. 8: гараж - масив об'єктів, створених через new
    Vehicle* garage[kGarageSize] = {};
    int count = 0;
    int plate_number = 100;
    int choice = -1;

    while (choice != 0) {
        cout << "\n================ МЕНЮ АВТОБАЗИ ================\n"
            << "--- Пункт 8: створення і знищення об'єктів ---\n"
            << "1. Створити вантажівку (Car)\n"
            << "2. Створити автобус (Bus)\n"
            << "3. Створити фургон (CargoPassengerVan)\n"
            << "4. Створити рефрижератор (RefrigeratedTruck)\n"
            << "5. Показати всі об'єкти\n"
            << "6. Знищити об'єкт\n"
            << "7. Записати і прочитати об'єкт з файлу (пункт 7)\n"
            << "--- Лабораторна 5 ---\n"
            << "8.  Пункт 2: віртуальне наслідування\n"
            << "9.  Пункт 3: віртуальні і невіртуальні деструктори\n"
            << "10. Пункти 5, 6: статичні і динамічні об'єкти\n"
            << "11. Пункт 7: помилки при роботі з файлами\n"
            << "12. Пункт 9: поліморфізм, зміна форми об'єкта\n"
            << "13. Пункти 10, 11: зв'язування, обхід віртуальних функцій\n"
            << "14. Лабораторні 2-4\n"
            << "--- Лабораторна 6 ---\n"
            << "15. Пункт 1: оператори ++ і -- (автобус і вантажівка)\n"
            << "16. Пункти 2, 3: оператори маршруту (+, -, *, =, +=, -=, *=, [])\n"
            << "17. Пункт 4: шаблонна функція\n"
            << "18. Пункти 5, 6: шаблон класу, користувацький тип\n"
            << "--- Лабораторна 7 ---\n"
            << "19. Пункт 1: vector, list, deque\n"
            << "20. Пункт 1: set, multiset, map, multimap\n"
            << "21. Пункт 1: stack, queue, priority_queue\n"
            << "22. Пункт 2: ітератори\n"
            << "23. Пункт 3: алгоритми\n"
            << "24. Пункт 4.1: арифметичні функтори\n"
            << "25. Пункт 4.2: функтори порівняння\n"
            << "26. Пункт 4.3: логічні функтори\n"
            << "0.  Вихід\n"
            << "Ваш вибір: ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Потрібно ввести число!\n";
            choice = -1;
            continue;
        }

        if (choice >= 1 && choice <= 4) {
            // Лаб 5, п. 8: створення об'єкта
            if (count == kGarageSize) {
                cout << "Гараж заповнений!\n";
                Pause();
                continue;
            }
            string brand;
            int year = 0;
            cout << "Марка (латиницею, одним словом): ";
            cin >> brand;
            cout << "Рік випуску: ";
            cin >> year;
            if (cin.fail() || year < 1950 || year > 2026) {
                cin.clear();
                cout << "Неправильний рік!\n";
                Pause();
                continue;
            }
            string plate = "BX " + to_string(plate_number) + " AA";
            plate_number++;
            try {
                if (choice == 1) {
                    garage[count] = new Car(brand, plate, 400, false, year, 0, 200,
                        "База");
                }
                else if (choice == 2) {
                    garage[count] = new Bus(brand, plate, year, 40);
                }
                else if (choice == 3) {
                    garage[count] = new CargoPassengerVan(brand, plate, year, 8);
                }
                else {
                    garage[count] = new RefrigeratedTruck(brand, plate, year);
                }
                count++;
                cout << "Об'єкт створено\n";
            }
            catch (const bad_alloc& e) {
                cout << "Не вистачає пам'яті: " << e.what() << "\n";
            }
            Pause();
        }
        else if (choice == 5) {
            ShowGarage(garage, count);
            Pause();
        }
        else if (choice == 6) {
            // Лаб 5, п. 8: знищення об'єкта
            ShowGarage(garage, count);
            if (count > 0) {
                int number = 0;
                cout << "Номер об'єкта для знищення: ";
                cin >> number;
                if (!cin.fail() && number >= 1 && number <= count) {
                    delete garage[number - 1];
                    for (int i = number - 1; i < count - 1; i++) {
                        garage[i] = garage[i + 1];
                    }
                    count--;
                    garage[count] = nullptr;
                    cout << "Об'єкт знищено\n";
                }
                else {
                    cin.clear();
                    cout << "Немає такого номера\n";
                }
            }
            Pause();
        }
        else if (choice == 7) {
            // Лаб 5, п. 7: Service для вибраного об'єкта
            ShowGarage(garage, count);
            if (count > 0) {
                int number = 0;
                cout << "Номер об'єкта: ";
                cin >> number;
                if (!cin.fail() && number >= 1 && number <= count) {
                    Service(*garage[number - 1], filename);
                }
                else {
                    cin.clear();
                    cout << "Немає такого номера\n";
                }
            }
            Pause();
        }
        else if (choice == 8) {
            DemoVirtualInheritance();
            Pause();
        }
        else if (choice == 9) {
            DemoDestructors();
            Pause();
        }
        else if (choice == 10) {
            DemoArrays();
            Pause();
        }
        else if (choice == 11) {
            DemoFiles();
            Pause();
        }
        else if (choice == 12) {
            DemoPolymorphism();
            Pause();
        }
        else if (choice == 13) {
            DemoBinding();
            Pause();
        }
        else if (choice == 14) {
            RunOldLabsDemo();
            Pause();
        }
        else if (choice == 15) {
            DemoUnaryOperators();
            Pause();
        }
        else if (choice == 16) {
            DemoRouteOperators();
            Pause();
        }
        else if (choice == 17) {
            DemoTemplateFunction();
            Pause();
        }
        else if (choice == 18) {
            DemoTemplateClass();
            Pause();
        }
        else if (choice == 19) {
            // Лаб 7, п. 1: послідовні контейнери
            DemoSequenceContainers();
            Pause();
        }
        else if (choice == 20) {
            // Лаб 7, п. 1: асоціативні контейнери
            DemoAssociativeContainers();
            Pause();
        }
        else if (choice == 21) {
            // Лаб 7, п. 1: адаптери контейнерів
            DemoContainerAdapters();
            Pause();
        }
        else if (choice == 22) {
            // Лаб 7, п. 2: ітератори
            DemoIterators();
            Pause();
        }
        else if (choice == 23) {
            // Лаб 7, п. 3: алгоритми
            DemoAlgorithms();
            Pause();
        }
        else if (choice == 24) {
            // Лаб 7, п. 4.1: арифметичні функтори
            DemoArithmeticFunctors();
            Pause();
        }
        else if (choice == 25) {
            // Лаб 7, п. 4.2: функтори порівняння
            DemoComparisonFunctors();
            Pause();
        }
        else if (choice == 26) {
            // Лаб 7, п. 4.3: логічні функтори
            DemoLogicalFunctors();
            Pause();
        }
        else if (choice != 0) {
            cout << "Немає такого пункту меню\n";
        }
    }

    // Знищуємо всі об'єкти перед виходом
    for (int i = 0; i < count; i++) {
        delete garage[i];
    }
    return 0;
}