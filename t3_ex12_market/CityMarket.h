#pragma once
#include <vector>
#include "IDs.h"
#include "Products.h"
#include "DateTime.h"

class CityMarket
{
	double critical_coef;
	static const int minCount = 100;
	static const int minCnsmp = 40;
	Date current_date;
	Date begin_date;

	std::vector<Products* > Stock;					// все наименования продуктов	
	IDs id_gen;
	int Consumption;
	std::string filename = "market.txt";
public:
	CityMarket(int consumption = minCnsmp);
	~CityMarket();
	bool isEmpty() const { return Stock.size() == 0; }
	int AddProduct(
		std::string name, 
		int selfcost,
		int ourCount = minCount,
		int thrCount = 0
	);
	Date task_new_day(std::set<int>& saled, int new_cnspt);
	std::set<int> must_profit_product(Date begin, Date end);

	bool change_our_count		(int id, int dif);
	bool change_thr_count		(int id, int dif);
	bool set_our_count			(int id, int cnt);
	bool set_thr_count			(int id, int cnt);
	void set_consumption		(int val);
	Date get_current_date()		const;
	Date get_begin_date()		const;
	int get_consumption()		const { return Consumption; }

	bool change_consumption(int consumption);
	std::set<int> get_ids() const;
	std::set<int> sale_expensive();
	
	bool search_name(std::string name)	const;
	bool check_id(int id)				const;
	void print_products()				const;
	void print_price()					const;
	void print_names()					const;
	void clear();
	bool load_from_file();	
};

