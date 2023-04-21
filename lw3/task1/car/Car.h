#pragma once
#include <map>
#include <sstream>
#include <iostream>

enum class Gear
{
	Reverse,
	Neutral,
	First,
	Second,
	Third,
	Fourth,
	Fifth,
};

enum class Direction
{
	Forward,
	Backward,
	Standing
};

const int SPEED_RANGES[][2] = {
	{-20, 0},
	{-20, 150},
	{0, 30},
	{20, 50},
	{30, 60},
	{40, 90},
	{50, 150}
};

class CCar
{
public:
	CCar();

	bool IsTurnedOn() const;
	Direction GetDirection() const;
	int GetSpeed() const;
	Gear GetGear() const;

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(Gear gear);
	bool SetSpeed(int speed);
private:
	bool m_isEngineOn;
	int m_speed;
	Gear m_gear;


	bool SetSpeedBackwardOnNewtralGear(const int speed);
	bool SetSpeedForwardOnNewtralGear(const int speed);
	bool SetSpeedReverseGear(const int speed);
	bool SetSpeedForward(const int speed);

	int GearToInt(const Gear& gear);
	bool IsGearInRange(const Gear& gear);
	bool IsSpeedInRange(const int& speed);
};