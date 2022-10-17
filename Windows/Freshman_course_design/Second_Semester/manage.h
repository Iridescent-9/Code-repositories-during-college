#ifndef _MANAGE_H_
#define _MANAGE_H_
#include <iostream>
#include <string.h>
#include <string>
#include <Windows.h>
#include <fstream>
#include <cstring>
#include "Car.h"
#include "function.h"
#define PS 10
#define PS_S PS
#define CAP 500
#define LE CAP - 1
using namespace std;

class manage : public car
{
	car cars [ CAP ] , k , empty , *le;				 //对象数组acrs，删除离开时用到empty，排序时用到k，计算金额时用到 *le
	static int count;							 //总记录数
	static int ps , ps_s;						 //总车位数，剩余车位数 Parking space
	static int capacity;						 //最大记录数
	static int leave;							 //离开车库时使用，前十个为在位车辆，历史记录从后向前排列
	static int car_s , lorry_s , lorry_m , lorry_l; //小汽车，小卡，中卡，大卡
public:
	manage ( );											//无参构造函数
	~manage ( );											//析构，写文件
	friend ostream &operator<<( ostream &os , manage &m ); //运算符重载输出车库信息
	int Add ( );											//入库
	int car_delete ( );									//删除
	int car_leave ( );									//车离开车库
	int change ( );										//修改
	int search ( );										//查找
	void display ( int n );								//显示车辆信息
	int info_read ( car *info );							//读取车辆信息
	void info_write ( car *info );							//写车辆信息
	void price_c ( int n , int a );							//计算金额
	void print_statistic ( );								//输出统计信息
	void sort ( );										//按照到达时间的排序
	void statistics_model ( int n );						//统计车型，修改函数调用
	void statistics_model_minus ( int n );					//统计车型，减少
	void statistics_model_plus ( int n );					//统计车型,增加
};
int manage::capacity = CAP;
int manage::leave = LE;
int manage::car_s = 0;
int manage::lorry_s = 0;
int manage::lorry_m = 0;
int manage::lorry_l = 0;
int manage::ps = PS;
int manage::ps_s = PS_S;
int manage::count = 0;

manage::manage ( )
{
	info_read ( cars );
}

manage::~manage ( )
{
	system ( "CLS" );
	info_write ( cars );
	Sleep ( 2000 );
}

ostream &operator<<( ostream &os , manage &m )
{
	os << "停车场共有" << m.ps << "个车位，还剩余" << m.ps_s << "个车位";
	return os;
}

int manage::Add ( )
{
	string a , b;										 //车辆信息，a——车牌，b——颜色
	int c;												 //车型
	int l;												 //判断是否进车库
	int iy = 0 , imo = 0 , id = 0 , ih = 0 , im = 0 , is = 0; //进入车库时间
part1:
	{
		if ( ps_s == 0 ) //判断车库是否已满
		{
			cout << "车库已满" << endl;
			goto part2;
		}
		else
		{
			cout << "是否进入车库：1.是 2.否" << endl;
			string t;
			l = choice_12 ( t );
			cin.ignore ( );
			if ( l == 2 )
			{
				goto part2;
			}
		}
		cout << "输入要进入车库的车辆信息" << endl;
		cout << "车牌号：";
		getline ( cin , a );
		for ( int i = 0; i < ps; i++ )
		{
			if ( a == cars [ i ].get_num ( ) )
			{
				cout << "本车辆已经入库" << endl;
				cout << "是否修改预入库车辆信息；1.是 2.否" << endl;
				int j = 0;
				string t;
				j = choice_12 ( t );
				cin.ignore ( );
				if ( j == 1 )
				{
					goto part1;
				}
				else
					goto part2;
			}
		}
		for ( int i = 0; i < ps_s; i++ )
		{
			int j = 0;
			for ( int k = 0; k < ps; k++ )
			{
				if ( cars [ k ].get_num ( ) == " " )
				{
					j = k;
					goto s;
				}
			}
		s:
			{
				cout << "请输入车辆颜色：";
				getline ( cin , b );
				cout << "请输入车型（号码）：1.小汽车 2.小卡 3.中卡 4.大卡" << endl;
				string t1;
				c = choice_14 ( t1 );
				cin.ignore ( );
				cout << "请输入进入车库时间" << endl;
				cout << "年：";
				cin >> iy;
				cout << "月：";
				cin >> imo;
				cout << "日：";
				cin >> id;
				cout << "时：";
				cin >> ih;
				cout << "分：";
				cin >> im;
				cout << "秒：";
				cin >> is;
				statistics_model_plus ( c );
				le = &cars [ j ];
				le->set_car_num ( a );
				le->set_color ( b );
				le->set_type ( c );
				le->set_itime ( iy , imo , id , ih , im , is );
				if ( a == le->get_num ( ) && b == le->get_color ( ) )
				{
					count++;
					ps_s--;
					cout << "第" << count << "辆车入库成功   ";
					cout << "车库还有" << ps_s << "个空车位" << endl;
				}
				sort ( );
				cout << "是否继续添加；1.是 2，否" << endl;
				int j = 0;
				string t;
				j = choice_12 ( t );
				cin.ignore ( );
				if ( j == 2 )
				{
					system ( "CLS" );
					goto part2;
				}
				else
					goto part1;
			}
		}
	}
part2:
	info_write ( cars );
	return 0;
}

