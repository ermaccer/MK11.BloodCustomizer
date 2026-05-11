#pragma once
#include "utils/addr.h"

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

	bool m_bEnable;
	int  m_colors[3];
	float m_fColors[4] = {};

	void Init();
	void Save();
};

extern BloodSettings settings;

class PlayerInfoEx {
public:
	void SetColor(FName color, FVector* value);
};

extern int64 pSetColor;