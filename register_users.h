#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

#include "screen_cleaner.h"
#include "user_struct.h"
#include "print_file.h"
#include "file_handler.h"

#ifdef __unix__
#include <termios.h>
#include <unistd.h>
#include <clocale>
#endif

#define MAX_ATTEMPTS 3

void passwordInput(std::string& password) {

    char ch;
  

    // ************************************************
    #ifdef __unix__
    // Выключить echo и сохранить текущие настройки терминала
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt); // Получить текущие настройки терминала
    newt = oldt;
    newt.c_lflag &= ~ECHO;         // Выключить echo
    newt.c_lflag &= ~ICANON;       // Выключить режим canonical mode
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    #endif
    // ************************************************


    std::cout << "Введите пароль: ";
    while (true) {
        ch = getchar();        
        if (ch == '\n') { // Stop on newline
            break;
        }
        else if (ch == 0x7f || ch == '\b') { // Обработка backspace
            if (!password.empty()) {
              if (!isalnum(password.back()))
                password.pop_back();
              password.pop_back();
                // Переместить курсор назад, перезаписать текущий символ пробелом и переместить курсор еще раз назад
                std::cout << "\b \b";
            }  
        } 
        else if (!isalnum(ch)){
          // обработка для русских символов 
           password += ch;
           ch = getchar();
           password += ch;
           std::cout << '*';
        }
        else {         
            password += ch;
            std::cout << '*'; // Выводим на экран звездочки вместо пароля          
        }
    }

    // Восстановить предыдущие настройки
    #ifdef __unix__
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    #endif
    std::cout << std::endl;

}

bool CheckPasswordInDatabase(std::string& username, std::string& password,
	const std::string& filename, bool& isValid, struct User& user) {

	std::ifstream inputFile2(filename);
	bool isAuthenticated = false;
	while (inputFile2 >> username >> password) {
		if (username == user.login && password == user.password) {

			if (isValid = true) {
				std::cout << "Аутентификация успешна." << std::endl;
				isAuthenticated = true;
			}
			else {
				std::cout << "Ваш аккаунт заблокирован." << std::endl;
				ClearConsoleEnter();
				break;
			}
		}
	}
	inputFile2.close();
	return isAuthenticated;
}

bool CheckUsernameInDatabase(std::string& username, std::string& password,
	const std::string& filename, const std::string& login) {

	std::ifstream inputFile1(filename);
	bool validUsername = false;

	while (inputFile1 >> username >> password) {
		if (username == login) {
			validUsername = true;
			break;
		}
	}
	inputFile1.close();
	return validUsername;
}

bool AuthenticateUser(std::string filename) {
	struct User user;
	int attempts = 0;
	bool isAuthenticated = false, isValidUsername = false;
	std::string username{ "" }, password{ "" };

	// Запрос логина
	std::cout << "Введите логин: ";
	getline(std::cin, user.login);

	isValidUsername = CheckUsernameInDatabase(username, password, filename, user.login);

	if (isValidUsername == false) {
		std::cout << "Логин неверный. Аутентификация невозможна." << std::endl;
		ClearConsoleEnter();
		return false;
	}

	while (attempts < MAX_ATTEMPTS) {
		// Запрос пароля	
		passwordInput(user.password);

		isAuthenticated = CheckPasswordInDatabase(username, password, filename, isValidUsername, user);

		// Закрытие цикла при успешной аутентификации
		if (isAuthenticated == true) {
			break;
		}
		else {
			attempts++;
			std::cout << "Пароль неверный. Пожалуйста, повторите попытку." << std::endl;
			user.password.clear();
			user.password = "";
			ClearConsoleEnter();
		}
	}

	// Проверка превышения количества попыток
	if (attempts == MAX_ATTEMPTS) {
		std::cout << "Превышено максимальное Сезоны попыток. Аутентификация невозможна" << std::endl;
		ClearConsoleEnter();
	}

	return isAuthenticated;
}

void RegisterUser(std::string filename) {

	std::string username, password, fileUsername, filePassword;
	bool usernameExists = false;
	std::ifstream inputFile(filename);
	// Запрос логина и пароля
	std::cout << "Введите логин: ";
	getline(std::cin, username);

	// Проверка на наличие пробелов в логине
	if (username.find(' ') != std::string::npos) {
		std::cout << "Логин не должен содержать пробелы." << std::endl;
		ClearConsoleEnter();
		return;
	}
	else {
		passwordInput(password);

		// Проверка длины пароля
		if (password.length() < 8) {
			std::cout << "Пароль должен состоять не менее чем из 8 символов."
				<< std::endl;
			ClearConsoleEnter();
			return;
		}
	}

	// Проверка наличия логина в файле
	usernameExists = CheckUsernameInDatabase(fileUsername, filePassword, filename, username);

	//registerUserOtherInfo(user);
	// Регистрация нового пользователя или сообщение об ошибке, если логин уже существует
	if (!usernameExists) {
		std::ofstream outputFile(filename, std::ios::app);
		outputFile << username << " " << password << " " << std::endl;
		outputFile.close();
		std::cout << "Пользователь зарегистрирован." << std::endl;
		ClearConsoleEnter();
	}
	else {
		std::cout << "Пользователь с таким логином уже существует." << std::endl;
		ClearConsoleEnter();
	}
}

void DeleteUser(const std::string& filename) {
	
	ViewUsersFromFile(filename, false);

	std::cout << "Введите имя пользователя для удаления: ";
	std::string usernameToDelete{ "" };
	getline(std::cin, usernameToDelete);

	const char* temp_file = "temp.txt";

	std::ifstream input_temp_file(filename);
	if (!input_temp_file.is_open()) {
		std::cout << "Ошибка открытия файла!" << std::endl;
		return;
	}

	std::ofstream output_temp_file(temp_file);
	if (!output_temp_file.is_open()) {
		std::cout << "Ошибка создания временного файла!" << std::endl;
		input_temp_file.close();
		return;
	}

	std::string line;
	bool userDeleted = false;
	while (getline(input_temp_file, line)) {
		std::stringstream ss(line);
		std::string username;
		ss >> username;
		if (username != usernameToDelete) {
			output_temp_file << line << std::endl; // Записываем строку во временный файл, если имя пользователя не совпадает
		}
		else {
			userDeleted = true; // Устанавливаем флаг, что пользователь был удален
		}
	}

	input_temp_file.close();
	output_temp_file.close();

	if (remove(filename.c_str()) != 0) {
		std::cout << "Ошибка удаления файла!" << std::endl;
		return;
	}
	if (rename(temp_file, filename.c_str()) != 0) {
		std::cout << "Ошибка переименования временного файла!" << std::endl;
		return;
	}

	if (userDeleted) {
		pressEnterMessage("Пользователь успешно удален.");
	}
	else {
		std::string line{ "" };
		std::stringstream ss(line);
		ss << "Пользователь с именем " << usernameToDelete << " не найден.";
		pressEnterMessage(ss.str());
		ss.clear();
		line.clear();
	}
}