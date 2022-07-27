// MIT License - Copyright (c) 2022 Jared Cook
#pragma once

#include "FCTweenInstance.h"
class FCTWEEN_API FCTweenInstanceVector2D : public FCTweenInstance
{
public:
	FVector2D StartValue;
	FVector2D EndValue;
	TFunction<void(FVector2D)> OnUpdate;

	void Initialize(
		FVector2D InStart, FVector2D InEnd, TFunction<void(FVector2D)> InOnUpdate, float InDurationSecs, EFCEase InEaseType);

protected:
	virtual void ApplyEasing(float EasedPercent) override;
};
