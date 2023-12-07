#pragma once
#include "Pointer.h"

using namespace std;

int Rawdata_readinfromTerminal(PathNode* head, int numbers);

int AddingPointinfo(Pointinfo* head);

int Rawdata_readinfromFile(PathNode* head, string readfilePath);

void Rawdata_saveinFile(PathNode* head, int numbers, string savefilePath);