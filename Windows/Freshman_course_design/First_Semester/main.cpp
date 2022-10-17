//实际应为.c
#include<stdio.h>
#include<windows.h>
#include<string.h>
struct student
{
	int xuehao;
	char name[20];
	char sex[3];
	int score1;
	int score2;
	int score3;
	int score4;
	int ave;
}stu[200], stu1[200]; //stu是最大能记录的人数，stu1是在排序时暂时借用的函数 
int number;//总人数 
int main()
{
	int menu0, j=1, i;
	void menu();
	void input();
	void output();
	void cx();
	void outave();
	void px1();
	void px2();
	void begin();
	void end();
	number = 0;
	begin();
	system("pause");
	system("cls");
	while (j == 1)
	{
		system("pause");
		menu();
		scanf("%d", &menu0);
		switch (menu0)
		{
		case 1:
			input();
			break;
		case 2:
			output();
			break;
		case 3:
			cx();
			break;
		case 4:
			outave();
			break;
		case 5:
			printf("按1选择按学号排序，按2选择按平均分排序\n");
			scanf("%d", &i);
			switch (i)
			{
			case 1:
				px1();
				break;
			case 2:
				px2();
				break;
			}
			break;
		case 6:
			j = 0;
			end();
			break;
		}
	}
}
void begin()//开始函数 
{
	system("color 0E");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n                                 欢迎使用学生管理系统\n                     ");
}
void menu()//菜单函数 
{
	printf("请按照提示输入信息\n");
	printf("					1.输入学生信息\n");
	printf("					2.显示所有学生信息\n");
	printf("					3.查询学生信息\n");
	printf("					4.显示学生平均分\n");
	printf("					5.排序\n");
	printf("					6.退出学生信息系统\n");
	printf("					请输入:");
}
void input()//输入函数 
{
	int i=0, j=1;
	void ave();
	while (j == 1)
	{
		printf("请输入第%d学生的姓名，学号，性别，和四门成绩\n", i + 1);
		printf("					学号:");
		scanf("%d", &stu[i].xuehao);
		printf("					姓名:");
		scanf("%s", stu[i].name);
		printf("					性别:");
		scanf("%s", stu[i].sex);
		printf("					第一门成绩:");
		scanf("%d", &stu[i].score1);
		printf("					第二门成绩:");
		scanf("%d", &stu[i].score2);
		printf("					第三门成绩:");
		scanf("%d", &stu[i].score3);
		printf("					第四门成绩:");
		scanf("	%d", &stu[i].score4);
		printf("					记录成功\n");
		printf("					是否继续输入？1为是,0为否\n");
		printf("					请输入");
		i++;
		number++;
		scanf("%d", &j);
	}
	ave();
}
void output()//显示函数 
{
	int i=0;
	printf("学号     姓名     性别     第一门成绩    第二门成绩    第三门成绩     第四门成绩\n");
	for (i = 0; i < number; i++)
	{
		printf("%d,        %s,       %s,          %d,              %d,              %d,              %d\n", stu[i].xuehao, stu[i].name, stu[i].sex, stu[i].score1, stu[i].score2, stu[i].score3, stu[i].score4);
	}
}
void cx()//查询模板的总函数 
{
	void cx1();
	void cx2();
	int j = 1,k;
	while (j == 1)
	{
		system("pause");
		printf("					请按照提示查询所需要的信息\n");
		printf("					1.按照学号查询成绩\n");
		printf("					2.按照姓名查询成绩\n");
		printf("					请输入：");
		scanf("%d", &k);
		switch (k)
		{
		case 1: 
			cx1();
			break;
		case 2: 
			cx2(); 
			break;
		}
		printf("					是否继续查询？1为是，0为否\n");
		printf("					请输入：");
		scanf("%d", &j);

	}
}
void cx1()//查询模板的第一个函数 
{
	int k, i, j=0;
	printf("请输入学生的学号");
	scanf("%d", &k);
	for (i = 0; i < number; i++)
	{
		if (k == stu[i].xuehao)
		{
			printf("该学生的信息为：\n");
			printf("学号：%d，姓名：%s，性别：%s，第一门成绩：%d，第二门成绩：%d第三门成绩：%d第四门成绩：%d\n", stu[i].xuehao, stu[i].name, stu[i].sex, stu[i].score1, stu[i].score2, stu[i].score3, stu[i].score4);
			j++;
		}

	}
	if (j == 0) printf("查无此人\n");
}
void cx2()//查询模板的第二个按照姓名查找的函数 
{
	printf("请输入学生的姓名：\n");
	char name[20]; 
	int i, k=0; 
	(void)scanf("%s", name);
	for (i = 0; i < number; i++)
	{
		if (strcmp(name, stu[i].name) == 0)
		{
			printf("该学生的信息为：\n");
			printf("学号：%d，姓名：%s，性别：%s，第一门成绩：%d，第二门成绩：%d第三门成绩：%d第四门成绩：%d\n", stu[i].xuehao, stu[i].name, stu[i].sex, stu[i].score1, stu[i].score2, stu[i].score3, stu[i].score4);
			k++;
		}
	}
	if (k == 0) printf("查无此人\n");
}
void px1()//按照学号排序的函数 
{
	struct student t;
	int i, j;
	for (i = 0; i < number; i++)
		stu1[i] = stu[i];
	for (i = 0; i < number - 1; i++)
	{
		for (j = 0; j < number - 1 - i; j++)
		{
			if (stu1[j].xuehao > stu1[j + 1].xuehao)
			{
				t = stu1[j]; 
				stu1[j] = stu1[j + 1];
				stu1[j + 1] = t;
			}
		}
	}
	for (i = 0; i < number; i++)
	{
		printf("学号：%d，姓名：%s，性别：%s，第一门成绩：%d，第二门成绩：%d第三门成绩：%d第四门成绩：%d\n", stu1[i].xuehao, stu1[i].name, stu1[i].sex, stu1[i].score1, stu1[i].score2, stu1[i].score3, stu1[i].score4);
	}
}
void px2()//按照平均分排名的函数 
{
	struct student t;
	int i, j;
	for (i = 0; i < number; i++)
		stu1[i] = stu[i];
	for (i = 0; i < number - 1; i++)
	{
		for (j = 0; j < number - 1 - i; j++)
		{
			if (stu1[j].ave > stu1[j + 1].ave)
			{
				t = stu1[j];
				stu1[j] = stu1[j + 1];
				stu1[j + 1] = t;
			}
		}
	}
	for (i = 0; i < number; i++)
	{
		printf("学号：%d，姓名：%s，性别：%s，第一门成绩：%d，第二门成绩：%d第三门成绩：%d第四门成绩：%d,平均分：%d\n", stu1[i].xuehao, stu1[i].name, stu1[i].sex, stu1[i].score1, stu1[i].score2, stu1[i].score3, stu1[i].score4, stu1[i].ave);
	}
}
void outave()//求平均分的函数 
{
	int i;
	for (i = 0; i < number; i++)
	{
		printf("		%s的平均成绩是%d\n", stu[i].name, stu[i].ave);
	}

}
void ave()//求出结构体里面平均分的函数 
{
	int i;
	for (i = 0; i < number; i++)
	{
		stu[i].ave = (stu[i].score1 + stu[i].score2 + stu[i].score3 + stu[i].score4) / 4;
	}
}
void end()//结束函数 
{
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n   								谢谢使用学生管理系统\n                                   再见！！！！");

}
