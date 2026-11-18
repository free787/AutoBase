#include "StlDemo.h"

#include <algorithm>
#include <deque>
#include <forward_list>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#include "Bus.h"
#include "Car.h"
#include "Cargo.h"
#include "Route.h"
#include "Vehicle.h"

using namespace std;

// ==================== Лаб 7, п. 1: контейнери ====================

// Лаб 7, п. 1: послідовні контейнери vector, list, deque
void DemoSequenceContainers() {
    cout << "\n===== vector<Vehicle*>: автопарк =====\n";
    vector<Vehicle*> fleet;
    // Лаб 7, п. 1: vector - метод 1: push_back (додати в кінець)
    fleet.push_back(new Car("Volvo", "AA1111AA", 20, false, 2020, 150000, 120,
        "База"));
    fleet.push_back(new Bus("Mercedes", "BB2222BB", 2019, 40));
    fleet.push_back(new Car("MAN", "CC3333CC", 25, false, 2018, 230000, 80,
        "Київ"));
    // Лаб 7, п. 1: vector - метод 2: size (кількість елементів)
    cout << "У автопарку " << fleet.size() << " машини:\n";
    for (int i = 0; i < (int)fleet.size(); i++) {
        // Лаб 7, п. 1: vector - метод 3: at (доступ за номером з перевіркою)
        cout << i + 1 << ". " << fleet.at(i)->GetTypeName() << " "
            << fleet.at(i)->brand_ << " (" << fleet.at(i)->plate_number_ << ")\n";
    }
    // Звільняємо пам'ять
    for (int i = 0; i < (int)fleet.size(); i++) {
        delete fleet[i];
    }
    fleet.clear();

    cout << "\n===== list<Cargo>: вантажі на складі =====\n";
    list<Cargo> warehouse;
    // Лаб 7, п. 1: list - метод 1: push_back (додати в кінець)
    warehouse.push_back(Cargo("Цемент", 1500));
    warehouse.push_back(Cargo("Меблі", 700));
    // Лаб 7, п. 1: list - метод 2: push_front (додати на початок)
    warehouse.push_front(Cargo("Продукти", 300));
    cout << "До сортування:\n";
    for (list<Cargo>::iterator it = warehouse.begin(); it != warehouse.end();
        it++) {
        cout << "  " << *it << "\n";
    }
    // Лаб 7, п. 1: list - метод 3: sort (сортує за вагою через operator<)
    warehouse.sort();
    cout << "Після сортування за вагою:\n";
    for (list<Cargo>::iterator it = warehouse.begin(); it != warehouse.end();
        it++) {
        cout << "  " << *it << "\n";
    }

    cout << "\n===== deque<Route>: черга маршрутів =====\n";
    deque<Route> routes;
    // Лаб 7, п. 1: deque - метод 1: push_back (додати в кінець)
    routes.push_back(Route("Київ - Житомир", 140));
    routes.push_back(Route("Київ - Львів", 540));
    // Лаб 7, п. 1: deque - метод 2: push_front (термінове - на початок)
    routes.push_front(Route("Київ - Бровари (терміново)", 25));
    cout << "Перший маршрут: " << routes.front().GetRouteInfo() << "\n";
    cout << "Останній маршрут: " << routes.back().GetRouteInfo() << "\n";
    // Лаб 7, п. 1: deque - метод 3: pop_back (видалити з кінця)
    routes.pop_back();
    cout << "Після pop_back залишилось маршрутів: " << routes.size() << "\n";
    for (int i = 0; i < (int)routes.size(); i++) {
        cout << "  " << routes[i].GetRouteInfo() << "\n";
    }
}

