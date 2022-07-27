// MIT License - Copyright (c) 2022 Jared Cook
#pragma once

#include "FCTweenInstance.h"
class FCTWEEN_API FCTweenInstanceQuat : public FCTweenInstance
{
public:
	FQuat StartValue;
	FQuat EndValue;
	TFunction<void(FQuat)> OnUpdate;

	void Initialize(FQuat InStart, FQuat InEnd, TFunction<void(FQuat)> InOnUpdate, float InDurationSecs, EFCEase InEaseType);

protected:
	virtual void ApplyEasing(float EasedPercent) override;
};
