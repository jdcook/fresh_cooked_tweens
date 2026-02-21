// MIT License - Copyright 2026 Jared Cook
#include "FCTweenInstanceVector.h"

FCTweenInstanceVector* FCTweenInstanceVector::Initialize(FVector InStart, FVector InEnd, TFunction<void(FVector)> InOnUpdate, float InDurationSecs, EFCEase InEaseType)
{
	this->StartValue = InStart;
	this->EndValue = InEnd;
	this->OnUpdate = MoveTemp(InOnUpdate);
	this->InitializeSharedMembers(InDurationSecs, InEaseType);
	return this;
}

void FCTweenInstanceVector::ApplyEasing(float EasedPercent)
{
	OnUpdate(FMath::Lerp<FVector>(StartValue, EndValue, EasedPercent));
}
