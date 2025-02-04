#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "stuff.h"
#include "supply_struct.h"

/***************************************МЕТОДЫ ДЛЯ ПЕЧАТИ ВВЕРХА И НИЗА ТАБЛИЦЫ****************************/
void PrintRepeatedChar(char c, size_t count) {
	if (count > 100) {
		return;
	}
	for (size_t i = 0; i < count; ++i) {
		std::cout << c;
	}
}

void PrintTopTable(std::vector<size_t>& fields, std::vector<std::string>& namings) {

	for (int i = 0; i < fields.size(); i++) {
		std::cout << "+";
		PrintRepeatedChar('-', fields[i] + (size_t)2);
	}
	std::cout << "+" << std::endl;

	for (int i = 0; i < namings.size(); i++) {
		std::cout << "|" << namings[i];
		PrintRepeatedChar(' ', fields[i] - namings[i].length() + (size_t)2);
	}
	std::cout << "|" << std::endl;

	for (int i = 0; i < namings.size(); i++) {
		std::cout << "+";
		PrintRepeatedChar('-', fields[i] + 2);
	}
	std::cout << "+" << std::endl;
}

void PrintDownTable(std::vector<size_t>& fields) {
	for (int i = 0; i < fields.size(); i++) {
		std::cout << "+";
		PrintRepeatedChar('-', fields[i] + (size_t)2);
	}
	std::cout << "+" << std::endl;
}
/**********************************************************************************************************/

/**************************************МЕТОДЫ ДЛЯ НАХОЖДЕНИЯ ДЛИНЫ КАЖДОГО СТОЛБЦА ТАБЛИЦЫ*****************/
void FindMaxLengthSupplier(std::vector<std::shared_ptr<Supplier>>& vector, 
	std::vector<size_t> &fields) {

	for (int i = 0; i < vector.size(); i++) {
		if (std::to_string(vector[i]->supplier_id).length() > fields[0]) {
			fields[0] = std::to_string(vector[i]->supplier_id).length() + 1;
		}
		if (vector[i]->address.length() > fields[1]) {
			fields[1] = vector[i]->address.length();
		}
	}
}

void FindMaxLengthSupply(std::vector<std::shared_ptr<Employee>>& vector,
	std::vector<size_t>& fields) {

	for (int i = 0; i < vector.size(); i++) {
		if (std::to_string(vector[i]->supplier_id).length() > fields[0]) {
			fields[0] = std::to_string(vector[i]->supplier_id).length() + 1;
		}
		if (std::to_string(vector[i]->part_id).length() > fields[1]) {
			fields[1] = std::to_string(vector[i]->part_id).length() + 1;
		}
		if (std::to_string(vector[i]->quantity).length() > fields[2]) {
			fields[2] = std::to_string(vector[i]->quantity).length() + 1;
		}
		if (vector[i]->date.length() > fields[3]) {
			fields[3] = vector[i]->date.length() + 1;
		}		
	}
}

void FindMaxLengthUserAdmin(std::vector<std::shared_ptr<User>>& vector,
	std::vector<size_t>& fields) {
	for (int i = 0; i < vector.size(); i++) {

		if (vector[i]->login.length() > fields[0]) {
			fields[0] = vector[i]->login.length();
		}
		if (vector[i]->password.length() > fields[1]) {
			fields[1] = vector[i]->password.length();
		}
	}
}

void FindMaxLengthParts(std::vector<std::shared_ptr<Parts>>& vector,
	std::vector<size_t>& fields) {
	for (int i = 0; i < vector.size(); i++) {

		if (std::to_string(vector[i]->part_id).length() > fields[0]) {
			fields[0] = std::to_string(vector[i]->part_id).length() + 1;
		}
		if (vector[i]->name.length() > fields[1]) {
			fields[1] = vector[i]->name.length();
		}
		if (std::to_string(vector[i]->vendor_code).length() > fields[2]) {
			fields[2] = std::to_string(vector[i]->vendor_code).length();
		}
		if (lengthOfDouble(vector[i]->price) > fields[3]) {
			fields[3] = lengthOfDouble(vector[i]->price);
		}
		if (vector[i]->note.length() > fields[4]) {
			fields[4] = vector[i]->note.length();
		}
	}
}
/**********************************************************************************************************/

