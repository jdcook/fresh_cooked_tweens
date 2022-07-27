// MIT License - Copyright (c) 2022 Jared Cook
#pragma once
#include "FCEasing.h"
#include "FCTween.h"

#include "FCTweenBlueprintLibrary.generated.h"

UCLASS()
class FCTWEEN_API UFCTweenBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Ease with overriding parameters
	 * @param t the percent complete, 0-1
	 * @param EaseType The easing function to interpolate with
	 */
	UFUNCTION(BlueprintPure, Category = "Tween")
	static float Ease(float t, EFCEase EaseType);

	/**
	 * Ease with overriding parameters that affect Elastic, Back, Stepped, and Smoothstep. 0 means no override
	 * @param t the percent complete, 0-1
	 * @param EaseType The easing function to interpolate with
	 * @param Param1 Elastic: Amplitude (1.0) / Back: Overshoot (1.70158) / Stepped: Steps (10) / Smoothstep: x0 (0)
	 * @param Param2 Elastic: Period (0.2) / Smoothstep: x1 (1)
	 */
	UFUNCTION(BlueprintPure, Category = "Tween")
	static float EaseWithParams(float t, EFCEase EaseType, float Param1 = 0, float Param2 = 0);

	// Make sure there are at least these many of each type of tween available in memory. Call this only once, probably in a
	// GameInstance blueprint, if you need more initial memory reserved on game startup.
	UFUNCTION(BlueprintCallable, Category = "Tween|Utility")
	static void EnsureTweenCapacity(
		int NumFloatTweens = 75, int NumVectorTweens = 50, int NumVector2DTweens = 50, int NumQuatTweens = 10);
};
