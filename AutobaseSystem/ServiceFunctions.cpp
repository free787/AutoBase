#include "ServiceFunctions.h"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

// Лаб 5, п. 6: перевірка параметрів (кидає винятки)
void CheckArguments(const void* arr, int size, int min_year) {
    // Виняток 1: масиву не існує
    if (arr == nullptr) {
        throw invalid_argument("Масив не існує (nullptr)!");
    }
    // Виняток 2: неправильний розмір масиву
    if (size < 0 || size > 100) {
        throw out_of_range("Неправильний розмір масиву: " + to_string(size));
    }
    // Виняток 3: неправильний критерій (рік)
    if (min_year < 1950 || min_year > 2026) {
        throw domain_error("Неправильний рік: " + to_string(min_year));
    }
}

// Лаб 5, п. 6: видалення зі статичного масиву (елементи зсуваються)
void Service_Static(Car arr[], int& size, int min_year) {
    CheckArguments(arr, size, min_year);

    int new_size = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i].GetYear() < min_year) {
            cout << "  Списано: " << arr[i].brand_ << " (" << arr[i].GetYear()
                << " р.)\n";
        }
        else {
            arr[new_size] = arr[i];
            new_size++;
        }
    }
    cout << "Service_Static: видалено " << size - new_size << " авто\n";
    size = new_size;
}

// Лаб 5, п. 6: видалення з динамічного масиву (через delete)
void Service_Dinamic(Vehicle* arr[], int& size, int min_year) {
    CheckArguments(arr, size, min_year);

    // Виняток 4: в масиві є вже видалений елемент
    for (int i = 0; i < size; i++) {
        if (arr[i] == nullptr) {
            throw logic_error("Елемент [" + to_string(i) +
                "] вже видалено (nullptr)!");
        }
    }

    int new_size = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i]->GetYear() < min_year) {
            cout << "  Списано: " << arr[i]->GetTypeName() << " " << arr[i]->brand_
                << " (" << arr[i]->GetYear() << " р.)\n";
            delete arr[i];
            arr[i] = nullptr;
        }
        else {
            arr[new_size] = arr[i];
            new_size++;
        }
    }
    for (int i = new_size; i < size; i++) {
        arr[i] = nullptr;
    }
    cout << "Service_Dinamic: видалено " << size - new_size << " авто\n";
    size = new_size;
}

// Лаб 5, п. 5: перевірка індексу і nullptr перед доступом до об'єкта
Vehicle* GetVehicle(Vehicle* arr[], int size, int index) {
    if (index < 0 || index >= size) {
        throw out_of_range("Індекс " + to_string(index) +
            " виходить за межі масиву!");
    }
    if (arr[index] == nullptr) {
        throw logic_error("Об'єкт з індексом " + to_string(index) +
            " вже видалено з пам'яті!");
    }
    return arr[index];
}

// Лаб 5, п. 7: функція Service - запис і читання через Write / Read
void Service(Vehicle& vehicle, const string& filename, bool only_read) {
    cout << "[Service] Файл \"" << filename << "\", об'єкт "
        << vehicle.GetTypeName() << " " << vehicle.brand_ << "\n";
    try {
        // Виняток 1: порожнє ім'я файлу
        if (filename.empty()) {
            throw invalid_argument("Ім'я файлу порожнє!");
        }
        // Виняток 2: файл не .txt
        if (filename.size() < 5 ||
            filename.substr(filename.size() - 4) != ".txt") {
            throw domain_error("Файл має бути з розширенням .txt!");
        }

        if (!only_read) {
            ofstream out(filename);
            // Виняток 3: файл не відкривається для запису
            if (!out.is_open()) {
                throw ios_base::failure("Не вдалося відкрити файл для запису!");
            }
            out << vehicle.GetTypeName() << "\n";
            vehicle.Write(out);
            out.close();
            cout << "Об'єкт записано у файл\n";
        }

        ifstream in(filename);
        // Виняток 4: файл не відкривається для читання
        if (!in.is_open()) {
            throw ios_base::failure("Не вдалося відкрити файл для читання!");
        }
        // Виняток 5: файл порожній
        if (in.peek() == EOF) {
            throw runtime_error("Файл порожній!");
        }
        string type_name;
        getline(in, type_name);
        // Виняток 6: у файлі записаний об'єкт іншого класу
        if (type_name != vehicle.GetTypeName()) {
            throw logic_error("У файлі об'єкт " + type_name + ", а не " +
                vehicle.GetTypeName() + "!");
        }
        // Виняток 7: дані пошкоджені (кидає метод Read)
        vehicle.Read(in);
        in.close();

        cout << "Об'єкт прочитано з файлу: ";
        vehicle.DisplayVehicleInfo();
    }
    catch (const invalid_argument& e) {
        cout << "  [Помилка 1] " << e.what() << "\n";
    }
    catch (const domain_error& e) {
        cout << "  [Помилка 2] " << e.what() << "\n";
    }
    catch (const logic_error& e) {
        cout << "  [Помилка 6] " << e.what() << "\n";
    }
    catch (const ios_base::failure& e) {
        cout << "  [Помилка 3/4] " << e.what() << "\n";
    }
    catch (const range_error& e) {
        cout << "  [Помилка 7] " << e.what() << "\n";
    }
    catch (const runtime_error& e) {
        cout << "  [Помилка 5] " << e.what() << "\n";
    }
    catch (...) {
        cout << "  [Невідома помилка]\n";
    }
}