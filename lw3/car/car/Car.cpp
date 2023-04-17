#include "Car.h"

CCar::CCar()
	:m_isEngineOn(false),
	m_gear(Gear::Neutral),
	m_speed(0)
{

};

bool CCar::IsTurnedOn() const
{
	return m_isEngineOn;
};

Direction CCar::GetDirection() const
{
	if (m_speed == 0)
	{
		return Direction::Standing;
	}
	else if (m_speed > 0)
	{
		return Direction::Forward;
	}
	else
	{
		return Direction::Backward;
	}
};

int CCar::GetSpeed() const
{
	if (m_speed < 0)
	{
		return m_speed * (-1);
	}
	else
	{
		return m_speed;
	}
};

Gear CCar::GetGear() const
{
	return m_gear;
};

bool CCar::TurnOnEngine()
{
	if (!m_isEngineOn)
	{
		m_isEngineOn = true;
	}

	return true;
};

bool CCar::TurnOffEngine()
{
	if (!m_isEngineOn)
	{
		return true;
	}

	if (m_gear == Gear::Neutral && m_speed == 0)
	{
		m_isEngineOn = false;
		return true;
	}
	else
	{
		return false;
	}
};

int CCar::GearToInt(const Gear& gear)
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
	}
};

bool CCar::SetGear(Gear gear)
{
	if (!m_isEngineOn && gear != Gear::Neutral)
	{
		return false;
	}

	if (gear == m_gear)
	{
		return true;
	}

	if (gear == Gear::Neutral)
	{
		m_gear = gear;
		return true;
	}
	else if (gear == Gear::Reverse)
	{
		if (m_speed == 0)
		{
			m_gear = gear;
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (IsGearInRange(gear))
	{
		m_gear = gear;
		return true;
	}
	else
	{
		return false;
	}
};

bool CCar::SetSpeedBackwardOnNewtralGear(const int speed)
{
	if (speed > m_speed)
	{
		if (speed > m_speed * (-1))
		{
			return false;
		}
		else
		{
			m_speed = speed * (-1);
			return true;
		}
	}
	else
	{
		return false;
	}
};

bool CCar::SetSpeedForwardOnNewtralGear(const int speed)
{
	if (speed < m_speed)
	{
		m_speed = speed;
		return true;
	}
	else
	{
		return false;
	}
};

bool CCar::SetSpeedReverseGear(const int speed)
{
	if (IsSpeedInRange(speed * (-1)))
	{
		m_speed = speed * (-1);
		return true;
	}
	else
	{
		return false;
	}
};

bool CCar::SetSpeedForward(const int speed)
{
	if (IsSpeedInRange(speed))
	{
		m_speed = speed;
		return true;
	}
	else
	{
		return false;
	}
};

bool CCar::SetSpeed(int speed)
{
	if (speed < 0)
	{
		return false;
	}

	if (!m_isEngineOn)
	{
		return false;
	}

	if (m_speed == speed)
	{
		return false;
	}

	if (m_gear == Gear::Neutral)
	{
		if (m_speed < 0)
		{
			return SetSpeedBackwardOnNewtralGear(speed);
		}
		else if (m_speed == 0)
		{
			return false;
		}
		else
		{
			return SetSpeedForwardOnNewtralGear(speed);
		}
	}
	else if (m_gear == Gear::Reverse)
	{
		return SetSpeedReverseGear(speed);
	}
	else
	{
		return SetSpeedForward(speed);
	}
};

bool CCar::IsGearInRange(const Gear& gear)
{
	return m_speed >= SPEED_RANGES[GearToInt(gear) + 1][0] && m_speed <= SPEED_RANGES[GearToInt(gear) + 1][1];
};

bool CCar::IsSpeedInRange(const int& speed)
{
	return speed >= SPEED_RANGES[GearToInt(m_gear) + 1][0] && speed <= SPEED_RANGES[GearToInt(m_gear) + 1][1];
};