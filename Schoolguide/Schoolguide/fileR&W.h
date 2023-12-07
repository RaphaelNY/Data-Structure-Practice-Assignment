#pragma once
#include "Pointer.h"

using namespace std;

int Rawdata_readinfromTerminal(PathNode* head, int numbers);
int Rawdata_readinfromTerminal(PathNode* head, int numbers, int vA);

int AddingPointinfo(Pointinfo* head, int nums);
int AddingPointinfo(Pointinfo* head, int nums, int nu);

int PopingPointinfo(Pointinfo* head, string name, int nums);

int Rawdata_readinfromFile(PathNode* head, string readfilePath);

void Rawdata_saveinFile(PathNode* head, Pointinfo* infohead, int nums, int numbers, string savefilePath);