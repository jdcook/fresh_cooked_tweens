
#include "FCTweenInstanceVector2D.h"

void FCTweenInstanceVector2D::Initialize(
	FVector2D InStart, FVector2D InEnd, TFunction<void(FVector2D)> InOnUpdate, float InDurationSecs, EFCEase InEaseType)
{
	this->StartValue = InStart;
	this->EndValue = InEnd;
	this->OnUpdate = MoveTemp(InOnUpdate);
	this->InitializeSharedMembers(InDurationSecs, InEaseType);
}

void FCTweenInstanceVector2D::ApplyEasing(float EasedPercent)
{
	OnUpdate(FMath::Lerp<FVector2D>(StartValue, EndValue, EasedPercent));
}
