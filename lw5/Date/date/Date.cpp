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
	m_days += CountDaysInMonths(static_cast<int>(month), year);
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
	if (m_days > MAX_DAYS)
	{
		m_valid = false;
	}
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
		if (year % 4 == 0)
		{
			days -= QUANTITY_DAYS_HIGH_YEAR;
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
	while (days >= 0 and month <= 12)
	{
		if (year % 4 == 0 && month == 2)
		{
			days -= 29;
		}
		else
		{
			days -= CountQuantityDaysInMonth(month);
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
	days -= CountDaysInMonths(static_cast<int>(month), year);

 	return days;
};

WeekDay CDate::GetWeekDay() const
{
	if (!IsValid())
	{
		throw "Invalid date";
	}

	int weekDay = 4 + m_days % 7;
	return static_cast<WeekDay>(weekDay % 7);
};

bool CDate::IsValid() const
{
	return m_valid;
};

unsigned CDate::CountQuantityDaysInMonth(int const& numMonth) const
{
	switch (numMonth)
	{
	case 1:
		return 31;
		break;
	case 2:
		return 28;
		break;
	case 3:
		return 31;
		break;
	case 4:
		return 30;
		break;
	case 5:
		return 31;
		break;
	case 6:
		return 30;
		break;
	case 7:
		return 31;
		break;
	case 8:
		return 31;
		break;
	case 9:
		return 30;
		break;
	case 10:
		return 31;
		break;
	case 11:
		return 30;
		break;
	case 12:
		return 31;
		break;
	default:
		assert(false);
		return 0;
		break;
	}
};

int CDate::CountDaysInMonths(int const& month, int const& year) const
{
	int days = 0;

	for (int m = 1; m < month; m++)
	{
		if (year % 4 == 0 && m == 2)
		{
			days += 29;
		}
		else
		{
			days += CountQuantityDaysInMonth(m);
		}
	}

	return days;
};

int CDate::CountDaysInYears(int year) const
{
	int days = 0;

	for (int y = MIN_YEAR; y < year; y++)
	{
		if (y % 4 == 0)
		{
			days += QUANTITY_DAYS_HIGH_YEAR;
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
	if (month == Month::FEBRUARY && year % 4 == 0)
	{
		if (day >= 1 && day <= 29)
		{
			return true;
		}
		return false;
	}
	else
	{
		if (day >= 1 && day <= CountQuantityDaysInMonth(static_cast<int>(month)))
		{
			return true;
		}
		return false;
	}
};

bool operator==(CDate const& date1, CDate const& date2)
{
	if (!date1.IsValid() || !date2.IsValid())
	{
		throw "Cannot compare invalid dates";
	};

	return date1.GetDay() == date2.GetDay() 
		&& date1.GetMonth() == date2.GetMonth() 
		&& date1.GetYear() == date2.GetYear();
};


bool operator!=(CDate const& date1, CDate const& date2)
{
	if (!date1.IsValid() || !date2.IsValid())
	{
		throw "Cannot compare invalid dates";
	};

	return date1.GetDay() != date2.GetDay() 
		|| date1.GetMonth() != date2.GetMonth() 
		|| date1.GetYear() != date2.GetYear();
};

bool operator>(CDate const& date1, CDate const& date2)
{
	if (!date1.IsValid() || !date2.IsValid())
	{
		throw "Cannot compare invalid dates";
	};

	if (date1.GetYear() > date2.GetYear())
	{
		return true;
	}
	else if (date1.GetYear() == date2.GetYear())
	{
		if (date1.GetMonth() > date2.GetMonth())
		{
			return true;
		}
		else if (date1.GetMonth() == date2.GetMonth())
		{
			return date1.GetDay() > date2.GetDay();
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
};

bool operator<(CDate const& date1, CDate const& date2)
{
	if (!date1.IsValid() || !date2.IsValid())
	{
		throw "Cannot compare invalid dates";
	};

	if (date1.GetYear() < date2.GetYear())
	{
		return true;
	}
	else if (date1.GetYear() == date2.GetYear())
	{
		if (date1.GetMonth() < date2.GetMonth())
		{
			return true;
		}
		else if (date1.GetMonth() == date2.GetMonth())
		{
			return date1.GetDay() < date2.GetDay();
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
};

bool operator>=(CDate const& date1, CDate const& date2)
{
	if (!date1.IsValid() || !date2.IsValid())
	{
		throw "Cannot compare invalid dates";
	};

	if (date1.GetYear() > date2.GetYear())
	{
		return true;
	}
	else if (date1.GetYear() == date2.GetYear())
	{
		if (date1.GetMonth() > date2.GetMonth())
		{
			return true;
		}
		else if (date1.GetMonth() == date2.GetMonth())
		{
			return date1.GetDay() >= date2.GetDay();
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
};

bool operator<=(CDate const& date1, CDate const& date2)
{
	if (!date1.IsValid() || !date2.IsValid())
	{
		throw "Cannot compare invalid dates";
	};

	if (date1.GetYear() < date2.GetYear())
	{
		return true;
	}
	else if (date1.GetYear() == date2.GetYear())
	{
		if (date1.GetMonth() < date2.GetMonth())
		{
			return true;
		}
		else if (date1.GetMonth() == date2.GetMonth())
		{
			return date1.GetDay() <= date2.GetDay();
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
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
		days -= CountDaysInMonths(static_cast<int>(date.GetMonth()), date.GetYear());
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