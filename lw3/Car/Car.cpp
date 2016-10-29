#include "stdafx.h"

#include "Car.h"

namespace
{

template <typename T>
bool IsInRange(const T number, const std::pair<T, T> range)
{
	return (range.first <= number) && (number <= range.second);
}

bool IsSpeedInGearRange(const Gear gear, const int speed)
{
	return (gear == Gear::Neutral) ||
		   (IsInRange(speed, REVERSE_SPEED_RANGE) && (gear == Gear::Reverse)) ||
		   (IsInRange(speed, FIRST_SPEED_RANGE) && (gear == Gear::First)) ||
		   (IsInRange(speed, SECOND_SPEED_RANGE) && (gear == Gear::Second)) ||
		   (IsInRange(speed, THIRD_SPEED_RANGE) && (gear == Gear::Third)) ||
		   (IsInRange(speed, FOURTH_SPEED_RANGE) && (gear == Gear::Fourth)) ||
		   (IsInRange(speed, FIFTH_SPEED_RANGE) && (gear == Gear::Fifth));
}

}

CCar::CCar() = default;

CCar::~CCar() = default;

bool CCar::IsEngineTurnOn() const
{
	return m_isEngineTurnOn;
}

bool CCar::SetGear(Gear gear)
{
	if (!m_isEngineTurnOn)
	{
		if (gear == Gear::Neutral)
		{
			m_gear = gear;
			return true;
		}
	}
	else
	{
		if (IsSpeedInGearRange(gear, m_speed) || (m_gear == gear))
		{
			m_gear = gear;
			return true;
		}
	}

	return false;
}

Gear CCar::GetGear() const
{
	return m_gear;
}

bool CCar::SetSpeed(unsigned speed)
{
	if (m_gear == Gear::Neutral)
	{
		if (speed <= static_cast<unsigned>(m_speed))
		{
			m_speed = speed;
			return true;
		}
		return false;
	}
	if (IsSpeedInGearRange(m_gear, speed))
	{
		int signedSpeed = speed;
		m_speed = (m_gear == Gear::Reverse) ? -signedSpeed : signedSpeed;
		return true;
	}
	return false;
}

int CCar::GetSpeed() const
{
	return abs(m_speed);
}

Direction CCar::GetDirection() const
{
	if (m_speed == 0)
	{
		return Direction::Stop;
	}
	else if ((m_gear == Gear::Reverse) || 
		    ((m_gear == Gear::Neutral) && (m_speed < 0)))
	{
		return Direction::Back;
	}
	else
	{
		return Direction::Forward;
	}
}

bool CCar::TurnOnEngine()
{
	if (!m_isEngineTurnOn)
	{
		m_isEngineTurnOn = true;
		return true;
	}
	return false;
}

bool CCar::TurnOffEngine()
{
	if ((m_isEngineTurnOn) && (m_gear == Gear::Neutral) && (m_speed == 0))
	{
		m_isEngineTurnOn = false;
		return true;
	}
	return false;
}
