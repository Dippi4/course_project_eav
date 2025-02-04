#pragma once
#include <iostream>

struct Supplier { // поставщики
	int supplier_id{ 0 }; // id
	std::string address{ "" }; // адрес
	std::string phone{ "" }; // телефонный номер
}; // 3

struct Parts { // детали
	int part_id{ 0 }; // id
 	std::string name{ "" }; // название
	int vendor_code{ 0 }; // артикул
	double price{ 0.0 }; // цена
	std::string note{ "" }; // примечание
}; // 5

struct Employee { // поставки
	int supplier_id{ 0 }; // id поставщика
	int part_id{ 0 }; // id детали
	int quantity{ 0 }; // количество деталей
	std::string date{ "" }; // дата 
}; // 4
