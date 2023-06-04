#pragma once
#include <sstream>
#include <iostream>
#include <cassert>

const int MIN_DAYS = 0;
const int MAX_DAYS = 2932956;
const int MIN_YEAR = 1970;
const int MAX_YEAR = 9999;
const int QUANTITY_DAYS_HIGH_YEAR = 366;
const int QUANTITY_DAYS_YEAR = 365;

enum class Month
{
	JANUARY = 1, 
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
};

enum class WeekDay
{
	SUNDAY = 0,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY
};

class CDate
{
public:
	// �������������� ���� ��������� ����, ������� � �����.
	// ����������: ��� >= 1970
	CDate(unsigned day, Month month, unsigned year);

	// �������������� ���� ����������� ����, ��������� ����� 1 ������ 1970 ����
	// ��������, 2 = 3 ������ 1970, 32 = 2 ������� 1970 ���� � �.�.
	CDate(unsigned timestamp = 0);

	// ���������� ���� ������ (�� 1 �� 31)
	unsigned GetDay()const;

	// ���������� �����
	Month GetMonth()const;

	// ���������� ���
	unsigned GetYear()const;

	// ���������� ���� ������
	WeekDay GetWeekDay()const;

	// ���������� ���������� � ������������ �������� ����.
	// ��������, ����� ������ CDate date(99, static_cast<Month>(99), 10983);
	// ��� �����:
	//	CDate date(1, January, 1970); --date;
	// ����� date.IsValid() ������ ������� false;
	bool IsValid() const;

	/*���������� �����*/
	CDate& operator++();
	CDate& operator--();

	/*����������� �����*/
	CDate operator++(int i);
	CDate operator--(int i);

	CDate operator+(int i);
	CDate operator-(int i);
	int operator-(CDate const& date);

	CDate& operator+=(int i);
	CDate& operator-=(int i);
private:
	int m_days;
	bool m_valid;

	unsigned CountQuantityDaysInMonth(int const& numMonth) const;
	int CountDaysInYears(int year) const;
	int CountDaysInMonths(int const& month, int const& year) const;
	bool CheckRangeDaysMonth(unsigned day, Month month, unsigned year);
};

bool operator==(CDate const& date1, CDate const& date2);
bool operator!=(CDate const& date1, CDate const& date2);
bool operator<=(CDate const& date1, CDate const& date2);
bool operator<(CDate const& date1, CDate const& date2);
bool operator>(CDate const& date1, CDate const& date2);
bool operator>=(CDate const& date1, CDate const& date2);

std::ostream& operator<<(std::ostream& stream, CDate& date);
std::istream& operator>>(std::istream& stream, CDate& date);