#include <iostream>
#include <vector>
#include "pcb.h"
#include "function.h"

int main(void)
{
	std::vector<pcb> multi_process;
	std::vector<std::string> order;
	int num_process = 0;
	int i;
	while (true)
	{
		display_menu();
		std::cin >> i;
		if (i == 5)
		{
			break;
		}
		choice(multi_process, order, num_process, i);
	}
	system("pause");
	return 0;
}
