#include "Date.h"

CDate::CDate(unsigned day, Month month, unsigned year)
	:m_valid(true)
{
	if (year < MIN_YEAR)
	{
		throw "When initialized, the year of the date must be at least 1970";
	}

	if (!CheckRangeDaysMonth(day, month, year))
	{
		throw "The day is out of range for the month";
	}

	m_days = -1;
	m_days += CountDaysInYears(year);
	m_days += CountDaysInMonths(month, year);
	m_days += day;

	if (year > MAX_YEAR)
	{
		m_valid = false;
	}
};

CDate::CDate(unsigned timestamp)
	:m_days(timestamp),
	m_valid(true)
{
	m_valid = m_days <= MAX_DAYS;
};

unsigned CDate::GetYear() const
{
	if (!IsValid())
	{
		throw "Invalid date";
	}

	unsigned year = MIN_YEAR;
	int days = m_days;
	while (days >= 0)
	{
		//4 вынести в константу
		if (CheckLeapYear(year))
		{
			days -= QUANTITY_DAYS_LEAP_YEAR;
		}
		else
		{
			days -= QUANTITY_DAYS_YEAR;
		}
		year++;
	};

	year--;

	return year;
};

Month CDate::GetMonth() const
{
	if (!IsValid())
	{
		throw "Invalid date";
	}


	int year = GetYear();
	int days = m_days;

	days -= CountDaysInYears(year);

	int month = 1;
	while (days >= 0 and month <= QUANTITY_MONTH)
	{
		if (CheckLeapYear(year) && month == 2)
		{
			days -= QUANTITY_DAYS_FEBRUARY_LEAP_YEAR;
		}
		else
		{
			days -= CountQuantityDaysInMonth(static_cast<Month>(month));
		}
		month++;
	}

	month--;
	return static_cast<Month>(month);
};

unsigned CDate::GetDay() const
{
	if (!IsValid())
	{
		throw "Invalid date";
	}

	int year = GetYear();
	Month month = GetMonth();
	int days = m_days + 1;

	days -= CountDaysInYears(year);
	days -= CountDaysInMonths(month, year);

 	return days;
};

WeekDay CDate::GetWeekDay() const
{
	if (!IsValid())
	{
		throw "Invalid date";
	}

	int weekDay = WEEKDAY_MIN_DAY + m_days % QUANTITY_WEEKDAY;
	return static_cast<WeekDay>(weekDay % QUANTITY_WEEKDAY);
};

bool CDate::IsValid() const
{
	return m_valid;
};

unsigned CDate::CountQuantityDaysInMonth(Month month) const
{
	switch (month)
	{
	case Month::JANUARY:
		return 31;
		break;
	case Month::FEBRUARY:
		return 28;
		break;
	case Month::MARCH:
		return 31;
		break;
	case Month::APRIL:
		return 30;
		break;
	case Month::MAY:
		return 31;
		break;
	case Month::JUNE:
		return 30;
		break;
	case Month::JULY:
		return 31;
		break;
	case Month::AUGUST:
		return 31;
		break;
	case Month::SEPTEMBER:
		return 30;
		break;
	case Month::OCTOBER:
		return 31;
		break;
	case Month::NOVEMBER:
		return 30;
		break;
	case Month::DECEMBER:
		return 31;
		break;
	default:
		assert(false);
		return 0;
		break;
	}
}

bool CDate::CheckLeapYear(int year) const
{
	return (year % MULTIPLICITY_LEAP_YEAR == 0 && year % CENTURY != 0) || (year % MULTIPLICITY_CENTURY_LEAP_YEAR == 0);
};

int CDate::CountDaysInMonths(Month month, int year) const
{
	int days = 0;
	int currentMonth = static_cast<int>(month);

	for (int m = 1; m < currentMonth; m++)
	{
		if (CheckLeapYear(year) && m == 2)
		{
			days += QUANTITY_DAYS_FEBRUARY_LEAP_YEAR;
		}
		else
		{
			days += CountQuantityDaysInMonth(static_cast<Month>(m));
		}
	}

	return days;
};

