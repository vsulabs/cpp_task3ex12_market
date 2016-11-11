#include "Product.h"
#include <string>
#include <iostream>
using namespace std; 

double Product::multiplier_exp = 6.5;
double Product::multiplier_cnt = 20;
double Product::coef_max = 2.5;
double Product::coef_sale = 0.2;

Product::Product(int index, string name, int self_cost)
{
	if (name.length() == 0)
		throw exception();		
	id = index;	
	SelfCost = self_cost;
	Name = name;
}

Product::Product(const Product& other) : Name(other.Name), id(other.id), SelfCost(other.SelfCost) {	}

Product::~Product() { }

bool Product::change_selfcost(int selfcost)
{
	if (selfcost <= 0)
		return false;	
	SelfCost = selfcost;	
	return true;
}

double Product::get_Cost(int aCount, int ñonsumption) const
{
	int sale = 0;
	if (aCount > 100) {		
		sale = aCount / 100;
		if (sale > coef_sale * SelfCost)
			sale = coef_sale * SelfCost;
	}
	int upSale = exp(ñonsumption / 10) * multiplier_exp + ñonsumption % 10 * multiplier_cnt;
	if (upSale > coef_max * SelfCost)
		upSale = coef_max * SelfCost;
	return SelfCost - sale + upSale;
}

string Product::product_to_string() const
{
	return to_string(id) + "\t" + Name + "\r\n";
}

void Product::print() const
{
	cout << to_string(id) + "\t" + Name << endl;
}