/************************************МЕТОДЫ ДЛЯ ВЫВОДА САМИХ ТАБЛИЦ (4 штуки)******************************/
void PrintDynamicTableSupplier(std::vector<std::shared_ptr<Supplier>>& vector,
	std::vector<size_t>& fields, std::vector<std::string>& namings) {

	PrintTopTable(fields, namings);

	for (size_t index = 0; index < vector.size(); index++) {

		std::cout << "|" << vector[index]->supplier_id;
		PrintRepeatedChar(' ', fields[0] - std::to_string(vector[index]->supplier_id).length() + (size_t)2);

		std::cout << "|" << vector[index]->address;
		PrintRepeatedChar(' ', fields[1] - vector[index]->address.length() + (size_t)2);

		std::cout << "|" << vector[index]->phone;
		PrintRepeatedChar(' ', fields[2] - vector[index]->phone.length() + (size_t)2);

		std::cout << "|" << std::endl;

		PrintDownTable(fields);
	}
}

void PrintDynamicTableSupply(std::vector<std::shared_ptr<Employee>>& vector,
	std::vector<size_t>& fields, std::vector<std::string>& namings) {

	PrintTopTable(fields, namings);

	for (size_t index = 0; index < vector.size(); index++) {

		std::cout << "|" << vector[index]->supplier_id;
		PrintRepeatedChar(' ', fields[0] - std::to_string(vector[index]->supplier_id).length() + (size_t)2);

		std::cout << "|" << vector[index]->part_id;
		PrintRepeatedChar(' ', fields[1] - std::to_string(vector[index]->part_id).length() + (size_t)2);

		std::cout << "|" << vector[index]->quantity;
		PrintRepeatedChar(' ', fields[2] - std::to_string(vector[index]->quantity).length() + (size_t)2);

		std::cout << "|" << vector[index]->date;
		PrintRepeatedChar(' ', fields[3] - vector[index]->date.length() + (size_t)2);

		std::cout << "|" << std::endl;

		PrintDownTable(fields);
	}
}

void PrintDynamicTableUserAdmin(std::vector<std::shared_ptr<User>>& vector,
	std::vector<size_t>& fields, std::vector<std::string>& namings) {

	PrintTopTable(fields, namings);

	for (size_t index = 0; index < vector.size(); index++) {

		std::cout << "|" << vector[index]->login;
		PrintRepeatedChar(' ', fields[0] - vector[index]->login.length() + (size_t)2);

		std::cout << "|" << vector[index]->password;
		PrintRepeatedChar(' ', fields[1] - vector[index]->password.length() + (size_t)2);

		std::cout << "|" << std::endl;

		PrintDownTable(fields);
	}
}

void PrintDynamicTableParts(std::vector<std::shared_ptr<Parts>>& vector,
	std::vector<size_t>& fields, std::vector<std::string>& namings) {

	PrintTopTable(fields, namings);

	for (size_t index = 0; index < vector.size(); index++) {

		std::cout << "|" << vector[index]->part_id;
		PrintRepeatedChar(' ', fields[0] - std::to_string(vector[index]->part_id).length() + (size_t)2);

		std::cout << "|" << vector[index]->name;
		PrintRepeatedChar(' ', fields[1] - vector[index]->name.length() + (size_t)2);

		std::cout << "|" << vector[index]->vendor_code;
		PrintRepeatedChar(' ', fields[2] - std::to_string(vector[index]->vendor_code).length() + (size_t)2);

		std::cout << "|" << vector[index]->price;
		PrintRepeatedChar(' ', fields[3] - lengthOfDouble(vector[index]->price) + (size_t)2);

		std::cout << "|" << vector[index]->note;
		PrintRepeatedChar(' ', fields[4] - vector[index]->note.length() + (size_t)2);

		std::cout << "|" << std::endl;
		PrintDownTable(fields);
	}
}
/**********************************************************************************************************/