int manage::car_delete ( )
{
	string a;		   //车牌号
	int i , j = 0 , ddd; //循环使用，判断是否删除成功的对象数组下标，判断是否进入删除
start:
	{
		cout << "是否进入删除系统 1.是 2.否" << endl;
		string t;
		ddd = choice_12 ( t );
		cin.ignore ( );
		if ( ddd == 2 )
		{
			goto endl_l;
		}
		cout << "请输入你要删除的车辆信息:  " << endl;
		cout << "车牌号: ";
		getline ( cin , a );
		if ( count == 0 )
			cout << "记录为空!" << endl;
		for ( i = 0; i < capacity; i++ )
		{
			if ( a == cars [ i ].get_num ( ) )
			{
				statistics_model_minus ( cars [ i ].get_type_unm ( ) );
				cars [ i ] = empty;
				if ( i <= ps )
				{
					ps_s++;
				}
				count--;
				j = i;
			}
		}
		if ( cars [ j ].get_num ( ) == " " )
		{
			cout << "删除成功" << endl;
			sort ( );
		}
		else
		{
			cout << "删除失败，请重新开始";
			goto start;
		}
		sort ( );
	}
endl_l:
	info_write ( cars );
	return 0;
}

int manage::car_leave ( )
{
	int index = 0 , lll = 0; //给计算车费函数的下标，判断是否进入离开系统
	string b;				//车牌号
	display ( 1 );
	cout << "是否有车辆要离开 1.是 2.否" << endl;
	string t;
	lll = choice_12 ( t );
	cin.ignore ( );
	if ( lll == 2 )
	{
		goto partend;
	}
	cout << "请输入预备离开车的车牌号:" << endl;
restart:
	{
		getline ( cin , b );
		for ( int i = 0; i < capacity; i++ )
		{
			if ( b == cars [ i ].get_num ( ) )
			{
				if ( cars [ i ].get_state ( ) == "in" )
				{
					cout << "以下为该车信息" << endl;
					cars [ i ].car_base ( );
					index = i;
				}
				else
				{
					cout << "该车以离开车库，请重新输入" << endl;
					goto restart;
				}
				break;
			}
			if ( i == capacity - 1 )
			{
				cout << "记录为空!" << endl;
				goto partend;
			}
		}
	}
	price_c ( 1 , index );
partend:
	info_write ( cars );
	return 0;
}

