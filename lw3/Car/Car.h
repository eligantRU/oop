#pragma once

#include "stdafx.h"

class CCar
{
public:
	CCar();
	~CCar();

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool IsEngineTurnOn() const;

	bool SetGear(int gear);
	int GetGear() const;

	bool SetSpeed(int speed);
	int GetSpeed() const;

private:

	bool m_isEngineTurnOn = false;
	int m_gear = 0;
};
