#include "lecturer.h"

using namespace std;

lecturer::lecturer(string str, const int num)
{
	name = move(str);
	number = num;
}

lecturer::lecturer()
= default;

int lecturer::getNumber(void) const
{
	return number;
}

string lecturer::getName(void) const
{
	return name;
}

double lecturer::getScore(void) const
{
	return score;
}

void lecturer::rating(void)
{
	vector<int> judgesScores;
	judgesScores.reserve(10);
	for (int i = 0; i < 10; i++)
	{
		judgesScores.push_back(rand() % 5 + 6);
	}
	judgesScores.erase(ranges::max_element(judgesScores));
	judgesScores.erase(ranges::min_element(judgesScores));
	score = accumulate(judgesScores.begin(), judgesScores.end(), 0) / static_cast<double>(judgesScores.size());
}

void listSort(vector<lecturer>& l)
{
	ranges::sort(l, [](const lecturer& a, const lecturer& b)
	{
		return a.number < b.number;
	});
}
