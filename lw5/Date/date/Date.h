#pragma once
#include <sstream>
#include <iostream>
#include <cassert>

const int MIN_DAYS = 0;
const int MAX_DAYS = 2932896;
const int MIN_YEAR = 1970;
const int MAX_YEAR = 9999;
const int QUANTITY_DAYS_LEAP_YEAR = 366;
const int QUANTITY_DAYS_YEAR = 365;
const int QUANTITY_DAYS_FEBRUARY_LEAP_YEAR = 29;
const int QUANTITY_MONTH = 12;
const int WEEKDAY_MIN_DAY = 4;
const int QUANTITY_WEEKDAY = 7;
const int CENTURY = 100;
const int MULTIPLICITY_LEAP_YEAR = 4;
const int MULTIPLICITY_CENTURY_LEAP_YEAR = 400;

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
	unsigned GetDay() const;

	// возвращает месяц
	Month GetMonth() const;

	// возвращает год
	unsigned GetYear() const;

	// возвращает день недели
	WeekDay GetWeekDay() const;

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

	bool operator==(CDate const& date) const;
	bool operator!=(CDate const& date) const;
	bool operator<=(CDate const& date) const;
	bool operator<(CDate const& date) const;
	bool operator>(CDate const& date) const;
	bool operator>=(CDate const& date) const;
private:
	int m_days;
	bool m_valid;
	
	/*Примитивные типы передавать по значению*/
	unsigned CountQuantityDaysInMonth(Month month) const;
	int CountDaysInYears(int year) const;
	int CountDaysInMonths(Month month, int year) const;
	bool CheckRangeDaysMonth(unsigned day, Month month, unsigned year);
	bool CheckLeapYear(int year) const;
};

std::ostream& operator<<(std::ostream& stream, CDate& date);
std::istream& operator>>(std::istream& stream, CDate& date);