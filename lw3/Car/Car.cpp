#include "stdafx.h"

#include "Car.h"

static const std::pair<int, int> REVERSE_SPEED_RANGE(0, 20);
static const std::pair<int, int> NEUTRAL_SPEED_RANGE(0, 150);
static const std::pair<int, int> FIRST_SPEED_RANGE(0, 30);
static const std::pair<int, int> SECOND_SPEED_RANGE(20, 50);
static const std::pair<int, int> THIRD_SPEED_RANGE(30, 60);
static const std::pair<int, int> FOURTH_SPEED_RANGE(40, 90);
static const std::pair<int, int> FIFTH_SPEED_RANGE(50, 150);

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

bool operator==(const CCar & left, const CCar & right)
{
	return (left.m_isEngineTurnOn == right.m_isEngineTurnOn) && (left.m_speed == right.m_speed) && (left.m_gear == right.m_gear);
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
	else if (m_speed < 0)
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