// Лаб 7, п. 1: асоціативні контейнери set, multiset, map, multimap
void DemoAssociativeContainers() {
    cout << "\n===== set<Cargo>: вантажі без повторів ваги =====\n";
    set<Cargo> cargo_set;
    // Лаб 7, п. 1: set - метод 1: insert (додати, повтор не додається)
    cargo_set.insert(Cargo("Цемент", 1500));
    cargo_set.insert(Cargo("Меблі", 700));
    cargo_set.insert(Cargo("Пісок", 1500));  // така вага вже є - не додасться
    cargo_set.insert(Cargo("Продукти", 300));
    cout << "Елементів у set: " << cargo_set.size()
        << " (Пісок не додався, бо вага 1500 вже є)\n";
    for (set<Cargo>::iterator it = cargo_set.begin(); it != cargo_set.end();
        it++) {
        cout << "  " << *it << "\n";
    }
    // Лаб 7, п. 1: set - метод 2: find (пошук вантажу вагою 700 кг)
    set<Cargo>::iterator found = cargo_set.find(Cargo("", 700));
    if (found != cargo_set.end()) {
        cout << "Знайдено вантаж 700 кг: " << *found << "\n";
    }
    // Лаб 7, п. 1: set - метод 3: erase (видалити вантаж)
    cargo_set.erase(Cargo("", 300));
    cout << "Після erase(300 кг) елементів: " << cargo_set.size() << "\n";

    cout << "\n===== multiset<Cargo>: вантажі з повторами =====\n";
    multiset<Cargo> cargo_multiset;
    // Лаб 7, п. 1: multiset - метод 1: insert (повтори дозволені)
    cargo_multiset.insert(Cargo("Цемент", 1500));
    cargo_multiset.insert(Cargo("Пісок", 1500));
    cargo_multiset.insert(Cargo("Щебінь", 1500));
    cargo_multiset.insert(Cargo("Меблі", 700));
    for (multiset<Cargo>::iterator it = cargo_multiset.begin();
        it != cargo_multiset.end(); it++) {
        cout << "  " << *it << "\n";
    }
    // Лаб 7, п. 1: multiset - метод 2: count (скільки вантажів по 1500 кг)
    cout << "Вантажів по 1500 кг: " << cargo_multiset.count(Cargo("", 1500))
        << "\n";
    // Лаб 7, п. 1: multiset - метод 3: size (всього елементів)
    cout << "Всього вантажів: " << cargo_multiset.size() << "\n";

    cout << "\n===== map<string, Cargo>: номер машини -> вантаж =====\n";
    map<string, Cargo> loads;
    // Лаб 7, п. 1: map - метод 1: insert / operator[] (додати пару)
    loads.insert(make_pair("AA1111AA", Cargo("Цемент", 1500)));
    loads["CC3333CC"] = Cargo("Меблі", 700);
    loads["BB2222BB"] = Cargo("Продукти", 300);
    for (map<string, Cargo>::iterator it = loads.begin(); it != loads.end();
        it++) {
        cout << "  " << it->first << " -> " << it->second << "\n";
    }
    // Лаб 7, п. 1: map - метод 2: find (пошук за ключем)
    map<string, Cargo>::iterator car_it = loads.find("CC3333CC");
    if (car_it != loads.end()) {
        cout << "Машина CC3333CC везе: " << car_it->second << "\n";
    }
    // Лаб 7, п. 1: map - метод 3: erase (машина розвантажилась)
    loads.erase("BB2222BB");
    cout << "Після erase(BB2222BB) машин з вантажем: " << loads.size() << "\n";

    cout << "\n===== multimap<string, Route>: водій -> маршрути =====\n";
    multimap<string, Route> driver_routes;
    // Лаб 7, п. 1: multimap - метод 1: insert (один ключ - багато значень)
    driver_routes.insert(make_pair("Петренко", Route("Київ - Житомир", 140)));
    driver_routes.insert(make_pair("Петренко", Route("Житомир - Рівне", 190)));
    driver_routes.insert(make_pair("Іваненко", Route("Київ - Одеса", 475)));
    for (multimap<string, Route>::iterator it = driver_routes.begin();
        it != driver_routes.end(); it++) {
        cout << "  " << it->first << ": " << it->second.GetRouteInfo() << "\n";
    }
    // Лаб 7, п. 1: multimap - метод 2: count (скільки маршрутів у водія)
    cout << "Маршрутів у Петренка: " << driver_routes.count("Петренко") << "\n";
    // Лаб 7, п. 1: multimap - метод 3: erase (видалити всі маршрути водія)
    driver_routes.erase("Петренко");
    cout << "Після erase(Петренко) записів: " << driver_routes.size() << "\n";
}