int manage::change ( )
{
	string a;		   //车牌号
	int c;			   // 可以选择修改方式
	int b = 0;		   //下标
	int i , t , kkk = 0; //循环使用，车型号码，判断是否进入修改系统
	string d;		   //修改后的数据
	string t1 , t2;
	cout << "是否进入修改系统 1.是 2.否" << endl;
	string tt;
	kkk = choice_12 ( tt );
	cin.ignore ( );
	if ( kkk == 2 )
	{
		goto finish;
	}
	cout << "请输入你要修改车的车牌号";
	getline ( cin , a );
	for ( i = 0; i < capacity; i++ )
	{
		if ( a == cars [ i ].get_num ( ) )
		{
			if ( cars [ i ].get_state ( ) == "in" )
			{
				cars [ i ].car_base ( );
			}
			else
				cars [ i ].car_history ( );
			b = i;
			break;
		}
		if ( i == capacity - 1 )
		{
			cout << "记录为空！" << endl;
			goto finish;
		}
	}
	cout << "1.修改车牌号" << endl;
	cout << "2.修改车的颜色" << endl;
	cout << "3.修改车型" << endl;
	cout << "4.修改进入时间" << endl;
	cout << "5.修改出库时间" << endl;
	cout << "6.退出修改界面" << endl;
	cout << endl;
	cout << "请输入选择:" << endl;
	c = choice_16 ( t2 );
	cin.ignore ( );
	switch ( c )
	{
		case 1:
			cout << "将车牌号修改为：" << endl;
			getline ( cin , d );
			cars [ b ].set_car_num ( d );
			if ( cars [ b ].get_num ( ) == d )
			{
				cout << "修改成功,以下是修改后的信息： " << endl;
				if ( cars [ b ].get_state ( ) == "leave" )
				{
					cars [ b ].car_history ( );
				}
				else
					cars [ b ].car_base ( );
			}
			break;
		case 2:
			cout << "将车的颜色修改为：" << endl;
			getline ( cin , d );
			cars [ b ].set_color ( d );
			if ( cars [ b ].get_color ( ) == d )
			{
				cout << "修改成功,以下是修改后的信息： " << endl;
				if ( cars [ b ].get_state ( ) == "leave" )
				{
					cars [ b ].car_history ( );
				}
				else
					cars [ b ].car_base ( );
			}
			break;
		case 3:
			cout << "将车型改成（号码）：1.小汽车 2.小卡 3.中卡 4.大卡" << endl;
			t = choice_14 ( t1 );
			cin.ignore ( );
			statistics_model_minus ( cars [ b ].get_type_unm ( ) );
			statistics_model_plus ( t );
			cars [ b ].set_type ( t );
			if ( t == cars [ b ].get_type_unm ( ) )
			{
				cout << "修改成功,以下是修改后的信息： " << endl;
				if ( cars [ b ].get_state ( ) == "leave" )
				{
					cars [ b ].car_history ( );
				}
				else
					cars [ b ].car_base ( );
			}
			break;
		case 4:
			price_c ( 3 , b );
			cout << "修改成功,以下是修改后的信息： " << endl;
			if ( cars [ b ].get_state ( ) == "leave" )
			{
				cars [ b ].car_history ( );
			}
			else
				cars [ b ].car_base ( );
			sort ( );
			cout << endl;
			break;
		case 5:
			if ( cars [ b ].get_state ( ) == "in" )
			{
				cout << "该车未离开车库，是否修改 1.是 2.否" << endl;
				goto che;
			}
			else
			{
				price_c ( 2 , b );
				goto en;
			}
		che:
			{
				int le;
				string t0;
				le = choice_12 ( t0 );
				cin.ignore ( );
				if ( le == 1 )
				{
					price_c ( 1 , b );
				}
				else
				{
					if ( le == 2 )
					{
						goto finish;
					}
				}
			}
		en:
			cout << "修改成功,以上是修改后的信息： " << endl;
			break;
		case 6:
			cout << "已退出修改系统";
			break;
	}
finish:
	info_write ( cars );
	return 0;
}

