#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <sstream>
#include "supply_struct.h"
#include "stuff.h"
#include "checkInput.h"
#include <unordered_map>
#define NUMBER_OF_ELEMENTS_TO_FIND 3
// Поиск, сортировка структуры Supplier
void SortSuppliersByAddress(std::vector<std::shared_ptr<Supplier>>& suppliers) {
	std::sort(suppliers.begin(), suppliers.end(),
		[](const std::shared_ptr<Supplier>& a, const std::shared_ptr<Supplier>& b) {
			return a->address < b->address;
		}); // сортировка с помощью метода sort и компаратора в виде лямбда функции
}

void SearchSupplierByPhone(std::vector<std::shared_ptr<Supplier>>& suppliers) {
	
	FindMaxLengthSupplier(suppliers, SUPPLIER::fields);
	std::cout << "Введите номер телефона, по которому хотите найти поставщика\n";
	std::string phone;
	bool found = false;
	phone = PhoneInput();
	

	for (auto& value : suppliers){
	
		if (phone == value->phone) {
			PrintOneSupplier(value, SUPPLIER::fields, SUPPLIER::namings, !found);
			if (!found) {
				found = true;
			}
		}
	}
	if (!found) {
		std::cout << "Поставщик с таким номером телефона не найден." << std::endl;
	}
	ClearConsoleEnter();
}

void SearchSupplierByAdress(std::vector<std::shared_ptr<Supplier>>& suppliers) {
	
	FindMaxLengthSupplier(suppliers, SUPPLIER::fields);

	std::cout << "Введите номер адрес, по которому хотите найти поставщика\n";
	std::string adress;
	bool found = false;
	adress = StringInput();

	for (auto& value : suppliers) {
		if (adress == value->address) {
			PrintOneSupplier(value, SUPPLIER::fields, SUPPLIER::namings, !found);
			if (!found) {
				found = true;
			}
		}
	}
	if (!found) {
		std::cout << "Поставщик с таким адресом не найден." << std::endl;
	}
	ClearConsoleEnter();
}

/********************************************************************************************/

// Поиск, фильтр, сортировка структуры Parts
void SearchPartsByName(std::vector<std::shared_ptr<Parts>>& parts) {
	
	FindMaxLengthParts(parts, PARTS::fields);

	std::cout << "Введите название детали, которую вы хотите найти\n";
	std::string name{ "" };
	name = StringInput();
	std::cout << std::endl << std::endl;
	bool found{ false };

	for (auto& value : parts) {
		if (name == value->name) {
			PrintOnePart(value, PARTS::fields, PARTS::namings, !found);
			if (!found) {
				found = true;
			}
		}
	}
	if (found == false) {
		std::cout << "Файл пустой либо Вы ввели неверные данные.\n";
	}
	ClearConsoleEnter();
}

void SearchPartsByVendorCode(std::vector<std::shared_ptr<Parts>>& parts) {
	
	FindMaxLengthParts(parts, PARTS::fields);
	std::cout << "Введите артикул детали, которую вы хотите найти\n";
	int vendor_code{ 0 };
	vendor_code = IntInput();
	std::cout << std::endl << std::endl;
	bool found{ false };

	for (auto& value : parts) {
		if (vendor_code == value->vendor_code) {
			PrintOnePart(value, PARTS::fields, PARTS::namings, !found);
			if (!found) {
				found = true;
			}
		}
	}
	if (found == false) {
		std::cout << "Файл пустой либо Вы ввели неверные данные.\n";
	}
	ClearConsoleEnter();
}

void SearchPartsByPrice(std::vector<std::shared_ptr<Parts>>& parts) {

	FindMaxLengthParts(parts, PARTS::fields);
	std::cout << "Введите цену детали, которую вы хотите найти\n";
	double price{ 0.0 };
	price = DoubleInput();
	std::cout << std::endl << std::endl;
	bool found{ false };

	for (auto& value : parts) {
		if (price == value->price) {
			PrintOnePart(value, PARTS::fields, PARTS::namings, !found);
			if (!found) {
				found = true;
			}

		}
	}
	if (found == false) {
		std::cout << "Файл пустой либо Вы ввели неверные данные.\n";
	}
	ClearConsoleEnter();
}

