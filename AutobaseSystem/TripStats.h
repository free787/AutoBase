#pragma once
#ifndef TRIP_STATS_H_
#define TRIP_STATS_H_

#include <iostream>
#include <string>

// Лаб 6, п. 5: шаблон класу - статистика рейсів.
// T може бути int (пасажири), double (кілометри) або
// користувацький клас Cargo (вантаж).
// Від типу T потрібні оператори: =, +, <, > і виведення <<.
template <typename T>
class TripStats {
public:
    explicit TripStats(std::string title);

    void Add(const T& value);
    void Print() const;
    void Clear();

    T GetFirst() const { return first_; }
    T GetLast() const { return last_; }
    T GetMin() const { return min_; }
    T GetMax() const { return max_; }
    T GetTotal() const { return total_; }
    int GetCount() const { return count_; }

private:
    std::string title_;
    // Лаб 6, п. 5: п'ять шаблонних даних
    T first_;  // перше значення
    T last_;   // останнє значення
    T min_;    // найменше
    T max_;    // найбільше
    T total_;  // сума всіх
    int count_;
};

// Лаб 6, п. 5: шаблонні методи класу

template <typename T>
TripStats<T>::TripStats(std::string title)
    : title_(title), first_(), last_(), min_(), max_(), total_(), count_(0) {}

template <typename T>
void TripStats<T>::Add(const T& value) {
    if (count_ == 0) {
        first_ = value;
        min_ = value;
        max_ = value;
        total_ = value;
    }
    else {
        total_ = total_ + value;
        if (value < min_) {
            min_ = value;
        }
        if (value > max_) {
            max_ = value;
        }
    }
    last_ = value;
    count_++;
}

template <typename T>
void TripStats<T>::Print() const {
    std::cout << "--- " << title_ << " ---\n";
    if (count_ == 0) {
        std::cout << "Даних немає\n";
        return;
    }
    std::cout << "Кількість записів: " << count_ << "\n"
        << "Перше:   " << first_ << "\n"
        << "Останнє: " << last_ << "\n"
        << "Мінімум: " << min_ << "\n"
        << "Максимум: " << max_ << "\n"
        << "Разом:   " << total_ << "\n";
}

template <typename T>
void TripStats<T>::Clear() {
    first_ = T();
    last_ = T();
    min_ = T();
    max_ = T();
    total_ = T();
    count_ = 0;
}

#endif  // TRIP_STATS_H_