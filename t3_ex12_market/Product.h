#pragma once
#include <set>

class Product
{
	static double multiplier_exp;
	static double multiplier_cnt;
	static double coef_max;
	static double coef_sale;

	std::string Name;
	int			id;
	int			SelfCost;	
public:
	Product(
		int id,
		std::string name,
		int self_cost
	);
	Product(const Product& other);
	~Product();
	
	bool change_selfcost(int selfcost);	
	int get_id()		const { return id; }
	int get_selfcost()	const { return SelfCost; }
	double get_Cost(
		int aCount, 
		int ñonsumption
	) const;
	std::string get_name() const { return Name; }
	
	std::string	product_to_string() const;
	void		print()				const;

};