// Лаб 7, п. 1: адаптери контейнерів stack, queue, priority_queue
void DemoContainerAdapters() {
    cout << "\n===== stack<Route>: історія поїздок (останній - зверху) =====\n";
    stack<Route> history;
    // Лаб 7, п. 1: stack - метод 1: push (покласти зверху)
    history.push(Route("Київ - Житомир", 140));
    history.push(Route("Житомир - Рівне", 190));
    history.push(Route("Рівне - Луцьк", 70));
    cout << "Поїздок в історії: " << history.size() << "\n";
    while (!history.empty()) {
        // Лаб 7, п. 1: stack - метод 2: top (подивитись верхній елемент)
        cout << "  " << history.top().GetRouteInfo() << "\n";
        // Лаб 7, п. 1: stack - метод 3: pop (забрати верхній елемент)
        history.pop();
    }

    cout << "\n===== queue<Cargo>: черга на завантаження (перший прийшов - "
        "перший пішов) =====\n";
    queue<Cargo> loading;
    // Лаб 7, п. 1: queue - метод 1: push (стати в кінець черги)
    loading.push(Cargo("Продукти", 300));
    loading.push(Cargo("Цемент", 1500));
    loading.push(Cargo("Меблі", 700));
    while (!loading.empty()) {
        // Лаб 7, п. 1: queue - метод 2: front (перший у черзі)
        cout << "  Завантажуємо: " << loading.front() << "\n";
        // Лаб 7, п. 1: queue - метод 3: pop (вийти з черги)
        loading.pop();
    }

    cout << "\n===== priority_queue<Cargo>: спочатку найважчий вантаж =====\n";
    priority_queue<Cargo> heavy_first;
    // Лаб 7, п. 1: priority_queue - метод 1: push (сортує сам за operator<)
    heavy_first.push(Cargo("Продукти", 300));
    heavy_first.push(Cargo("Цемент", 1500));
    heavy_first.push(Cargo("Меблі", 700));
    while (!heavy_first.empty()) {
        // Лаб 7, п. 1: priority_queue - метод 2: top (найважчий)
        cout << "  Відправляємо: " << heavy_first.top() << "\n";
        // Лаб 7, п. 1: priority_queue - метод 3: pop (забрати найважчий)
        heavy_first.pop();
    }
}

// ==================== Лаб 7, п. 2: ітератори ====================

