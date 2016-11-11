#include "Task.h"
#include <iostream>
#include "CityMarket.h"
#include <string>

using namespace std;

void Run()
{
	CityMarket market;
	int menu_mark;
	do {
		PrintMenu();
		menu_mark = Select();

		switch (menu_mark)
		{
		case 1: // new Day
			TaskNewDay(market);
			break;
		case 2: // add supply
			update_supply(market);
			break;
		case 3: // add product
			add_product(market);
			break;
		case 4: // print price
			print_price(market);
			break;
		case 5: // print products
			print_products(market);
			break;
		case 6: // load
			load_market(market);
			break;
		case 7: // clear
			clear_market(market);
			break;
		case 8: // print must profit
			profit_products(market);
			break;
		} // switch

	} while (menu_mark != 0);
	Write("Программа завершила работу");	
}

int Select(int max_item)
{
	int k;
	bool errorInput = false;
	do {
		if (errorInput)
			Write("Некорректный ввод, повторите!");
		k = InputInt();
		errorInput = k < 0 || k > max_item;
	} while (errorInput);
	cout << endl;
	return k;
}

void PrintMenu()
{
	cout << endl;
	Write(main_menu);
	Write(main_menu1);
	Write(main_menu2);
	Write(main_menu3);
	Write(main_menu4);
	Write(main_menu5);
	Write(main_menu6);
	Write(main_menu7);
	Write(main_menu8);
	Write(menu_exit);
	cout << endl;
}

void TaskNewDay(CityMarket& market)
{	
	int cnsmpt = market.get_consumption();
	cout << cnsmpt;
	Write("\t : текущее потребление.");
	if (yes_or_no("хотите ли изменить уровень потребления города?\r\n"
		"Если нет, аналитики сделают это сами на основе своих данных")) {
		
		do {
			if (!InputUVal("Введите новое потребление города, значение от 1 до 100", cnsmpt))
				Write("Некорректные данные, повторите ввод значения от 1 до 100");
		} while (cnsmpt > 100 || cnsmpt < 1);
	}
	else
		cnsmpt += rand() % 10 - 5;

	set<int> res;
	Date date = market.task_new_day(res, cnsmpt);
	cout << cnsmpt;
	Write("\t : новое потребление.");
	Write("Город просыпается, добро пожаловать в новый день.");
	cout << "Сегодня: ";
	date.printFormat();


	if (market.isEmpty()){		
		Write("Для изменения состояния рынка, добавьте товары");
		return;
	}

	if (res.size() > 0) {
		Write("По итогу дня были проданы товары со слишком высокой ценой");
		if (yes_or_no("Распечатать id товаров, которые были проданы?")) {
			for (auto it : res)
				cout << it << endl;
			cout << endl;
		}
	}	
}

void update_supply(CityMarket & market)
{
	if (market.isEmpty()) {
		Write("Нет данных ни об одном товаре");
		return;
	}
	market.print_names();
	int id;
	if (!InputUVal("Количество какого товара будет отредактировано? Введите id", id)) {
		Write("Некорректный ввод");
		return;
	}
	int dif;
	if (!InputUVal("Сколько товаров было завезено?", dif)) {
		Write("Некорректный ввод");
		return;
	}	
	if (dif == 0)
		return;
	if (!market.check_id(id)) {
		Write("Введен некорректный индекс");
		return;
	}

	if (yes_or_no("Вы хотите осуществить пополнение нашего склада?\r\n"
		"Если нет, изменения будут касаться данных о конкурентах на рынке")) 		
		market.change_our_count(id, dif);			
	else 
		market.change_thr_count(id, dif);	
	
	if (yes_or_no("Данные были изменены. Распечатать результат?"))
		market.print_products();
}

void add_product(CityMarket & market)
{
	Write("Введите наименование продукта:");
	string name;
	getline(cin, name);
	Trim(name);
	if (market.search_name(name) && !yes_or_no("продукт с таким именем существует. Добавить ещё один?"))
		return;
	int prc;
	if (!InputUVal("Введите себестоимость товара:", prc)) {
		Write("некорректный ввод");
		return;
	}
	int id = market.AddProduct(name, prc);
	if (yes_or_no("Установить начальное количество товара на нашем складе?")) {
		int cnt = 0;
		while (true) {
			if (!InputUVal("Введите количество товара", cnt) && yes_or_no("некорректное значение. Повторить ввод?")) {				
				continue;
			}
			market.set_our_count(id, cnt);
			Write("Продукт добавлен");
			return;
		}			
	}
}

void print_price(CityMarket & market)
{
	if (market.isEmpty())
		Write("Рынок пуст");
	else
		market.print_price();
}

void print_products(CityMarket & market)
{
	if (market.isEmpty())
		Write("Рынок пуст");
	else
		market.print_products();
}

void load_market(CityMarket & market)
{
	bool okLoad = false;
	if (market.isEmpty())
		okLoad = market.load_from_file();
	else if (yes_or_no("Данные уже заполнены - заменить?"))
		okLoad = market.load_from_file();
	if (okLoad) {
		Write("Данные загружены");
		if (yes_or_no("Распечатать список продуктов?"))
			market.print_products();
	}
	else
		Write("Данные не смогли быть загружены");
}

void clear_market(CityMarket & market)
{
	if (!market.isEmpty() && yes_or_no("Вы действительно хотите очистить список?")) {
		market.clear();
		Write("Данные очищены");
	}
}

void profit_products(CityMarket& market)
{
	if (market.get_begin_date() == market.get_current_date() || market.isEmpty()) {
		Write("Рынок ещё не успел обновиться, не продан ни один товар");
		return;
	}
	Date b_date = Date(market.get_begin_date());
	Date e_date = Date(market.get_current_date());
	cout << "Дата начала отсчета: \t\t";
	market.get_begin_date().printFormat();
	cout << "Дата сегодняшняя:\t\t ";
	market.get_current_date().printFormat();
	cout << endl;
	Write("Введите обе даты из диапазона [начало отсчета, текущая дата)");
	if (!InputDate(b_date, "Введите первую дату") ||
		b_date < market.get_begin_date() || b_date >= market.get_current_date() ||
		!InputDate(e_date, "Введите вторую дату") || 
		e_date >= market.get_current_date() || b_date > e_date){
		
		Write("Некорректный ввод дат");
		return;
	}
	
	set<int> ids = market.must_profit_product(b_date, e_date);
	if (ids.size() == 0) {
		Write("Продукты не найдены ");
		return;
	}
	cout << endl;
	Write("ID самых прибыльных продуктов");
	for (auto it : ids)
		cout << it << endl;
}

