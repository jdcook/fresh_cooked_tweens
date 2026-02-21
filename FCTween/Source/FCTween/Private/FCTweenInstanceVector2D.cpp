// MIT License - Copyright 2026 Jared Cook
#include "FCTweenInstanceVector2D.h"

FCTweenInstanceVector2D* FCTweenInstanceVector2D::Initialize(FVector2D InStart, FVector2D InEnd, TFunction<void(FVector2D)> InOnUpdate, float InDurationSecs, EFCEase InEaseType)
{
	this->StartValue = InStart;
	this->EndValue = InEnd;
	this->OnUpdate = MoveTemp(InOnUpdate);
	this->InitializeSharedMembers(InDurationSecs, InEaseType);
	return this;
}

void FCTweenInstanceVector2D::ApplyEasing(float EasedPercent)
{
	OnUpdate(FMath::Lerp<FVector2D>(StartValue, EndValue, EasedPercent));
}
