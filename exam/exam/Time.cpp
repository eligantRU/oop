#include "stdafx.h"

#include "Time.h"

namespace
{

bool IsInRange(int value, std::pair<int, int> range)
{
	return ((range.first <= value) && (value <= range.second));
}

std::string FormatNumber(int num)
{
	return (num < 10) ? ("0" + std::to_string(num)) : std::to_string(num);
}

const std::pair<int, int> SECOND_RANGE(0, 59);
const std::pair<int, int> MINUTE_RANGE(0, 59);
const std::pair<int, int> HOUR_RANGE(0, 23);

}

CTime::CTime(int time)
	:m_timeStamp(time)
{

}

CTime::CTime(int hours, int minutes, int seconds)
{
	if (!IsInRange(hours, HOUR_RANGE))
	{
		throw std::invalid_argument("hours must be in 0..23");
	}
	if (!IsInRange(minutes, MINUTE_RANGE))
	{
		throw std::invalid_argument("minutes must be in 0..59");
	}
	if (!IsInRange(seconds, SECOND_RANGE))
	{
		throw std::invalid_argument("seconds must be in 0..59");
	}
	m_timeStamp = 3600 * hours + 60 * minutes + seconds;
}

int CTime::GetHours() const
{
	return (m_timeStamp / 3600) % 24;
}

int CTime::GetMinutes() const
{
	return (m_timeStamp / 60) % 60;
}

int CTime::GetSeconds() const
{
	return m_timeStamp % 60;
}

std::string CTime::ToString() const
{
	auto hours = FormatNumber(GetHours());
	auto minutes = FormatNumber(GetMinutes());
	auto seconds = FormatNumber(GetSeconds());
	return {
		hours + ":" + minutes + ":" + seconds
	};
}

CTime & CTime::operator+=(const CTime & other)
{
	m_timeStamp = (m_timeStamp + other.m_timeStamp) % (24 * 60 * 60);
	return *this;
}

CTime & CTime::operator-=(const CTime & other)
{
	m_timeStamp = ((24 * 60 * 60) + (m_timeStamp - other.m_timeStamp)) % (24 * 60 * 60);
	return *this;
}

int CTime::GetTimeStamp() const
{
	return m_timeStamp;
}

std::ostream & operator<<(std::ostream & stream, const CTime & time)
{
	stream << time.ToString();
	return stream;
}

const CTime operator+(const CTime & lhs, const CTime & rhs)
{
	return CTime((lhs.GetTimeStamp() + rhs.GetTimeStamp()) % (24 * 60 * 60));
}

const CTime operator-(const CTime & lhs, const CTime & rhs)
{
	return CTime((lhs.GetTimeStamp() - rhs.GetTimeStamp() + (24 * 60 * 60)) % (24 * 60 * 60));
}
