#include "BloodCustomizer.h"
#include "IniReader.h"

BloodSettings settings;

void BloodSettings::Init()
{
	CIniReader ini("");

	R = ini.ReadInteger("Settings", "Red", 255);
	G = ini.ReadInteger("Settings", "Green", 255);
	B = ini.ReadInteger("Settings", "Blue", 255);
}

void PlayerInfo::SetColor(FName color, FVector* value)
{
	float red = ((settings.R * 100.0f) / 255.0f) / 100.0f;
	float green = ((settings.G * 100.0f) / 255.0f) / 100.0f;
	float blue = ((settings.B * 100.0f) / 255.0f) / 100.0f;

	*value = { red, green, blue };
	((void(__fastcall*)(PlayerInfo*, FName, FVector*))_addr(0x140E4E5B0))(this, color, value);
}
