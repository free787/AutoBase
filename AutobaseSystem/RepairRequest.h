#ifndef REPAIR_REQUEST_H_
#define REPAIR_REQUEST_H_

#include <string>

// Лаб 5, п. 3: заявка на ремонт - клас з НЕвіртуальним деструктором
// (для порівняння з віртуальними деструкторами у класах машин)
class RepairRequest {
public:
	explicit RepairRequest(std::string plate);

	// Лаб 5, п. 3: невіртуальний деструктор (навмисно)
	~RepairRequest();

	// Лаб 5, п. 4: віртуальна функція
	virtual void Describe() const;

protected:
	std::string plate_;
};

// Лаб 5, п. 3: термінова заявка - виділяє динамічну пам'ять під запчастини
class UrgentRepairRequest : public RepairRequest {
public:
	UrgentRepairRequest(std::string plate, int parts_count);
	~UrgentRepairRequest();

	// Лаб 5, п. 4: перевизначена віртуальна функція
	void Describe() const override;

private:
	int* parts_;  // динамічний масив кодів запчастин
	int parts_count_;
};

#endif  // REPAIR_REQUEST_H_