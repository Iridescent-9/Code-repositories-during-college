#pragma once
#include "lecturer.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <format>

void initialize(vector<lecturer>&);
void sortWithinGroup(vector<vector<lecturer>>::value_type&);
void startTheRace(vector<lecturer>&, vector<vector<lecturer>>);
void group(const vector<lecturer>&, int, vector<vector<lecturer>>&);
void firstRound(vector<lecturer>&, int);
void secondRound(vector<lecturer>&, int);
void finalRound(vector<lecturer>&);