int manage::search ( )
{
	int a , i; //判断是否进入查找系统，循环使用
	string b; //车牌号
	int c;	  //车型
	cout << "请输入查询车辆信息方式:  1.按照车牌号查询  2.按照车型查询" << endl;
	string t;
	a = choice_12 ( t );
	cin.ignore ( );
	if ( count == 0 )
	{
		cout << "历史记录为空!" << endl;
	}
	switch ( a )
	{
		case 1:
			{
				cout << "请输入你要查询的车牌号:" << endl;
				getline ( cin , b );
				for ( i = 0; i < capacity; i++ )
				{
					if ( b == cars [ i ].get_num ( ) )
					{
						if ( cars [ i ].get_state ( ) == "in" )
						{
							cars [ i ].car_base ( );
							goto e;
						}
						else
						{
							if ( cars [ i ].get_state ( ) == "leave" )
							{
								cars [ i ].car_history ( );
								goto e;
							}
						}
					}
					if ( i + 1 == capacity )
					{
						cout << "历史记录为空！" << endl;
						break;
					}
				}
			};
		e:
			break;
		case 2:
			{
				cout << "请输入查询的车的车型数字(1.小汽车 2.小卡 3.中卡 4.大卡):" << endl;
				string t1;
				c = choice_14 ( t1 );
				cin.ignore ( );
				statistics_model ( c );
				for ( i = 0; i < capacity; i++ )
				{
					if ( c == cars [ i ].get_type_unm ( ) )
					{
						if ( cars [ i ].get_state ( ) == "in" )
						{
							cars [ i ].car_base ( );
						}
						else
						{
							if ( cars [ i ].get_state ( ) == "leave" )
							{
								cars [ i ].car_history ( );
							}
						}
					}
				}
			};
			break;
	}
	return 0;
}

void manage::display ( int n )
{
	switch ( n )
	{
		case 1:
			cout << "以下为车库车辆信息" << endl;
			for ( int i = 0; i < ps; i++ )
			{
				cars [ i ].car_base ( );
			}
			cout << endl;
			break;
		case 2:
			for ( int i = capacity - 1; i > ps; i-- )
			{
				if ( cars [ i ].get_num ( ) != " " )
					goto s;
				else
				{
					if ( i == ps + 1 )
					{
						cout << "没有车辆离开" << endl;
						goto ed;
					}
				}
			}
		s:
			cout << "以下为已离开车辆信息" << endl;
			for ( int i = capacity - 1; i > ps; i-- )
			{
				if ( cars [ i ].get_num ( ) != " " )
				{
					cars [ i ].car_history ( );
				}
			}
		ed:
			break;
		default:
			break;
	}
}

