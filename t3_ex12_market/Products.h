#pragma once
#include "Product.h"
#include <vector>

struct Products {
	Product product;
	int Supply_our;
	int Supply_thr;
	
	std::vector<double> cost_by_dates;

	Products(const Product& p, int our, int thr);
	~Products();	
	
	static void print_product(Products* p);
	static void print_supply(Products* p);
	static void print_price(Products* p);
	
	static void day_new(Products* p);

	static int Consumption;
};
