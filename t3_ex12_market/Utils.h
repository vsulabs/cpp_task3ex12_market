#pragma once
#include "CityMarket.h"

static const int max_size = 256;

int				InputInt(std::string message = "");
bool			InputUVal(std::string message, int& val);
bool			InputDate(Date& date, std::string message);
void			Trim(std::string &str);
void			DelSpaces(std::string &str);

void			Write(std::string str, int count = 1);
bool			yes_or_no(std::string message);