int manage::info_read ( car *info )
{
	car *info1 = info;
	string a , b;																					  //车辆信息，a——车牌，b——颜色
	string c;																						  //车型
	string iy , imo , id , ih , im , is;																	  //进入车库时间
	string oy , omo , od , oh , om , os , t_p;															  //离开车库时间，停车时长
	string str , str1;																				  //停车位车辆数，总记录车辆数
	int j;																							  //停车位车辆数
	ifstream fin ( "D:/MyCode/VisualStudio/VSC/VS-Code/Windows/Freshman_course_design/Second_Semester/car_info.txt" ); //此处为绝对路径，克隆到本地后需注意
	if ( !fin )
	{
		cout << "文件打开失败" << endl;
		ofstream fout ( "D:/MyCode/VisualStudio/VSC/VS-Code/Windows/Freshman_course_design/Second_Semester/car_info.txt" );
		fout << " " << endl;
		fout << " " << endl;
		fout.close ( );
		return 0;
	}
	getline ( fin , str );
	getline ( fin , str );
	getline ( fin , str1 );
	if ( str == " " )
		return 0;
	j = stoi ( str , 0 , 10 );
	count = stoi ( str1 , 0 , 10 );
	for ( int i = 0; i < j; i++ )
	{
		fin >> a;
		fin >> b;
		fin >> c;
		fin >> iy;
		fin >> imo;
		fin >> id;
		fin >> ih;
		fin >> im;
		fin >> is;
		info->set_car_num ( a );
		info->set_color ( b );
		info->set_type ( stoi ( c , 0 , 10 ) );
		info->set_itime ( stoi ( iy , 0 , 10 ) , stoi ( imo , 0 , 10 ) , stoi ( id , 0 , 10 ) , stoi ( ih , 0 , 10 ) , stoi ( im , 0 , 10 ) , stoi ( is , 0 , 10 ) );
		statistics_model_plus ( stoi ( c , 0 , 10 ) );
		info++;
		ps_s--;
	}
	sort ( );
	if ( count > j ) //如果总记录数大于停车位车辆数，后面继续读取的数据为已经离开车辆的历史记录
	{
		info1 += capacity - 1; //指针偏移至历史记录最后一个
		for ( int i = 0; i < ( count - j ); i++ )
		{
			fin >> a;
			fin >> b;
			fin >> c;
			fin >> iy;
			fin >> imo;
			fin >> id;
			fin >> ih;
			fin >> im;
			fin >> is;
			fin >> oy;
			fin >> omo;
			fin >> od;
			fin >> oh;
			fin >> om;
			fin >> os;
			fin >> t_p;
			info1->set_car_num ( a );
			info1->set_color ( b );
			info1->set_type ( stoi ( c , 0 , 10 ) );
			info1->set_itime ( stoi ( iy , 0 , 10 ) , stoi ( imo , 0 , 10 ) , stoi ( id , 0 , 10 ) , stoi ( ih , 0 , 10 ) , stoi ( im , 0 , 10 ) , stoi ( is , 0 , 10 ) );
			info1->set_otime ( stoi ( oy , 0 , 10 ) , stoi ( omo , 0 , 10 ) , stoi ( od , 0 , 10 ) , stoi ( oh , 0 , 10 ) , stoi ( om , 0 , 10 ) , stoi ( os , 0 , 10 ) );
			info1->set_price ( stoi ( t_p , 0 , 10 ) );
			info1->set_state ( );
			statistics_model_plus ( stoi ( c , 0 , 10 ) );
			info1--;
			leave--;
		}
	}
	fin.close ( );
	return 0;
}

void manage::info_write ( car *info )
{
	car *info1 = info;
	fstream fout ( "D:\\VSCode\\work\\Windows\\Freshman_course_design\\Second_Semester\\car_info.txt" , ios::out | ios::trunc ); //打开文件并清空内容，重新写入
	fout << "" << endl;
	fout << ( ps - ps_s ) << endl; //写入停车位车辆个数
	fout << count << endl;		 //写入总记录数
	for ( int i = 0; i < ( ps - ps_s ); i++ )
	{
		fout << info->get_num ( ) << '\t';
		fout << info->get_color ( ) << '\t';
		fout << info->get_type_unm ( ) << '\t';
		fout << info->itime.get_year ( ) << '\t';
		fout << info->itime.get_month ( ) << '\t';
		fout << info->itime.get_day ( ) << '\t';
		fout << info->itime.get_hour ( ) << '\t';
		fout << info->itime.get_minute ( ) << '\t';
		fout << info->itime.get_second ( ) << '\t' << endl;
		info++;
	}
	info1 += capacity - 1;
	while ( info1->get_num ( ) != " " )
	{
		fout << info1->get_num ( ) << '\t';
		fout << info1->get_color ( ) << '\t';
		fout << info1->get_type_unm ( ) << '\t';
		fout << info1->itime.get_year ( ) << '\t';
		fout << info1->itime.get_month ( ) << '\t';
		fout << info1->itime.get_day ( ) << '\t';
		fout << info1->itime.get_hour ( ) << '\t';
		fout << info1->itime.get_minute ( ) << '\t';
		fout << info1->itime.get_second ( ) << '\t';
		fout << info1->otime.get_year ( ) << '\t';
		fout << info1->otime.get_month ( ) << '\t';
		fout << info1->otime.get_day ( ) << '\t';
		fout << info1->otime.get_hour ( ) << '\t';
		fout << info1->otime.get_minute ( ) << '\t';
		fout << info1->otime.get_second ( ) << '\t';
		fout << info1->get_p_t ( ) << '\t' << endl;
		info1--;
	}
	fout.close ( );
	cout << "文件已保存" << endl;
}

