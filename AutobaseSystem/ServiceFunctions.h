#ifndef SERVICE_FUNCTIONS_H_
#define SERVICE_FUNCTIONS_H_

#include <string>

#include "Car.h"
#include "Vehicle.h"

// Лаб 5, п. 6: видалення з масивів авто, випущених раніше min_year
void Service_Static(Car arr[], int& size, int min_year);
void Service_Dinamic(Vehicle* arr[], int& size, int min_year);

// Лаб 5, п. 5: безпечний доступ до об'єкта в динамічному масиві
Vehicle* GetVehicle(Vehicle* arr[], int size, int index);

// Лаб 5, п. 7: запис об'єкта у файл і читання з файлу (Write / Read)
// only_read = true - тільки читання з уже існуючого файлу
void Service(Vehicle& vehicle, const std::string& filename,
    bool only_read = false);

#endif  // SERVICE_FUNCTIONS_H_