#include "CityMarket.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;

CityMarket::CityMarket(int consumption) : 
	critical_coef(1.75),  //critical_coef(1.5), 
	current_date(Date::default_date()), 
	begin_date(Date::default_date())
{
	if (consumption < 1)
		Consumption = 1;
	else if (consumption > 100)
		Consumption = 100;
	else
		Consumption = consumption;
	Products::Consumption = Consumption;
}

CityMarket::~CityMarket() { clear(); }

int CityMarket::AddProduct(string name, int selfcost, int ourCount, int thrCount)
{	
	if (ourCount < minCount)
		ourCount = minCount;
	if (thrCount < 0)
		thrCount = 0;	
	Stock.push_back(new Products(Product(id_gen.generate(), name, selfcost), ourCount, thrCount));
	for (int i = 0; i < Date::daysBetween(begin_date, current_date); ++i)
		Stock.back()->cost_by_dates.push_back(0);
	return Stock.back()->product.get_id();
}

Date CityMarket::task_new_day(std::set<int>& saled, int new_cnspt)
{		
	for_each(Stock.begin(), Stock.end(), Products::day_new);
	saled = sale_expensive();
	set_consumption(new_cnspt);
	Products::Consumption = Consumption;
	++current_date; 
	return current_date;
}

set<int> CityMarket::must_profit_product(Date begin, Date end)
{	
	set<int> res;
	if (isEmpty() || begin < begin_date || end >= current_date || begin > end)
		return res;

	int sz_b = Date::daysBetween(begin_date, begin);
	int sz_e = Date::daysBetween(begin_date, end) + 1;

	double maxCost = 0;
	double cost;

	for_each(Stock.begin(), Stock.end(), [sz_b, sz_e, &res, &cost, &maxCost](Products* it) {
		cost = accumulate(it->cost_by_dates.begin() + sz_b, it->cost_by_dates.begin() + sz_e, 0);
		if (cost > maxCost) {
			res.clear();
			res.insert(it->product.get_id());
			maxCost = cost;
		}
		else if (abs(cost - maxCost) < 0.00001)
			res.insert(it->product.get_id());
	});
	if (abs(maxCost) < 0.000001)
		res.clear();
	return res;
}


bool CityMarket::change_our_count(int id, int dif)
{
	auto it = find_if(Stock.begin(), Stock.end(),
		[id](const Products* p){ return p->product.get_id() == id; });
	if (it == Stock.end())
		return false;

	(*it)->Supply_our += dif;
	if ((*it)->Supply_our < 0)
		(*it)->Supply_our = 0;
	return true;
}

bool CityMarket::change_thr_count(int id, int dif)
{	
	auto it = find_if(Stock.begin(), Stock.end(), 
		[id](const Products* p){ return p->product.get_id() == id; });
	if (it == Stock.end())
		return false;

	(*it)->Supply_thr += dif;
	if ((*it)->Supply_thr < 0)
		(*it)->Supply_thr = 0;
	return true;
}

bool CityMarket::set_our_count(int id, int cnt)
{
	if (!check_id(id) || cnt < 0)
		return false;
	
	for_each(Stock.begin(), Stock.end(),
		[id, cnt](Products* it) {if (it->product.get_id() == id) it->Supply_our = cnt; });
	
	return true;
}

bool CityMarket::set_thr_count(int id, int cnt)
{
	if (!check_id(id) || (cnt < 0))
		return false;
	
	for_each(Stock.begin(), Stock.end(),
		[id, cnt](Products* it) {if (it->product.get_id() == id) it->Supply_thr = cnt; });
	
	return true;
}

void CityMarket::set_consumption(int val)
{
	if (val < 1)
		Consumption = 1;
	else if (val > 100)
		Consumption = 100;
	else
		Consumption = val;
}

Date CityMarket::get_current_date() const {	return current_date; }

Date CityMarket::get_begin_date() const { return begin_date; }

bool CityMarket::change_consumption(int consumption)
{
	if (consumption < 1 || consumption > 100)
		return false;
	Consumption = consumption;
	return true;
}

set<int> CityMarket::get_ids() const
{
	set<int> result;
	
	for_each(Stock.begin(), Stock.end(), 
		[&result](const Products* it){result.insert(it->product.get_id()); }
	);
	
	return result;	
}

set<int> CityMarket::sale_expensive()
{	
	set<int> result;
	double cost;
	for_each(Stock.begin(), Stock.end(), [&cost, &result, this](Products* it) {
		cost = it->product.get_Cost(it->Supply_our, Consumption);
		if (cost > critical_coef * it->product.get_selfcost() && it->Supply_our > 0) {			
			it->Supply_our = 0;
			result.insert(it->product.get_id());			
		}
		else 
			cost = 0;
		it->cost_by_dates.back() += cost;		
	});
	return result;
	
}

bool CityMarket::search_name(std::string name) const
{	
	return 
		find_if(Stock.begin(), Stock.end(), 
		[name](const Products* it) {
		return it->product.get_name() == name; })		
		!= Stock.end();	
}

bool CityMarket::check_id(int id) const
{	
	return 
		find_if(Stock.begin(), Stock.end(), 
		[id](const Products* it) {
		return id == it->product.get_id();}) != Stock.end();	
}

void CityMarket::print_products() const
{
	cout << "\t * \t Товары \t *" << endl;
	for_each(Stock.begin(), Stock.end(), Products::print_supply);
}

void CityMarket::print_price() const
{
	cout << "\t * \t Цены \t *" << endl;
	for_each(Stock.begin(), Stock.end(), Products::print_price);		
}

void CityMarket::print_names() const
{
	for_each(Stock.begin(), Stock.end(), Products::print_product);	
}

void CityMarket::clear()
{
	while (Stock.size() > 0) {
		delete Stock.back();
		Stock.pop_back();
	}
	begin_date = Date(current_date);
}

bool CityMarket::load_from_file()
{
	ifstream infile;
	string s;
	string name;
	string::size_type sz;

	clear();	
	infile.open(filename);
	while (!infile.eof()) { // To get you all the lines.	
		getline(infile, name); // Saves the line in tmp_string					
		getline(infile, s); // Saves the line in tmp_string			
		int cost = stoi(s, &sz);
		getline(infile, s); // Saves the line in tmp_string					
		int our = stoi(s, &sz);
		s = s.substr(sz + 1);
		int thr = stoi(s, &sz);
		AddProduct(name, cost, our, thr);
		getline(infile, s);
	}
	return true;
}

