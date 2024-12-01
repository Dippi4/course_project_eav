#include "user_functions.h"
#include "stuff.h"

int main(void) {
    //предварительная подготовка
	RussianLanguage();
	makeFiles();

	std::string hint = "Выберите пункт\n1.Регистрация\n"
		"2.Вход\n3.Выход из программы\n? ";
	char choice{ 0 };

	while (1) {

		switch (CharInput(hint)) {

		case '3': {
			return 0;
			break;
		}

		case '1': {
			std::string hint1 = "1.Регистрация администратора\n"
				"2.Регистрация пользователя\n0.Назад\n";
			switch (CharInput(hint1)) {
			case '1':
				RegisterUser(ADMIN_FILE);
				break;
			case '2':
				RegisterUser(USER_FILE);
				break;
			case '0':
				break;
			default:
				NoSuchOption();
				break;
			}
			break;
		}
		case '2': {
			std::string hint2 = "1.Войти как администратор\n2.Войти как пользователь\n0.Назад\n";
			do {
				choice = CharInput(hint2);
				if (choice == '0')
					break;
				switch (choice) {

				case '1': {
					if (AuthenticateUser(ADMIN_FILE)) {
						admin_functions();
					}
					break;

				}

				case '2': {

					if (AuthenticateUser(USER_FILE)) {
						std::string hint3 = "1.Просмотреть файлы\n"
							"2.Сортировка\n"
							"3.Поиск/Фильтр\n0.Назад\n";
						do {

							choice = CharInput(hint3);

							switch (choice) {

							case '1': {

								ViewSupplierFromFile(SUPPLIERS_FILE, true);
								ViewPartsFromFile(PART_FILE, true);
								ViewSupplyFromFile(SUPPLY_FILE, true);

								break;
							}

							case '2': {
								user_functions_sort();

								break;
							}

							case '3': {

								user_functions_find_filter();
								break;
							}

							case '0': {
								break;
							}
							default:
								NoSuchOption();
								break;
							}

						} while (choice != '0');
					}
				}

				default: {
					if (choice != '0')
						NoSuchOption();
					break;
				}

				}

			} while (choice != '0');
			continue;
		}

		default:
			NoSuchOption();
			break;
		}

	}
	
	ClearVectorsNamespace();
	return 0;
}