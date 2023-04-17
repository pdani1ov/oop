#include "../../../catch/catch.hpp"
#include "../car/Car.h"
#include "../car/CarController.h"

TEST_CASE("Check work of engine")
{
	CCar car;

	/*��������� ��������� ���������*/
	REQUIRE(car.TurnOnEngine());

	/*���������, ��� ��������� ������ ���������, ���� �������� �� �����������, �������� = 0*/
	REQUIRE(car.SetGear(Gear::First));
	REQUIRE(car.GetGear() == Gear::First);
	REQUIRE(!car.TurnOffEngine());

	/*���������, ��� ������ ��������� ���������, ���� �������� != 0, �������� �����������*/
	REQUIRE(car.SetSpeed(10));
	REQUIRE(car.GetSpeed() == 10);
	REQUIRE(car.SetGear(Gear::Neutral));
	REQUIRE(car.GetGear() == Gear::Neutral);
	REQUIRE(!car.TurnOffEngine());

	/*���������, ��� ������ ��������� ���������, ���� �������� != 0, �������� �� �����������*/
	REQUIRE(car.SetGear(Gear::First));
	REQUIRE(car.GetGear() == Gear::First);
	REQUIRE(!car.TurnOffEngine());
};

TEST_CASE("Check work reverse gear")
{
	CCar car;
	car.TurnOnEngine();

	/*��������, ��� �� ������ �������� �������������*/
	REQUIRE(car.SetGear(Gear::Reverse));
	REQUIRE(car.GetGear() == Gear::Reverse);

	/*��������, ��������� �������� �� ��, ������� �� ������ � ��������*/
	REQUIRE(!car.SetSpeed(21));

	/*��������, ������, ����� ���������� ���� �����(�������� != 0) �� ���������� �������� � �� �� ����� ����������� �������� �� ������(����� �������� = 0)*/
	REQUIRE(car.SetSpeed(10));
	REQUIRE(car.GetSpeed() == 10);
	REQUIRE(car.SetGear(Gear::Neutral));
	REQUIRE(car.GetGear() == Gear::Neutral);
	REQUIRE(!car.SetGear(Gear::Reverse));

	/*���������, ��� �� ���������� �������� ������ ��������� ��������, �� ����� ��������*/
	REQUIRE(!car.SetSpeed(11));
	REQUIRE(car.SetSpeed(5));
	REQUIRE(car.GetSpeed() == 5);
};

TEST_CASE("Check work neutral gear")
{
	CCar car;

	/*���������, ��� ��� ����������� ��������� ����� ������������� ������ �� ����������� ��������*/
	REQUIRE(!car.SetGear(Gear::Reverse));
	REQUIRE(!car.SetGear(Gear::First));
	REQUIRE(car.SetGear(Gear::Neutral));

	/*���������, ��� �� ����������� �������� ����� ������ ��������� ��������*/
	car.TurnOnEngine();
	REQUIRE(car.SetGear(Gear::First));
	REQUIRE(car.GetGear() == Gear::First);
	REQUIRE(car.SetSpeed(20));
	REQUIRE(car.GetSpeed() == 20);
	REQUIRE(car.SetGear(Gear::Neutral));
	REQUIRE(car.GetGear() == Gear::Neutral);
	REQUIRE(!car.SetSpeed(21));
	REQUIRE(car.SetSpeed(10));
	REQUIRE(car.GetSpeed() == 10);

	/*���������, ��� �� ����������� �������� ������ ��������� �������� ������ �� 0*/
	REQUIRE(!car.SetSpeed(-1));
};

TEST_CASE("Check set gear and set speed")
{
	CCar car;
	car.TurnOnEngine();

	/*��������� ������������ ������������ �������� � ������������ ���������*/
	REQUIRE(car.SetGear(Gear::First));
	REQUIRE(car.GetGear() == Gear::First);
	REQUIRE(!car.SetSpeed(-1));
	REQUIRE(car.SetSpeed(30));
	REQUIRE(car.GetSpeed() == 30);
	REQUIRE(!car.SetSpeed(31));

	REQUIRE(car.SetGear(Gear::Second));
	REQUIRE(car.GetGear() == Gear::Second);
	REQUIRE(!car.SetSpeed(19));
	REQUIRE(car.SetSpeed(20));
	REQUIRE(car.GetSpeed() == 20);
	REQUIRE(car.SetSpeed(50));
	REQUIRE(car.GetSpeed() == 50);
	REQUIRE(!car.SetSpeed(51));

	REQUIRE(car.SetGear(Gear::Third));
	REQUIRE(car.GetGear() == Gear::Third);
	REQUIRE(!car.SetSpeed(29));
	REQUIRE(car.SetSpeed(30));
	REQUIRE(car.GetSpeed() == 30);
	REQUIRE(car.SetSpeed(60));
	REQUIRE(car.GetSpeed() == 60);
	REQUIRE(!car.SetSpeed(61));

	REQUIRE(car.SetGear(Gear::Third));
	REQUIRE(car.GetGear() == Gear::Third);
	REQUIRE(!car.SetSpeed(29));
	REQUIRE(car.SetSpeed(30));
	REQUIRE(car.GetSpeed() == 30);
	REQUIRE(car.SetSpeed(60));
	REQUIRE(car.GetSpeed() == 60);
	REQUIRE(!car.SetSpeed(61));

	REQUIRE(car.SetGear(Gear::Fourth));
	REQUIRE(car.GetGear() == Gear::Fourth);
	REQUIRE(!car.SetSpeed(39));
	REQUIRE(car.SetSpeed(40));
	REQUIRE(car.GetSpeed() == 40);
	REQUIRE(car.SetSpeed(90));
	REQUIRE(car.GetSpeed() == 90);
	REQUIRE(!car.SetSpeed(91));

	REQUIRE(car.SetGear(Gear::Fifth));
	REQUIRE(car.GetGear() == Gear::Fifth);
	REQUIRE(!car.SetSpeed(49));
	REQUIRE(car.SetSpeed(50));
	REQUIRE(car.GetSpeed() == 50);
	REQUIRE(car.SetSpeed(150));
	REQUIRE(car.GetSpeed() == 150);
	REQUIRE(!car.SetSpeed(151));
};