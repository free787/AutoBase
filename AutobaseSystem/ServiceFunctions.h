#ifndef SERVICE_FUNCTIONS_H_
#define SERVICE_FUNCTIONS_H_

#include "Vehicle.h"
#include "Car.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <new>

// ==========================================
// [Лаб 5, П. 6] Видалення об'єктів з масивів за критерієм
// Передбачено 3 виключні ситуації з динамічною пам'яттю (try-catch, throw).
// ==========================================
void Service_Static(Car arr[], int& size, double fuel_criterion) {
    try {
        if (size < 0 || size > 100) throw std::out_of_range("Невірний розмір статичного масиву!"); // Виняток 1
        if (arr == nullptr) throw std::invalid_argument("Масив не існує (nullptr)!"); // Виняток 2

        int new_size = 0;
        for (int i = 0; i < size; i++) {
            if (arr[i].fuel_level >= fuel_criterion) {
                arr[new_size++] = arr[i]; // Залишаємо авто, в якого достатньо пального
            }
        }
        std::cout << "Видалено " << (size - new_size) << " авто з недостатнім пальним.\n";
        size = new_size;

        // Виняток 3: Симуляція помилки пам'яті, якщо видалили всі авто
        if (size == 0) throw std::bad_alloc();

    }
    catch (const std::out_of_range& e) {
        std::cerr << "Помилка меж: " << e.what() << "\n";
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Помилка аргументу: " << e.what() << "\n";
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Помилка виділення пам'яті (усі авто видалено).\n";
    }
}

void Service_Dynamic(Car** arr, int& size, double fuel_criterion) {
    try {
        if (size < 0) throw std::out_of_range("Від'ємний розмір динамічного масиву!");
        if (arr == nullptr) throw std::invalid_argument("Динамічний масив не ініціалізовано!");
        int new_size = 0;
        for (int i = 0; i < size; i++) {
            if (arr[i]->fuel_level >= fuel_criterion) {
                arr[new_size++] = arr[i];
            }
            else {
                delete arr[i];
            } // Знищуємо об'єкт у динамічній пам'яті
        }
        std::cout << "Динамічно видалено " << (size - new_size) << " авто.\n";
        size = new_size;
        if (size == 0) throw std::bad_alloc();
    }
    catch (const std::exception& e) {
        std::cerr << "Помилка динамічного сервісу: " << e.what() << "\n";
    }
}

// ==========================================
// [Лаб 5, П. 7] Запис та зчитування об'єкта з файлу (Service)
// Передбачено 5 виключних ситуацій (try-catch, throw).
// ==========================================
void Service(Vehicle* v, const std::string& filename) {
    try {
        if (!v) throw std::invalid_argument("Передано порожній вказівник на об'єкт!"); // Файловий виняток 1
        if (filename.empty()) throw std::runtime_error("Ім'я файлу порожнє!"); // Файловий виняток 2

        std::ofstream out(filename);
        if (!out.is_open()) throw std::ios_base::failure("Не вдалося відкрити файл для запису!"); // Файловий виняток 3
        v->WriteToFile(out);
        out.close();

        std::ifstream in(filename);
        if (!in.is_open()) throw std::ios_base::failure("Не вдалося відкрити файл для читання!"); // Файловий виняток 4
        v->ReadFromFile(in);

        if (in.bad()) throw std::logic_error("Помилка цілісності даних при читанні!"); // Файловий виняток 5
        in.close();

        std::cout << "Файлові операції успішно завершено. Дані записано у " << filename << "\n";

    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Помилка файлу [1]: " << e.what() << "\n";
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Помилка файлу [2]: " << e.what() << "\n";
    }
    catch (const std::ios_base::failure& e) {
        std::cerr << "Помилка файлу [3/4]: " << e.what() << "\n";
    }
    catch (const std::logic_error& e) {
        std::cerr << "Помилка файлу [5]: " << e.what() << "\n";
    }
    catch (...) { std::cerr << "Невідома помилка роботи з файлом!\n"; }
}

#endif