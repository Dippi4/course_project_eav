#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "stuff.h"
#include "checkInput.h"
#include "supply_struct.h"
#include "print_file.h"
#include <set>

void ViewSupplierFromFile(const std::string filename, bool flag);

void ViewSupplyFromFile(const std::string filename, bool flag);

void ViewPartsFromFile(const std::string filename, bool flag);

void ViewUsersFromFile(const std::string filename, bool flag);

void ReadSuppliersFromFile(std::vector<std::shared_ptr<Supplier>>& vector, 
	std::string filename) {

	std::ifstream input_file(filename, std::ios::in);
	if (!input_file.is_open()) {
		std::cout << "Ошибка открытия файла " << filename << std::endl;
		return;
	}

	std::string line{ "" };
	int number_of_lines{ 0 };
	while (getline(input_file, line)) {
		if (!line.empty()) {
			number_of_lines++;
		}
	}

	line = { "" };
	input_file.clear();
	input_file.seekg(0, std::ios::beg); // переходим в начало файла
	
	for (int i = 0; i < number_of_lines; ++i) {
		getline(input_file, line);
		std::stringstream ss(line);
		std::shared_ptr<Supplier> supplier = std::make_shared<Supplier>();
		ss >> supplier->supplier_id >> supplier->address >>
			supplier->phone;

		replaceChars(supplier->address, '_', ' ');
		vector.push_back(supplier);
		ss.clear();
	}
	input_file.close();
}

void ReadSupplyFromFile(std::vector<std::shared_ptr<Supply>>& vector,
	std::string filename) {

	std::ifstream input_file(filename, std::ios::in);
	if (!input_file.is_open()) {
		std::cout << "Ошибка открытия файла " << filename << std::endl;
		return;
	}

	std::string line{ "" };
	int number_of_lines{ 0 };
	while (getline(input_file, line)) {
		if (!line.empty()) {
			number_of_lines++;
		}
	}

	line = { "" };
	input_file.clear();
	input_file.seekg(0, std::ios::beg); // переходим в начало файла
	for (int i = 0; i < number_of_lines; ++i) {
		getline(input_file, line);
		std::stringstream ss(line);
		std::shared_ptr<Supply> supply = std::make_shared<Supply>();
		ss >> supply->supplier_id >> supply->part_id >>
			supply->quantity >> supply->date;

		vector.push_back(supply);
		ss.clear();
	}

	input_file.close();
}

void ReadPartsFromFile(std::vector<std::shared_ptr<Parts>>& vector, 
	std::string filename) {

	std::ifstream input_file(filename, std::ios::in);
	if (!input_file.is_open()) {
		std::cout << "Ошибка открытия файла " << filename << std::endl;
		return;
	}

	std::string line{ "" };
	int number_of_lines{ 0 };
	while (getline(input_file, line)) {
		if (!line.empty()) {
			number_of_lines++;
		}
	}

	line = { "" };
	input_file.clear();
	input_file.seekg(0, std::ios::beg); // переходим в начало файла
	for (int i = 0; i < number_of_lines; ++i) {
		getline(input_file, line);
		std::stringstream ss(line);
		std::shared_ptr<Parts> part = std::make_shared<Parts>();
		ss >> part->part_id >> part->name >> part->vendor_code >>
			part->price >> part->note;
			
		replaceChars(part->name, '_', ' ');
		replaceChars(part->note, '_', ' ');
		vector.push_back(part);
		ss.clear();
	}

	input_file.close();
}

void ReadUsersFromFile(std::vector<std::shared_ptr<User>>& vector, const std::string& filename) {

	std::ifstream input_file(filename, std::ios::in);
	if (!input_file.is_open()) {
		std::cout << "Ошибка открытия файла " << filename << std::endl;
		return;
	}

	std::string line;
	int user_number = 0;
	while (getline(input_file, line)) {
		if (!line.empty()) {
			user_number++;
		}
	}

	line = "";
	input_file.clear();
	input_file.seekg(0, std::ios::beg); // переходим в начало файла
	for (int i = 0; i < user_number; ++i) {
		getline(input_file, line);
		std::stringstream ss(line);
		std::shared_ptr<User> users = std::make_shared<User>();
		ss >> users->login >> users->password;

		vector.push_back(users);
	}

	input_file.close();
}

