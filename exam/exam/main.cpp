#include "stdafx.h"
#include <string>
#include <memory>
#include <iostream>

using namespace std;

/*struct Student
{
	Student() = default;

	~Student() noexcept(true)
	{
	}

	Student & operator=(const Student & student)
	{
		Student temp;
		temp.m_name = student.m_name;
		temp.m_surname = student.m_surname;
		temp.m_patronymic = student.m_patronymic;
		std::swap(temp, *this);
		return *this;
	}

	void DoSthWrong()
	{
		throw std::exception("Sth was wrong");
	}

	string m_name;
	string m_surname;
	string m_patronymic;
};


void DoSomething(unique_ptr<string> && s1, unique_ptr<string> && s2)
{

}*/

class CMyException 
	:public runtime_error
{
public:
	explicit CMyException(const string & msg, const size_t code)
		:runtime_error(msg)
		,m_code(code)
	{
		
	}

	size_t GetCode() const
	{
		return m_code;
	}

private:
	size_t m_code;
};

/*int main()
{
	try
	{
		throw CMyException("Malov, die balls", 36);
	}
	catch (const CMyException & ex)
	{
		std::cerr << ex.what() << std::endl;
		std::cerr << "Error code: " << ex.GetCode() << std::endl;
	}

	try
	{
		throw CMyException("My first exception", 11);
	}
	catch (const std::runtime_error & ex)
	{
		std::cerr << ex.what() << std::endl;
	}

	try
	{
		throw CMyException("My second exception", 11);
	}
	catch (const std::exception & ex)
	{
		std::cerr << ex.what() << std::endl;
	}
}*/

class Base
{
public:
	virtual ~Base() {}
protected:
	virtual void DoSomething()
	{
		std::cerr << "U DID IT!" << std::endl;
	}

	static void Hack(Base & base)
	{
		base.DoSomething();
	}
};

class Child : public Base
{
public:
	void Help(Base & base)
	{
		DoSomething();
		Hack(base);
		//base.DoSomething();
	}

	/*void Hack(Base & base)
	{
		(base.*&Child::DoSomething)();
	}*/

protected:

};

int main()
{
	Base b;
	Child ch;
	ch.Help(b);
}

/*int main()
{
	using namespace std;
	DoSomething(unique_ptr<string>(new string("hello")), unique_ptr<string>(new string("world")));

	try
	{
		Student student;
		// student.DoSthWrong();
		student.m_name = "Nick";
		student.m_surname = "Yegorov";
	}
	catch (...)
	{

	}
	return 0;
}*/