void manage::price_c ( int n , int a )
{
	switch ( n )
	{
		case 1: //离开函数调用；修改函数，车辆未离开时调用
			{
				int oy , omo , od , oh , om , os , inde = a , day_c , l = leave , p;
				cout << "请输入该车离开时间" << endl;
				cout << "年：";
				cin >> oy;
				cout << "月：";
				cin >> omo;
				cout << "日：";
				cin >> od;
				cout << "时：";
				cin >> oh;
				cout << "分：";
				cin >> om;
				cout << "秒：";
				cin >> os;
				cin.ignore ( );
				cars [ leave ] = cars [ inde ];
				cars [ inde ] = empty;
				le = &cars [ leave ];
				le->set_otime ( oy , omo , od , oh , om , os );
				le->set_state ( );
				day_c = d ( le );
				p = price_base ( day_c , le );
				le->set_price ( p );
				le->car_history ( );
				sort ( );
				leave--;
				ps_s++;
				break;
			}
		case 2: //修改函数，车辆已经离开时调用
			{
				int oy , omo , od , oh , om , os , inde = a , day_c , p;
				cout << "请输入该车离开时间" << endl;
				cout << "年：";
				cin >> oy;
				cout << "月：";
				cin >> omo;
				cout << "日：";
				cin >> od;
				cout << "时：";
				cin >> oh;
				cout << "分：";
				cin >> om;
				cout << "秒：";
				cin >> os;
				cin.ignore ( );
				le = &cars [ a ];
				le->set_otime ( oy , omo , od , oh , om , os );
				day_c = d ( le );
				p = price_base ( day_c , le );
				le->set_price ( p );
				le->car_history ( );
				break;
			}
		case 3: //修改入库时间
			{
				int iy , imo , id , ih , im , is , inde = a , day_c , p;
				cout << "请输入该车入库时间" << endl;
				cout << "年：";
				cin >> iy;
				cout << "月：";
				cin >> imo;
				cout << "日：";
				cin >> id;
				cout << "时：";
				cin >> ih;
				cout << "分：";
				cin >> im;
				cout << "秒：";
				cin >> is;
				cin.ignore ( );
				le = &cars [ a ];
				le->set_itime ( iy , imo , id , ih , im , is );
				day_c = d ( le );
				p = price_base ( day_c , le );
				le->set_price ( p );
				break;
			}
		default:
			break;
	}
}

void manage::print_statistic ( )
{
	cout.fill ( '-' );
	cout.width ( 50 );
	cout << "-" << endl;
	cout.fill ( ' ' );
	cout.width ( 10 );
	cout << " ";
	cout << "停车场共有" << count << "条记录" << endl;
	cout.fill ( ' ' );
	cout.width ( 5 );
	cout << " ";
	cout << "其中" << endl;
	cout.fill ( ' ' );
	cout.width ( 10 );
	cout << " ";
	cout << "小汽车有：" << car_s << endl;
	cout.fill ( ' ' );
	cout.width ( 10 );
	cout << " ";
	cout << "小卡有：" << lorry_s << endl;
	cout.fill ( ' ' );
	cout.width ( 10 );
	cout << " ";
	cout << "中卡有：" << lorry_m << endl;
	cout.fill ( ' ' );
	cout.width ( 10 );
	cout << " ";
	cout << "大卡有：" << lorry_l << endl;
	cout.fill ( '-' );
	cout.width ( 50 );
	cout << "-" << endl;
}

