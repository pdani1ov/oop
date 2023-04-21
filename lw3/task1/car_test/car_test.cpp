#include "../../../catch/catch.hpp"
#include "../car/Car.h"
#include "../car/CarController.h"

int GearToInt(const Gear& gear)
{
	switch (gear)
	{
	case Gear::Reverse:
		return -1;
		break;
	case Gear::Neutral:
		return 0;
		break;
	case Gear::First:
		return 1;
		break;
	case Gear::Second:
		return 2;
		break;
	case Gear::Third:
		return 3;
		break;
	case Gear::Fourth:
		return 4;
		break;
	case Gear::Fifth:
		return 5;
		break;
	default:
		assert(false);
		return 0;
	}
};

void CheckLimitSpeed(CCar& car, Gear gear)
{
	REQUIRE(car.SetGear(gear));
	REQUIRE(car.GetGear() == gear);
	REQUIRE(!car.SetSpeed(SPEED_RANGES[GearToInt(gear) + 1][0] - 1));
	REQUIRE(car.SetSpeed(SPEED_RANGES[GearToInt(gear) + 1][0]));
	REQUIRE(!car.SetSpeed(SPEED_RANGES[GearToInt(gear) + 1][0]));//���������, ��� ������������ �������� �� ��, � ������� ��� ���� ����������, ���������� false
	REQUIRE(car.GetSpeed() == SPEED_RANGES[GearToInt(gear) + 1][0]);
	REQUIRE(car.SetSpeed(SPEED_RANGES[GearToInt(gear) + 1][1]));
	REQUIRE(car.GetSpeed() == SPEED_RANGES[GearToInt(gear) + 1][1]);
	REQUIRE(!car.SetSpeed(SPEED_RANGES[GearToInt(gear) + 1][1] + 1));
};

/*SHOW TEST COVERAGE - ���������� ������� �� ������� ������ ������� ����*/

TEST_CASE("Check work of engine")
{
	CCar car;

	/*��������� ��������� ���������*/
	REQUIRE(car.TurnOnEngine());
	REQUIRE(car.IsTurnedOn());

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

	/*��������� ���������� ��������� ��� ����������� �������� � �������� = 0*/
	REQUIRE(car.SetSpeed(0));
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE(car.SetGear(Gear::Neutral));
	REQUIRE(car.GetGear() == Gear::Neutral);
	REQUIRE(car.TurnOffEngine());
	REQUIRE(!car.IsTurnedOn());

	/*���������, ��� ��� ���������� ���������, ���� �� ��� ��������, ���������� true*/
	REQUIRE(car.TurnOffEngine());
	REQUIRE(!car.IsTurnedOn());
};

TEST_CASE("Check work reverse gear")
{
	CCar car;
	car.TurnOnEngine();
	REQUIRE(car.GetDirection() == Direction::Standing);

	/*��������, ��� �� ������ �������� �������������*/
	REQUIRE(car.SetGear(Gear::Reverse));
	REQUIRE(car.GetGear() == Gear::Reverse);

	/*��������, ��������� �������� �� ��, ������� �� ������ � ��������*/
	REQUIRE(!car.SetSpeed(21));

	/*��������, ������, ����� ���������� ���� �����(�������� != 0) �� ���������� �������� � �� �� ����� ����������� �������� �� ������(����� �������� = 0)*/
	REQUIRE(car.SetSpeed(10));
	REQUIRE(car.GetSpeed() == 10);
	REQUIRE(car.GetDirection() == Direction::Backward);
	REQUIRE(car.SetGear(Gear::Neutral));
	REQUIRE(car.GetGear() == Gear::Neutral);
	REQUIRE(car.GetDirection() == Direction::Backward);
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

	car.TurnOnEngine();

	/*���������, ��� ��� �������� = 0 � ����������� �������� ������ ������ �������� ��������*/
	REQUIRE(!car.SetSpeed(20));
	REQUIRE(!car.SetSpeed(-20));

	/*���������, ��� �� ����������� �������� ����� ������ ��������� ��������*/
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

	/*���������, ��� ��� ����������� ��������� ������ ������ ��������*/
	REQUIRE(!car.SetSpeed(10));
	REQUIRE(!car.SetSpeed(0));
	REQUIRE(!car.SetSpeed(-10));

	car.TurnOnEngine();

	/*��������� ������������ ������������ �������� � ������������ ���������*/
	REQUIRE(car.SetGear(Gear::First));
	REQUIRE(car.GetGear() == Gear::First);
	REQUIRE(!car.SetSpeed(-1));
	REQUIRE(car.SetSpeed(30));
	REQUIRE(car.GetSpeed() == 30);
	REQUIRE(car.GetDirection() == Direction::Forward);
	REQUIRE(!car.SetSpeed(31));

	/*���������, ��� ������������ �� ��������, ������� �� ������ � �������� ���������, ����������*/
	REQUIRE(!car.SetGear(Gear::Fifth));

	CheckLimitSpeed(car, Gear::Second);
	CheckLimitSpeed(car, Gear::Third);
	CheckLimitSpeed(car, Gear::Fourth);
	CheckLimitSpeed(car, Gear::Fifth);
};