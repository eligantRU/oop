#pragma once

#include "stdafx.h"

#include "Car.h"

class CCarMenu
{
public:
	CCarMenu(CCar & car);
	~CCarMenu() = default;

	void DoCommand(std::string & commandLine);

	void GetInfo() const;
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);

private:
	CCar & m_car;
};