void manage::sort ( )
{
	for ( int i = 0; i < ps + 1; i++ )
	{
		for ( int j = 0; j < ps + 1; j++ )
		{
			if ( cars [ j ].itime.get_time ( ) > cars [ j + 1 ].itime.get_time ( ) )
			{
				k = cars [ j ];
				cars [ j ] = cars [ j + 1 ];
				cars [ j + 1 ] = k;
			}
		}
	}
}

void manage::statistics_model ( int n )
{
	switch ( n )
	{
		case 1:
			if ( car_s == 0 )
			{
				cout << "该车型记录为空" << endl;
			}
			break;
		case 2:
			if ( lorry_s == 0 )
			{
				cout << "该车型记录为空" << endl;
			}
			break;
		case 3:
			if ( lorry_m == 0 )
			{
				cout << "该车型记录为空" << endl;
			}
			break;
		case 4:
			if ( lorry_l == 0 )
			{
				cout << "该车型记录为空" << endl;
			}
			break;
		default:
			break;
	}
}

void manage::statistics_model_minus ( int n )
{
	switch ( n )
	{
		case 1:
			car_s--;
			break;
		case 2:
			lorry_s--;
			break;
		case 3:
			lorry_m--;
			break;
		case 4:
			lorry_l--;
			break;
		default:
			break;
	}
}

void manage::statistics_model_plus ( int n )
{
	switch ( n )
	{
		case 1:
			car_s++;
			break;
		case 2:
			lorry_s++;
			break;
		case 3:
			lorry_m++;
			break;
		case 4:
			lorry_l++;
			break;
		default:
			break;
	}
}

int menu ( ) //菜单
{
	manage k1;
	while ( 1 )
	{
		cout.fill ( '-' );
		cout.width ( 50 );
		cout << "-" << endl;
		cout.fill ( ' ' );
		cout.width ( 10 );
		cout << " ";
		cout << "1.停车进入车库" << endl;
		cout.fill ( ' ' );
		cout.width ( 10 );
		cout << " ";
		cout << "2.离开车库" << endl;
		cout.fill ( ' ' );
		cout.width ( 10 );
		cout << " ";
		cout << "3.查询信息" << endl;
		cout.fill ( ' ' );
		cout.width ( 10 );
		cout << " ";
		cout << "4.修改信息" << endl;
		cout.fill ( ' ' );
		cout.width ( 10 );
		cout << " ";
		cout << "5.显示车辆信息" << endl;
		cout.fill ( ' ' );
		cout.width ( 10 );
		cout << " ";
		cout << "6.删除车辆信息" << endl;
		cout.fill ( ' ' );
		cout.width ( 10 );
		cout << " ";
		cout << "7.停车场统计信息" << endl;
		cout.fill ( ' ' );
		cout.width ( 10 );
		cout << " ";
		cout << "8.清屏" << endl;
		cout.fill ( ' ' );
		cout.width ( 10 );
		cout << " ";
		cout << "9.退出系统" << endl;
		cout.fill ( ' ' );
		cout.width ( 10 );
		cout << "停车每小时3元，停车半小时内不收费" << endl;
		cout.fill ( ' ' );
		cout.width ( 10 );
		cout << k1 << endl;
		cout.fill ( '-' );
		cout.width ( 50 );
		cout << "-" << endl;
		cout << "输入功能序号" << endl;
		int n = 0;
		string c;
		n = choice_19 ( c );
		cin.ignore ( );
		switch ( n )
		{
			case 1:
				k1.Add ( );
				k1.display ( 1 );
				break;
			case 2:
				k1.car_leave ( );
				break;
			case 3:
				k1.search ( );
				break;
			case 4:
				k1.change ( );
				break;
			case 5:
				k1.display ( 1 );
				k1.display ( 2 );
				break;
			case 6:
				k1.car_delete ( );
				break;
			case 9:
				goto end0;
			case 7:
				k1.print_statistic ( );
				break;
			case 8:
				system ( "CLS" );
			default:
				break;
		}
	}
end0:
	return 0;
}
#endif