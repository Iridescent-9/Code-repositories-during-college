#include "lecturer.h"
#include "function.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

int main(void)
{
	const auto seed = static_cast<unsigned> (time(nullptr));
	srand(seed);
	vector<lecturer> list;
	initialize(list);
	firstRound(list, 4);
	secondRound(list, 2);
	finalRound(list);
	system("pause");
	return 0;
}