void AddSupplierToFile(std::string filename) {
	Supplier supplier;
	std::cout << "Введите адрес: ";
	supplier.address = StringInput();
	supplier.address = strip(supplier.address); //убираем лишние пробелы (при наличии)
	// заменяем пробелы на другие символы для корректности занесения информации в файл
	replaceChars(supplier.address, ' ', '_'); 
	std::cout << "Телефонный номер: ";
	supplier.phone = PhoneInput();	
	supplier.supplier_id = getSpareID(filename);

	// Открываем файл для добавления новой плательщика в конец
	std::ofstream output_file(filename, std::ios::app);
	if (!output_file.is_open()) {
		std::cout << "Ошибка открытия файла!" << std::endl;
		return;
	}

	output_file << supplier.supplier_id << " " <<
		supplier.address << " " << supplier.phone << "\n";
	output_file.close();
	
	pressEnterMessage("Данные успешно добавлены!");
}

void AddSupplyToFile(std::string filename) {
	
	/**************************************Открываем файлы для чтения********************************/
	std::ifstream suppliers_file(SUPPLIERS_FILE), part_file(PART_FILE);

	if (!suppliers_file.is_open()) {
		std::cerr << "Ошибка открытия файла " << SUPPLIERS_FILE << std::endl;
		return;
	}
	if (!part_file.is_open()) {
		std::cerr << "Ошибка открытия файла " << PART_FILE << std::endl;
		return;
	}
	/************************************************************************************************/

	/**************************************Чтение данных из файла************************************/
	std::string line;
	std::vector<std::string> supplier_lines, part_lines;
	
	while (getline(suppliers_file, line)) {
		supplier_lines.push_back(line);
	}
	suppliers_file.close(); // закрываем файл
	line.clear();
	while (getline(part_file, line)) {
		part_lines.push_back(line);
	}
	part_file.close(); // закрываем файл
	/************************************************************************************************/
	
	/*************************************Ввод данных для поиска*************************************/
	int supplier_id_input{ 0 }, part_id_input{ 0 };
	
	ViewSupplierFromFile(SUPPLIERS_FILE, false);

	std::cout << "Введите ID поставщика: ";
	supplier_id_input = IntInput();

	ViewPartsFromFile(PART_FILE, false);
	
	std::cout << "Введите ID детали: ";
	part_id_input = IntInput();

	/************************************************************************************************/
	
	/************************************Поиск поставщика********************************************/
	bool supplier_found{ false }, part_found{ false };
	size_t isFound{ 0 };
	for (auto& str : supplier_lines) {
		isFound = str.find(std::to_string(supplier_id_input));
		if (isFound != std::string::npos) {
			supplier_found = true;
			break;
		}
	}

	if (!supplier_found) {
		std::cout << "id: " << supplier_id_input << " поставщика не найден в файле."
			<< std::endl;
		return;
	}

	/************************************Поиск детали************************************************/
	isFound = { 0 };

	for (auto& str : part_lines) {
		isFound = str.find(std::to_string(part_id_input));
		if (isFound != std::string::npos) {
			part_found = true;
			break;
		}
	}

	if (!part_found) {
		std::cout << "id: " << part_id_input << " детали не найден в файле."
			<< std::endl;
		return;
	}

	/*****************************Cохранить данные файла в векторе, после их перезаписать************/

	Supply supply;
	supply.supplier_id = supplier_id_input;
	supply.part_id = part_id_input;

	std::cout << "Введите количество деталей:";
	supply.quantity = IntInput();
	std::cout << "Введите дату поставки:";
	supply.date = DateInput();
	

	std::ofstream output_file(filename, std::ios::app);
	if (!output_file.is_open()) {
		std::cout << "Ошибка открытия файла " << filename << std::endl;
		return;
	}
	
	output_file << supply.supplier_id << " " << supply.part_id << " "
		<< supply.quantity << " " << supply.date << std::endl;



	supplier_lines.clear();
	part_lines.clear();
	output_file.close();
	pressEnterMessage("Данные успешно добавлены!");
}

