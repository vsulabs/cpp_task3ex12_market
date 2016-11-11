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

class Date		// ����
{
	int day;		// ����
	int month;		// �����
	int year;		// ���	

	static const Date DefaultDate;
public:
	static Date default_date();
	Date( 
		int d = MinDay, 
		int m = MinMonth, 
		int y = MinYear );						// �����������, ����� ������� ������������� ��� ����������
	Date(const Date& other);					// ����������� �����������
	Date(std::string& dataStr);					// ������� �� ������
	
	void copy_by(const Date& other);

	int getDay()			const { return day; }	// �������� ������� � ���� ����
	int getMonth()			const { return month; }	// �������� ������� � ���� �����
	int getYear()			const { return year; }	// �������� ������� � ���� ���

	void print()			const ;					// ������� �� ����� ������� ���� � ��������� ����
	void printFormat()		const ;					// ������� �� ����� ������� ���� � ������� ��.��.����.
	
	Date& operator =(const Date& other);		// �������� ������������ ������������ ������������ 

	// ��������� ���������

	bool operator ==(const Date& other) const;
	bool operator !=(const Date& other) const;
	bool operator > (const Date& other) const;
	bool operator < (const Date& other) const;
	bool operator >=(const Date& other) const;
	bool operator <=(const Date& other) const;
	
	Date& operator++(); // ++Date
	Date operator++(int); // Date++

	// ������������� ��������� �����-������
	std::ostream& operator << (std::ostream& output) const;
	std::istream& operator >> (std::istream& input);	
	std::string toString()	const;			// ���������� ���� � ���� ������
	
	// fixedBegin � fixedOut - ��������, �� ��������� � ������� �������� ��������
	// ���������� 1, ���� �������� ��� in out ������������ � ���������� fixedBegin, fixedEnd
	// ���������� 0, ���� �� ���� in ��� ���� out �� �������� � �������� fixedBegin, fixedEnd
	static bool dates_crossed(
		const Date& fixedBegin, 
		const Date& fixedEnd, 
		const Date& in,
		const Date& out);
	// ������� ���������� ���� ����� ����� ������
	static int daysBetween(
		const Date& begin, 
		const Date& end); 
	// ������ ������� �������� begin � end, ���� end ������ ��� begin
	static void days_correct(
		Date& begin,
		Date& end);
	~Date();

};
