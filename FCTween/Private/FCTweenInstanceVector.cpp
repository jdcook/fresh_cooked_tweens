
#include "FCTweenInstanceVector.h"

void FCTweenInstanceVector::Initialize(
	FVector InStart, FVector InEnd, TFunction<void(FVector)> InOnUpdate, float InDurationSecs, EFCEase InEaseType)
{
	this->StartValue = InStart;
	this->EndValue = InEnd;
	this->OnUpdate = MoveTemp(InOnUpdate);
	this->InitializeSharedMembers(InDurationSecs, InEaseType);
}

void FCTweenInstanceVector::ApplyEasing(float EasedPercent)
{
	OnUpdate(FMath::Lerp<FVector>(StartValue, EndValue, EasedPercent));
}