void AddPartsToFile(std::string filename) {
	
	Parts part;
	part.part_id = getSpareID(filename);
	std::cout << "Введите название детали: ";
	part.name = StringInput();
	part.name = strip(part.name);
	replaceChars(part.name, ' ', '_');
	std::cout << "Введите артикул детали: "; 
	part.vendor_code = IntInputWithBounds(0, INT_MAX);
	std::cout << "Введите цену детали: ";
	part.price = DoubleInput();
	std::cout << "Введите примечание (по желанию): ";
	getline(std::cin, part.note);
	if (part.note == "" || part.note == "\n" || part.note == " ") {
		part.note = "примечание отсутствует";
	}
	part.note = strip(part.note);
	replaceChars(part.note, ' ', '_');

	// Открываем файл для добавления нового плательщика в конец
	std::ofstream output_file(filename, std::ios::app);
	if (!output_file.is_open()) {
		std::cout << "Ошибка открытия файла!" << std::endl;
		return;
	}

	output_file << part.part_id << " " << part.name << " " << part.vendor_code <<
		" " << part.price << " " << part.note << "\n";

	output_file.close();
	pressEnterMessage("Данные успешно добавлены!");
}

void EditSupplier(const std::string& filename) {

	/**********************Открытие файла********************************/
	std::fstream file(filename, std::ios::in | std::ios::out);
	if (!file.is_open()) {
		std::cout << "Ошибка открытия файла " << filename << std::endl;
		return;
	}
	/*********************************************************************/
	
	
	/**********************Получение данных из файла**********************/
	std::string line;
	int total_lines{ 0 }, line_to_edit{ 0 }, id{ 0 };
	std::vector<std::string> supplier_lines;
	while (getline(file, line)) {
		supplier_lines.push_back(line);
		total_lines += 1;
	}
	file.close();
	if (total_lines == 0) {
		pressEnterMessage("Файл пустой.\n");
		return;
	}
	ViewSupplierFromFile(filename, false);
	/*********************************************************************/



	// Запрашиваем у пользователя номер строки для редактирования
	std::cout << "Введите номер строки для редактирования: ";
	line_to_edit = IntInputWithBounds(1, total_lines);
	line_to_edit--;
	

	std::stringstream ss(supplier_lines[line_to_edit]);
	ss >> id;
	ss.clear();
	// Запрашиваем у пользователя новые данные

	std::cout << "Введите новые данные:" << std::endl;
	Supplier supplier;
	std::cout << "Введите адрес: ";
	getline(std::cin, supplier.address);
	supplier.address = strip(supplier.address); //убираем лишние пробелы (при наличии)
	// заменяем пробелы на другие символы для корректности занесения информации в файл
	replaceChars(supplier.address, ' ', '_');
	std::cout << "Телефонный номер: ";
	supplier.phone = PhoneInput();
	supplier.supplier_id = id;
	
	ss.str("");
	ss.clear();
	
	ss << supplier.supplier_id << " " <<
		supplier.address << " " << supplier.phone;

	
	std::ofstream output_file(filename, std::ios::trunc);

	if (output_file.fail()) {
		std::cout << "Ошибка открытия файла " << filename << std::endl;
		return;
	}
	else {
		for (int i{ 0 }; i < total_lines; i++) {
			if (i != line_to_edit)
				output_file << supplier_lines[i];
			else
				output_file << ss.str();
			output_file << "\n";
		}
	}

	supplier_lines.clear();
	ss.clear();
	file.close();
	pressEnterMessage("Данные успешно отредактированы!");
}

