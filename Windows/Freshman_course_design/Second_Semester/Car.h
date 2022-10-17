#ifndef _CAR_H_
#define _CAR_H_
#include <iostream>
#include <string.h>
#include <string>
#include "time.h"

using namespace std;

class car : public Time
{
private:
	int price , price_time; //停车费，停车时间
	int type_num;		   //车型，数字型的
	string car_num;		   //车牌号 a
	string color;		   //颜色 b
	string state = "in";   //车辆状态
	string type;		   //车的型号 c
public:
	car ( );															   //无参构造函数
	Time itime;														   //到达时间
	Time otime;														   //离开时间
	int get_p_t ( );													   //得到停车时间
	int get_type_unm ( );												   //得到车型数字型的
	string get_color ( );												   //得到车颜色
	string get_num ( );												   //得到车牌号
	string get_state ( );												   //得到车的状态，离开或是在位
	string get_type ( );												   //得到车型号
	void car_base ( );												   //输出车辆的信息,车在停车位时使用
	void car_history ( );												   //车辆历史记录
	void set_car_num ( string a );										   //设置车牌号
	void set_color ( string b );										   //设置车的颜色
	void set_itime ( int iy , int imo , int id , int ih , int imin , int is ); //设置到达时间
	void set_otime ( int oy , int omo , int od , int oh , int omin , int os ); //设置离开时间
	void set_price ( int x );											   //计算停车费用
	void set_state ( );												   //设置车辆状态
	void set_type ( int n );											   //设置车的车型
};

car::car ( )
{
	car_num = ' ';
	color = ' ';
	type = ' ';
	itime.set_time ( 99999 , 12 , 31 , 23 , 59 , 59 );
}

int car::get_p_t ( )
{
	return price_time;
}

int car::get_type_unm ( )
{
	return type_num;
}

string car::get_color ( )
{
	return color;
}

string car::get_num ( )
{
	return car_num;
}

string car::get_state ( )
{
	return state;
}

string car::get_type ( )
{
	return type;
}

void car::car_base ( )
{
	if ( get_num ( ) == " " )
	{
		cout.fill ( '-' );
		cout.width ( 80 );
		cout << "-" << endl;
		cout << endl;
		cout << endl;
		cout.fill ( ' ' );
		cout.width ( 35 );
		cout << " ";
		cout << "空车位" << endl;
		cout << endl;
		cout << endl;
		cout.fill ( '-' );
		cout.width ( 80 );
		cout << "-" << endl;
	}
	else
	{
		cout.fill ( '-' );
		cout.width ( 80 );
		cout << "-" << endl;
		cout << " ";
		cout << "车辆信息:" << endl;
		cout.fill ( ' ' );
		cout.width ( 10 );
		cout << " ";
		cout << "车牌号:" << car_num << endl;
		cout.fill ( ' ' );
		cout.width ( 10 );
		cout << " ";
		cout << "颜色:" << color << endl;
		cout.fill ( ' ' );
		cout.width ( 10 );
		cout << " ";
		cout << "车型:" << type << endl;
		cout.fill ( ' ' );
		cout.width ( 10 );
		cout << " ";
		cout << itime << "进入停车场" << endl;
		cout.fill ( '-' );
		cout.width ( 80 );
		cout << "-" << endl;
	}
}

void car::car_history ( )
{
	cout.fill ( '-' );
	cout.width ( 80 );
	cout << "-" << endl;
	cout << " ";
	cout << "车辆信息:" << endl;
	cout.fill ( ' ' );
	cout.width ( 10 );
	cout << " ";
	cout << "车牌号:" << car_num << endl;
	cout.fill ( ' ' );
	cout.width ( 10 );
	cout << " ";
	cout << "颜色:" << color << endl;
	cout.fill ( ' ' );
	cout.width ( 10 );
	cout << " ";
	cout << "车型:" << type << endl;
	cout.fill ( ' ' );
	cout.width ( 10 );
	cout << " ";
	cout << itime << "进入停车场  " << otime << "离开停车场" << endl;
	if ( price == 0 )
	{
		cout.fill ( ' ' );
		cout.width ( 10 );
		cout << " ";
		cout << "停车不到半小时 停车费用：" << price << "元" << endl;
	}
	else
	{
		cout.fill ( ' ' );
		cout.width ( 10 );
		cout << " ";
		cout << "停车时长：" << price_time << "小时 停车费用：" << price << "元" << endl;
	}
	cout.fill ( '-' );
	cout.width ( 80 );
	cout << "-" << endl;
}

void car::set_car_num ( string a )
{
	car_num = a;
}

void car::set_color ( string b )
{
	color = b;
}

void car::set_itime ( int iy , int imo , int id , int ih , int imin , int is )
{
	itime.set_time ( iy , imo , id , ih , imin , is );
}

void car::set_otime ( int oy , int omo , int od , int oh , int omin , int os )
{
	otime.set_time ( oy , omo , od , oh , omin , os );
}

void car::set_price ( int x )
{
	price = x * 3;
	price_time = x;
}

void car::set_state ( )
{
	state = "leave";
}

void car::set_type ( int n )
{
	switch ( n )
	{
		case 1:
			type = "小汽车";
			break;
		case 2:
			type = "小卡";
			break;
		case 3:
			type = "中卡";
			break;
		case 4:
			type = "大卡";
			break;
		default:
			break;
	}
	type_num = n;
}
#endif