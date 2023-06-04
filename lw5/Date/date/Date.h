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
	// инициализируем дату заданными днем, месяцем и годом.
	// примечание: год >= 1970
	CDate(unsigned day, Month month, unsigned year);

	// инициализируем дату количеством дней, прошедших после 1 января 1970 года
	// например, 2 = 3 января 1970, 32 = 2 февраля 1970 года и т.д.
	CDate(unsigned timestamp = 0);

	// возвращает день месяца (от 1 до 31)
	unsigned GetDay()const;

	// возвращает месяц
	Month GetMonth()const;

	// возвращает год
	unsigned GetYear()const;

	// возвращает день недели
	WeekDay GetWeekDay()const;

	// возвращает информацию о корректности хранимой даты.
	// Например, после вызова CDate date(99, static_cast<Month>(99), 10983);
	// или после:
	//	CDate date(1, January, 1970); --date;
	// метод date.IsValid() должен вернуть false;
	bool IsValid() const;

	/*Префиксная форма*/
	CDate& operator++();
	CDate& operator--();

	/*Постфиксная форма*/
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