
#include "FCTweenInstanceQuat.h"

void FCTweenInstanceQuat::Initialize(
	FQuat InStart, FQuat InEnd, TFunction<void(FQuat)> InOnUpdate, float InDurationSecs, EFCEase InEaseType)
{
	this->StartValue = InStart;
	this->EndValue = InEnd;
	this->OnUpdate = MoveTemp(InOnUpdate);
	this->InitializeSharedMembers(InDurationSecs, InEaseType);
}

void FCTweenInstanceQuat::ApplyEasing(float EasedPercent)
{
	OnUpdate(FQuat::Slerp(StartValue, EndValue, EasedPercent));
}
