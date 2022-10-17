#pragma once
#include "pcb.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <vector>
#include <deque>

void choice(std::vector<pcb>&, std::vector<std::string>&, int&, const int&);
void display_menu();
void first_come_first_service(std::vector<pcb>&, std::vector<std::string>&, int&);
void highest_response_ratio_next(std::vector<pcb>&, std::vector<std::string>&, int&);
void initialize_process(std::vector<pcb>&, int&);
void print_process_information(std::vector<pcb>&, std::vector<std::string>&, int&);
void round_robin(std::vector<pcb>&, std::vector<std::string>&, int&);
void shortest_job_first(std::vector<pcb>&, std::vector<std::string>&, int&);
