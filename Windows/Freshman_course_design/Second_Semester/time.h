#ifndef _TIME_H_
#define _TIME_H_
#include <iostream>
#include <math.h>

using namespace std;

class Time
{
private:
	int year , month , day , hour , minute , second;

public:
	Time ( );
	void set_time ( int y , int mo , int d , int h , int min , int s );
	int get_year ( );
	int get_month ( );
	int get_day ( );
	int get_hour ( );
	int get_minute ( );
	int get_second ( );
	long long int get_time ( );
	friend ostream &operator<<( ostream &os , Time &t );
};
Time::Time ( )
{
	year = 0;
	month = 0;
	day = 0;
	hour = 0;
	minute = 0;
	second = 0;
}

void Time::set_time ( int y , int mo , int d , int h , int min , int s )
{
	year = y;
	month = mo;
	day = d;
	hour = h;
	minute = min;
	second = s;
}

int Time::get_year ( )
{
	return year;
}

int Time::get_month ( )
{
	return month;
}

int Time::get_day ( )
{
	return day;
}

int Time::get_hour ( )
{
	return hour;
}

int Time::get_minute ( )
{
	return minute;
}

int Time::get_second ( )
{
	return second;
}

long long int Time::get_time ( )
{
	long long int a;
	a = year * pow ( 10 , 10 ) + month * pow ( 10 , 8 ) + day * pow ( 10 , 6 ) + hour * pow ( 10 , 4 ) + minute * pow ( 10 , 2 ) + second;
	return a;
}

ostream &operator<<( ostream &os , Time &t )
{
	os << t.year << "年" << t.month << "月" << t.day << "日  " << t.hour << ':' << t.minute << ':' << t.second;
	return os;
}
#endif