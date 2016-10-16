#include "stdafx.h"

#include "Car.h"

CCar::CCar() = default;

CCar::~CCar() = default;

bool CCar::IsEngineTurnOn() const
{
	return m_isEngineTurnOn;
}

bool CCar::SetGear(int gear)
{
	if (!m_isEngineTurnOn)
	{
		if (gear == 0)
		{
			m_gear = gear;
			return true;
		}
		return false;
	}
	return false;
}

int CCar::GetGear() const
{
	return m_gear;
}

bool CCar::TurnOnEngine()
{
	if (m_isEngineTurnOn)
	{
		return false;
	}
	else
	{
		m_isEngineTurnOn = true;
		return true;
	}
}

bool CCar::TurnOffEngine()
{
	if (!m_isEngineTurnOn)
	{
		return false;
	}
	else
	{
		m_isEngineTurnOn = false;
		return true;
	}
}