void FilterPartsByPrice(std::vector<std::shared_ptr<Parts>>& parts) {
	
	FindMaxLengthParts(parts, PARTS::fields);
	double min_price{ 0.0 }, max_price = { 0.0 };
	std::cout << "Введите минимальную цену: ";
	min_price = DoubleInput();
	std::cout << "Введите максимальную цену: ";
	max_price = DoubleInput();
	std::cout << std::endl << std::endl;
	bool found{ false };

	for (auto& value : parts) {
		if (min_price <= value->price and value->price <= max_price) {
			PrintOnePart(value, PARTS::fields, PARTS::namings, !found);
			if (!found) {
				found = true;
			}
		}
	}
	if (found == false) {
		std::cout << "Файл пустой либо Вы ввели неверные данные.\n";
	}
	ClearConsoleEnter();
}

void FilterPartsByVendorCode(std::vector<std::shared_ptr<Parts>>& parts) {

	FindMaxLengthParts(parts, PARTS::fields);
	int min_vendor_code{ 0 }, max_vendor_code = { 0 };
	std::cout << "Введите артикул (нижняя граница): ";
	min_vendor_code = IntInput();
	std::cout << "Введите артикул (верхняя граница): ";
	max_vendor_code = IntInput();
	std::cout << std::endl << std::endl;
	bool found{ false };

	for (auto& value : parts) {
		if (min_vendor_code <= value->vendor_code and value->vendor_code <= max_vendor_code) {
			PrintOnePart(value, PARTS::fields, PARTS::namings, !found);
			if (!found) {
				found = true;
			}
		}
	}
	if (found == false) {
		std::cout << "Файл пустой либо Вы ввели неверные данные.\n";
	}
	ClearConsoleEnter();
}

void SortPartsByName(std::vector<std::shared_ptr<Parts>>& parts) {
	std::sort(parts.begin(), parts.end(),
		[](const std::shared_ptr<Parts>& a, const std::shared_ptr<Parts>& b) {
			return a->name < b->name;
		}); // сортировка с помощью метода sort и компаратора в виде лямбда функции
}

void SortPartsByPrice(std::vector<std::shared_ptr<Parts>>& parts) {
	std::sort(parts.begin(), parts.end(),
		[](const std::shared_ptr<Parts>& a, const std::shared_ptr<Parts>& b) {
			return a->price < b->price;
		}); // сортировка с помощью метода sort и компаратора в виде лямбда функции
}

void SortPartsByVendorCode(std::vector<std::shared_ptr<Parts>>& parts) {
	std::sort(parts.begin(), parts.end(),
		[](const std::shared_ptr<Parts>& a, const std::shared_ptr<Parts>& b) {
			return a->vendor_code < b->vendor_code;
		}); // сортировка с помощью метода sort и компаратора в виде лямбда функции
}

/********************************************************************************************/

// Поиск, фильтр, сортировка структуры Supply
void SearchSupplyByDate(std::vector<std::shared_ptr<Supply>>& supply) {
	
	FindMaxLengthSupply(supply, SUPPLY::fields);
	std::cout << "Введите дату, по которой вы хотите найти поставку\n";
	std::string date{ "" };
	date = DateInput();
	std::cout << std::endl << std::endl;
	bool found{ false };

	for (auto& value : supply) {
		if (date == value->date) {
			PrintOneSupply(value, SUPPLY::fields, SUPPLY::namings, !found);
			if (!found) {
				found = true;
			}
		}
	}
	if (found == false) {
		std::cout << "Файл пустой либо Вы ввели неверные данные.\n";
	}
	ClearConsoleEnter();
}

void SearchSupplyByQuantity(std::vector<std::shared_ptr<Supply>>& supply) {

	FindMaxLengthSupply(supply, SUPPLY::fields);
	std::cout << "Введите количество деталей, по которому вы хотите найти поставку\n";
	int quantity{ 0 };
	quantity = IntInput();
	std::cout << std::endl << std::endl;
	bool found{ false };

	for (auto& value : supply) {
		if (quantity == value->quantity) {
			PrintOneSupply(value, SUPPLY::fields, SUPPLY::namings, !found);
			if (!found) {
				found = true;
			}
		}
	}
	if (found == false) {
		std::cout << "Файл пустой либо Вы ввели неверные данные.\n";
	}
	ClearConsoleEnter();
}

bool CompareDates(std::shared_ptr<Supply>& date1, std::shared_ptr<Supply>& date2) {
	std::istringstream ss1(date1->date);
	std::istringstream ss2(date2->date);
	char dot;

	int day1, month1, year1, day2, month2, year2;

	ss1 >> day1 >> dot >> month1 >> dot >> year1;
	ss2 >> day2 >> dot >> month2 >> dot >> year2;

	if (year1 != year2) {
		return year1 <= year2;
	}
	if (month1 != month2) {
		return month1 <= month2;
	}

	return day1 <= day2;
}

