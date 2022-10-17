#include "function.h"

using namespace std;

void initialize(vector<lecturer>& list)
{
	int number = 0;
	string name;
	ifstream inFile(R"(list.txt)");
	/*
	 *The contents of the list.txt
	 *The first column is the entry number
	 *The second column is name
	 */
	for (int i = 0; i < 24; i++)
	{
		inFile >> number;
		inFile >> name;
		lecturer temp(name, number);
		list.push_back(temp);
	}
	listSort(list);
	cout << format("参赛号\t姓名\n");
	for (auto& l : list)
	{
		cout << format("{}\t{}\n", l.getNumber(), l.getName());
	}
}

void sortWithinGroup(vector<vector<lecturer>>::value_type& x)
{
	ranges::sort(x, [](const lecturer& a, const lecturer& b)
	{
		if (a.getScore() != b.getScore())
		{
			return a.getScore() > b.getScore();
		}
		return a.getNumber() < b.getNumber();
	});
}

void startTheRace(vector<lecturer>& list, vector<vector<lecturer>> fr)
{
	list.clear();
	int constituencies = 1;
	for (auto& x : fr)
	{
		for (auto& y : x)
		{
			y.rating();
		}
		sortWithinGroup(x);
		x.erase(x.begin() + 3, x.end());
		cout << format("\n第{}组晋升的参赛者为\n", constituencies);
		for (auto& y : x)
		{
			cout << format("{}\t{}\n", y.getNumber(), y.getName());
			list.push_back(y);
		}
		constituencies++;
	}
	listSort(list);
}

void group(const vector<lecturer>& list, const int groupNumber, vector<vector<lecturer>>& fr)
{
	for (int row = 0, index = 0; row < groupNumber; row++)
	{
		vector<lecturer> temp;
		for (int col = 0; col < 6; col++, index++)
		{
			temp.push_back(list[index]);
		}
		fr[row] = temp;
		temp.clear();
		cout << format("   第{}组\n", row + 1);
		for (auto& x : fr[row])
		{
			cout << format("{}\t{}\n", x.getNumber(), x.getName());
		}
	}
}

void firstRound(vector<lecturer>& list, int groupNumber)
{
	cout << endl << "----------第一轮比赛----------" << endl;
	cout << endl << "----------分组情况-----------" << endl;
	vector<vector<lecturer>> fr(groupNumber);
	group(list, groupNumber, fr);
	startTheRace(list, fr);
}

void secondRound(vector<lecturer>& list, int groupNumber)
{
	cout << endl << "----------第二轮比赛----------" << endl;
	cout << endl << "----------分组情况-----------" << endl;
	vector<vector<lecturer>> fr(groupNumber);
	group(list, groupNumber, fr);
	startTheRace(list, fr);
}

void finalRound(vector<lecturer>& list)
{
	cout << endl << "----------决赛----------" << endl;
	cout << endl << "----------选手信息-----------" << endl;
	for (auto& l : list)
	{
		cout << format("{}\t{}\n", l.getNumber(), l.getName());
		l.rating();
	}
	sortWithinGroup(list);
	list.erase(list.begin() + 3, list.end());
	cout << "决赛前三名为" << endl;
	for (auto& x : list)
	{
		cout << format("{}\t{}\t分数：{}\n", x.getNumber(), x.getName(), x.getScore());
	}
}
