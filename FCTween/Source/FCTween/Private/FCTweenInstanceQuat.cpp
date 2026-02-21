// MIT License - Copyright 2026 Jared Cook
#include "FCTweenInstanceQuat.h"

FCTweenInstanceQuat* FCTweenInstanceQuat::Initialize(FQuat InStart, FQuat InEnd, TFunction<void(FQuat)> InOnUpdate, float InDurationSecs, EFCEase InEaseType)
{
	this->StartValue = InStart;
	this->EndValue = InEnd;
	this->OnUpdate = MoveTemp(InOnUpdate);
	this->InitializeSharedMembers(InDurationSecs, InEaseType);
	return this;
}

void FCTweenInstanceQuat::ApplyEasing(float EasedPercent)
{
	OnUpdate(FQuat::Slerp(StartValue, EndValue, EasedPercent));
}
