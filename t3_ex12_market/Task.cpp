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
	Write("��������� ��������� ������");	
}

int Select(int max_item)
{
	int k;
	bool errorInput = false;
	do {
		if (errorInput)
			Write("������������ ����, ���������!");
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
	Write("\t : ������� �����������.");
	if (yes_or_no("������ �� �������� ������� ����������� ������?\r\n"
		"���� ���, ��������� ������� ��� ���� �� ������ ����� ������")) {
		
		do {
			if (!InputUVal("������� ����� ����������� ������, �������� �� 1 �� 100", cnsmpt))
				Write("������������ ������, ��������� ���� �������� �� 1 �� 100");
		} while (cnsmpt > 100 || cnsmpt < 1);
	}
	else
		cnsmpt += rand() % 10 - 5;

	set<int> res;
	Date date = market.task_new_day(res, cnsmpt);
	cout << cnsmpt;
	Write("\t : ����� �����������.");
	Write("����� �����������, ����� ���������� � ����� ����.");
	cout << "�������: ";
	date.printFormat();


	if (market.isEmpty()){		
		Write("��� ��������� ��������� �����, �������� ������");
		return;
	}

	if (res.size() > 0) {
		Write("�� ����� ��� ���� ������� ������ �� ������� ������� �����");
		if (yes_or_no("����������� id �������, ������� ���� �������?")) {
			for (auto it : res)
				cout << it << endl;
			cout << endl;
		}
	}	
}

void update_supply(CityMarket & market)
{
	if (market.isEmpty()) {
		Write("��� ������ �� �� ����� ������");
		return;
	}
	market.print_names();
	int id;
	if (!InputUVal("���������� ������ ������ ����� ���������������? ������� id", id)) {
		Write("������������ ����");
		return;
	}
	int dif;
	if (!InputUVal("������� ������� ���� ��������?", dif)) {
		Write("������������ ����");
		return;
	}	
	if (dif == 0)
		return;
	if (!market.check_id(id)) {
		Write("������ ������������ ������");
		return;
	}

	if (yes_or_no("�� ������ ����������� ���������� ������ ������?\r\n"
		"���� ���, ��������� ����� �������� ������ � ����������� �� �����")) 		
		market.change_our_count(id, dif);			
	else 
		market.change_thr_count(id, dif);	
	
	if (yes_or_no("������ ���� ��������. ����������� ���������?"))
		market.print_products();
}

void add_product(CityMarket & market)
{
	Write("������� ������������ ��������:");
	string name;
	getline(cin, name);
	Trim(name);
	if (market.search_name(name) && !yes_or_no("������� � ����� ������ ����������. �������� ��� ����?"))
		return;
	int prc;
	if (!InputUVal("������� ������������� ������:", prc)) {
		Write("������������ ����");
		return;
	}
	int id = market.AddProduct(name, prc);
	if (yes_or_no("���������� ��������� ���������� ������ �� ����� ������?")) {
		int cnt = 0;
		while (true) {
			if (!InputUVal("������� ���������� ������", cnt) && yes_or_no("������������ ��������. ��������� ����?")) {				
				continue;
			}
			market.set_our_count(id, cnt);
			Write("������� ��������");
			return;
		}			
	}
}

void print_price(CityMarket & market)
{
	if (market.isEmpty())
		Write("����� ����");
	else
		market.print_price();
}

void print_products(CityMarket & market)
{
	if (market.isEmpty())
		Write("����� ����");
	else
		market.print_products();
}

void load_market(CityMarket & market)
{
	bool okLoad = false;
	if (market.isEmpty())
		okLoad = market.load_from_file();
	else if (yes_or_no("������ ��� ��������� - ��������?"))
		okLoad = market.load_from_file();
	if (okLoad) {
		Write("������ ���������");
		if (yes_or_no("����������� ������ ���������?"))
			market.print_products();
	}
	else
		Write("������ �� ������ ���� ���������");
}

void clear_market(CityMarket & market)
{
	if (!market.isEmpty() && yes_or_no("�� ������������� ������ �������� ������?")) {
		market.clear();
		Write("������ �������");
	}
}

void profit_products(CityMarket& market)
{
	if (market.get_begin_date() == market.get_current_date() || market.isEmpty()) {
		Write("����� ��� �� ����� ����������, �� ������ �� ���� �����");
		return;
	}
	Date b_date = Date(market.get_begin_date());
	Date e_date = Date(market.get_current_date());
	cout << "���� ������ �������: \t\t";
	market.get_begin_date().printFormat();
	cout << "���� �����������:\t\t ";
	market.get_current_date().printFormat();
	cout << endl;
	Write("������� ��� ���� �� ��������� [������ �������, ������� ����)");
	if (!InputDate(b_date, "������� ������ ����") ||
		b_date < market.get_begin_date() || b_date >= market.get_current_date() ||
		!InputDate(e_date, "������� ������ ����") || 
		e_date >= market.get_current_date() || b_date > e_date){
		
		Write("������������ ���� ���");
		return;
	}
	
	set<int> ids = market.must_profit_product(b_date, e_date);
	if (ids.size() == 0) {
		Write("�������� �� ������� ");
		return;
	}
	cout << endl;
	Write("ID ����� ���������� ���������");
	for (auto it : ids)
		cout << it << endl;
}

