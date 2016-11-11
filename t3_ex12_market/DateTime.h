#pragma once
#include <string>

static const int MaxYear = 2020;
static const int MaxMonth = 12;
static const int MaxDay = 31;

static const int MinYear = 1950;
static const int MinMonth = 1;
static const int MinDay = 1;

static const int DaysPerYear = 365;
static const int DaysPerMonth = 31;

static const int date_size = 11;

class Date		// дата
{
	int day;		// день
	int month;		// месяц
	int year;		// год	

	static const Date DefaultDate;
public:
	static Date default_date();
	Date( 
		int d = MinDay, 
		int m = MinMonth, 
		int y = MinYear );						// конструктор, может служить конструктором без параметров
	Date(const Date& other);					// конструктор копирования
	Date(std::string& dataStr);					// парсинг из строки
	
	void copy_by(const Date& other);

	int getDay()			const { return day; }	// свойство доступа к полю день
	int getMonth()			const { return month; }	// свойство доступа к полю месяц
	int getYear()			const { return year; }	// свойство доступа к полю год

	void print()			const ;					// выводит на экран текущую дату в текстовом виде
	void printFormat()		const ;					// выводит на экран текущую дату в формате дд.мм.гггг.
	
	Date& operator =(const Date& other);		// оператор присваивания осуществляет присваивание 

	// операторы сравнения

	bool operator ==(const Date& other) const;
	bool operator !=(const Date& other) const;
	bool operator > (const Date& other) const;
	bool operator < (const Date& other) const;
	bool operator >=(const Date& other) const;
	bool operator <=(const Date& other) const;
	
	Date& operator++(); // ++Date
	Date operator++(int); // Date++

	// перегруженные операторы ввода-вывода
	std::ostream& operator << (std::ostream& output) const;
	std::istream& operator >> (std::istream& input);	
	std::string toString()	const;			// сохранение даты в виде строки
	
	// fixedBegin и fixedOut - диапазон, на вхождение в который делается проверка
	// возвращает 1, если диапазон дат in out пересекается с диапазоном fixedBegin, fixedEnd
	// возвращает 0, если ни дата in или дата out не попадает в диапазон fixedBegin, fixedEnd
	static bool dates_crossed(
		const Date& fixedBegin, 
		const Date& fixedEnd, 
		const Date& in,
		const Date& out);
	// подсчет количества дней между двумя датами
	static int daysBetween(
		const Date& begin, 
		const Date& end); 
	// меняет местами значения begin и end, если end меньше чем begin
	static void days_correct(
		Date& begin,
		Date& end);
	~Date();

};