void EditParts(const std::string& filename) {
	/**********************Открытие файла********************************/
	std::ifstream file(filename, std::ios::in | std::ios::out);
	if (!file.is_open()) {
		std::cout << "Ошибка открытия файла " << filename << std::endl;
		return;
	}
	/*********************************************************************/


	/**********************Получение данных из файла**********************/
	std::string line;
	int total_lines{ 0 }, line_to_edit{ 0 }, id{ 0 };
	std::vector<std::string> parts_lines;
	while (getline(file, line)) {
		parts_lines.push_back(line);
		total_lines += 1;
	}
	file.close();
	if (total_lines == 0) {
		pressEnterMessage("Файл пустой.\n");
		return;
	}
	ViewPartsFromFile(filename, false);
	/*********************************************************************/



	// Запрашиваем у пользователя номер строки для редактирования
	std::cout << "Введите номер строки для редактирования: ";
	line_to_edit = IntInputWithBounds(1, total_lines);
	line_to_edit--;


	std::stringstream ss(parts_lines[line_to_edit]);
	ss >> id;
	ss.clear();
	// Запрашиваем у пользователя новые данные

	std::cout << "Введите новые данные:" << std::endl;
	Parts part;
	std::cout << "Введите название детали: ";
	part.name = StringInput();
	part.name = strip(part.name);
	replaceChars(part.name, ' ', '_');
	std::cout << "Введите артикул детали: ";
	part.vendor_code = IntInputWithBounds(0, INT_MAX);
	std::cout << "Введите цену детали: ";
	part.price = DoubleInput();
	std::cout << "Введите примечание (по желанию): ";
	getline(std::cin, part.note);
	if (part.note == "" || part.note == "\n" || part.note == " ") {
		part.note = "примечание отсутствует";
	}
	part.note = strip(part.note);
	replaceChars(part.note, ' ', '_');
	part.part_id= id;

	ss.str("");
	ss.clear();

	ss << part.part_id << " " << part.name << " " << part.vendor_code <<
		" " << part.price << " " << part.note;

	std::ofstream output_file(filename, std::ios::trunc);

	if (output_file.fail()) {
		std::cout << "Ошибка открытия файла " << filename << std::endl;
		return;
	}
	else {
		std::cout << "insert into file:\n";
		for (int i{ 0 }; i < total_lines; i++) {
			if (i != line_to_edit) {
				output_file << parts_lines[i];
			}
			else {
				output_file << ss.str();
			}
			output_file << "\n";
		}
	}

	parts_lines.clear();
	ss.clear();
	file.close();

	pressEnterMessage("Данные успешно отредактированы!");
}

void EditSupply(const std::string& filename) {
	/**********************Открытие файлов********************************/
	std::fstream file(filename, std::ios::in | std::ios::out);
	if (!file.is_open()) {
		std::cout << "Ошибка открытия файла " << filename << std::endl;
		return;
	}
	/*********************************************************************/

	/**********************Получение данных из файла**********************/
	std::string line;
	int total_lines{ 0 }, line_to_edit{ 0 }, supplier_id{ 0 }, part_id{ 0 };
	std::vector<std::string> supply_lines;
	while (getline(file, line)) {
		supply_lines.push_back(line);
		total_lines += 1;
	}
	file.close();
	if (total_lines == 0) {
		pressEnterMessage("Файл пустой.\n");
		return;
	}
	ViewSupplyFromFile(filename, false);
	/*********************************************************************/



	// Запрашиваем у пользователя номер строки для редактирования
	std::cout << "Введите номер строки для редактирования: ";
	line_to_edit = IntInputWithBounds(1, total_lines);
	line_to_edit--;


	std::stringstream ss(supply_lines[line_to_edit]);
	ss >> supplier_id >> part_id;
	// Запрашиваем у пользователя новые данные
	Supply supply;

	std::cout << "Введите количество деталей:";
	supply.quantity = IntInput();
	std::cout << "Введите дату поставки:";
	supply.date = DateInput();
	supply.supplier_id = supplier_id;
	supply.part_id = part_id;
	ss.str("");
	ss.clear();

	ss << supply.supplier_id << " " << supply.part_id << " "
		<< supply.quantity << " " << supply.date;


	std::ofstream output_file(filename, std::ios::trunc);

	if (output_file.fail()) {
		std::cout << "Ошибка открытия файла " << filename << std::endl;
		return;
	}
	else {
		for (int i{ 0 }; i < total_lines; i++) {
			if (i != line_to_edit)
				output_file << supply_lines[i];
			else
				output_file << ss.str();
			output_file << "\n";
		}
	}

	supply_lines.clear();
	ss.clear();
	file.close();

	pressEnterMessage("Данные успешно отредактированы!");
}

