#include "BloodCustomizer.h"
#include "utils/IniReader.h"

BloodSettings settings;
int64 pSetColor = 0;

static CIniReader ini("BloodCustomizer.ini");

void BloodSettings::Init()
{
	m_bEnable = ini.ReadBoolean("Settings", "Enable", true);
	m_colors[0] = ini.ReadInteger("Settings", "R", 0);
	m_colors[1] = ini.ReadInteger("Settings", "G", 255);
	m_colors[2] = ini.ReadInteger("Settings", "B", 0);

	for (int i = 0; i < 3; i++)
	{
		if (m_colors[i] > 255)
			m_colors[i] = 255;
		if (m_colors[i] < 0)
			m_colors[i] = 0;
	}
	float red = ((m_colors[0] * 100.0f) / 255.0f) / 100.0f;
	float green = ((m_colors[1] * 100.0f) / 255.0f) / 100.0f;
	float blue = ((m_colors[2] * 100.0f) / 255.0f) / 100.0f;
	m_fColors[0] = red;
	m_fColors[1] = green;
	m_fColors[2] = blue;
	m_fColors[3] = 1.0f;
}

void BloodSettings::Save()
{
	ini.WriteBoolean("Settings", "Enable", m_bEnable);
	ini.WriteInteger("Settings", "R", m_colors[0]);
	ini.WriteInteger("Settings", "G", m_colors[1]);
	ini.WriteInteger("Settings", "B", m_colors[2]);
}

void PlayerInfoEx::SetColor(FName color, FVector* value)
{
	if (settings.m_bEnable)
	{
		float scale = 100.0f;
		float red = ((settings.m_colors[0] * 100.0f) / 255.0f) / scale;
		float green = ((settings.m_colors[1] * 100.0f) / 255.0f) / scale;
		float blue = ((settings.m_colors[2] * 100.0f) / 255.0f) / scale;

		*value = { red, green, blue };
	}

	if (pSetColor)
		((void(__fastcall*)(PlayerInfoEx*, FName, FVector*))pSetColor)(this, color, value);
}
