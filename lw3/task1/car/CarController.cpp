#include "CarController.h"
#include <cassert>

using namespace std::placeholders;

CCarController::CCarController(CCar& car, std::istream& input, std::ostream& output)
	:m_car(car),
	m_input(input),
	m_output(output),
	m_actionMap({
		{"Info", std::bind(&CCarController::Info, this, _1)},
		{"EngineOn", std::bind(&CCarController::EngineOn, this, _1)},
		{"EngineOff", std::bind(&CCarController::EngineOff, this, _1)},
		{"SetGear", std::bind(&CCarController::SetGear, this, _1)},
		{"SetSpeed", std::bind(&CCarController::SetSpeed, this, _1)}
		})
{
};

bool CCarController::HandleCommand()
{
	std::string commandLine;
	std::getline(m_input, commandLine);
	std::istringstream strm(commandLine);

	std::string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
};

Gear CCarController::IntToGear(const int& gear)
{
	switch (gear)
	{
	case -1:
		return Gear::Reverse;
		break;
	case 0:
		return Gear::Neutral;
		break;
	case 1:
		return Gear::First;
		break;
	case 2:
		return Gear::Second;
		break;
	case 3:
		return Gear::Third;
		break;
	case 4:
		return Gear::Fourth;
		break;
	case 5:
		return Gear::Fifth;
		break;
	default:
		assert(false);
		return Gear::Neutral;
	}
};

int CCarController::GearToInt(const Gear& gear)
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

bool CCarController::Info(std::istream& args)
{
	std::string info = "Gear is ";
	info += std::to_string(GearToInt(m_car.GetGear())) + "\nSpeed is ";
	info += std::to_string(m_car.GetSpeed()) + "\nEngine is ";
	info += (m_car.IsTurnedOn()) ? "on" : "off";

	switch (m_car.GetDirection())
	{
	case Direction::Forward:
		info += "\nCar moves forward\n";
		break;
	case Direction::Backward:
		info += "\nCar moves backward\n";
		break;
	case Direction::Standing:
		info += "\nCar is standing still\n";
		break;
	}

	m_output << info;

	return true;
};

bool CCarController::EngineOn(std::istream& args)
{
	if (m_car.IsTurnedOn())
	{
		m_output << "The car engine is already on\n";
		return true;
	}
	else
	{
		if (m_car.TurnOnEngine())
		{
			m_output << "Car engine started successfully\n";
			return true;
		}
		else
		{
			m_output << "Unable to start engine\n";
			return true;
		}
	}

};

bool CCarController::EngineOff(std::istream& args)
{
	if (!m_car.IsTurnedOn())
	{
		m_output << "The car engine is already off\n";
		return true;
	}
	else
	{
		if (m_car.TurnOffEngine())
		{
			m_output << "Car engine turned off successfully\n";
			return true;
		}
		else
		{
			m_output << "Unable to turn off engine\n";
			return true;
		}
	}
};

bool CCarController::SetGear(std::istream& args)
{
	std::string arg;
	args >> arg;

	int gear;

	if (ConvertStringToint(arg, gear))
	{
		if (m_car.SetGear(IntToGear(gear)))
		{
			m_output << "You have successfully set gear\n";
		}
		else
		{
			m_output << "Unable to set gear\n";
		}
	}

	return true;
};

bool CCarController::SetSpeed(std::istream& args)
{
	std::string arg;
	args >> arg;

	int speed;

	if (ConvertStringToint(arg, speed))
	{
		m_output << speed << std::endl;
		if (m_car.SetSpeed(speed))
		{
			m_output << "You have successfully set speed\n";
		}
		else
		{
			m_output << "Unable to set speed\n";
		}
	}

	return true;
};

bool CCarController::ConvertStringToint(const std::string& str, int& num)
{
	try
	{
		num = std::stoi(str);
		return true;
	}
	catch (const std::invalid_argument& e)
	{
		m_output << e.what() << std::endl;
		return false;
	}
};