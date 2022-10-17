/*克隆至本地后请先修改manage.h中
void manage::info_read ( car* info )和void manage::info_write(car*info)函数打开文件的路径
由于是用UTF-8编码格式写的
克隆至本地后可能会出现乱码
自己想办法了，编码格式UTF-8情况下不能输入中文
GBK和GB2312情况下可以，这个bug我也很懵逼*/
#include<iostream>
#include<string.h>
#include<string>
#include<Windows.h>
#include"manage.h"

using namespace std;

int main ( )
{
	start ( );
	copyright ( );
	menu ( );
	system ( "CLS" );
	system ( "color 05" );
	cout << endl << endl << endl << "感谢使用，再见";
	Sleep ( 2000 );
	return 0;
}