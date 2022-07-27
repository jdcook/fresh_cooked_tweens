// MIT License - Copyright (c) 2022 Jared Cook
#pragma once

#include "FCTweenInstance.h"
class FCTWEEN_API FCTweenInstanceFloat : public FCTweenInstance
{
public:
	float StartValue;
	float EndValue;
	TFunction<void(float)> OnUpdate;

	void Initialize(float InStart, float InEnd, TFunction<void(float)> InOnUpdate, float InDurationSecs, EFCEase InEaseType);

protected:
	virtual void ApplyEasing(float EasedPercent) override;
};
