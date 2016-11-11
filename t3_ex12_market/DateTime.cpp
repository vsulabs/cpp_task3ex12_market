#include "DateTime.h"
#include <iostream>

using namespace std;

const Date Date::DefaultDate = Date(1, 1, 2016);

Date Date::default_date()
{
	return DefaultDate;
}

Date::Date(int d, int m, int y) {	// конструктор, может служить конструктором без параметров
	if (d < MinDay || d > MaxDay || m < MinMonth || m > MaxMonth || y < MinYear || y > MaxYear)
		throw invalid_argument("некорректные значени€");
	day = d;
	month = m;
	year = y;
}
// копирование с помощью начальной инициализации. ѕредполагаетс€, что уже созданный экземпл€р проходил проверку на корректность данных
Date::Date(const Date& other) : day(other.day), month(other.month), year(other.year) { }

Date::Date(std::string& dataStr)
{
	if (dataStr.length() != date_size - 1)
		throw invalid_argument("строка имеет неверный формат");
	dataStr[date_size - 1] = '\0';

	bool isOkNumber =
		(*(dataStr.begin() + 2) == '.') && (*(dataStr.begin() + 5) == '.') ||
		(*(dataStr.begin() + 2) == ',') && (*(dataStr.begin() + 5) == ',') ||
		(*(dataStr.begin() + 2) == '/') && (*(dataStr.begin() + 5) == '/');

	string::iterator it = dataStr.begin();
	for (; it != dataStr.end() && isOkNumber; ++it) {
		if (dataStr.begin() + 2 != it && dataStr.begin() + 5 != it)
			isOkNumber = ((*it) <= '9') && ((*it) >= '0');
	}

	if (!isOkNumber || dataStr.begin() + 10 != it)
		throw invalid_argument("строка имеет неверный формат");

	string::size_type sz;

	day = stoi(dataStr, &sz);
	dataStr = dataStr.substr(sz + 1);
	month = stoi(dataStr, &sz);
	dataStr = dataStr.substr(sz + 1);
	year = stoi(dataStr, &sz);	
}

void Date::copy_by(const Date& other) {
	day = other.day;
	month = other.month;
	year = other.year;
}
Date& Date::operator=(const Date& other) {
	if (*this != other) {
		day = other.day;
		month = other.month;
		year = other.year;
	}
	return *this;
}

bool Date::operator ==(const Date& other) const {
	return (day == other.day && month == other.month && year == other.year);
}
bool Date::operator !=(const Date& other) const {
	return (day != other.day || month != other.month || year != other.year);
}
bool Date::operator >(const Date& other) const {
	return (
		(year > other.year) ||
		(year == other.year && month > other.month) ||
		(year == other.year && month == other.month && day > other.day));
}
bool Date::operator <(const Date& other) const {
	return 
		(year < other.year) ||
		(year == other.year && month < other.month) ||
		(year == other.year && month == other.month && day < other.day);
}
bool Date::operator >=(const Date& other) const {
	return 
		(day == other.day && month == other.month && year == other.year) || (
		(year > other.year) ||
		(year == other.year && month > other.month) ||
		(year == other.year && month == other.month && day > other.day));
}


bool Date::operator <=(const Date& other) const {
	return 
		(day == other.day || month == other.month || year == other.year) || (
		(year < other.year) ||
		(year == other.year && month < other.month) ||
		(year == other.year && month == other.month && day < other.day));
}

Date& Date::operator++() {
	++day;
	if (day > MaxDay) {
		day = MinDay;
		++month;
		if (month > MaxMonth) {
			month = MinMonth;
			++year;
		}
	}
	return *this;
}

Date Date::operator++(int)
{
	Date tmp(*this);
	++(*this);
	return tmp;
}

std::ostream& Date::operator << (std::ostream& output) const {
	output << endl << "Day: " << day << ". Month: " << month << ". Year: " << year << endl;
	return output;
}
std::istream& Date::operator >> (std::istream& input) {
	cout << "введите год, мес€ц, день" << endl;
	input >> year >> month >> day;
	return input;
}

int Date::daysBetween(const Date& begin, const Date& end) {
	int res = (end.year - begin.year) * DaysPerYear + (end.month - begin.month) * DaysPerMonth + (end.day - begin.day);
	if (res < 0)
		res = -res;
	return res;
}

std::string Date::toString() const {
	string result = to_string(day).length() < 2 ? "0" + to_string(day) : to_string(day);
	result += ".";
	result += to_string(month).length() < 2 ? "0" + to_string(month) : to_string(month);
	result += ".";
	return result + to_string(year);
}

void Date::print() const {
	cout << "Day: " << day << ". Month: " << month << ". Year: " << year << endl;
}

void Date::printFormat() const {
	cout << toString() << endl;
}

void Date::days_correct(Date & begin, Date & end) {
	if (end < begin) {
		Date tmp = Date(begin);
		begin = Date(end);
		end = Date(tmp);
	}
}

bool Date::dates_crossed(const Date& fixedBegin, const Date& fixedEnd, const Date& in, const Date& out){
	return !(
		in < fixedBegin &&
		out < fixedBegin ||
		in > fixedEnd &&
		out > fixedBegin); 
}

Date::~Date() { }
