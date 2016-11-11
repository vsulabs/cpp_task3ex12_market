#include "Products.h"
#include <iostream>
#include <string>
using namespace std;

int Products::Consumption = 1;

Products::Products(const Product& p, int our, int thr) : product(Product(p)), Supply_our(our), Supply_thr(thr) { }

Products::~Products(){ }

void Products::print_product(Products* p)
{
	p->product.print();
}

void Products::print_supply(Products* p)
{
	cout << "id" << "\t" << "Наименование" << endl;
	p->product.print();
	cout << endl << "\t" << "Запас на нашем складке: " << p->Supply_our << endl <<
		"\t" << "Запас у конкурентов: " << p->Supply_thr << endl << endl;
}

void Products::print_price(Products* p)
{
	cout << "id" << "\t" << "Наименование" << endl;
	p->product.print();
	cout << endl << "\t" << to_string(p->product.get_Cost(p->Supply_our, Consumption)) << endl << endl;
}

void Products::day_new(Products* p)
{
	p->cost_by_dates.push_back(0);
	if (p->Supply_our >= Consumption) {
		p->cost_by_dates.back() += Consumption * p->product.get_Cost(p->Supply_our, Consumption);
		p->Supply_our -= Consumption;
	}
	else if (p->Supply_our > 0) {
		p->cost_by_dates.back() += Consumption * p->product.get_Cost(p->Supply_our, Consumption);
		p->Supply_our = 0;
	}
	else
		p->Supply_our = 0;

	// у конкурентов продается некоторое количество товаров, но может быть также и пополнение склада на величину
	// не превышающую Consumption / 2
	p->Supply_thr += rand() % Consumption - Consumption / 2;
	if (p->Supply_thr < 0)
		p->Supply_thr = 0;
}
