#include "Utils.h"
#include <string>
#include <iostream>
using namespace std;

int InputInt(std::string message)
{
	char s[max_size];
	char *str;
	bool isOkNumber = true;
	int res;
	if (message != "")
		Write(message);
	do {
		if (!isOkNumber)
			cout << "bad input, try again!" << endl;
		cout << "--> ";

		std::cin.getline(s, max_size);
		isOkNumber = true;
		s[max_size - 1] = '\0';

		str = s;
		if (s[0] == '-' || s[0] == '+')
			str++;
		if (*str == '\0')
			isOkNumber = false;
		for (; *str != '\0' && isOkNumber; str++)
			isOkNumber = isOkNumber && (*str >= '0' && *str <= '9');
	} while (!isOkNumber);
	res = atoi(s);
	return res;
}

bool InputUVal(string message, int& val)
{
	string s;

	cout << message << endl;
	cout << "--> ";

	getline(cin, s);		
	string::iterator it = s.begin();
	if (it == s.end())
		return false;
			
	if (*it == '+')
		++it;
	if (it == s.end())
		return false;

	for (; it != s.end(); ++it)
		if (*it < '0' || *it > '9')
			return false;
	
	val = stoi(s);
	return true;
}

bool InputDate(Date& date, string message) 
{
	string s;
	if (message != "")
		Write(message);
	cout << "Формат даты: дд.мм.гггг" << endl;
	cout << MinDay << "\t< дд <\t" << MaxDay << endl;
	cout << MinMonth << "\t< мм <\t" << MaxMonth << endl;
	cout << MinYear << "\t<гггг<\t" << MaxYear << endl;
	cout << "--> ";
	getline(cin, s);

	DelSpaces(s);

	if (s.length() != date_size - 1)
		return false;
	s[date_size - 1] = '\0';
	bool isOkNumber;
	isOkNumber =
		(*(s.begin() + 2) == '.') && (*(s.begin() + 5) == '.') ||
		(*(s.begin() + 2) == ',') && (*(s.begin() + 5) == ',') ||
		(*(s.begin() + 2) == '/') && (*(s.begin() + 5) == '/');

	string::iterator it = s.begin();
	for (; it != s.end() && isOkNumber; ++it)
		if (s.begin() + 2 != it && s.begin() + 5 != it)
			isOkNumber = ((*it) <= '9') && ((*it) >= '0');

	if (!isOkNumber || s.begin() + 10 != it)
		return false;

	int d, m, y;
	string::size_type sz;

	d = stoi(s, &sz);
	s = s.substr(sz + 1);
	m = stoi(s, &sz);
	s = s.substr(sz + 1);
	y = stoi(s, &sz);

	
	try{
		Date tmpDate = Date(d, m, y); 
		// чтобы не портилось значение Date, переданное по ссылке
		// при некорректном вводе уже здесь будет исключение
		date = tmpDate;
		return true;
	}
	catch (const invalid_argument& e) {
		cerr << e.what() << endl;
		return false;
	}
	
}



void Write(string str, int count)
{
	cout << str;
	for (int i = 0; i < count; ++i)
		cout << std::endl;
}


void Trim(std::string &str)
{
	const auto strBegin = str.find_first_not_of(" \t");
	if (strBegin != std::string::npos) {
		const auto strEnd = str.find_last_not_of(" \t");
		const auto strRange = strEnd - strBegin + 1;
		str = str.substr(strBegin, strRange);
	}
	else
		return;

	std::string result = "";
	for (unsigned int i = 0; i < str.length(); i++)
		result += static_cast<unsigned char>(str.at(i));

	str = result;
}

void DelSpaces(std::string &str)
{
	std::string result = "";
	Trim(str);
	unsigned i = 0;
	while (i < str.length()) {
		while (str[i] != ' ' && i < str.length()) {
			result.push_back(str[i]);
			i++;
		}
		if (str[i] == ' ' && i < str.length())
			result.push_back(' ');
		while (str[i] == ' ' && i < str.length())
			i++;
	} // while
	str = result;
}

bool yes_or_no(string message)
{
	cout << message << endl;
	cout << "1 - yes, 0 - no" << endl << endl;
	int k;
	bool errorInput = false;
	do {
		if (errorInput)
			cout << "Некорректный ввод, повторите!" << endl;
		k = InputInt();
		errorInput = k < 0 || k > 1;
	} while (errorInput);
	return k == 1;
}


