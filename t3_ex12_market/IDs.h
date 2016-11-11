#pragma once
class IDs
{
	int ID;
public:
	IDs();
	~IDs();
	int generate();	
	int get_current_max() const;
};

