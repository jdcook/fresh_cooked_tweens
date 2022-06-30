
#include "FCTweenInstanceFloat.h"

void FCTweenInstanceFloat::Initialize(
	float InStart, float InEnd, TFunction<void(float)> InOnUpdate, float InDurationSecs, EFCEase InEaseType)
{
	this->StartValue = InStart;
	this->EndValue = InEnd;
	this->OnUpdate = MoveTemp(InOnUpdate);
	this->InitializeSharedMembers(InDurationSecs, InEaseType);
}

void FCTweenInstanceFloat::ApplyEasing(float EasedPercent)
{
	OnUpdate(FMath::Lerp<float>(StartValue, EndValue, EasedPercent));
}
