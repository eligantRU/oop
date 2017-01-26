#include "stdafx.h"

#include <string>

class CTime
{
public:
	// Конструирует время (чч:мм:сс). 
	// Если часы, минуты, или секунды выходят за пределы 23:59:59, бросает
	// исключение invalid_argument
	CTime() = default;
	explicit CTime(int time);
	CTime(int hours, int minutes, int seconds);

	// Возвращает количество часов (0..23)
	int GetHours() const;

	// Возвращает количество минут (0..59)
	int GetMinutes() const;

	// Возвращает количество секунд (0..59)
	int GetSeconds() const;

	// Возвращает строковое представление времени в формате чч:мм:сс
	std::string ToString() const;

	CTime & operator+=(const CTime & other);
	CTime & operator-=(const CTime & other);

	int GetTimeStamp() const;

private:
	int m_timeStamp = 0;
};

std::ostream & operator<<(std::ostream & stream, const CTime & time);
const CTime operator+(const CTime & lhs, const CTime & rhs);
const CTime operator-(const CTime & lhs, const CTime & rhs);