void FilterSupplyByDate(std::vector<std::shared_ptr<Supply>>& supply) {
	
	FindMaxLengthSupply(supply, SUPPLY::fields);
	std::string min_date{ "" }, max_date{ "" };
	std::cout << "Введите дату (нижняя граница): ";
	min_date = DateInput();
	std::cout << "Введите дату (верхняя граница): ";
	max_date = DateInput();
	std::cout << std::endl << std::endl;
	bool found{ false };
	std::shared_ptr<Supply> date1 = std::make_shared<Supply>();
	std::shared_ptr<Supply> date2 = std::make_shared<Supply>();
	date1->date = min_date;
	date2->date = max_date;

	for (auto& value : supply) {
		if (CompareDates(date1, value) and CompareDates(value, date2)) {
			PrintOneSupply(value, SUPPLY::fields, SUPPLY::namings, !found);
			if (!found) {
				found = true;
			}
		}
	}
	if (found == false) {
		std::cout << "Файл пустой либо Вы ввели неверные данные.\n";
	}
	ClearConsoleEnter();
}

void FilterSupplyByQuantity(std::vector<std::shared_ptr<Supply>>& supply) {

	FindMaxLengthSupply(supply, SUPPLY::fields);
	double min_quantity{ 0.0 }, max_quantity{ 0.0 };
	std::cout << "Введите наименьшее количество (нижняя граница): ";
	min_quantity = DoubleInput();
	std::cout << "Введите максимальное количество (верхняя граница): ";
	max_quantity = DoubleInput();
	std::cout << std::endl << std::endl;
	bool found{ false };


	for (auto& value : supply) {
		if (min_quantity <= value->quantity and value->quantity <= max_quantity) {
			PrintOneSupply(value, SUPPLY::fields, SUPPLY::namings, !found);
			if (!found) {
				found = true;
			}
		}
	}
	if (found == false) {
		std::cout << "Файл пустой либо Вы ввели неверные данные.\n";
	}
	ClearConsoleEnter();
}

void SortSupplyByDate(std::vector<std::shared_ptr<Supply>>& supply) {

	std::sort(supply.begin(), supply.end(), CompareDates);
}

void SortSupplyByQuantity(std::vector<std::shared_ptr<Supply>>& supply) {
	std::sort(supply.begin(), supply.end(), 
		[](const std::shared_ptr<Supply>& a, const std::shared_ptr<Supply>& b) {
			return a->quantity < b->quantity;
		});
}

/********************************************************************************************/

/***********************************ЗАДАНИЕ**************************************************/
/*
*
*  Вывести список из 3 самых востребованных деталей в этом году
*
*/

std::vector<int> findTop3Frequent(const std::vector<int>& nums, const int& k) {
	
	std::unordered_map<int, int> freqMap;

	for (int num : nums) {
		freqMap[num]++;
	}

	std::vector<std::pair<int, int>> freqVec(freqMap.begin(), freqMap.end());
	std::sort(freqVec.begin(), freqVec.end(),
		[](const std::pair<int, int>& a, const std::pair<int, int>& b) {
			return a.second > b.second;
		});

	std::vector<int> result;
	for (int i = 0; i < k && i < freqVec.size(); i++) {
		result.push_back(freqVec[i].first);
	}

	return result;
}

bool contains(const std::vector<int>& parts, int elementToFind) {
	return std::find(parts.begin(), parts.end(), elementToFind) != parts.end();
}

void FindFrequentParts() {
    /* Самые востребованные детали - те, которые
	* чаще всего встречаются в поставках, поэтому
	* в векторе с поставками ищем те ID деталей, 
	* которые встречаются чаще всего, а после выводим
	* их на экран.
	*/
	std::vector<std::shared_ptr<Supply>> vector;
	ReadSupplyFromFile(vector, SUPPLY_FILE);

	std::vector<int> part_id, top3;
	for (auto& value : vector) {
		part_id.push_back(value->part_id);
	}
	top3 = findTop3Frequent(part_id, NUMBER_OF_ELEMENTS_TO_FIND);
	for (auto& value : top3) {		
	}
	std::vector<std::shared_ptr<Parts>> parts;
	ReadPartsFromFile(parts, PART_FILE);
	FindMaxLengthParts(parts, PARTS::fields);

	bool found = { false };
	for (auto& value : parts) {
		if (contains(top3, value->part_id)) {
			PrintOnePart(value, PARTS::fields, PARTS::namings, !found);
			if (!found)
				found = true;
		}
	}
	
	ClearConsoleEnter();
}