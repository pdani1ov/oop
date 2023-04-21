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
	REQUIRE(!car.SetSpeed(SPEED_RANGES[GearToInt(gear) + 1][0]));//Проверяем, что переключении скорости на ту, с которой уже едет автомобиль, возвращает false
	REQUIRE(car.GetSpeed() == SPEED_RANGES[GearToInt(gear) + 1][0]);
	REQUIRE(car.SetSpeed(SPEED_RANGES[GearToInt(gear) + 1][1]));
	REQUIRE(car.GetSpeed() == SPEED_RANGES[GearToInt(gear) + 1][1]);
	REQUIRE(!car.SetSpeed(SPEED_RANGES[GearToInt(gear) + 1][1] + 1));
};

/*SHOW TEST COVERAGE - показывает покрыта ли тестами каждая строчка кода*/

TEST_CASE("Check work of engine")
{
	CCar car;

	/*Проверяем включение двигателя*/
	REQUIRE(car.TurnOnEngine());
	REQUIRE(car.IsTurnedOn());

	/*Проверяем, что двигатель нельзя выключить, если передача не нейтральная, скорость = 0*/
	REQUIRE(car.SetGear(Gear::First));
	REQUIRE(car.GetGear() == Gear::First);
	REQUIRE(!car.TurnOffEngine());

	/*Проверяем, что нельзя выключить двигатель, если скорость != 0, передача нейтральная*/
	REQUIRE(car.SetSpeed(10));
	REQUIRE(car.GetSpeed() == 10);
	REQUIRE(car.SetGear(Gear::Neutral));
	REQUIRE(car.GetGear() == Gear::Neutral);
	REQUIRE(!car.TurnOffEngine());

	/*Проверяем, что нельзя выключить двигатель, если скорость != 0, передача не нейтральная*/
	REQUIRE(car.SetGear(Gear::First));
	REQUIRE(car.GetGear() == Gear::First);
	REQUIRE(!car.TurnOffEngine());

	/*Проверяем выключение двигателя при нейтральной передачи и скорости = 0*/
	REQUIRE(car.SetSpeed(0));
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE(car.SetGear(Gear::Neutral));
	REQUIRE(car.GetGear() == Gear::Neutral);
	REQUIRE(car.TurnOffEngine());
	REQUIRE(!car.IsTurnedOn());

	/*Проверяем, что при выключении двигателя, если он уже выключен, возвращает true*/
	REQUIRE(car.TurnOffEngine());
	REQUIRE(!car.IsTurnedOn());
};

TEST_CASE("Check work reverse gear")
{
	CCar car;
	car.TurnOnEngine();
	REQUIRE(car.GetDirection() == Direction::Standing);

	/*Проверям, что на заднюю передачу переключается*/
	REQUIRE(car.SetGear(Gear::Reverse));
	REQUIRE(car.GetGear() == Gear::Reverse);

	/*Проверям, изменение скорости на ту, которая не входит в диапазон*/
	REQUIRE(!car.SetSpeed(21));

	/*Проверям, случай, когда автомобиль едет назад(скорость != 0) на нетральной передаче и он не может переключить передачу на заднюю(нужна скорость = 0)*/
	REQUIRE(car.SetSpeed(10));
	REQUIRE(car.GetSpeed() == 10);
	REQUIRE(car.GetDirection() == Direction::Backward);
	REQUIRE(car.SetGear(Gear::Neutral));
	REQUIRE(car.GetGear() == Gear::Neutral);
	REQUIRE(car.GetDirection() == Direction::Backward);
	REQUIRE(!car.SetGear(Gear::Reverse));

	/*Проверяем, что на нетральной передаче нельзя поднимать скорость, но можно понижать*/
	REQUIRE(!car.SetSpeed(11));
	REQUIRE(car.SetSpeed(5));
	REQUIRE(car.GetSpeed() == 5);
};

TEST_CASE("Check work neutral gear")
{
	CCar car;

	/*Проверяем, что при выключенном двигателе можно переключиться только на нейтральную передачу*/
	REQUIRE(!car.SetGear(Gear::Reverse));
	REQUIRE(!car.SetGear(Gear::First));
	REQUIRE(car.SetGear(Gear::Neutral));

	car.TurnOnEngine();

	/*Проверяем, что при скорости = 0 и нейтральной передачи нельзя вообще изменять скорость*/
	REQUIRE(!car.SetSpeed(20));
	REQUIRE(!car.SetSpeed(-20));

	/*Проверяем, что на нейтральной передаче можно только уменьшить скорость*/
	REQUIRE(car.SetGear(Gear::First));
	REQUIRE(car.GetGear() == Gear::First);
	REQUIRE(car.SetSpeed(20));
	REQUIRE(car.GetSpeed() == 20);
	REQUIRE(car.SetGear(Gear::Neutral));
	REQUIRE(car.GetGear() == Gear::Neutral);
	REQUIRE(!car.SetSpeed(21));
	REQUIRE(car.SetSpeed(10));
	REQUIRE(car.GetSpeed() == 10);

	/*Проверяем, что на нейтральной передаче нельзя уменьшить скорость только до 0*/
	REQUIRE(!car.SetSpeed(-1));
};

TEST_CASE("Check set gear and set speed")
{
	CCar car;

	/*Проверяем, что при выключенном двигателе нельзя менять скорость*/
	REQUIRE(!car.SetSpeed(10));
	REQUIRE(!car.SetSpeed(0));
	REQUIRE(!car.SetSpeed(-10));

	car.TurnOnEngine();

	/*Проверяем правильность переключения передачи и переключения скоростей*/
	REQUIRE(car.SetGear(Gear::First));
	REQUIRE(car.GetGear() == Gear::First);
	REQUIRE(!car.SetSpeed(-1));
	REQUIRE(car.SetSpeed(30));
	REQUIRE(car.GetSpeed() == 30);
	REQUIRE(car.GetDirection() == Direction::Forward);
	REQUIRE(!car.SetSpeed(31));

	/*Проверяем, что переключение на передачу, которая не входит в диапазон скоростей, невозможно*/
	REQUIRE(!car.SetGear(Gear::Fifth));

	CheckLimitSpeed(car, Gear::Second);
	CheckLimitSpeed(car, Gear::Third);
	CheckLimitSpeed(car, Gear::Fourth);
	CheckLimitSpeed(car, Gear::Fifth);
};