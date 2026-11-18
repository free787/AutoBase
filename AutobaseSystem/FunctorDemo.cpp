#include "FunctorDemo.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <set>
#include <string>
#include <vector>

#include "Car.h"
#include "Cargo.h"
#include "Route.h"

using namespace std;

// Лаб 7, п. 4.1: арифметичні функтори
void DemoArithmeticFunctors() {
    Car truck("Volvo", "AA1111AA", 20, false, 2020, 150000, 120, "База");
    cout << "\nВантажівка " << truck.GetBrand() << ", пального "
        << truck.GetFuelLevel() << " л\n";

    // Лаб 7, п. 4.1: plus - додавання (долили пальне)
    plus<double> add;
    truck.SetFuelLevel(add(truck.GetFuelLevel(), 30));
    cout << "plus: долили 30 л -> " << truck.GetFuelLevel() << " л\n";

    // Лаб 7, п. 4.1: minus - віднімання (витратили пальне)
    minus<double> subtract;
    truck.SetFuelLevel(subtract(truck.GetFuelLevel(), 45));
    cout << "minus: витратили 45 л -> " << truck.GetFuelLevel() << " л\n";

    // Лаб 7, п. 4.1: multiplies - множення (вартість рейсу)
    multiplies<double> times;
    Route route("Київ - Львів", 540);
    cout << "multiplies: " << route.GetDistance() << " км * 12.5 грн = "
        << times(route.GetDistance(), 12.5) << " грн\n";

    // Лаб 7, п. 4.1: divides - ділення (витрата на 100 км)
    divides<double> divide;
    cout << "divides: 45 л на 150 км -> " << divide(45, 150) * 100
        << " л на 100 км\n";

    // Лаб 7, п. 4.1: modulus - остача від ділення (хто не влізе в автобус)
    modulus<int> mod;
    cout << "modulus: 47 пасажирів, автобус на 20 місць -> повних автобусів "
        << 47 / 20 << ", залишиться " << mod(47, 20) << " пасажирів\n";

    // Лаб 7, п. 4.1: negate - зміна знаку (витрата як від'ємне число)
    negate<double> change_sign;
    cout << "negate: витрата 45 л -> зміна запасу " << change_sign(45)
        << " л\n";

    // Лаб 7, п. 4.1: функтори разом з алгоритмами
    vector<Cargo> cargos;
    cargos.push_back(Cargo("Цемент", 1500));
    cargos.push_back(Cargo("Меблі", 700));
    cargos.push_back(Cargo("Продукти", 300));
    vector<double> weights;
    for (int i = 0; i < (int)cargos.size(); i++) {
        weights.push_back(cargos[i].GetWeight());
    }
    cout << "\naccumulate + plus: загальна вага вантажів = "
        << accumulate(weights.begin(), weights.end(), 0.0, plus<double>())
        << " кг\n";

    vector<double> fuel_before;
    fuel_before.push_back(120);
    fuel_before.push_back(90);
    fuel_before.push_back(60);
    vector<double> fuel_after;
    fuel_after.push_back(75);
    fuel_after.push_back(40);
    fuel_after.push_back(55);
    vector<double> used(3);
    transform(fuel_before.begin(), fuel_before.end(), fuel_after.begin(),
        used.begin(), minus<double>());
    cout << "transform + minus: витрата пального трьох машин: ";
    for (int i = 0; i < (int)used.size(); i++) {
        cout << used[i] << " л  ";
    }
    cout << "\n";
}

