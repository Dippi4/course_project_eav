#pragma once
#define NOMINMAX
#include <iostream>
#include <sstream>
#include "screen_cleaner.h"

/******************ФУНКЦИИ ДЛЯ ВВОДА С ПРОВЕРКАМИ*********************/

char CharInput(std::string& hint) {
	char choice;
	while (1) {
		std::cout << hint;
		std::cin >> choice;
		ClearConsole();

		if (!isdigit(choice)) {
			std::cout << "Ошибка: пожалуйста, введите число." << std::endl;
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			ClearConsoleEnter();
			continue;
		}
		else {
			char c = getchar(); // C6031
			return choice;
		}
	}

}

bool isValidDateNumbers(int day, int month, int year) {
	if (day >= 1 and day <= 31 and
		month >= 1 and month <= 12) {
		return true;
	}
	else {
		return false;
	}
}

bool isValidDateFormat(const std::string& input) {
	std::istringstream iss(input);
	int num1, num2, num3;
	char dot1, dot2;

	if ((iss >> num1 >> dot1 >> num2 >> dot2 >> num3 && dot1 == '.' && dot2 == '.')
		and isValidDateNumbers(num1, num2, num3)) {
		return true;
	}
	else {
		return false;
	}
}

std::string DateInput() {

	std::string input;
	while (1) {
		std::cout << "Введите дату в таком формате dd.mm.yy\n";
		getline(std::cin, input);
		if (!isValidDateFormat(input)) {
			std::cout << "Попробуйте ещё раз\n";
		}
		else {
			break;
		}
	}
	return input;
}

double DoubleInput() {
	double double_value = -1.0;
	while (double_value < 0.0) {
		while (!(std::cin >> double_value)) {
			std::cout << "Неверный ввод, попробуйте ещё раз." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return double_value;
}

int IntInput() {
	int int_value = -1;
	while (int_value < 0) {
		while (!(std::cin >> int_value)) {
			std::cout << "Неверный ввод, попробуйте ещё раз." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return int_value;
}

int IntInputWithBounds(int a, int b) {
	int x;
	while (!(std::cin >> x) ||
		(std::cin.peek() != '\n') ||
		(x < a) || (x > b) || x < 0) {

		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Неверный ввод, попробуйте ещё раз.\n";
	}
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return x;
}

bool hasDigits(const std::string& str) {
	// функция проверяет строку на нахождение в ней цифр 
	for (char c : str) {
		if (std::isdigit(c)) {
			return true;
		}
	}
	return false;
}

void ClearInputBuffer() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string StringInput() {
	// ввод строки, который гарантирует, что возвращенная строка 
	// не будет содержать цифры
	std::string input;
	while (1) {
		getline(std::cin, input);
		if (input.find_first_not_of(" \t\n") == std::string::npos)
			continue;
		if (hasDigits(input)) {
			std::cout << "Строка не должна содержать цифры.\n";
		}
		else {
			break;
		}
	}
	return input;
}

std::string PhoneInput() {
	// ввод номера телефона (адапитрована под c++, функция из примера)
	std::string input{ "+375(44)" };
	int phone_number{ 0 };

	std::cout << "Введите номер телефона\n(+375(44)*******)\n";

	phone_number = IntInputWithBounds(1000000, 9999999);
	input += std::to_string(phone_number);

	return input;
}
/*********************************************************************/