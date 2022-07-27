// MIT License - Copyright (c) 2022 Jared Cook
#pragma once

#include "FCTweenInstance.h"
class FCTWEEN_API FCTweenInstanceVector : public FCTweenInstance
{
public:
	FVector StartValue;
	FVector EndValue;
	TFunction<void(FVector)> OnUpdate;

	void Initialize(FVector InStart, FVector InEnd, TFunction<void(FVector)> InOnUpdate, float InDurationSecs, EFCEase InEaseType);

protected:
	virtual void ApplyEasing(float EasedPercent) override;
};
