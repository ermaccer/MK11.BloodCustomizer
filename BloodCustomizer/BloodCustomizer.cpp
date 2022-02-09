#include "pch.h"
#include "BloodCustomizer.h"

void SetColor(int64 ptr, FName name, FVector* color)
{
	*color = { 0.5,0.5,0 };
	((void(__fastcall*)(int64, FName, FVector*))_addr(0x140E4E240))(ptr, name, color);
}

void BloodSettings::Init()
{
}
