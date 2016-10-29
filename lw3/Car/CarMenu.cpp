#include "stdafx.h"

#include "CarMenu.h"

namespace
{

bool IsNumber(const std::string & str)
{
	return std::all_of(str.begin(), str.end(), isdigit); 
}

template <typename T>
bool IsInRange(const T number, const std::pair<T, T> range)
{
	return (range.first <= number) && (number <= range.second);
}

std::string DirectionToString(const Direction & direction)
{
	switch (direction)
	{
	case Direction::Back:
		return "back";
	case Direction::Forward:
		return "forward";
	case Direction::Stop:
		return "stop";
	default:
		assert(!"unexpected direction");
		return "<unknown direction>";
	}
}

std::string GearToString(const Gear & gear)
{
	switch (gear)
	{
	case Gear::Reverse:
		return "reverse";
	case Gear::Neutral:
		return "neutral";
	case Gear::First:
		return "first";
	case Gear::Second:
		return "second";
	case Gear::Third:
		return "third";
	case Gear::Fourth:
		return "fourth";
	case Gear::Fifth:
		return "fifth";
	default:
		assert(!"unexpected gear");
		return "<unknown gear>";
	}
}

void Info(const CCar & car)
{
	std::cout << "Engine status: " << ((car.IsEngineTurnOn()) ? ("turned on") : ("turned off")) << std::endl;
	std::cout << "Speed: " << car.GetSpeed() << std::endl;
	std::cout << "Direction: " << DirectionToString(car.GetDirection()).c_str() << std::endl;
	std::cout << "Gear: " << GearToString(car.GetGear()).c_str() << std::endl;
}

Gear IntToGear(const int gear)
{
	if (IsInRange(gear, std::pair<int, int>(-1, 5)))
	{
		switch (gear)
		{
		case -1:
			return Gear::Reverse;
		case 0:
			return Gear::Neutral;
		case 1:
			return Gear::First;
		case 2:
			return Gear::Second;
		case 3:
			return Gear::Third;
		case 4:
			return Gear::Fourth;
		case 5:
			return Gear::Fifth;
		default:
			throw std::logic_error("<unknown gear>");
		}
	}
	throw std::runtime_error("gear must be -1..5");
}

}

CCarMenu::CCarMenu(CCar & car)
	:m_car(car)
{
	
}

void CCarMenu::DoCommand(std::string & commandLine)
{
	boost::to_upper(commandLine);
	std::vector<std::string> commands;
	boost::split(commands, commandLine, boost::is_any_of(" "));
	if ((commands[0] == "INFO") && (commands.size() == 1))
	{
		GetInfo();
	}
	else if ((commands[0] == "ENGINE") && (commands[1] == "ON"))
	{
		TurnOnEngine();
	}
	else if ((commands[0] == "ENGINE") && (commands[1] == "OFF"))
	{
		TurnOffEngine();
	}
	else if ((commands[0] == "SETGEAR") && IsNumber(commands[1]))
	{
		SetGear(stoi(commands[1]));
	}
	else if ((commands[0] == "SETSPEED") && IsNumber(commands[1]))
	{
		SetSpeed(stoi(commands[1]));
	}
	else
	{
		std::cout << "Unknown command" << std::endl;
	}
}

bool CCarMenu::TurnOnEngine()
{
	auto result = m_car.TurnOnEngine();
	if (result)
	{
		std::cout << "engine was turned on" << std::endl;
	}
	else
	{
		std::cout << "engine is already enabled" << std::endl;
	}
	return result;
}

bool CCarMenu::TurnOffEngine()
{
	auto result = m_car.TurnOffEngine();
	if (result)
	{
		std::cout << "engine was turned off" << std::endl;
	}
	else
	{
		std::cout << "engine wasn't turned off" << std::endl;
	}
	return result;
}

void CCarMenu::GetInfo() const
{
	Info(m_car);
}

bool CCarMenu::SetGear(int gear)
{
	try
	{
		auto carGear = IntToGear(gear);
		auto result = m_car.SetGear(carGear);
		if (result)
		{
			std::cout << "gear now at " << gear << std::endl;
		}
		else
		{
			std::cout << "gear didn't change" << std::endl;
		}
		return result;
	}
	catch (std::exception & exception)
	{
		std::cout << "gear didn't change" << std::endl;
		std::cerr << exception.what() << std::endl;
		return false;
	}
}

bool CCarMenu::SetSpeed(int speed)
{
	auto result = m_car.SetSpeed(speed);
	if (result)
	{
		std::cout << "speed now at " << speed << std::endl;
	}
	else
	{
		std::cout << "speed didn't changed" << std::endl;
	}
	return result;
}
