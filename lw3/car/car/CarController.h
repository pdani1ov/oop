#pragma once
#include <fstream>
#include <sstream>
#include <map>
#include <functional>
#include <string>
#include "Car.h"

class CCarController
{
	public:
		CCarController(CCar& car, std::istream& input, std::ostream& output);

		bool HandleCommand();
	private:
		bool Info(std::istream& args);
		bool EngineOn(std::istream& args);
		bool EngineOff(std::istream& args);
		bool SetGear(std::istream& args);
		bool SetSpeed(std::istream& args);

		CCar& m_car;
		std::istream& m_input;
		std::ostream& m_output;

		using ActionMap = std::map<std::string, std::function<bool(std::istream& args)>>;

		ActionMap m_actionMap;

		bool ConvertStringToint(const std::string& str, int& num);
		int GearToInt(const Gear& gear);
		Gear IntToGear(const int& gear);
};