int CDate::CountDaysInYears(int year) const
{
	int days = 0;

	for (int y = MIN_YEAR; y < year; y++)
	{
		if (CheckLeapYear(y))
		{
			days += QUANTITY_DAYS_LEAP_YEAR;
		}
		else
		{
			days += QUANTITY_DAYS_YEAR;
		}
	}

	return days;
};

bool CDate::CheckRangeDaysMonth(unsigned day, Month month, unsigned year)
{
	if (month == Month::FEBRUARY && CheckLeapYear(year))
	{
		if (day >= 1 && day <= QUANTITY_DAYS_FEBRUARY_LEAP_YEAR)
		{
			return true;
		}
		return false;
	}
	else
	{
		if (day >= 1 && day <= CountQuantityDaysInMonth(month))
		{
			return true;
		}
		return false;
	}
};

bool CDate::operator<(CDate const& date) const
{
	return m_days < date.m_days;
};

bool CDate::operator<=(CDate const& date) const
{
	return m_days <= date.m_days;
};

bool CDate::operator==(CDate const& date) const
{
	return m_days == date.m_days;
};

bool CDate::operator!=(CDate const& date) const
{
	return m_days != date.m_days;
};

bool CDate::operator>(CDate const& date) const
{
	return m_days > date.m_days;
};

bool CDate::operator>=(CDate const& date) const
{
	return m_days >= date.m_days;
};

CDate& CDate::operator-=(int i)
{
	if (!IsValid())
	{
		return *this;
	};

	m_days -= i;

	if (m_days < MIN_DAYS)
	{
		m_valid = false;
	}

	return *this;
};

CDate& CDate::operator+=(int i)
{
	if (!IsValid())
	{
		return *this;
	}

	m_days += i;

	if (m_days > MAX_DAYS)
	{
		m_valid = false;
	}

	return *this;
};

CDate CDate::operator+(int i)
{
	if (IsValid())
	{
		return CDate(m_days + i);
	}
	else
	{
		return CDate(m_days);
	}
};

CDate CDate::operator-(int i)
{
	if (IsValid())
	{
		return CDate(m_days - i);
	}
	else
	{
		return CDate(m_days);
	}
};

int CDate::operator-(CDate const& date)
{
	if (IsValid() && date.IsValid())
	{
		int days = m_days + 1;
		days -= CountDaysInYears(date.GetYear());
		days -= CountDaysInMonths(date.GetMonth(), date.GetYear());
		days -= date.GetDay();
		return days;
	}
	else
	{
		return 0;
	}
};

CDate& CDate::operator++()
{
	if (!IsValid())
	{
		return *this;
	}

	m_days++;

	if (m_days > MAX_DAYS)
	{
		m_valid = false;
	}

	return *this;
};

CDate& CDate::operator--()
{
	if (!IsValid())
	{
		return *this;
	}

	m_days--;

	if (m_days < MIN_DAYS)
	{
		m_valid = false;
	}

	return *this;
};

CDate CDate::operator++(int i)
{
	CDate copy(*this);

	if (!IsValid())
	{
		return copy;
	}

	++*this;

	if (m_days > MAX_DAYS)
	{
		m_valid = false;
	}

	return copy;
};

CDate CDate::operator--(int i)
{
	CDate copy(*this);

	if (!IsValid())
	{
		return copy;
	}

	--*this;

	if (m_days < MIN_DAYS)
	{
		m_valid = false;
	}

	return copy;
};

std::ostream& operator<<(std::ostream& stream, CDate& date)
{
	if (!date.IsValid())
	{
		stream << "INVALID";
	}
	else
	{
		stream << date.GetDay() << "." << static_cast<int>(date.GetMonth()) << "." << date.GetYear();
	}

	return stream;
};

std::istream& operator>>(std::istream& stream, CDate& date)
{
	unsigned day;
	unsigned month;
	unsigned year;
	std::string str;

	if (stream >> str && str == "INVALID")
	{
		date = CDate(1, Month::JANUARY, MIN_YEAR);
	}
	else
	{
		std::stringstream strm(str);
		if ((strm >> day) && (strm.get() == '.') &&
			(strm >> month) && (strm.get() == '.') &&
			(strm >> year))
		{
			CDate d(day, static_cast<Month>(month), year);
			date = d;
		}
	}

	return stream;
};