void DeletePartsFromFile(const std::string& filename) {
	std::vector<std::shared_ptr<Parts>> vector;
	ReadPartsFromFile(vector, filename);
	PrintPartsFromVector(vector, false);
	int line_to_delete{ 0 };
	std::cout << "Введите номер строки, которую вы хотите удалить: ";
	line_to_delete = IntInputWithBounds(1, (int)vector.size());
	line_to_delete--;
	std::ofstream output_file(filename, std::ios::trunc);
	if (output_file.fail()) {
		std::cerr << "Невозможно открыть " << filename << std::endl;
		return;
	}
	int current_line{ 0 };
	for (auto& value : vector) {
		if (current_line != line_to_delete) {
			output_file << value->part_id << " " << value->name << " "
				<< value->vendor_code << " " << value->price << 
				" " << value->note << std::endl;
		}
		current_line++;
	}
	output_file.close();
	vector.clear();
	pressEnterMessage("Удаление успешно!\n");
}

void DeleteSupplierFromFile(const std::string& filename) {
	std::vector<std::shared_ptr<Supplier>> vector;
	ReadSuppliersFromFile(vector, filename);
	PrintSuppliersFromVector(vector, false);
	int line_to_delete{ 0 };
	std::cout << "Введите номер строки, которую вы хотите удалить: ";
	line_to_delete = IntInputWithBounds(1, (int)vector.size());
	line_to_delete--;
	std::ofstream output_file(filename, std::ios::trunc);
	if (output_file.fail()) {
		std::cerr << "Невозможно открыть " << filename << std::endl;
		return;
	}
	int current_line{ 0 };
	for (auto& value : vector) {
		if (current_line != line_to_delete) {
			output_file << value->supplier_id << " " << 
				value->address << " " << value->phone << std::endl;
		}
		current_line++;
	}
	output_file.close();
	vector.clear();
	pressEnterMessage("Удаление успешно!\n");
}

void DeleteSupplyFromFile(const std::string& filename) {
	std::vector<std::shared_ptr<Supply>> vector;
	ReadSupplyFromFile(vector, filename);
	PrintSupplyFromVector(vector, false);
	int line_to_delete{ 0 };
	std::cout << "Введите номер строки, которую вы хотите удалить: ";
	line_to_delete = IntInputWithBounds(1, (int)vector.size());
	line_to_delete--;
	std::ofstream output_file(filename, std::ios::trunc);
	if (output_file.fail()) {
		std::cerr << "Невозможно открыть " << filename << std::endl;
		return;
	}
	int current_line{ 0 };
	for (auto& value : vector) {
		if (current_line != line_to_delete) {
			output_file << value->supplier_id << " " << value->part_id <<
				" " << value->quantity << " " << value->date << std::endl;
		}
		current_line++;
	}
	output_file.close();
	vector.clear();
	pressEnterMessage("Удаление успешно!\n");
}

void ViewSupplierFromFile(const std::string filename, bool flag) {
	std::vector<std::shared_ptr<Supplier>> vector;
	ReadSuppliersFromFile(vector, filename);
	PrintSuppliersFromVector(vector, flag);
}

void ViewSupplyFromFile(const std::string filename, bool flag) {
	std::vector<std::shared_ptr<Supply>> vector;
	ReadSupplyFromFile(vector, filename);
	PrintSupplyFromVector(vector, flag);
}

void ViewPartsFromFile(const std::string filename, bool flag) {
	std::vector<std::shared_ptr<Parts>> vector;
	ReadPartsFromFile(vector, filename);	
	PrintPartsFromVector(vector, flag);
}

void ViewUsersFromFile(const std::string filename, bool flag) {
	std::vector<std::shared_ptr<User>> vector;
	ReadUsersFromFile(vector, filename);
	PrintUsersFromVector(vector, flag);
	vector.clear();
}

