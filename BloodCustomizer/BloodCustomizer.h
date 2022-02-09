#pragma once
#include "mk10utils.h"

struct FVector
{
	float X;
	float Y;
	float Z;
};

class FName {
public:

};


class BloodSettings {
public:
	int R, G, B;

	void Init();
};

extern BloodSettings settings;

void SetColor(int64 ptr, FName name, FVector* color);