void DemoIterators() {
    // Лаб 7, п. 2: ітератор введення (istream_iterator) - тільки читає
    cout << "\n--- Ітератор введення (istream_iterator) ---\n";
    istringstream input("140 540 25 190");
    istream_iterator<double> in_it(input);
    istream_iterator<double> in_end;
    vector<double> distances;
    while (in_it != in_end) {
        distances.push_back(*in_it);
        ++in_it;
    }
    cout << "Прочитано відстаней: " << distances.size() << "\n";

    // Лаб 7, п. 2: ітератор виведення (ostream_iterator) - тільки пише
    cout << "\n--- Ітератор виведення (ostream_iterator) ---\n";
    ostream_iterator<double> out_it(cout, " км; ");
    copy(distances.begin(), distances.end(), out_it);
    cout << "\n";
    vector<Cargo> cargos;
    cargos.push_back(Cargo("Цемент", 1500));
    cargos.push_back(Cargo("Меблі", 700));
    cargos.push_back(Cargo("Продукти", 300));
    ostream_iterator<Cargo> cargo_out(cout, "\n");
    copy(cargos.begin(), cargos.end(), cargo_out);

    // Лаб 7, п. 2: прямий ітератор (forward_list) - тільки вперед, ++
    cout << "\n--- Прямий ітератор (forward_list) ---\n";
    forward_list<Cargo> trailer;
    trailer.push_front(Cargo("Цемент", 1500));
    trailer.push_front(Cargo("Пісок", 1000));
    for (forward_list<Cargo>::iterator it = trailer.begin(); it != trailer.end();
        ++it) {
        cout << "  " << *it << "\n";
    }

    // Лаб 7, п. 2: двонаправлений ітератор (list) - вперед ++ і назад --
    cout << "\n--- Двонаправлений ітератор (list) ---\n";
    list<Route> trip;
    trip.push_back(Route("Київ - Житомир", 140));
    trip.push_back(Route("Житомир - Рівне", 190));
    trip.push_back(Route("Рівне - Луцьк", 70));
    cout << "Туди:\n";
    for (list<Route>::iterator it = trip.begin(); it != trip.end(); ++it) {
        cout << "  " << it->GetRouteInfo() << "\n";
    }
    cout << "Назад:\n";
    list<Route>::iterator back_it = trip.end();
    while (back_it != trip.begin()) {
        --back_it;
        cout << "  " << back_it->GetRouteInfo() << "\n";
    }

    // Лаб 7, п. 2: ітератор довільного доступу (vector) - +n, -n, [], <
    cout << "\n--- Ітератор довільного доступу (vector) ---\n";
    vector<Cargo>::iterator first = cargos.begin();
    vector<Cargo>::iterator last = cargos.end() - 1;
    cout << "Перший: " << *first << "\n";
    cout << "Третій (first + 2): " << *(first + 2) << "\n";
    cout << "Другий (first[1]): " << first[1] << "\n";
    cout << "Останній (end - 1): " << *last << "\n";
    cout << "Відстань між ними: " << last - first << "\n";
    if (first < last) {
        cout << "first < last - ітератори можна порівнювати\n";
    }
}

// ==================== Лаб 7, п. 3: алгоритми ====================

// Лаб 7, п. 3: допоміжні функції для алгоритмів
bool IsHeavyCargo(const Cargo& cargo) {
    return cargo.GetWeight() > 1000;
}

bool CompareByName(const Cargo& a, const Cargo& b) {
    return a.GetName() < b.GetName();
}

void PrintCargo(const Cargo& cargo) {
    cout << "  " << cargo << "\n";
}

void DemoAlgorithms() {
    vector<Cargo> cargos;
    cargos.push_back(Cargo("Цемент", 1500));
    cargos.push_back(Cargo("Меблі", 700));
    cargos.push_back(Cargo("Щебінь", 2000));
    cargos.push_back(Cargo("Продукти", 300));
    cargos.push_back(Cargo("Агрегати", 1200));

    // Лаб 7, п. 3: алгоритм 1 - for_each (виконати функцію для кожного)
    cout << "\n1) for_each - всі вантажі:\n";
    for_each(cargos.begin(), cargos.end(), PrintCargo);

    // Лаб 7, п. 3: алгоритм 2 - sort (за вагою, потім за назвою)
    cout << "\n2) sort - за вагою (operator<):\n";
    sort(cargos.begin(), cargos.end());
    for_each(cargos.begin(), cargos.end(), PrintCargo);
    cout << "sort - за назвою (функція CompareByName):\n";
    sort(cargos.begin(), cargos.end(), CompareByName);
    for_each(cargos.begin(), cargos.end(), PrintCargo);

    // Лаб 7, п. 3: алгоритм 3 - find_if (перший важкий вантаж > 1000 кг)
    cout << "\n3) find_if - перший вантаж важчий 1000 кг: ";
    vector<Cargo>::iterator heavy =
        find_if(cargos.begin(), cargos.end(), IsHeavyCargo);
    if (heavy != cargos.end()) {
        cout << *heavy << "\n";
    }

    // Лаб 7, п. 3: алгоритм 4 - count_if (скільки важких вантажів)
    cout << "\n4) count_if - важких вантажів: "
        << count_if(cargos.begin(), cargos.end(), IsHeavyCargo) << "\n";

    // Лаб 7, п. 3: алгоритм 5 - max_element (найважчий вантаж)
    cout << "\n5) max_element - найважчий вантаж: "
        << *max_element(cargos.begin(), cargos.end()) << "\n";
}