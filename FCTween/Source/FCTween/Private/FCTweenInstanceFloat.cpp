// MIT License - Copyright 2026 Jared Cook
#include "FCTweenInstanceFloat.h"

FCTweenInstanceFloat* FCTweenInstanceFloat::Initialize(float InStart, float InEnd, TFunction<void(float)> InOnUpdate, float InDurationSecs, EFCEase InEaseType)
{
	this->StartValue = InStart;
	this->EndValue = InEnd;
	this->OnUpdate = MoveTemp(InOnUpdate);
	this->InitializeSharedMembers(InDurationSecs, InEaseType);
	return this;
}

void FCTweenInstanceFloat::ApplyEasing(float EasedPercent)
{
	OnUpdate(FMath::Lerp<float>(StartValue, EndValue, EasedPercent));
}
