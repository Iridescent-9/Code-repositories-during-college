#pragma once
#include <string>
#include <algorithm>
#include <utility>
#include <vector>
#include <numeric>

using namespace std;

class lecturer
{
private:
	string name;
	int number = 0;
	double score = 0;
public:
	lecturer(string, int);
	lecturer();
	[[nodiscard]] int getNumber(void) const;
	[[nodiscard]] string getName(void) const;
	[[nodiscard]] double getScore(void) const;
	void rating(void);
	friend void listSort(vector<lecturer>&);
};
