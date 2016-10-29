#pragma once

#include "stdafx.h"

enum class Gear
{
	Reverse = -1,
	Neutral = 0,
	First,
	Second,
	Third,
	Fourth,
	Fifth
};

enum class Direction
{
	Back,
	Stop,
	Forward
};

const std::pair<int, int> REVERSE_SPEED_RANGE(0, 20);
const std::pair<int, int> NEUTRAL_SPEED_RANGE(0, 150);
const std::pair<int, int> FIRST_SPEED_RANGE(0, 30);
const std::pair<int, int> SECOND_SPEED_RANGE(20, 50);
const std::pair<int, int> THIRD_SPEED_RANGE(30, 60);
const std::pair<int, int> FOURTH_SPEED_RANGE(40, 90);
const std::pair<int, int> FIFTH_SPEED_RANGE(50, 150);

class CCar
{
public:
	CCar();
	~CCar();

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool IsEngineTurnOn() const;

	bool SetGear(Gear gear);
	Gear GetGear() const;

	bool SetSpeed(unsigned speed);
	int GetSpeed() const;

	Direction GetDirection() const;

	friend bool operator==(const CCar & left, const CCar & right);

private:
	bool m_isEngineTurnOn = false;
	Gear m_gear = Gear::Neutral;
	int m_speed = 0;
};

bool operator==(const CCar & left, const CCar & right)
{
	return (left.m_isEngineTurnOn == right.m_isEngineTurnOn) && (left.m_speed == right.m_speed) && (left.m_gear == right.m_gear);
}