// Лаб 7, п. 4.2: функтори порівняння
void DemoComparisonFunctors() {
    cout << boolalpha;  // виводити true/false замість 1/0
    // Лаб 7, п. 4.2: equal_to і not_equal_to - порівняння номерів машин
    equal_to<string> same;
    not_equal_to<string> different;
    string plate1 = "AA1111AA";
    string plate2 = "BB2222BB";
    cout << "\nequal_to(" << plate1 << ", " << plate1
        << ") = " << same(plate1, plate1) << "\n";
    cout << "not_equal_to(" << plate1 << ", " << plate2
        << ") = " << different(plate1, plate2) << "\n";

    // Лаб 7, п. 4.2: greater і less - порівняння відстаней маршрутів
    Route kyiv_lviv("Київ - Львів", 540);
    Route kyiv_zhytomyr("Київ - Житомир", 140);
    greater<double> more;
    less<double> fewer;
    cout << "greater(540, 140) = "
        << more(kyiv_lviv.GetDistance(), kyiv_zhytomyr.GetDistance()) << "\n";
    cout << "less(540, 140) = "
        << fewer(kyiv_lviv.GetDistance(), kyiv_zhytomyr.GetDistance()) << "\n";

    // Лаб 7, п. 4.2: greater_equal - чи вистачить пального
    greater_equal<double> enough;
    cout << "greater_equal: пального 80 л, треба 80 л -> " << enough(80, 80)
        << "\n";

    // Лаб 7, п. 4.2: less_equal - чи не перевищено вантажопідйомність
    less_equal<double> not_overloaded;
    cout << "less_equal: вантаж 21000 кг, максимум 20000 кг -> "
        << not_overloaded(21000, 20000) << "\n";

    // Лаб 7, п. 4.2: функтори порівняння разом з сортуванням
    vector<double> distances;
    distances.push_back(140);
    distances.push_back(540);
    distances.push_back(25);
    distances.push_back(190);
    sort(distances.begin(), distances.end(), less<double>());
    cout << "\nsort + less (за зростанням): ";
    for (int i = 0; i < (int)distances.size(); i++) {
        cout << distances[i] << " ";
    }
    sort(distances.begin(), distances.end(), greater<double>());
    cout << "\nsort + greater (за спаданням): ";
    for (int i = 0; i < (int)distances.size(); i++) {
        cout << distances[i] << " ";
    }

    // Лаб 7, п. 4.2: set з greater - вантажі від найважчого (operator>)
    set<Cargo, greater<Cargo> > cargos;
    cargos.insert(Cargo("Продукти", 300));
    cargos.insert(Cargo("Цемент", 1500));
    cargos.insert(Cargo("Меблі", 700));
    cout << "\nset<Cargo, greater<Cargo>> (від найважчого):\n";
    for (set<Cargo, greater<Cargo> >::iterator it = cargos.begin();
        it != cargos.end(); it++) {
        cout << "  " << *it << "\n";
    }
    cout << noboolalpha;
}

// Лаб 7, п. 4.3: логічні функтори
void DemoLogicalFunctors() {
    cout << boolalpha;  // виводити true/false замість 1/0
    // Дані трьох машин: чи активна і чи є пальне
    string plates[3] = { "AA1111AA", "BB2222BB", "CC3333CC" };
    bool is_active[3] = { true, true, false };
    bool has_fuel[3] = { true, false, true };

    logical_and<bool> both;
    logical_or<bool> any;
    logical_not<bool> opposite;

    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << plates[i] << ": активна = " << is_active[i]
            << ", пальне = " << has_fuel[i] << "\n";
        // Лаб 7, п. 4.3: logical_and - їде, якщо активна І є пальне
        cout << "  logical_and -> може їхати в рейс: "
            << both(is_active[i], has_fuel[i]) << "\n";
        // Лаб 7, п. 4.3: logical_or - є проблема, якщо неактивна АБО без пального
        cout << "  logical_or  -> є проблема: "
            << any(opposite(is_active[i]), opposite(has_fuel[i])) << "\n";
        // Лаб 7, п. 4.3: logical_not - заперечення (чи стоїть на базі)
        cout << "  logical_not -> стоїть на базі: " << opposite(is_active[i])
            << "\n";
    }

    // Лаб 7, п. 4.3: логічні функтори разом з transform
    vector<bool> active(is_active, is_active + 3);
    vector<bool> fuel(has_fuel, has_fuel + 3);
    vector<bool> ready(3);
    transform(active.begin(), active.end(), fuel.begin(), ready.begin(),
        logical_and<bool>());
    vector<bool> stopped(3);
    transform(active.begin(), active.end(), stopped.begin(),
        logical_not<bool>());
    cout << "\ntransform + logical_and (готові до рейсу): ";
    for (int i = 0; i < 3; i++) {
        cout << ready[i] << " ";
    }
    cout << "\ntransform + logical_not (стоять на базі): ";
    for (int i = 0; i < 3; i++) {
        cout << stopped[i] << " ";
    }
    cout << "\n" << noboolalpha;
}