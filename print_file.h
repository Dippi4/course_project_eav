#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "supply_struct.h"
#include "user_struct.h"
#include "table_handler.h"
#include "screen_cleaner.h"
#include "stuff.h"

/************************************МЕТОДЫ ДЛЯ ПЕЧАТИ ТАБЛИЦ****************************************/
void PrintSuppliersFromVector(std::vector<std::shared_ptr<Supplier>>& vector, bool flag) {
	resetValuesNamespace();
	FindMaxLengthSupplier(vector, SUPPLIER::fields);
	PrintDynamicTableSupplier(vector, SUPPLIER::fields, SUPPLIER::namings);
	if (flag)
		ClearConsoleEnter();
}

void PrintSupplyFromVector(std::vector<std::shared_ptr<Supply>>& vector, bool flag) {
	resetValuesNamespace();
	FindMaxLengthSupply(vector, SUPPLY::fields);
	PrintDynamicTableSupply(vector, SUPPLY::fields, SUPPLY::namings);
	if (flag)
		ClearConsoleEnter();
}

void PrintUsersFromVector(std::vector<std::shared_ptr<User>>& vector, bool flag) {
	resetValuesNamespace();
	FindMaxLengthUserAdmin(vector, USER::fields);
	PrintDynamicTableUserAdmin(vector, USER::fields, USER::namings);
	if (flag)
		ClearConsoleEnter();
}

void PrintPartsFromVector(std::vector<std::shared_ptr<Parts>>& vector, bool flag) {
	resetValuesNamespace();
	FindMaxLengthParts(vector, PARTS::fields);
	PrintDynamicTableParts(vector, PARTS::fields, PARTS::namings);
	if (flag)
		ClearConsoleEnter();
}

void PrintOneSupply(std::shared_ptr<Supply>& supply, 
	std::vector<size_t>& fields, std::vector<std::string>&namings, bool flag) {

	if (flag) {
		PrintTopTable(SUPPLY::fields, SUPPLY::namings);
	}
	std::cout << "|" << supply->supplier_id;
	PrintRepeatedChar(' ', fields[0] - std::to_string(supply->supplier_id).length() + (size_t)2);

	std::cout << "|" << supply->part_id;
	PrintRepeatedChar(' ', fields[1] - std::to_string(supply->part_id).length() + (size_t)2);

	std::cout << "|" << supply->quantity;
	PrintRepeatedChar(' ', fields[2] - std::to_string(supply->quantity).length() + (size_t)2);

	std::cout << "|" << supply->date;
	PrintRepeatedChar(' ', fields[3] - supply->date.length() + (size_t)2);

	std::cout << "|" << std::endl;


	PrintDownTable(SUPPLY::fields);
}

void PrintOneSupplier(std::shared_ptr<Supplier>& supplier,
	std::vector<size_t>& fields, std::vector<std::string>& namings, bool flag) {

	
	if (flag) {
		PrintTopTable(SUPPLIER::fields, SUPPLIER::namings);
	}
	std::cout << "|" << supplier->supplier_id;
	PrintRepeatedChar(' ', fields[0] - std::to_string(supplier->supplier_id).length() + (size_t)2);

	std::cout << "|" << supplier->address;
	PrintRepeatedChar(' ', fields[1] - supplier->address.length() + (size_t)2);

	std::cout << "|" << supplier->phone;
	PrintRepeatedChar(' ', fields[2] - supplier->phone.length() + (size_t)2);

	std::cout << "|" << std::endl;


	PrintDownTable(SUPPLIER::fields);
}

void PrintOnePart(std::shared_ptr<Parts>& parts,
	std::vector<size_t>& fields, std::vector<std::string>& namings, bool flag) {
		
	if (flag) {
		PrintTopTable(PARTS::fields, PARTS::namings);
	}
	std::cout << "|" << parts->part_id;
	PrintRepeatedChar(' ', fields[0] - std::to_string(parts->part_id).length() + (size_t)2);

	std::cout << "|" << parts->name;
	PrintRepeatedChar(' ', fields[1] - parts->name.length() + (size_t)2);

	std::cout << "|" << parts->vendor_code;
	PrintRepeatedChar(' ', fields[2] - std::to_string(parts->vendor_code).length() + (size_t)2);

	std::cout << "|" << parts->price;
	PrintRepeatedChar(' ', fields[3] - lengthOfDouble(parts->price) + (size_t)2);

	std::cout << "|" << parts->note;
	PrintRepeatedChar(' ', fields[4] - parts->note.length() + (size_t)2);

	std::cout << "|" << std::endl;


	PrintDownTable(PARTS::fields);
}
/***********************************************************************************************************************/