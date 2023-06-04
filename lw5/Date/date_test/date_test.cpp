#include "../../../catch/catch.hpp"
#include "../date/Date.h"

/*
Список тестов:
Инициальзация даты, указывая день, месяц, год
Инициализация даты, указывая количество дней от 1 января 1970 года
Проверяем, что у даты есть день, месяц, год
Смотрим, в какой день недели была данная дата
Проверяем перевод даты на следующий день с помощью префиксной и постфиксной формы ++
Проверяем перевод даты на предыдущий день с помощью префиксной и постфиксной формы --
Проверяем оператор +=
Проверяем оператор -=
Проверяем оператор +
Проверяем оператор -
Проверка оператора вывода в поток
Проверка оператора ввода из потока
Проверка операторов сравнения
Проверяем, что в ходе операций, если дата выходит из диапазона допустимых значений, то она становится недопустимой
*/

TEST_CASE("Check invalid initialization date")
{
	/*Инициальзация даты, указывая день, месяц, год*/
	CDate invalidDate1(31, Month::DECEMBER, 10000);
	/*Инициализация даты, указывая количество дней от 1 января 1970 года*/
	CDate invalidDate2(3000000);
	REQUIRE(!invalidDate1.IsValid());
	REQUIRE(!invalidDate2.IsValid());
};

TEST_CASE("Check valid initialization date")
{
	/*Инициальзация даты, указывая день, месяц, год*/
	CDate date1(2, Month::OCTOBER, 1972);
	REQUIRE(date1.IsValid());

	/*Инициализация даты, указывая количество дней от 1 января 1970 года */
	CDate date2(1);
	REQUIRE(date2.IsValid());

	/*Проверяем, что у даты есть день, месяц, год*/
	//Эти даты хранят 2 января 1970 года
	REQUIRE(date1.GetDay() == 2);
	REQUIRE(date1.GetMonth() == Month::OCTOBER);
	REQUIRE(date1.GetYear() == 1972);

	REQUIRE(date2.GetDay() == 2);
	REQUIRE(date2.GetMonth() == Month::JANUARY);
	REQUIRE(date2.GetYear() == 1970);

	/*Смотрим, в какой день недели была данная дата*/
	REQUIRE(date1.GetWeekDay() == WeekDay::MONDAY);
	REQUIRE(date2.GetWeekDay() == WeekDay::FRIDAY);
}

TEST_CASE("Check operator ++")
{
	/*Проверяем перевод даты на следующий день с помощью префиксной и постфиксной формы ++*/
	CDate date(29, Month::DECEMBER, 9999);
	CDate date1(29, Month::DECEMBER, 9999);
	CDate date2(31, Month::DECEMBER, 9999);
	REQUIRE(date1 == date++);
	REQUIRE(date.GetDay() == 30);
	REQUIRE(date2 == ++date);
	REQUIRE(date.GetDay() == 31);
	/*Проверяем, что в ходе операций, если дата выходит из диапазона допустимых значений, то она становится недопустимой*/
	date++;
	REQUIRE(!date.IsValid());
	date++;
	++date;
};

TEST_CASE("Check operator --")
{
	/*Проверяем перевод даты на предыдущий день с помощью префиксной и постфиксной формы --*/
	CDate date(3, Month::JANUARY, 1970);
	CDate date1(3, Month::JANUARY, 1970);
	CDate date2(1, Month::JANUARY, 1970);
	REQUIRE(date1 == date--);
	REQUIRE(date.GetDay() == 2);
	REQUIRE(date2 == --date);
	REQUIRE(date.GetDay() == 1);
	/*Проверяем, что в ходе операций, если дата выходит из диапазона допустимых значений, то она становится недопустимой*/
	date--;
	date--;
	REQUIRE(!date.IsValid());
	--date;
};

TEST_CASE("Check operator += and -=")
{
	CDate date(3, Month::JANUARY, 1970);
	/*Проверяем оператор +=*/
	date += 3;
	REQUIRE(date.GetDay() == 6);

	/*Проверяем оператор -=*/
	date -= 2;
	REQUIRE(date.GetDay() == 4);

	date -= 5;
	date -= 1;

	CDate invalidDate(31, Month::DECEMBER, 9999);
	invalidDate += 1;
	invalidDate += 1;
	REQUIRE(!invalidDate.IsValid());
};

TEST_CASE("Check operator + and -")
{
	CDate date(3, Month::JANUARY, 1970);
	CDate date1(5, Month::JANUARY, 1970);
	CDate date2(2, Month::JANUARY, 1970);
	/*Проверяем оператор +*/
	REQUIRE(date1 == date + 2);
	/*Проверяем оператор -*/
	REQUIRE(date2 == date - 1);
	REQUIRE(3 == date1 - date2);
	REQUIRE(-1 == date2 - date);

	/*Проверям операции над недопустимыми данными*/
	CDate date3(31, Month::DECEMBER, 9999);
	date = date3 + 1;
	int difference = date - date1;
	REQUIRE(difference == 0);
};

TEST_CASE("Check operator <, >, <=, >=, ==, !=")
{
	CDate date1(3, Month::JANUARY, 1970);
	CDate date2(5, Month::JANUARY, 1970);
	CDate date3(3, Month::JANUARY, 1970);
	/*Проверка операторов сравнения*/
	REQUIRE(date1 < date2);
	REQUIRE(!(date2 < date1));
	REQUIRE(date2 > date1);
	REQUIRE(!(date1 > date2));
	REQUIRE(date1 <= date2);
	REQUIRE(date1 <= date3);
	REQUIRE(!(date2 <= date1));
	REQUIRE(date2 >= date1);
	REQUIRE(date1 >= date3);
	REQUIRE(!(date1 >= date2));
	REQUIRE(date1 == date3);
	REQUIRE(!(date1 == date2));
	REQUIRE(date1 != date2);
	REQUIRE(!(date1 != date3));
};

TEST_CASE("Check operator input and output stream")
{
	CDate date1(3, Month::JANUARY, 1970);
	CDate date2(31, Month::DECEMBER, 10000);

	std::stringstream strm;
	strm << date1 << " " << date2;

	CDate info;
	strm >> info;
	REQUIRE(info.GetDay() == 3);
	REQUIRE(info.GetMonth() == Month::JANUARY);
	REQUIRE(info.GetYear() == 1970);

	strm >> info;
	REQUIRE(info.GetDay() == 1);
	REQUIRE(info.GetMonth() == Month::JANUARY);
	REQUIRE(info.GetYear() == 1970);
};