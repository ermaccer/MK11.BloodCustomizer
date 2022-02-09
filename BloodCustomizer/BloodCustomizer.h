#pragma once
#include "mk10utils.h"

struct FVector
{
	float X;
	float Y;
	float Z;
};

class FName {
private:
	int Index;
	int Number;
public:
};

class BloodSettings {
public:
	int R, G, B;

	void Init();
};

extern BloodSettings settings;

class PlayerInfo {
public:
	void SetColor(FName color, FVector* value);
};