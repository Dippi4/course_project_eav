#pragma once
#include <iostream>

/******************ОЧИСТКА ЭКРАНА, ВЫВОД СООБЩЕНИЙ*********************/
void ClearConsole() {
	system("cls");
}

void ClearConsoleEnter() {
	std::cout << "\nНажмите ВВОД чтобы продолжить." << std::endl;
	std::cin.get();
	ClearConsole();
}

void pressEnterMessage(std::string message) {
	ClearConsole();
	std::cout << message << "\n\n";
	ClearConsoleEnter();
}

void NoSuchOption() {
	std::cout << "\nНет такого варианта, введите заново:\n";
	ClearConsoleEnter();
}
/*********************************************************************/